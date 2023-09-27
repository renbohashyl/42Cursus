import { BadRequestException, ConsoleLogger, Logger } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { DisconnectReason, Server, Socket } from 'socket.io';
import * as config from 'config';
import { UserRepository } from 'src/users/repositories/user.repository';
import { SocketWithDataDTO } from './dto/socketWithData.dto';
import { Users } from 'src/users/entities/users.entity';
import { UserChannelsRepository, iChanUsers } from './repositories/userChannel.repository';
import { Channel } from './entities/channel.entity';
import { jwtConfig } from 'src/auth/auth.module';
import { UserChannel, eRole } from './entities/userChannel.entity';
import { BlockRepository } from './repositories/block.repository';
import { FriendRepository, iFriends } from './repositories/friend.repository';
import { cookieName } from 'src/auth/auth.service';

const domain: string = config.get<string>('FEServer.host');
export const FEServer: string = domain.concat(config.get<string>('FEServer.port'));

export interface iChans {
	roomID: number,
	isProtected: boolean,
	name: string,
};

export interface iChannels {
	roomID: number,
	roomIDstr: string,
	isProtected: boolean,
	name: string,
	owner: Users,
	password: string
};

export const userManager: Map<string, SocketWithDataDTO> = new Map<string, SocketWithDataDTO>();

@WebSocketGateway({cors: {
  origin: [`http://${FEServer}`,
		   `https://${FEServer}`]
}, cookie: true})
export class ChatGateway {
  constructor(
	private readonly userChnnelRepository: UserChannelsRepository,
	private readonly userRepository: UserRepository,
	private readonly blockRepository: BlockRepository,
	private readonly friendRepository: FriendRepository,
	private readonly jwtService: JwtService,
  ) {}
  @WebSocketServer()
  server: Server;
  logger: Logger = new Logger('Chat.GateWay.ts says: ');
  UserManager: Map<string, SocketWithDataDTO> = userManager;
  progNumber: number = 0;

  afterInit()
  {
	this.server.setMaxListeners(500);

	//Connect
	this.server.on('connection', async (socket: SocketWithDataDTO) => {
		this.tryConnect(socket);
	});

	//Disconnect
	this.server.on('connection', async (socket: SocketWithDataDTO) => {
	  socket.on('disconnect', async (reason: DisconnectReason) => {
		  this.logger.log(`${socket.login} is disconnected, for ${reason}`)
		  await state(this.server, socket, 'offline', this.friendRepository, this.userRepository);
	  })
	});

	//Create New Chat Room
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('create', async ({ name, isProtected, password }) => {

		if (typeof(name) != 'string' || typeof(isProtected) != 'boolean' || typeof(password) != 'string')
			return (this.reject(socket, "create"));

		this.logger.log(`${socket.login} is trying to create a room: ${name} with ${password}`);

		try {
			const roomID = await this.create(name, isProtected, password, socket);
			this.open(roomID, isProtected, name);
			await this.join(socket, roomID, password, name, true);
			await this.sendUserList(roomID, socket, socket.login);
		} catch (err) {
			this.reject(socket, "create", err.message);
		}
	  })
	});

	//Join Room
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('join', async ({roomID, password}) => {
		if (typeof(roomID) != 'number' || typeof(password) != 'string')
			return (this.reject(socket, "join", "Invalid room"));

		if (socket.rooms.has(roomID.toString()))
			return (this.reject(socket, "join", "you are already in that room"));

		try {
			await this.join(socket, roomID, password);
			await this.sendUserList(roomID, socket);
		} catch (err) {
			this.reject(socket, "join", err.message);
		}
	  })
	});

	//Leave Room
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('leave', async ({roomID}) => {
		if (typeof(roomID) != 'number')
			return (this.reject(socket, "leave", "Invalid room"));

		try {
			const leftChannel: Channel | UserChannel = await this.userChnnelRepository.leaveChannel(socket.dbID, roomID);
			this.server.to(roomID.toString()).emit("leave", {roomID, nick: socket.login});
			socket.leave(roomID.toString());
			if (leftChannel instanceof Channel)
				this.close(roomID);
		} catch (err) {
			return (this.reject(socket, "leave", err.message));
		}
	  })
	});

	//Make Admin
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('admin', async ({roomID, nick}) => {
		if (typeof(roomID) != 'number' || typeof(nick) != 'string' || nick === socket.login)
			return (this.reject(socket, "admin", "Invalid Data"));

		const sockChan: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID);
		if ((sockChan instanceof UserChannel && sockChan.role === eRole.MEMBER))
			return (this.reject(socket, "admin", "you cannot control other users"));
		
		const uc: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(nick, roomID);
		if (uc instanceof Channel)
			return (this.reject(socket, "admin", "you cannot control the owner"));
		else if (uc instanceof UserChannel && uc.role === eRole.ADMIN)
			return (this.reject(socket, "admin", "he is admin, you cannot promote more"));

		try {
			await this.userChnnelRepository.makeAdmin(roomID, nick);
			this.server.to(roomID.toString()).emit("admin", {roomID, nick});
		} catch (err) {
			return (this.reject(socket, "admin", err.message));
		}
	  })
	});

	//Kick
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('kick', async ({roomID, nick}) => {
		if (typeof(roomID) != 'number' || typeof(nick) != 'string' || nick === socket.login)
			return (this.reject(socket, "kick", "Invalid Data"));

		try {
		const sockChan: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID);
		if ((sockChan instanceof UserChannel && sockChan.role === eRole.MEMBER))
			return (this.reject(socket, "mute", "you cannot control other users"));
	
		const uc: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(nick, roomID);

		if (uc instanceof Channel)
			return (this.reject(socket, "mute", "you cannot control the owner"));
			await this.userChnnelRepository.kick(roomID, nick);
			const otherSocket: SocketWithDataDTO = this.UserManager.get(nick);
			this.server.to(roomID.toString()).emit("kick", {roomID, nick});
			otherSocket.leave(roomID.toString());
		} catch (err) {
			this.reject(socket, "kick", err.message);
		}
	  })
	});

	//Ban
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('ban', async ({roomID, nick}) => {
		if (typeof(roomID) != 'number' || typeof(nick) != 'string' || nick === socket.login)
			return (this.reject(socket, "ban", "Invalid Data"));

		try {
		const sockChan: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID);
		if ((sockChan instanceof UserChannel && sockChan.role === eRole.MEMBER))
			return (this.reject(socket, "ban", "you cannot control other users"));

		const uc: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(nick, roomID);
		if (uc instanceof Channel)
			return (this.reject(socket, "ban", "you cannot control the owner"));

			const otherSocket: SocketWithDataDTO = this.UserManager.get(nick);
			await this.userChnnelRepository.ban(roomID, nick);
			this.server.to(roomID.toString()).emit("ban", {roomID, nick});
			otherSocket.leave(roomID.toString());
		} catch (err) {
			this.reject(socket, "ban", err.message);
		}})
	});

	//Mute
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('mute', async ({roomID, nick, timeInSec}) => {
		if (typeof(timeInSec) != 'number' || typeof(nick) != 'string' ||
			typeof(roomID) != 'number' || (false === socket.rooms.has(roomID.toString())) ||
			nick === socket.login)
			  return (this.reject(socket, "mute", "Invalid Data"));

		try{
		const sockChan: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID);
		if ((sockChan instanceof UserChannel && sockChan.role === eRole.MEMBER))
			return (this.reject(socket, "mute", "you cannot control other users"));

		const uc: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(nick, roomID);
  
		if (uc instanceof UserChannel && (uc.muted || uc.banned))
			return (this.reject(socket, "mute", "you cannot mute him"));
		else if (uc instanceof UserChannel && false === uc.muted) {
			this.server.to(roomID.toString()).emit("mute", {roomID, nick});
			await this.userChnnelRepository.updateUserChannelMutedStatus(uc, true);
			setTimeout(unmute, timeInSec * 1000, {roomID, nick, server: this.server, uc, repo: this.userChnnelRepository});
		}
		else
			this.reject(socket, "mute", "you cannot mute owner");
		} catch (err) {
			this.reject(socket, "mute", err.message);
		}})
	})

	//public
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('public', async ({roomID}) => {
		if (typeof(roomID) != 'number')
			return (this.reject(socket, "public", "Invalid Data"));

		const chan: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID)
		if (chan instanceof UserChannel)
			return (this.reject(socket, "public", "You cannot control this channel"));

		try {
			await this.userChnnelRepository.changePublicState(chan, socket.dbID, true);
			this.server.to(roomID.toString()).emit("public", {roomID});
			this.server.emit("open", {roomID, isProtected: false, name: chan.name});
		} catch (err) {
			return (this.reject(socket, "public", err.message));
		}
	  })
	});

	//private
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('private', async ({roomID}) => {
		if (typeof(roomID) != 'number')
			return (this.reject(socket, "private", "Invalid Data"));

		const chan: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID)
		if (chan instanceof UserChannel)
			return (this.reject(socket, "public", "You cannot control this channel"));

		try {
			await this.userChnnelRepository.changePublicState(chan, socket.dbID, false);
			this.server.to(roomID.toString()).emit("private", {roomID});
			this.server.emit("close", {roomID});
		} catch (err) {
			return (this.reject(socket, "public", err.message));
		}
	  })
	});

	//protect
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('protect', async ({roomID, password}) => {
		if (typeof(roomID) != 'number' || typeof(password) != 'string')
			return (this.reject(socket, "protect", "Invalid Data"));

		const chan: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID)
		if (chan instanceof UserChannel)
			return (this.reject(socket, "public", "You cannot control this channel"));

		try {
			await this.userChnnelRepository.protect(chan, password);
			this.server.to(roomID.toString()).emit("protect", {roomID});
			this.server.emit("open", {roomID, isProtected: true, name: chan.name});
		} catch (err) {
			this.reject(socket, "protect", err.message);
		}
	  })
	});

	//Direct Message
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('dm', ({ nick, message }) => {
		if (nick === socket.login)
			return this.reject(socket, "dm", "really? are you gonna sending dm to yourself?");
		if (true == this.UserManager.has(nick)) {
			const HisID: string = this.UserManager.get(nick).id;
			socket.to(HisID).emit("dm", {from: socket.login, to: nick, message});
			this.server.to(socket.id).emit("dm", {from: socket.login, to: nick, message});
		} else {
			this.reject(socket, "dm", `there is no user: ${nick}`);
		}
	  })
	});

	//Send a Message to Room
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('msg', async ({roomID, message}) => {
		try {
		  const roomIDstr: string = roomID.toString();
		  const channel: Channel = await this.userChnnelRepository.findChannel(roomID);
		  if (!channel)
		    return (this.reject(socket, "msg", "channel not found"));

		  const uc: UserChannel | Channel = await this.userChnnelRepository.getOneUserChannel(socket.login, roomID);
		  if (uc instanceof Channel || uc.muted === false)
			this.server.to(roomIDstr).emit("msg", {roomID, nick: socket.login, message});
		  else
			this.reject(socket, "msg", "you are muted. boy");
		  } catch (err) {
			return (this.reject(socket, "msg", err.message));
		}
	  })
	})

	//Block
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('block', async ({nick}) => {
		if (undefined === nick || typeof(nick) != 'string' || nick === socket.login)
			return (this.reject(socket, "block", "Invalid Data"));

		try {
			await this.blockRepository.addBlock(socket.dbID, nick);
			this.server.to(socket.id).emit("block", {nick});
		} catch (err) {
			return (this.reject(socket, "block", err.message));
		}
	  })
	});

	//UnBlock
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('unblock', async ({nick}) => {
		if (undefined === nick || typeof(nick) != 'string' || nick === socket.login)
			return (this.reject(socket, "unblock", "Invalid Data"));

		try {
			await this.blockRepository.unBlock(socket.dbID, nick);
			this.server.to(socket.id).emit("unblock", {nick});
		} catch (err) {
			return (this.reject(socket, "unblock", err.message))
		}
	  })
	});

	//Subscribe Friend
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('friend', async ({nick}) => {
		if (undefined === nick || typeof(nick) != 'string' || nick === socket.login)
			return (this.reject(socket, "friend", "Invalid Data"));

		try {
			const friendList = await this.friendRepository.subScribeFriend(socket.dbID, nick);
			this.server.to(socket.id).emit("friend", {nick, status: friendList.subscribedUser.socketStatus});
		} catch (err) {
			return (this.reject(socket, "friend", err.message));
		}
	  })
	});

	//Unsubscribe Friend
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('unfriend', async ({nick}) => {
		if (undefined === nick || typeof(nick) != 'string' || nick === socket.login)
			return (this.reject(socket, "unfriend", "Invalid Data"));

		try {
			await this.friendRepository.deleteFriend(socket.dbID, nick);
			this.server.to(socket.id).emit("unfriend", {nick});
		} catch (err) {
			return (this.reject(socket, "unfriend", err.message));
		}
	  })
	});

	//nick
	this.server.on('connection', (socket: SocketWithDataDTO) => {
	  socket.on('nick', async ({newNick}) => {
		if (typeof(newNick) != 'string')
			return (this.reject(socket, "nick", "Invalid Data"));
		else if (socket.login === newNick)
			return (this.reject(socket, "nick", "that name is already in use"));

		try {
			await this.userRepository.updateUserNickname(socket.dbID, newNick);
			this.UserManager.delete(socket.login);
			this.UserManager.set(newNick, socket);
			this.server.emit("nick", {oldNick: socket.login, newNick});
			socket.login = newNick;
		} catch (err) {
			if (err.code === '23505')
				return (this.reject(socket, "nick", "that name is already in use"));
			else
				return (this.reject(socket, "nick", err.message));
		}
	  })
	});

  } // afterInit end

  async sendUserList(roomID: number, socket: SocketWithDataDTO, ownerOrNull?: string)
  	: Promise<void>
  {
	if (this.progNumber == undefined || !socket)
		return (this.reject(socket, "users", "Invalid RoomID"));

	if (undefined === ownerOrNull || null === ownerOrNull) {
		const ToJoinChannel: Channel = await this.userChnnelRepository.findChannel(roomID);
		if (ToJoinChannel.owner)
			ownerOrNull = ToJoinChannel.owner.login;
	}
	const users: iChanUsers[] = await this.userChnnelRepository.getChannelUsers(roomID);
	const tempObject = {
		roomID,
		ownerOrNull,
		users
	}
	this.server.to(socket.id).emit("users", tempObject);
  }

  async getUserName(socket: SocketWithDataDTO)
  	: Promise<boolean>
  {
	const bearerToken: string = `${socket.handshake.headers.cookie}`;
	if (!bearerToken) {
		throw new BadRequestException('cookie data is wrong');
	}
	const token = bearerToken && bearerToken.match(cookieName).input.split('=')[1];
	if (!token) return (false);

	try {
	  const decodedToken: Users = await this.jwtService.verifyAsync(token, {secret: jwtConfig.secret});
	  if (!decodedToken) return (false);

	  const user: Users = await this.userRepository.getOneUserByID(decodedToken.id);
	  if (!user) return (false);

	  socket.login = user.login;
	  socket.ftLogin = user.loginID;
	  socket.dbID = user.id;
	} catch (err) {
	  this.reject(socket, "connect", "Failed to verify data");
	  return (false);
	}
  }

  async tryConnect(socket: SocketWithDataDTO)
  	: Promise<void>
  {
	if (false == await this.getUserName(socket)) {
		this.logger.log(`WARNING : ${socket.id} trying to login, but there is no data for it, needs invetigate ${socket.handshake.address}`);
		this.reject(socket, "connect", "Invalid data");
		socket.disconnect(true);
	} else if (true === await this.checkSocket(socket)) {
		this.logger.log(`${socket.id}: ${socket.login} is re-connected`);
	}

	try {
	this.UserManager.set(socket.login, socket);
	const chans: iChans[] = await this.userChnnelRepository.getAlliChans();
	const blocks: string[] = await this.blockRepository.getAlliBlocks(socket.dbID);
	const friends: iFriends[] = await this.friendRepository.getAlliFriends(socket.dbID);
	this.server.to(socket.id).emit('chans', {chans});
	this.server.to(socket.id).emit('blocks', {blocks});
	this.server.to(socket.id).emit('friends', {friends});
	const userChans: UserChannel[] = await this.userChnnelRepository.getUserChannels(socket);
	const ownChans: Channel[] = await this.userChnnelRepository.getOwnChannels(socket);
	if (ownChans) {
		ownChans.forEach(async (oc) => {
			socket.join(oc.roomIDstr);
			this.server.to(socket.id).emit("join", { roomID: oc.roomID, nick: socket.login, name: oc.name });
			await this.sendUserList(oc.roomID, socket);
		})
	} if (userChans) {
		userChans.forEach(async (uc) => {
			if (uc.banned === false) {
				socket.join(uc.channel.roomIDstr);
				this.server.to(socket.id).emit("join", { roomID: uc.channel.roomID, nick: socket.login, name: uc.channel.name });
				await this.sendUserList(uc.channel.roomID, socket);
			}
		})
	}
	this.logger.log(`${socket.id}: ${socket.login} connected`);
	state(this.server, socket, 'online', this.friendRepository, this.userRepository);
	} catch (err) {
		return ;
	}
  }

  async create(name: string, isProtected: boolean, password: string, socket: SocketWithDataDTO)
	: Promise<number>
  {
	const nowDate: Date = new Date();
	const toPlusDate: number = Math.floor(nowDate.getTime() / 1000);
	const ToCreateRoom: number = (this.progNumber++) + toPlusDate;
	const owner: Users = await this.userRepository.getOneUserByID(socket.dbID);
	const NewOne: iChannels = {
		roomID: ToCreateRoom,
		roomIDstr: ToCreateRoom.toString(),
		isProtected,
		name,
		owner,
		password: password
	}

	await this.userChnnelRepository.createChannel(NewOne);
	return (ToCreateRoom);
  }

  async join(socket: SocketWithDataDTO, roomID: number, password: string, name: string = undefined, owner: boolean = false)
  	: Promise<void>
  {
	const ToJoinRoom: string = roomID.toString();
	if (owner === false) {
		try {
			await this.userChnnelRepository.joinChannel(socket.dbID, roomID, password);
		} catch (err) {
			throw err;
		}
	}
	socket.join(ToJoinRoom);
	if (name === undefined) {
		name = (await this.userChnnelRepository.findChannel(roomID)).name;
	}
	this.server.to(roomID.toString()).emit("join", { roomID, nick: socket.login, name });
  }

  open(roomID: number, isProtected: boolean, name: string): void {
	if (undefined === roomID || undefined === isProtected || !name)
		throw new BadRequestException("Invalid Data");

	this.server.emit("open", {roomID, isProtected, name});
  }

  close(roomID: number): void {
	if (undefined === roomID)
		throw new BadRequestException("Invalid Data");

	this.server.emit("close", {roomID});
  }

  reject(socket: SocketWithDataDTO, request: string, msg: string = "Bad Request"): void {
	if (!socket || undefined === request || !msg)
		throw new BadRequestException("Invalid Data");

	this.server.to(socket.id).emit("reject", {message: `your \"${request}\" is rejected due to ${msg}`});
  }

  async checkSocket(socket: SocketWithDataDTO): Promise<boolean> {
	if (!socket)
		throw new BadRequestException("Invalid Data");

	return (socket.dbID && socket.login && true);
  }
}

export async function state(
	server: Server,
	socket: SocketWithDataDTO,
	status: string,
	friendRepository: FriendRepository,
	userRepository: UserRepository
): Promise<void> {
	if (undefined === socket || undefined === friendRepository || undefined === userRepository)
		return ;

	try {
	const friends: iFriends[] = await friendRepository.getSubscribedUser(socket.dbID);
	if (friends.length > 0) {
		friends.forEach((friends) => {
			if (userManager.has(friends.nick)) {
				server.to(userManager.get(friends.nick).id).emit("state", {nick: socket.login, status});
			}
		});
	}
	await userRepository.setStatus(socket.dbID, status);
	} catch (err) {
		;
	}
  }

function unmute({roomID, nick, server, uc, repo}): void {
	if (undefined === roomID || undefined === nick || undefined === server || undefined === uc || undefined === repo)
		throw new BadRequestException("Invalid Data");

	repo.updateUserChannelMutedStatus(uc, false);
	server.to(roomID.toString()).emit("unmute", {roomID, nick});
}
import { DataSource, DeleteResult, EntityRepository, Repository, UpdateResult } from "typeorm";
import { eRole, UserChannel } from "../entities/userChannel.entity";
import { iChannels, iChans } from "../chat.gateway";
import { BadRequestException, Logger, UnauthorizedException } from "@nestjs/common";
import { ChannelRepository } from "./Channel.repository";
import { UserRepository } from "src/users/repositories/user.repository";
import { Channel } from "../entities/channel.entity";
import * as bcrypt from 'bcrypt';
import { Users } from "src/users/entities/users.entity";
import { SocketWithDataDTO } from "../dto/socketWithData.dto";

export interface iChanUsers {
	nick: string,
	isAdmin: boolean,
	isMuted: boolean
};

@EntityRepository(UserChannel)
export class UserChannelsRepository extends Repository<UserChannel> {
	constructor(
		private dataSource: DataSource,
		private readonly channelRepository: ChannelRepository,
		private readonly userRepository: UserRepository
	) {
		super(UserChannel, dataSource.createEntityManager());
	}

	async createChannel(channel: iChannels)
	: Promise<Channel>
	{
		if (!channel)
			throw new BadRequestException('no channel');

		const saltRounds = 10;
		channel.password = await bcrypt.hash(channel.password, saltRounds);
		const newOne: Channel = this.channelRepository.create(channel);

		return (await this.channelRepository.save(newOne));
	}

	async joinChannel(userID: number, roomID: number, password: string, role: eRole = eRole.MEMBER)
	: Promise<UserChannel>
	{
		if (undefined === userID || undefined == roomID || undefined === password) {
			throw new BadRequestException("user or roomID is Invalid");
		}

		try {
		const ToJoinChannel = await this.channelRepository.findOne({where: {roomID: roomID}});
		const isBanned = await this.findOne({
			where: {
				user: {id: userID},
				channel: {roomID}
			}
		});
		if (!ToJoinChannel) {
			throw new BadRequestException('no channel');
		} else if ((ToJoinChannel.isProtected && undefined == password) ||
					(ToJoinChannel.isProtected && false == await bcrypt.compareSync(password, ToJoinChannel.password))) {
			throw new BadRequestException('incorrect password');
		} else if (isBanned && isBanned.banned) {
			throw new UnauthorizedException('you were banned');
		}

		const FoundChannel: UserChannel = await this.findOne({
			where: {
				user: {id : userID},
				channel: {roomID}
			}
		});
		if (FoundChannel)
			return (null);

		const NewOne = this.create({
			user : {id: userID},
			channel: ToJoinChannel,
			role
		});

			const userCount: number = (ToJoinChannel.userCount + 1);
			const savedUC: UserChannel = await this.save(NewOne);
			await this.channelRepository.update(ToJoinChannel.id, {
				userCount
			})
			return (savedUC);
		} catch (err) {
			throw new BadRequestException("save failed");
		}
	}

	async findChannel(roomID: number): Promise<Channel> {
		if (undefined === roomID)
			throw new BadRequestException("Invalid Data");

		return (await this.channelRepository.findOne({where: {roomID: roomID}}));
	}

	async getAllChannels(): Promise<Channel[]> {
		return (await this.channelRepository.find());
	}

	async getOwnChannels(socket:SocketWithDataDTO)
	: Promise<Channel[]> {
		if (!socket)
			throw new BadRequestException("Invalid Data");

		const user: Users = await this.userRepository.getOneUserByLogin(socket.login);
		return (await this.channelRepository.find({where: {owner: {id: user.id}}}));
	}

	async getUserChannels(socket: SocketWithDataDTO)
	: Promise<UserChannel[]>
	{
		if (!socket)
			throw new BadRequestException("Invalid Data");

		const userChannels = await this.find({
		where: {
			user: { id: socket.dbID },
			banned: false
		},
		});
		return (userChannels);
	}

	async getOneUserChannel(nick: string, roomID: number)
	: Promise<UserChannel | Channel>
	{
		if (!nick || undefined === roomID)
			throw new BadRequestException("Invalid Data");
		const user: Users = await this.userRepository.getOneUserByLogin(nick);
		if (!user)
			throw new BadRequestException("No User");

		const ownChannel: Channel = await this.channelRepository.findOne({
			where: {
				owner: {id: user.id},
				roomID
		}});
		if (ownChannel)
			return (ownChannel);

		const userChannel = await this.findOne({
		where: {
			user: { login: nick },
			channel: { roomID }
		}});
		return (userChannel);
	}

	async getAlliChans()
	: Promise<iChans[]> 
	{
		const channel: Channel[] = await this.channelRepository.find({
			where: {
				isOpened: true
			}
		});

		const ichans: iChans[] = channel.map(channel => ({
			roomID: channel.roomID,
			isProtected: channel.isProtected,
			name: channel.name
		}));
		return (ichans);
	}

	async getChannelUsers(roomID: number)
	: Promise<iChanUsers[]>
	{
		if (undefined == roomID) {
			throw new BadRequestException("Invalid Room");
		}

		const userChannels = await this.find({
			where: { 
				channel: { roomID: roomID },
				banned: false
			},
			relations: ["user"]
		});

		const users: iChanUsers[] = userChannels.map(uc => ({
			nick: uc.user.login,
			isAdmin: uc.role === eRole.ADMIN || uc.role === eRole.OWNER,
			isMuted: uc.muted
		}));
		return (users);
	}

	async updateUserChannelMutedStatus(uc: UserChannel, muted: boolean)
	: Promise<UpdateResult>
	{
		if (!uc)
			return (null);

		return (this.update(uc.id, {muted}));
	}

	async leaveChannel(userID: number, roomID: number)
	: Promise<Channel | UserChannel>
	{
		if (undefined === userID || undefined == roomID)
			throw new BadRequestException("Invalid Data");

		const userChannel = await this.findOne({
		  where: {
			user: { id: userID },
			channel: { roomID }
		  }
		});
		const channel: Channel = await this.channelRepository.findOne({where: {roomID}});

		if (userChannel)
		{
			const removedUC: UserChannel = await this.remove(userChannel);
			const userCount = (channel.userCount - 1);
			const banCount = (channel.banCount);
			await this.channelRepository.update(channel.id, {userCount});
			const remainingUserChannels: UserChannel[] = await this.find({
				where: {
				  channel: { roomID }
				}
			});

			if (userCount === 0) {
				if (channel && channel.owner === null) {
					if (banCount > 0) {
						for (const remUC of remainingUserChannels)
								await this.remove(remUC);
					}
					return (await this.channelRepository.remove(channel));
				} else {
					return (removedUC);
				}
			} else {
				return (removedUC);
			}
		}
		else
		{
			const user: Users = await this.userRepository.getOneUserByID(userID);
			if (channel && channel.owner.login === user.login) {
				if (channel.userCount > 0) {
					await this.channelRepository.update(channel.id, {owner: null});
					return (null);
				} else {
					return (await this.channelRepository.remove(channel));
				}
			}
			throw new BadRequestException("you are not in that room");
		}
	}
	
	async makeAdmin(roomID: number, nick: string)
	: Promise<UpdateResult>
	{
		if (undefined === roomID || !nick)
			throw new BadRequestException("Invalid Data");

		try {
		const user:Users = await this.userRepository.getOneUserByLogin(nick);

		const uc: UserChannel = await this.findOne({
			where: {
				user: {id: user.id},
				channel: {roomID}
		}});

		if (!uc)
			throw new BadRequestException("No user in that room or No room in this server");
		else if (uc.role !== eRole.MEMBER)
			throw new BadRequestException("That memeber is not a member");

			return (await this.update(uc.id, {
				role: eRole.ADMIN
			}));
		} catch (err) {
			throw err;
		}
	}

	async kick(roomID: number, nick: string)
	: Promise<UserChannel>
	{
		if (undefined === roomID || !nick)
			throw new BadRequestException("Invalid Data");

		try {
		const ToKickUser: Users = await this.userRepository.getOneUserByLogin(nick);
		if (!ToKickUser)
			throw new BadRequestException("no user");

		const ToKickChannel = await this.findOne({
			where : {
				user: { id: ToKickUser.id },
				channel: { roomID }
			}
		})

		if (!ToKickChannel)
			throw new BadRequestException("no user in that channel");

			const userCount = ToKickChannel.channel.userCount - 1;
			await this.channelRepository.update(ToKickChannel.channel.id, {userCount});
			return (this.remove(ToKickChannel));
		} catch (err) {
			throw err;
		}
	}

	async ban(roomID: number, nick: string)
	: Promise<UpdateResult>
	{
		if (undefined === roomID || !nick)
			throw new BadRequestException("Invalid Data");

		try {
		const ToBanUser: Users = await this.userRepository.getOneUserByLogin(nick);
		if (!ToBanUser)
			throw new BadRequestException("no user");
		let ToBanUserChannel: UserChannel = await this.findOne({
			where : {
				user: { id: ToBanUser.id },
				channel: { roomID }
			}
		});
		const ToBanChannel: Channel = await this.channelRepository.findOne({where : {roomID}});
		if (!ToBanChannel)
			throw new BadRequestException("no channel");

		const banCount: number = (ToBanChannel.banCount + 1);
		if (ToBanUserChannel && ToBanUserChannel.banned === true) {
			throw new UnauthorizedException("he were banned already");
		} else if (!ToBanUserChannel) {
			const NewOne = this.create({
				user : {id: ToBanUser.id},
				channel: ToBanChannel,
				role: eRole.MEMBER,
				muted: true,
				banned: true
			});
			await this.save(NewOne);
			await this.channelRepository.update(ToBanChannel.id, {
				banCount
			});
		} else {
			const ret: UpdateResult = await this.update(ToBanUserChannel.id, {
				role: eRole.MEMBER,
				banned: true
			});
			await this.channelRepository.update(ToBanChannel.id, {
				banCount
			});
			return (ret);
		}
		} catch (err) {
			throw (err);
		}
	}

	async protect(chan: Channel, password: string)
	: Promise<UpdateResult>
	{
		if (!chan || undefined === password)
			throw new BadRequestException("Invalid Data");

		const HashedPassword = await bcrypt.hashSync(password, 10);

		try{
			return (await this.channelRepository.update(chan.id,{
				isProtected: true,
				password: HashedPassword
			}));
		} catch (err) {
			throw (err);
		}
	}

	async changePublicState(chan: Channel, userID: number, status: boolean)
	: Promise<UpdateResult>
	{
		if (!chan || undefined === userID || undefined === status)
			throw new BadRequestException("Invalid Data");

		try {
			return (await this.channelRepository.update(chan.id, {
				isOpened: status,
				isProtected: !status
			}))
		} catch (err) {
			throw new BadRequestException('something went wrong');
		}
	}
}
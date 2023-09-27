import { BadRequestException, Logger } from "@nestjs/common";
import { Users } from "src/users/entities/users.entity";
import { Server } from "socket.io";
import { WebSocketGateway, WebSocketServer } from "@nestjs/websockets";
import { SocketWithDataDTO } from "src/chat/dto/socketWithData.dto";
import { UserRepository } from "src/users/repositories/user.repository";
import { MatchRecordService } from "./matchRecord/matchRecord.service";
import { eWinner } from "./matchRecord/matchRecord.entity";
import { userManager, state, FEServer } from "src/chat/chat.gateway";
import { FriendRepository, iFriends } from 'src/chat/repositories/friend.repository';

let g_matchRecordService: MatchRecordService;
let g_userRepository: UserRepository;
let g_friendRepository: FriendRepository;

const g_ftToSocketMap = {};

class GameCoord {
	x: number;
	y: number;
}

class GameObject {
	pos: GameCoord;
	v: GameCoord;
}

class GameInput {
	isUp: boolean;
	isDown: boolean;
}

class GamePlayer {
	sock: SocketWithDataDTO;
	paddle: GameObject;
	score: number;
}

export class GameData {
	server: Server;
	intervalID: NodeJS.Timeout;
	startDate: Date;
	lastTime: number;
	lastScoredTime: number;
	p1: GamePlayer;
	p2: GamePlayer;
	p1Input: GameInput;
	p2Input: GameInput;
	ball: GameObject;
	endScore: number;
	mode: string;
	isPlaying: boolean;
	isP1Disconnected: boolean;
	isP2Disconnected: boolean;
	winner: string
}

function gameloop(gameData: GameData): void
{
	//is fin
	let winner: eWinner;
	if (gameData.p1.score === gameData.endScore || gameData.isP2Disconnected) {
		gameData.winner = "p1";
		winner = eWinner.Player1;
	}
	if (gameData.p2.score === gameData.endScore || gameData.isP1Disconnected) {
		gameData.winner = "p2";
		winner = eWinner.Player2;
	}
	if (gameData.winner){
		g_matchRecordService.createMatchRecord(gameData.startDate, gameData.p1.sock, gameData.p2.sock, gameData.p1.score, gameData.p2.score, winner, gameData.mode)
		gameData.p1.sock.currentGame = null;
		gameData.p2.sock.currentGame = null;
		clearInterval(gameData.intervalID);
		if (gameData.isP1Disconnected === false) {
			state(gameData.server, gameData.p1.sock, 'online', g_friendRepository, g_userRepository);
			gameData.server.to(gameData.p1.sock.id).emit("fin", { message: gameData.winner + " is win!"});
		}
		if (gameData.isP2Disconnected === false) {
			state(gameData.server, gameData.p2.sock, 'online', g_friendRepository, g_userRepository);
			gameData.server.to(gameData.p2.sock.id).emit("fin", { message: gameData.winner + " is win!"});
		}
	}

	const currentTime: number = Date.now();
	const deltaTime = (currentTime - gameData.lastTime) / 10;
	gameData.lastTime = currentTime;
	gameData.p1.paddle.v.y = 0;
	gameData.p2.paddle.v.y = 0;
	gameData.p1.paddle.v.y -= gameData.p1Input.isUp ? 8 : 0;
	gameData.p2.paddle.v.y -= gameData.p2Input.isUp ? 8 : 0;
	gameData.p1.paddle.v.y += gameData.p1Input.isDown ? 8 : 0;
	gameData.p2.paddle.v.y += gameData.p2Input.isDown ? 8 : 0;
	//input
	gameData.p1.paddle.pos.y += deltaTime * gameData.p1.paddle.v.y;
	gameData.p2.paddle.pos.y += deltaTime * gameData.p2.paddle.v.y;
	if (gameData.p1.paddle.pos.y < 0) { gameData.p1.paddle.pos.y = 0; }
	if (gameData.p2.paddle.pos.y < 0) { gameData.p2.paddle.pos.y = 0; }
	if (gameData.p1.paddle.pos.y > 450 - 60) { gameData.p1.paddle.pos.y = 450 - 60 + 1; }
	if (gameData.p2.paddle.pos.y > 450 - 60) { gameData.p2.paddle.pos.y = 450 - 60 + 1; }
	gameData.server.to(gameData.p1.sock.id).to(gameData.p2.sock.id).emit("update", {
		p1: { pos: { x: gameData.p1.paddle.pos.x, y: gameData.p1.paddle.pos.y }, v: { x: gameData.p1.paddle.v.x, y: gameData.p1.paddle.v.y} },
		p2: { pos: { x: gameData.p2.paddle.pos.x, y: gameData.p2.paddle.pos.y }, v: { x: gameData.p2.paddle.v.x, y: gameData.p2.paddle.v.y} },
		ball: { pos: { x: gameData.ball.pos.x, y: gameData.ball.pos.y }, v: { x: gameData.ball.v.x, y: gameData.ball.v.y} }
	});
	if (currentTime - gameData.lastScoredTime < 1000){
		return;
	}
	//update ball pos
	gameData.ball.pos.x += deltaTime * gameData.ball.v.x;
	gameData.ball.pos.y += deltaTime * gameData.ball.v.y;
	//collide
		//upper side
	if (gameData.ball.pos.y < 0){
		gameData.ball.pos.y = 0;
		gameData.ball.v.y *= -1;
	}
		//down side
	if (gameData.ball.pos.y > 450 - 15){
		gameData.ball.pos.y = 450 - 15 + 1;
		gameData.ball.v.y *= -1;
	}
	let ballCenterPosY: number;
	let paddleCenterPosY: number;
	let diffCenterPosY: number;
		//p1 paddle
	if (gameData.ball.pos.y > gameData.p1.paddle.pos.y - 15
		&& gameData.ball.pos.y < gameData.p1.paddle.pos.y + 60 
		&& gameData.ball.pos.x > 0
		&& gameData.ball.pos.x < 15){
		gameData.ball.pos.x = 15;
		gameData.ball.v.x *= -1;
		ballCenterPosY = gameData.ball.pos.y + 7;
		paddleCenterPosY = gameData.p1.paddle.pos.y + 30;
		diffCenterPosY = ballCenterPosY - paddleCenterPosY;
		gameData.ball.v.y = diffCenterPosY / 4;
	}
		//p2 paddle
	if (gameData.ball.pos.y > gameData.p2.paddle.pos.y - 15
		&& gameData.ball.pos.y < gameData.p2.paddle.pos.y + 60 
		&& gameData.ball.pos.x > 800 - 30
		&& gameData.ball.pos.x < 800 - 15){
		gameData.ball.pos.x = 800 - 30;
		gameData.ball.v.x *= -1;
		ballCenterPosY = gameData.ball.pos.y + 7;
		paddleCenterPosY = gameData.p2.paddle.pos.y + 30;
		diffCenterPosY = ballCenterPosY - paddleCenterPosY;
		gameData.ball.v.y = diffCenterPosY / 4;
	}
	gameData.server.to(gameData.p1.sock.id).to(gameData.p2.sock.id).emit("update", {
		p1: { pos: { x: gameData.p1.paddle.pos.x, y: gameData.p1.paddle.pos.y }, v: { x: gameData.p1.paddle.v.x, y: gameData.p1.paddle.v.y} },
		p2: { pos: { x: gameData.p2.paddle.pos.x, y: gameData.p2.paddle.pos.y }, v: { x: gameData.p2.paddle.v.x, y: gameData.p2.paddle.v.y} },
		ball: { pos: { x: gameData.ball.pos.x, y: gameData.ball.pos.y }, v: { x: gameData.ball.v.x, y: gameData.ball.v.y} }
	});
	//score
	//p2 get score
	if (gameData.ball.pos.x < -15) {
		gameData.ball = { pos: { x: (800 - 15) / 2, y: (450 - 15) / 2 }, v: { x: -8, y: 0 } };
		gameData.p2.score++;
		gameData.lastScoredTime = currentTime;
		gameData.server.to(gameData.p1.sock.id).to(gameData.p2.sock.id).emit("score", { scorer: 'p2' });
		gameData.server.to(gameData.p1.sock.id).to(gameData.p2.sock.id).emit("update", {
			p1: { pos: { x: gameData.p1.paddle.pos.x, y: gameData.p1.paddle.pos.y }, v: { x: gameData.p1.paddle.v.x, y: gameData.p1.paddle.v.y} },
			p2: { pos: { x: gameData.p2.paddle.pos.x, y: gameData.p2.paddle.pos.y }, v: { x: gameData.p2.paddle.v.x, y: gameData.p2.paddle.v.y} },
			ball: { pos: { x: gameData.ball.pos.x, y: gameData.ball.pos.y }, v: { x: gameData.ball.v.x, y: gameData.ball.v.y} }
		});
	}
	//p1 get score
	if (gameData.ball.pos.x > 800) {
		gameData.ball = { pos: { x: (800 - 15) / 2, y: (450 - 15) / 2 }, v: { x: 8, y: 0 } };
		gameData.p1.score++;
		gameData.lastScoredTime = currentTime;
		gameData.server.to(gameData.p1.sock.id).to(gameData.p2.sock.id).emit("score", { scorer: 'p1' });
		gameData.server.to(gameData.p1.sock.id).to(gameData.p2.sock.id).emit("update", {
			p1: { pos: { x: gameData.p1.paddle.pos.x, y: gameData.p1.paddle.pos.y }, v: { x: gameData.p1.paddle.v.x, y: gameData.p1.paddle.v.y} },
			p2: { pos: { x: gameData.p2.paddle.pos.x, y: gameData.p2.paddle.pos.y }, v: { x: gameData.p2.paddle.v.x, y: gameData.p2.paddle.v.y} },
			ball: { pos: { x: gameData.ball.pos.x, y: gameData.ball.pos.y }, v: { x: gameData.ball.v.x, y: gameData.ball.v.y} }
		});	
	}
}

function createGameData(server: Server, p1socket: SocketWithDataDTO, p2socket: SocketWithDataDTO, mode: string, endScore: number): GameData {

	const gameData: GameData = new GameData();

	gameData.p1 = new GamePlayer();
	gameData.p1.sock = p1socket;
	gameData.p1.paddle = { pos: { x: 0, y: (450 - 60) / 2 }, v: { x:0, y:0 }};
	gameData.p1.score = 0;

	gameData.p2 = new GamePlayer();
	gameData.p2.sock = p2socket;
	gameData.p2.paddle = { pos: { x: 800 - 15 + 1, y: (450 - 60) / 2 }, v: { x:0, y:0 }};
	gameData.p2.score = 0;

	gameData.p1Input = new GameInput();
	gameData.p1Input.isUp = false;
	gameData.p1Input.isDown = false;
	gameData.p2Input = new GameInput();
	gameData.p2Input.isUp = false;
	gameData.p2Input.isDown = false;

	gameData.ball = { pos: { x: (800 - 15) / 2, y: (450 - 15) / 2 }, v: { x: -8, y: 0 } };

	gameData.server = server;

	gameData.endScore = endScore;
	gameData.mode = mode;
	gameData.isPlaying = false;

	gameData.isP1Disconnected = false;
	gameData.isP2Disconnected = false;

	return gameData;
}

class LadderWaiting {
	constructor(public socket: SocketWithDataDTO, public timeStamp: number) {}
}

class MatchMaker {
	queue: LadderWaiting[] = [];

	constructor(public server: Server) {}
	
	enque(socket: SocketWithDataDTO): boolean {
		for (let i = 0; i < this.queue.length; ++i) {
			if (this.queue[i].socket === socket){
				return false;
			}
		}
		this.queue.push(new LadderWaiting(socket, Date.now()));
		return true;
	}
	deque(socket: SocketWithDataDTO): void {
		for (let i = 0; i < this.queue.length; ++i) {
			if (this.queue[i].socket === socket) {
				this.queue.splice(i, 1);
				return;
			}
		}
	}
	isQueing(socket: SocketWithDataDTO): boolean {
		for (let i = 0; i < this.queue.length; ++i) {
			if (this.queue[i].socket === socket) {
				return true;
			}
		}
		return false;
	}
	makeMatches(): void {
		//shuffle
		for (let i = this.queue.length - 1; i > 0; --i) {
			const randomIndex = Math.floor(Math.random() * (i + 1));
			const temp = this.queue[i];
			this.queue[i] = this.queue[randomIndex];
			this.queue[randomIndex] = temp;
		}
		//makeMatches
		while (this.queue.length > 1) {
			const player1: SocketWithDataDTO = this.queue.shift().socket;
			const player2: SocketWithDataDTO = this.queue.shift().socket;
	
			const gameData = createGameData(this.server, player1, player2, "ladder", 10);
			gameData.p1.sock.currentGame = gameData;
			gameData.p2.sock.currentGame = gameData;
			gameData.isPlaying = true;
			gameData.startDate = new Date();
			gameData.lastTime = Date.now();
			gameData.lastScoredTime = Date.now();		
			gameData.intervalID = setInterval(gameloop, 10, gameData);
	
			this.server.to(player1.id).to(player2.id).emit("matched", { p1nick: player1.login, p2nick: player2.login });
			state(gameData.server, gameData.p1.sock, 'ongame', g_friendRepository, g_userRepository);
			state(gameData.server, gameData.p2.sock, 'ongame', g_friendRepository, g_userRepository);
		}
		//clear old waiting
		if (this.queue.length === 1 && this.queue[0].timeStamp < Date.now() - 15000) {
			const unmatchedSocket = this.queue.shift().socket;
			this.server.to(unmatchedSocket.id).emit("unmatched", {});
		}
	}
}

@WebSocketGateway({cors: {
	origin: [`http://${FEServer}`,
			 `https://${FEServer}`]
  }, cookie: true})
export class GameGateway {

	//Initialize
	@WebSocketServer()
	server: Server;
	matchQueue: SocketWithDataDTO[] = [];
	logger: Logger = new Logger("23-08-19 developing Game");
	matchMaker: MatchMaker;

	constructor(
		private matchRecordService: MatchRecordService,
		private userRepository: UserRepository,
		private friendRepository: FriendRepository
	) {}

	afterInit()
	{
	  this.server.setMaxListeners(500);

	  this.matchMaker = new MatchMaker(this.server);
	  setInterval(() => { this.matchMaker.makeMatches(); }, 1000);

	  g_matchRecordService = this.matchRecordService;
	  g_userRepository = this.userRepository;
	  g_friendRepository = this.friendRepository;

	  this.server.on('connection', async (socket: SocketWithDataDTO) => {
		socket.on('disconnect', async () => {
			//래더큐에서 제거하기 - done
			this.matchMaker.deque(socket);
			//진행중인 게임이 있으면 패배처리 - done
			if (socket.currentGame && socket.currentGame.isPlaying) {
				if (socket.currentGame.p1.sock.id === socket.id) {
					socket.currentGame.isP1Disconnected = true;;
				} else {
					socket.currentGame.isP2Disconnected = true;;
				}
			}
			//받은 도전은 시간돼서 저절로 없어지되, 신청한 도전은 만일을 위해 먼저 제거 -done
			socket.currentGame = null;
			g_ftToSocketMap[socket.ftLogin] = undefined;
		})
	  });
  
	  /*
	  this.server.on('connection', async (socket: SocketWithDataDTO) => {
	    socket.on("xxxx", async () => {
		  if (undefined === player || typeof(player) != 'string')
			throw new BadRequestException("Invalid Request");

		  const foundUser: Users = await this.userRepository.findOne({where: {login: player}});

		  if (undefined == foundUser || socket.dbID !== foundUser.id) {
			this.logger.log(`typeof socket.dbID == ${typeof(socket.dbID)} and foundUser.id == ${typeof(foundUser.id)}`);
		  	throw new BadRequestException("Invalid Data");
		  }

		  this.matchQueue.push(socket);
		  //this.server.to(socket.id).emit("inQueue", {msg: "finding your enemy"});
		  this.checkMatchQueue();
		})
	  });
	  */
	  
	  this.server.on('connection', async (socket: SocketWithDataDTO) => {
		socket.on("ladder", async () => {
			if (socket.currentGame) {
				this.server.to(socket.id).emit('reject-game', { message: "You can not make double game." });
				return;
			}
			if (this.matchMaker.enque(socket) === false) {
				this.server.to(socket.id).emit('reject-game', { message: "You are searching a match aready." });
				return;
			}
			this.server.to(socket.id).emit('waiting', {});
		})
	  })
	  this.server.on('connection', async (socket: SocketWithDataDTO) => {
		socket.on("challenge", async ({ nick, mode }) => {
			if (socket.login === nick) {
				this.server.to(socket.id).emit('reject-game', { message: "You can not play game with yourself." });
				return;
			}
			if (socket.currentGame) {
				this.server.to(socket.id).emit('reject-game', { message: "You can not make double game." });
				return;
			}
			if (this.matchMaker.isQueing(socket)) {
				this.server.to(socket.id).emit('reject-game', { message: "You are searching a match aready." });
				return;
			}
			if (!nick || typeof(nick) !== 'string' || !userManager.get(nick)) {
				this.server.to(socket.id).emit('reject-game', { message: "There's no such user" });
				return;
			}
			if (userManager.get(nick).currentGame) {
				this.server.to(socket.id).emit('reject-game', { message: "The user is on game aready." });
				return;
			}
			g_ftToSocketMap[socket.ftLogin] = socket;
			let endScore = 10;
			let modeToSend = "standard";
			if (mode === "deathmatch") {
				endScore = 1;
				modeToSend = "deathmatch";
			}
			socket.currentGame = createGameData(this.server, socket, userManager.get(nick), modeToSend, endScore);
			setTimeout(() => {
				if (!socket.currentGame || socket.currentGame.isPlaying) {
					return;
				}
				socket.currentGame = null;
				this.server.to(socket.id).emit('unmatched', {});
			}, 30000);
			this.server.to(socket.id).emit('waiting', {});
			this.server.to(userManager.get(nick).id).emit('challenge', { nick: socket.login, mode: modeToSend, ftLogin: socket.ftLogin });
		})
	  })

	  this.server.on('connection', async (socket: SocketWithDataDTO) => {
		socket.on("take", async ({ ftLogin }) => {
			if (socket.currentGame) {
				this.server.to(socket.id).emit('reject-game', { message: "You can not make double game." });
				return;
			}
			if (this.matchMaker.isQueing(socket)) {
				this.server.to(socket.id).emit('reject-game', { message: "You are searching a match aready." });
				return;
			}
			if (!ftLogin || typeof(ftLogin) !== 'string') {
				this.server.to(socket.id).emit('reject-game', { message: "Can not find challenge." });
				return;
			}
			const challengerSock = g_ftToSocketMap[ftLogin];
			if (!challengerSock
			|| !challengerSock.currentGame
			|| challengerSock.currentGame.p2.sock !== socket
			|| challengerSock.currentGame.isPlaying) {
				this.server.to(socket.id).emit('reject-game', { message: "Can not find challenge." });
				return;
			}
			const gameData = challengerSock.currentGame;
			gameData.p2.sock.currentGame = gameData;
			gameData.isPlaying = true;
			gameData.startDate = new Date();
			gameData.lastTime = Date.now();
			gameData.lastScoredTime = Date.now();		
			gameData.intervalID = setInterval(gameloop, 10, gameData);
	
			this.server.to(socket.id).to(challengerSock.id).emit("matched", { p1nick: challengerSock.login, p2nick: socket.login });
			state(gameData.server, gameData.p1.sock, 'ongame', g_friendRepository, g_userRepository);
			state(gameData.server, gameData.p2.sock, 'ongame', g_friendRepository, g_userRepository);
		})
	  })
	  this.server.on('connection', async (socket: SocketWithDataDTO) => {
		socket.on("refuse", async ({ ftLogin }) => {
			if (!ftLogin || typeof(ftLogin) !== 'string') {
				return;
			}
			const challengerSock = g_ftToSocketMap[ftLogin];
			if (!challengerSock
			|| !challengerSock.currentGame
			|| challengerSock.currentGame.p2.sock !== socket
			|| challengerSock.currentGame.isPlaying) {
				return;
			}
			challengerSock.currentGame = null;
			this.server.to(challengerSock.id).emit('unmatched', {});
		})
	  })

	  this.server.on('connection', (socket: SocketWithDataDTO) => {
		socket.on("control", ({ key, isPressed }) => {
			if (typeof(key) !== 'string' || typeof(isPressed) !== 'boolean') {
				return;
			}
			if (socket.currentGame === undefined || socket.currentGame === null){
				return;
			}
			let input: GameInput = socket.currentGame.p1Input;
			if (socket.currentGame.p1.sock.id !== socket.id) {
				input = socket.currentGame.p2Input;
			}
			if (key === "up") {
				input.isUp = isPressed;
			} else {
				input.isDown = isPressed;
			}
		})
	  });
	}

	/*
	checkMatchQueue(): void {
		if (this.matchQueue.length < 2)
			return ;

		//FIXME matchQueue
		const player1: SocketWithDataDTO = this.matchQueue.shift();
		const player2: SocketWithDataDTO = this.matchQueue.shift();

		const gameData = createGameData(this.server, player1, player2, "standard", 10);
		gameData.p1.sock.currentGame = gameData;
		gameData.p2.sock.currentGame = gameData;
		gameData.isPlaying = true;
		gameData.intervalID = setInterval(gameloop, 10, gameData);

		this.server.to(player1.id).to(player2.id).emit("matched", { p1nick: player1.login, p2nick: player2.login });
		
		//this.playGame(player1, player2);
	}

	async playGame(player1: SocketWithDataDTO, player2: SocketWithDataDTO): Promise<void> {
		//Somethings will happen here
		const startDate: Date = new Date();

		let player1Score: number = 0;
		let player2Score: number = 0;

		let winner: eWinner = eWinner.DRAW;
		if (player1Score > player2Score)
			winner = eWinner.Player1;
		else if (player1Score > player2Score)
			winner = eWinner.Player2;

		if (this.matchRecordService.createMatchRecord(startDate, player1, player2, player1Score, player2Score, winner))
			this.server.to(player1.id).to(player2.id).emit("matchEnd", {player1Score, player2Score, winner});
	}
	reject(socket: SocketWithDataDTO, request: string, msg: string = "Bad Request"): void {
		this.server.to(socket.id).emit("reject", {message: `your \"${request}\" is rejected due to ${msg}`});
	}
	*/
}

import { Socket } from "socket.io";
import { GameData } from "src/game/game.gateway";

export class SocketWithDataDTO extends Socket {
	dbID: number;
	login: string;
	ftLogin: string;
	currentGame?: GameData;
}

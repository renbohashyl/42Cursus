import { BadRequestException, Injectable, Logger, NotFoundException } from '@nestjs/common';
import { MatchRecordRepository } from './matchRecord.repository';
import { MatchRecord, eWinner } from './matchRecord.entity';
import { Users } from 'src/users/entities/users.entity';
import { SocketWithDataDTO } from 'src/chat/dto/socketWithData.dto';
import { UsersService } from 'src/users/users.service';

@Injectable()
export class MatchRecordService {

	constructor(
		private matchRecordRepository: MatchRecordRepository,
		private userService: UsersService
	) {}

	async getAllHistories(
		user: Users
	) : Promise<MatchRecord[]> {
		if (!user)
			return (null);

		try {
			return (await this.matchRecordRepository.getAllHistories(user));
		} catch (err) {
			throw (err);
		}
	}

	async getMatchRecordByID(id: number) : Promise <MatchRecord> {
		if (undefined === id)
			return (null);
		const found = await this.matchRecordRepository.findOne({where: {id}});

		if (!found) {
			throw new NotFoundException(`404 Not Found with ${id}`);
		}

		return (found);
	}

	async createMatchRecord(
		date: Date,
		player1: SocketWithDataDTO,
		player2: SocketWithDataDTO,
		player1Score: number,
		player2Score: number,
		winner: eWinner,
		matchType: string
	) : Promise<MatchRecord> {
		if (!date || !player1 || !player2 ||
			undefined === player1Score || undefined === player2Score ||
			undefined === winner || undefined === matchType)
			throw new BadRequestException("Invalid record data");

		try {
		let winnerUserName: string = null;
		let winnerUserID: string = null;
		if (winner === eWinner.Player1) {
			winnerUserName = player1.login;
			winnerUserID = player1.ftLogin;
		}
		else if (winner === eWinner.Player2) {
			winnerUserName = player2.login;
			winnerUserID = player2.ftLogin;
		}

		const result: MatchRecord = this.matchRecordRepository.create({
			date,
			player1: {id: player1.dbID},
			player2: {id: player2.dbID},
			winnerName: winnerUserName,
			winnerID: winnerUserID,
			winner,
			matchType,
			player1Score,
			player2Score
		})
		const saveResult = await this.matchRecordRepository.save(result);
		if (saveResult) {
			this.userService.updateRank(player1.dbID, winner === eWinner.Player1, winner === eWinner.DRAW, matchType === 'ladder');
			this.userService.updateRank(player2.dbID, winner === eWinner.Player2, winner === eWinner.DRAW, matchType === 'ladder');
		}
		return (saveResult);
		} catch (err) {
			throw (err);
		}
	}

	async deleteMatchRecord(id: number) : Promise<void> {
		if (undefined === id)
			return ;

		try {
			const foundRecord: MatchRecord = await this.getMatchRecordByID(id);
			if (!foundRecord)
				throw new BadRequestException("Invalid Data");

			if (foundRecord.player1 === null && foundRecord.player2 === null)
				await this.matchRecordRepository.delete( {id} );
		} catch (err) {
			throw (err);
		}
	}
}

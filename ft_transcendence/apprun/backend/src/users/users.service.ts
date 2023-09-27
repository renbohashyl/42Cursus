import { BadRequestException, Injectable, UnauthorizedException } from '@nestjs/common';
import { UserRepository } from './repositories/user.repository';
import { Users } from './entities/users.entity';
import { FTUserTypes } from 'src/auth/oauth/dto/oauth_user.dto';
import { ProfileDTO } from './dto/Profile.dto';
import { MatchRecord } from '../game/matchRecord/matchRecord.entity';
import sizeOf from 'image-size';
import { imagePath } from './multerOptions';
import * as fs from 'fs';
import { AchievementRepository } from './repositories/achievements.repository';
import { Achievement } from './entities/achievements.entity';
import { MatchRecordRepository } from 'src/game/matchRecord/matchRecord.repository';
import { MatchRecordDTO } from './dto/MatchRecord.dto';
import { JwtService } from '@nestjs/jwt';
import { jwtConfig } from 'src/auth/auth.module';

@Injectable()
export class UsersService {
	constructor(
		private userRepository: UserRepository,
		private achievementRepository: AchievementRepository,
		private MatchRecordRepository: MatchRecordRepository,
		private jwtService: JwtService
	) {}

	async AmIProtectedByTFA(cookie: string): Promise<void> {
		if (!cookie)
			throw new UnauthorizedException("You cannot access this page");

		const decodedToken: Users = await this.jwtService.verifyAsync(cookie, {secret: jwtConfig.secret});
		if (!decodedToken)
			throw new UnauthorizedException("Invalid Data");

		const user: Users = await this.userRepository.getOneUserByID(decodedToken.id);
		if (!user)
			throw new UnauthorizedException("Invalid User");
		else if (!user.bIsTFAEnabled)
			throw new BadRequestException("You cannot access this page because you are not using otp");
	}

	async getMyNickname(userID: number) : Promise<string> {
		if (undefined === userID)
			throw new UnauthorizedException("Invalid Data");

		try {
		const foundUser: Users = await this.userRepository.getOneUserByID(userID);
		if (!foundUser)
			throw new UnauthorizedException("Invalid ID");

		return (foundUser.login);
		} catch (err) {
			throw (err);
		}
	}

	async getAllHistories(nickname: string): Promise<MatchRecord[]> {
		if (!nickname)
			throw new BadRequestException("Invalid Data");
		
		try { 
		const foundUser: Users = await this.userRepository.getOneUserByLogin(nickname);
		if (!foundUser)
			throw new UnauthorizedException("Invalid Nickname");

		return (await this.MatchRecordRepository.getAllHistories(foundUser));
		} catch (err) {
			throw err;
		}
	}

	async getUserProfile(nickname: string): Promise<ProfileDTO> {
		if (!nickname)
			throw new UnauthorizedException("Invalid Data");

		try {
		const foundUser: Users = await this.userRepository.getOneUserByLogin(nickname);
		if (!foundUser)
			throw new UnauthorizedException("Invalid Nickname");
		
		let matchRecordDTO: MatchRecordDTO[] = null;
		const foundRecord: MatchRecord[] = await this.MatchRecordRepository.getAllHistories(foundUser);
		if (foundRecord) {
		matchRecordDTO = foundRecord.map(mr => ({
			date: mr.date,
			winner: mr.winnerName,
			winnerID: mr.winnerID,
			matchType: mr.matchType,
			player1Score: mr.player1Score,
			player2Score: mr.player2Score
		}));
		}

		const profile: ProfileDTO = {
			avatar: foundUser.avatar,
			rank: foundUser.rank,
			bIsTFAEnabled: foundUser.bIsTFAEnabled,
			achivements: foundUser.achievement,
			matchRecords: matchRecordDTO
		}
		return (profile);
		} catch (err) {
			throw (err);
		}
	}

	async uploadFile(user: Users, file: Express.Multer.File) {
		if (!user || !file)
			throw new BadRequestException("Invalid Data");

		const imagePos = imagePath + '/' + file.filename;
		try {
			const imageSize = sizeOf(imagePos);
			if (!imageSize)
				throw new BadRequestException("Something went wrong");
			else if (imageSize.height > 128 || imageSize.width > 128)
				throw new BadRequestException("The size of given image isn't 128*128");

			await this.userRepository.update(user.id, {
				avatar: file.filename
			});
		} catch (err) {
			fs.unlink(imagePos, (unlinkError) => {
				if (unlinkError) {
				  console.error('Error deleting file:', unlinkError);
				  return;
			}});
			throw (err);
		}
		return (file.filename);
	}

	async achieved(userID: number, name: string): Promise<Achievement> {
		if (undefined === userID || !name)
			throw new BadRequestException("Invalid Data");

		try {
			const user: Users = await this.userRepository.getOneUserByID(userID);
			if (!user)
				throw new UnauthorizedException("Invalid User");
			return (await this.achievementRepository.createAchievement(user, name));
		} catch (err) {
			throw (err);
		}
	}

	async updateRank(userID: number, isWinner: boolean, isDraw: boolean, isLadder: boolean): Promise<void> {
		if (undefined === userID || undefined === isWinner || undefined === isDraw || undefined === isLadder)
			throw new BadRequestException("update rank, Invalid Data");
	
		try {
			const user: Users = await this.userRepository.getOneUserByID(userID);
			if (!user)
				throw new UnauthorizedException("Invalid User");
			const ToUpdateRank: number = user.rank;
	
			if (isLadder) {
			if (isDraw)
				return (null);
			else if (isWinner) {
				await this.userRepository.updateRank(userID, user.rank + 1);
				await this.achieved(userID, "PWN!");
			}
			else
				await this.userRepository.updateRank(userID, user.rank - 1);
			}
		} catch (err) {
			throw (err);
		}
	}

	async createUser(user: FTUserTypes): Promise<Users> {
		if (!user)
			throw new BadRequestException("Invalid User");

		return (await this.userRepository.createUser(user));
	}

	async getOneUserByID(userID: number): Promise<Users> {
		if (undefined === userID)
			throw new BadRequestException("Invalid User");

		return (await this.userRepository.getOneUserByID(userID));
	}

	async getOneUserByLogin(login: string): Promise<Users> {
		if (!login)
			throw new BadRequestException("Invalid User");

		return (await this.userRepository.getOneUserByLogin(login));
	}

	async getOneUserByLoginID(loginID: string): Promise<Users> {
		if (!loginID)
			throw new BadRequestException("Invalid User");

		return (await this.userRepository.getOneUserByLoginID(loginID));
	}

	async updateAuthenticatedStatus(userID: number, status: boolean): Promise<void> {
		if (undefined === userID || undefined === status)
			throw new BadRequestException("Invalid Data");

		await this.userRepository.updateAuthenticatedStatus(userID, status);
	}

	async setTwoFactorAuthSecret(userID: number, secret: string): Promise<void> {
		if (undefined === userID || !secret)
			throw new BadRequestException("Invalid Data");

		await this.userRepository.setTwoFactorAuthSecret(userID, secret);
	}

	async unRegister(user: Users): Promise<void> {
		if (!user)
			throw new UnauthorizedException("Invalid User");

		await this.userRepository.remove(user);
	}

	async turnOFFTFA(user: Users): Promise<void> {
		if (!user)
			throw new UnauthorizedException("Invalid User");

		await this.userRepository.setTwoFactorAuthSecret(user.id, null);
		await this.userRepository.updateTwoFactorEnableStatus(user.id, false);
		await this.userRepository.updateAuthenticatedStatus(user.id, false);
	}

	async turnOnTFA(user: Users): Promise<void> {
		if (!user)
			throw new UnauthorizedException("Invalid User");

		await this.userRepository.updateTwoFactorEnableStatus(user.id, true);
		await this.achieved(user.id, "I'm not a robot, trust me pls");
	}
}

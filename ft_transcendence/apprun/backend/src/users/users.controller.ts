import { BadRequestException, Body, Controller, Get, Param, Post, Query, Req, Res, StreamableFile, UploadedFile, UseFilters, UseGuards, UseInterceptors } from '@nestjs/common';
import { Users } from './entities/users.entity';
import { UsersService } from './users.service';
import { ProfileDTO } from './dto/Profile.dto';
import { AuthGuard } from '@nestjs/passport';
import { GetUser } from 'src/auth/get-user.decorator';
import { MatchRecord } from '../game/matchRecord/matchRecord.entity';
import { FileInterceptor } from '@nestjs/platform-express';
import { Response as exRes, Request as exReq } from 'express';
import { cookieName } from 'src/auth/auth.service';
import * as fs from 'fs';
import * as path from 'path';

@Controller('users')
export class UsersController {
	constructor(
		private usersService: UsersService
	) {}

	@Get('/AmIProtectedByTFA')
	async AmIProtectedByTFA(
		@Req() req: exReq,
		@Res() res: exRes
	): Promise<void> {
		await this.usersService.AmIProtectedByTFA(req.headers.cookie.match(cookieName).input.split('=')[1]);
	}

	@Get('/mynick')
	@UseGuards(AuthGuard())
	async getMyNick(
		@GetUser() user: Users
	): Promise<string> {
		return (user.login);
	}

	@Get('/avatar/:filename')
	@UseGuards(AuthGuard())
	async getImage(
		@Param('filename') filename: string,
		@Res() res: exRes
	 ) {
		if (!filename)
			throw new BadRequestException("Unknkown filename");
		const imagePath = path.join(process.cwd(), '/images', filename);
		try {
			const file = fs.readFileSync(imagePath);
			res.send(file);
		} catch (err) {
			throw (err);
		}
	}

	@Get('/profile')
	async getProfile(
		@Query('nickname') nickname: string
	): Promise<ProfileDTO> {
		return (await this.usersService.getUserProfile(nickname));
	}

	@Get('/histories')
	async getHistories(
		@Body('nickname') nickname: string
	): Promise<MatchRecord[]> {
		return (await this.usersService.getAllHistories(nickname));
	}

	@Post('/avatar')
	@UseInterceptors(FileInterceptor('avatar'))
	@UseGuards(AuthGuard())
	async uploadFile(
		@GetUser() user: Users,
		@UploadedFile() file: Express.Multer.File
	): Promise<string> {
		return (await this.usersService.uploadFile(user, file));
	}
}

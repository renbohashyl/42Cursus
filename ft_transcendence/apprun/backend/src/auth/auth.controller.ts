import { Body, Controller, Delete, Get, Patch, Post, Query, Req, Res, UnauthorizedException, UseGuards } from '@nestjs/common';
import { AuthService, cookieName } from './auth.service';
import { AuthGuard } from '@nestjs/passport';
import { GetUser } from './get-user.decorator';
import { Users } from '../users/entities/users.entity';
import { FTUserTypes } from 'src/auth/oauth/dto/oauth_user.dto';
import { OauthService } from './oauth/oauth.service';
import { ConfigService } from '@nestjs/config';
import { Request as exReq, Response as exRes } from 'express';
import * as config from 'config';

@Controller('auth')
export class AuthController {
	constructor(
		private authService: AuthService,
		private oAuthService: OauthService,
		configService: ConfigService
	) {}

	@Get('/getcode')
	async oauth_pass(
		@Query('code') code: string,
		@Req() req: exReq,
		@Res() res: exRes
	) : Promise<void> {
		let accessToken: string = null;
		let otp: boolean = false;

		const user: FTUserTypes = await this.oAuthService.get42Info(code);
		const foundUser: Users = await this.authService.tryFind(user);

		if (!foundUser) {
			const regiteredUser = await this.authService.register(user);
			accessToken = await this.authService.generateAccessToken(regiteredUser);
		} else {
			otp = foundUser.bIsTFAEnabled;
			accessToken = await this.authService.generateAccessToken(foundUser, false, foundUser.bIsTFAEnabled);
		}
		const url = new URL(`${req.protocol}:${req.hostname}`);
		url.port = config.get('FEServer.port');
		if (otp) {
			url.pathname = config.get('FEServer.otppage');
		} else {
			url.pathname = config.get('FEServer.mainpage');
			const tempToken: string = await this.authService.authenticate(accessToken, null);
			accessToken = tempToken;
		}
		res.cookie(cookieName, accessToken);
		res.status(302).redirect(url.href);
	}

	@Get('/generate-2fa')
	@UseGuards(AuthGuard())
	async generateTFA(@Res() res: Response, @GetUser() user: Users) {
		const { otpAuthUrl } = await this.authService.generateTwoFactorAuth(user);

		return (await this.authService.pipeQrCodeStream(res, otpAuthUrl));
	}

	@Post('/authenticate')
	async authenticate(
		@Req() req: exReq,
		@Res() res: exRes,
		@Body('code') code: string
	) : Promise<void> {
		const Token: string = req.headers.cookie.match(cookieName).input.split('=')[1];
		const tempToken: string = await this.authService.authenticate(Token, code);

		res.cookie(cookieName, tempToken);
		res.status(200).send();
	}

	@Post('/logout')
	@UseGuards(AuthGuard())
	async logOut(
		@GetUser() user: Users,
		@Req() req: exReq,
		@Res() res: exRes
	) : Promise<void> {
		await this.authService.logOut(user, req, res);
	}

	@Post('/turn-on-2fa')
	@UseGuards(AuthGuard())
	async turnOnTFA(
		@GetUser() user: Users,
		@Body('code') code: string
	) : Promise<void> {
		if (false == await this.authService.isTFACodeValidate(user, code))
			throw new UnauthorizedException('Invalid Authentication-Code');

		return (this.authService.turnOnTFA(user));
	}

	@Post('/turn-off-2fa')
	@UseGuards(AuthGuard())
	async turnOffTFA(
		@GetUser() user: Users,
		@Body('code') code: string
	) : Promise<void> {
		if (false == await this.authService.isTFACodeValidate(user, code))
			throw new UnauthorizedException('Invalid Authentication-Code');

		return (this.authService.turnOffTFA(user));
	}

	@Post('/unregister')
	@UseGuards(AuthGuard())
	async unRegister(
		@GetUser() user: Users,
		@Req() req: exReq,
		@Res() res: exRes
	) : Promise<void> {
		await this.authService.unRegister(user, req, res);
	}
}
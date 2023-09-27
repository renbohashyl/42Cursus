import { BadRequestException, Injectable, UnauthorizedException } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { Users } from '../users/entities/users.entity';
import { authenticator } from 'otplib';
import * as config from "config";
import { TwoFactorAuthDTO } from './dto/TwoFactorAuth.dto';
import { toFileStream } from 'qrcode';
import { FTUserTypes } from 'src/auth/oauth/dto/oauth_user.dto';
import { ConfigService } from '@nestjs/config';
import { Request, Response as exRes } from 'express';
import { UsersService } from 'src/users/users.service';

export const cookieName: string = "CHOTENGENTOPPA";

@Injectable()
export class AuthService {
	constructor(
		private userService: UsersService,
		private jwtService: JwtService,
		configService: ConfigService
	) {}

	async register(user: FTUserTypes) : Promise<Users> {
		if (!user)
			throw new BadRequestException("register, Invalid Data");

		return (await this.userService.createUser(user));
	}

	async tryFind(user: FTUserTypes | Users) : Promise<Users> {
		if (!user)
			throw new BadRequestException("Invalid User");

		try {
			return (await this.userService.getOneUserByLoginID(user.loginID));
		} catch (err) {
			return (null);
		}
	}

	async logIn(user: Users) : Promise<string> {
		if (!user)
			throw new BadRequestException("Invalid User");

		try {
		const accessToken = await this.generateAccessToken(user, user.bIsTFAuthenticated);

		return (accessToken);
		} catch (err) {
			throw (err);
		}
	}

	async logOut(user: Users, req:Request, res: exRes) : Promise<void> {
		if (!user)
			throw new BadRequestException("logout, Invalid Data");

		try {
		await this.userService.updateAuthenticatedStatus(user.id, false);
		const url = new URL(`${req.protocol}:${req.hostname}`);
		url.port = config.get('FEServer.port');
		res.clearCookie(cookieName);
		res.status(200).send(url.href + "/login");
		} catch (err) {
			throw (err);
		}
	}

	async unRegister(user: Users, req: Request, res: exRes) : Promise<void> {
		if (!user)
			throw new BadRequestException("unregister, Invalid Data");

		await this.logOut(user, req, res);
		await this.userService.unRegister(user);
	}

	async generateTwoFactorAuth(user: Users) : Promise<TwoFactorAuthDTO> {
		if (!user)
			throw new BadRequestException("generate2fa, Invalid Data");
		else if (user.bIsTFAEnabled)
			throw new BadRequestException("already activated");

		try {
		const secret = authenticator.generateSecret();
		const otpAuthUrl = authenticator.keyuri(user.loginID, config.get('tfa.appName'), secret);

		await this.userService.setTwoFactorAuthSecret(user.id, secret);

		return ({secret, otpAuthUrl, code: ""});
		} catch (err) {
			throw new BadRequestException(err.message);
		}
	}

	async authenticate(accessToken: string, code: string): Promise<string> {
		if (!accessToken || undefined === code)
			throw new BadRequestException("authenticate, Invalid Data");

		try {
			const decodedToken: Users = await this.jwtService.verifyAsync(accessToken);
			const user = await this.userService.getOneUserByID(decodedToken.id);
		
			if (!user)
				throw new BadRequestException('Did you pwned?');

			else if (!user.bIsTFAEnabled)
				return (this.logIn(user));

			if (false == await this.isTFACodeValidate(user, code))
				throw new UnauthorizedException('Invalid Authentication code');

			await this.userService.updateAuthenticatedStatus(user.id, true);

			return (this.logIn(user));
		} catch (err) {
			throw err;
		}
	}

	async turnOnTFA(user: Users) : Promise<void> {
		if (!user)
			throw new UnauthorizedException("turnon2fa, Invalid User");
		else if (user.bIsTFAEnabled)
			throw new BadRequestException("already activated");

		try {
			await this.userService.turnOnTFA(user);
		} catch (err) {
			throw (err);
		}
	}

	async turnOffTFA(user: Users) : Promise<void> {
		if (!user)
			throw new UnauthorizedException("turnoff2fa, Invalid User");
		else if (user.bIsTFAEnabled === false)
			throw new BadRequestException("already deactivated");

		try {
		await this.userService.turnOFFTFA(user);
		} catch (err) {
			throw (err);
		}
	}

	async pipeQrCodeStream(stream: Response, otpAuthUrl: string): Promise<void> {
		if (!stream || !otpAuthUrl)
			throw new BadRequestException("cannot make QRCode, Invalid Data");
		return (toFileStream(stream, otpAuthUrl));
	}

	async isTFACodeValidate(user: Users, token: string) {
		if (!user.TFASecret)
			return false;
		else if (!user || !token)
			throw new UnauthorizedException("tfacode, Invalid Data");

		return authenticator.verify({token, secret: user.TFASecret});
	}

	async generateAccessToken(user: Users, bIsTFAuthenticated: boolean = false, oauthToken: boolean = false): Promise<string> {
		if (!user)
			throw new UnauthorizedException("generateToken, Invalid Data");

		const { id } = user;
		const payload = { id, bIsTFAuthenticated, oauthToken };
		return (this.jwtService.signAsync(payload));
	}
}

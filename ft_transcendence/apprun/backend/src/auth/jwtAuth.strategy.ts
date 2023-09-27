import { BadRequestException, Injectable, UnauthorizedException } from "@nestjs/common";
import { PassportStrategy } from "@nestjs/passport";
import { ExtractJwt, Strategy } from "passport-jwt";
import { UserRepository } from "../users/repositories/user.repository";
import { ConfigService } from "@nestjs/config";
import * as config from 'config';
import { Users } from "../users/entities/users.entity";
import { Request as exReq } from "express";

@Injectable()
export class JwtAuthStrategy extends PassportStrategy(Strategy)
{
	constructor (
		private userRepository: UserRepository,
		configService: ConfigService
	) {
		super({
			secretOrKey: config.get('jwt.secret'),
			jwtFromRequest: ExtractJwt.fromExtractors([
				JwtAuthStrategy.extractJWT,
				ExtractJwt.fromAuthHeaderAsBearerToken(),
			]),
			ignoreExpiration: false
		})
	}

	private static extractJWT(req: exReq): string | null {
		try {
		const accessToken: string = req.headers.cookie.split(';')[0].split('=')[1];

		return (accessToken);
		} catch (err) {
			throw new BadRequestException('something went wrong!!');
		}
	}

	async validate(payload) {
		if (payload.oauthToken)
			throw new BadRequestException('Did you pwned?');

		const user: Users = await this.userRepository.getOneUserByID(payload.id);

		if (!user)
			throw new UnauthorizedException('Invalid Token');
		else if (user)
			return (user);
		else if (user.bIsTFAEnabled && user.bIsTFAuthenticated === false)
			throw new UnauthorizedException('You are not authenticated with 2fa');

		throw new BadRequestException('Did you pwned?');
	}
}
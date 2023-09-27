import { Injectable, UnauthorizedException } from '@nestjs/common';
import * as config from 'config';
import { ConfigService } from '@nestjs/config';
import axios, { AxiosResponse } from 'axios';
import { FTUserTypes } from './dto/oauth_user.dto';

@Injectable()
export class OauthService {
	constructor(configService: ConfigService) { }

	public async get42Info(code: string): Promise<FTUserTypes> {
		if (!code)
			throw new UnauthorizedException("get42Info, Invalid code");

		const getTokenUrl: string = "https://api.intra.42.fr/oauth/token";
		const getUserUrl: string = 'https://api.intra.42.fr/v2/me';

		const request = {
			grant_type: 'authorization_code',
			client_id: config.get<string>('oauth.client_id'),
			client_secret: config.get<string>('oauth.client_secret'),
			code,
			redirect_uri: config.get<string>('oauth.redirect_uri')
		}

		try {
			const response: AxiosResponse = await axios.post(
				getTokenUrl,
				request
			);

			if (response.data.error) {
				console.log(response.data.error);
				throw new UnauthorizedException('failed to axios post with 42');
			}

			const { access_token } = response.data;
			const { data } = await axios.get(
				getUserUrl,
				{ headers: { Authorization: `Bearer ${access_token}` } }
			);

			const { email, login, first_name, last_name } = data;

			const ftUser: FTUserTypes = {
				email,
				login,
				loginID: login,
				first_name,
				last_name
			};

			return (ftUser);
		} catch (err) {
			throw new UnauthorizedException('Failed to auth with 42');
		}
	}
}

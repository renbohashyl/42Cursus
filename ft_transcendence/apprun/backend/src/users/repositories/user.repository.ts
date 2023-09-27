import { DataSource, Repository, UpdateResult, EntityRepository } from "typeorm";
import { Users } from "../entities/users.entity";
import { BadRequestException, ConflictException, InternalServerErrorException, UnauthorizedException } from "@nestjs/common";
import { FTUserTypes } from "src/auth/oauth/dto/oauth_user.dto";
import { ConfigService } from "@nestjs/config";

@EntityRepository()
export class UserRepository extends Repository<Users> {
	constructor(
		private dataSource: DataSource,
		configService: ConfigService
	) {
		super(Users, dataSource.createEntityManager());
	}

	async createUser(userDTO: FTUserTypes | Users) : Promise<Users> {
		if (!userDTO)
			throw new BadRequestException("Invalid Data");

		try {
		const oneUser = this.create({
			login: userDTO.login,
			loginID: userDTO.loginID,
			first_name: userDTO.first_name,
			last_name: userDTO.last_name,
			avatar: 'default'
		});

			await this.save(oneUser);
			return (oneUser);
		} catch (e) {
			if (e.code === '23505') {
				throw new ConflictException("that name is already in use");
			} else {
				throw new BadRequestException("Invalid Data");
			}
		}
	}

	async updateUserNickname(userID: number, newNickname: string): Promise<UpdateResult> {
		if (undefined === userID || undefined === newNickname)
			throw new BadRequestException("Invalid Data");

		try {
			return (await this.update(userID, {
				login: newNickname,
			}));
		} catch (err) {
			if (err.code === '23505')
				throw new ConflictException("that name is already in use");
			else
				throw new InternalServerErrorException("Something went wrong");
		}
	}

	async setTwoFactorAuthSecret(userID: number, secret: string): Promise<UpdateResult> {
		if (undefined === userID || undefined === secret)
			throw new BadRequestException("Invalid Data");

		try {
			return (await this.update(userID, {
			TFASecret: secret,
			}));
		} catch (err) {
			throw (err);
		}
	}

	async updateAuthenticatedStatus(userID: number, status: boolean) : Promise<UpdateResult> {
		if (undefined === userID || undefined === status)
			throw new BadRequestException("Invalid Data");

		try {
			return (await this.update(userID, {
				bIsTFAuthenticated: status
			}));
		} catch (err) {
			throw (err);
		}
	}

	async updateTwoFactorEnableStatus(userID: number, status: boolean) : Promise<UpdateResult> {
		if (undefined === userID || undefined === status)
			throw new BadRequestException("Invalid Data");

		try {
			return (await this.update(userID, {
				bIsTFAEnabled: status
			}));
		} catch (err) {
			throw (err);
		}
	}

	async setStatus(userID: number, status: string): Promise<UpdateResult> {
		if (undefined === userID || undefined === status)
			throw new BadRequestException("Invalid Data");

		try {
			return (await this.update(userID, {
				socketStatus: status
			}));
		} catch (err) {
			throw (err);
		}
	}

	async updateRank(userID: number, rank: number): Promise<UpdateResult> {
	if (undefined === userID || undefined === rank)
		throw new BadRequestException("update rank, Invalid Data");
	
	return (await this.update(userID, {rank}));
	}

	async getOneUserByID(userID: number): Promise<Users> {
		if (undefined === userID)
			throw new UnauthorizedException("Invalid user data");
		const foundUser: Users = await this.findOne({where: {id: userID}});
		if (!foundUser)
			throw new UnauthorizedException("Invalid user data");
		return (foundUser);
	}

	async getOneUserByLogin(login: string): Promise<Users> {
		if (undefined === login)
			throw new UnauthorizedException("Invalid user data");
		const foundUser: Users = await this.findOne({where: {login: login}});
		if (!foundUser)
			throw new UnauthorizedException("Invalid user data");
		return (foundUser);
	}

	async getOneUserByLoginID(loginID: string): Promise<Users> {
		if (undefined === loginID)
			throw new UnauthorizedException("Invalid user data");
		const foundUser: Users = await this.findOne({where: {loginID: loginID}});
		if (!foundUser)
			throw new UnauthorizedException("Invalid user data");
		return (foundUser);
	}
}
import { BadRequestException, Injectable, UnauthorizedException } from "@nestjs/common";
import { AchievementRepository } from "./repositories/achievements.repository";
import { UserRepository } from "./repositories/user.repository";
import { Achievement } from "./entities/achievements.entity";
import { Users } from "./entities/users.entity";

@Injectable()
export class AchievementService {
	constructor(
		private achievementRepository: AchievementRepository,
		private userRepository: UserRepository
	) {}

	async createAchievement(userID: number, name: string): Promise<Achievement> {
		if (undefined === userID || !name)
			throw new BadRequestException("Invlid Data");

		const user: Users = await this.userRepository.getOneUserByID(userID);
		if (!user)
			throw new UnauthorizedException("Invalid User");

		return (await this.achievementRepository.createAchievement(user, name));
	}
}
import { DataSource, EntityRepository, Repository } from "typeorm";
import { Achievement } from "../entities/achievements.entity";
import { Users } from "../entities/users.entity";
import { BadRequestException } from "@nestjs/common";

@EntityRepository()
export class AchievementRepository extends Repository<Achievement> {
	constructor(
		private dataSource: DataSource,
	) {
		super(Achievement, dataSource.createEntityManager());
	}

	async createAchievement(user: Users, name: string): Promise<Achievement> {
		if (undefined === user || undefined === name)
			throw new BadRequestException("Invalid Data");

		try {
		const checkOne: Achievement = await this.findOne({where: {
			achivementName: name,
			user: {id: user.id}
		}});
		if (checkOne)
			return ;

		const newOne: Achievement = this.create({
			user,
			achivementName: name,
			date: new Date()
		});

		return (await this.save(newOne));
		} catch (err) {
			throw (err);
		}
	}

	async getAllAchievementByOneUser(user: Users): Promise<Achievement[]> {
		if (undefined === user)
			throw new BadRequestException("Invalid Data");

		try {
		return (
		await this.find({
			where: {
				user: { id: user.id }
			}
		})
		);

		} catch (err) {
			throw (err);
		}
	}
}
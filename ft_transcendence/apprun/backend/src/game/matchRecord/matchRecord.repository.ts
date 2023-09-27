import { DataSource, EntityRepository, Repository } from "typeorm";
import { MatchRecord } from "./matchRecord.entity";
import { Users } from "src/users/entities/users.entity";
import { BadRequestException } from "@nestjs/common";

@EntityRepository(MatchRecord)
export class MatchRecordRepository extends Repository<MatchRecord> {
	constructor(private dataSource: DataSource) {
		super(MatchRecord, dataSource.createEntityManager());
	}

	async getAllHistories(
		user: Users
	) : Promise<MatchRecord[]> {
		if (!user)
			throw new BadRequestException("Invalid Data");

		try {
			const query = this.createQueryBuilder('MatchRecord');
			query.where('MatchRecord.player1 = :id OR MatchRecord.player2 = :id', { id: user.id } );

			return (await query.getMany());
		} catch (err) {
			throw (err);
		}
	}
}
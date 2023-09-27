import { DataSource, EntityRepository, Repository } from "typeorm";
import { Channel } from "../entities/channel.entity";

@EntityRepository(Channel)
export class ChannelRepository extends Repository<Channel> {
	constructor(private dataSource: DataSource) {
		super(Channel, dataSource.createEntityManager());
	}
}
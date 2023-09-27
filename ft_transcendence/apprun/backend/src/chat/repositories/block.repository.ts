import { DataSource, DeleteResult, EntityRepository, Repository } from "typeorm";
import { BadRequestException, UnauthorizedException } from "@nestjs/common";
import { Block } from "../entities/block.entity";
import { Users } from "src/users/entities/users.entity";
import { UserRepository } from "src/users/repositories/user.repository";

@EntityRepository(Block)
export class BlockRepository extends Repository<Block> {
	constructor(
		private dataSource: DataSource,
		private readonly userRepository: UserRepository
	) {
		super(Block, dataSource.createEntityManager());
	}

	async addBlock(requestor: number, nick: string)
	: Promise<Block>
	{
		if (undefined === requestor || !nick)
			throw new BadRequestException("cannot find that user");

		const isBlocked: Block = await this.findOne({where: {blocked: {login: nick}}});
		const blockedUser: Users = await this.userRepository.getOneUserByLogin(nick);
		if (!blockedUser)
			throw new BadRequestException("cannot find that user");
		if (isBlocked)
			throw new UnauthorizedException('already blocked');

		const WOULDBLOCK: Block = this.create({
			blocked: blockedUser,
			blocker: {id: requestor}
		});
		try {
			return (await this.save(WOULDBLOCK));
		} catch (err) {
			throw new BadRequestException("save failed :(");
		}
	}

	async unBlock(requestor: number, nick: string)
	: Promise<Block>
	{
		if (undefined === requestor || !nick)
			throw new BadRequestException("cannot find that user");

		const ToDeleteBlock: Block = await this.findOne({where : {
			blocked: {login: nick},
			blocker: {id: requestor}
		}})

		try {
			return (await this.remove(ToDeleteBlock));
		} catch (err) {
			throw new BadRequestException("delete failed :(");
		}
	}

	async getAlliBlocks(requestor: number)
	: Promise<string[]>
	{
		if (undefined === requestor)
			throw new BadRequestException("cannot find that user");

		const blocklist: Block[] = await this.find({where: {blocker: {id: requestor}}});
		const iblocks: string[] = blocklist.map(block => block.blocked.login);
		return (iblocks);
	}
}
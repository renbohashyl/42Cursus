import { DataSource, DeleteResult, EntityRepository, Repository } from "typeorm";
import { BadRequestException } from "@nestjs/common";
import { Friend } from "../entities/friend.entity";
import { UserRepository } from "src/users/repositories/user.repository";
import { Users } from "src/users/entities/users.entity";

export class iFriends {
	nick: string;
	status: string;
}

@EntityRepository(Friend)
export class FriendRepository extends Repository<Friend> {
	constructor(
		private dataSource: DataSource,
		private readonly userRepository: UserRepository
	) {
		super(Friend, dataSource.createEntityManager());
	}

	async subScribeFriend(requestor: number, nick: string): Promise<Friend> {
		if (undefined === requestor || !nick)
			throw new BadRequestException("cannot find that user");

		try {
		const isFriend: Friend = await this.findOne({where: {subscribedUser: {login: nick}}});
		const user: Users = await this.userRepository.getOneUserByLogin(nick);
		if (!user)
			throw new BadRequestException("cannot find that user");
		if (isFriend)
			throw new BadRequestException("he is your friend already");

		const ToSubUser: Friend = this.create({
			subscriber: {id: requestor},
			subscribedUser: user
		});

		
			return (await this.save(ToSubUser));
		} catch (err) {
			console.log(err);
			throw new BadRequestException("save failed :(");
		}
	}

	async deleteFriend(requestor: number, nick: string): Promise<Friend> {
		if (undefined === requestor || !nick)
			throw new BadRequestException("cannot find that user");

		try {
		const ToDeleteFriend: Friend = await this.findOne({
			where: {
				subscribedUser: {login: nick},
				subscriber: {id: requestor}
			}
		})

			return (await this.remove(ToDeleteFriend));
		} catch (err) {
			throw new BadRequestException("delete failed :(");
		}
	}

	async getAlliFriends(requestor: number): Promise<iFriends[]> {
		if (undefined === requestor)
			throw new BadRequestException("cannot find that user");

		const friends: Friend[] = await this.find({where: {subscriber: {id : requestor}}});
		const iFriends: iFriends[] = friends.map(friend => ({
			nick: friend.subscribedUser.login,
			status: friend.subscribedUser.socketStatus
		}));
		return (iFriends);
	}

	async getSubscribedUser(requested: number): Promise<iFriends[]> {
		if (undefined === requested)
			throw new BadRequestException("cannot find that user");

		const friends: Friend[] = await this.find({where: {subscribedUser: {id: requested}}});
		const iFriends: iFriends[] = friends.map(friend => ({
			nick: friend.subscriber.login,
			status: friend.subscribedUser.socketStatus
		}));
		return (iFriends);
	}
}
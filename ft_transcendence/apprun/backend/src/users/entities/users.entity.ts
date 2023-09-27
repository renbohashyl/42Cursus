
import { BaseEntity, Column, Entity, ManyToOne, OneToMany, PrimaryGeneratedColumn, Unique } from "typeorm";
import { MatchRecord } from "../../game/matchRecord/matchRecord.entity";
import { UserChannel } from "src/chat/entities/userChannel.entity";
import { Block } from "src/chat/entities/block.entity";
import { Friend } from "src/chat/entities/friend.entity";
import { Channel } from "src/chat/entities/channel.entity";
import { Achievement } from "./achievements.entity";

@Entity()
export class Users extends BaseEntity {
	@PrimaryGeneratedColumn()
	id: number;

	@Column({unique: true})
	login: string;

	@Column({unique: true})
	loginID: string;

	@Column()
	first_name: string;

	@Column()
	last_name: string;

	@Column({default: 'offline'})
	socketStatus: string;

	@Column({default: "nothing"})
	avatar: string;

	@Column({default: 0})
	rank: number;

	@Column({nullable: true})
	TFASecret: string;

	@Column({default: false})
	bIsTFAEnabled: boolean;

	@Column({default: false})
	bIsTFAuthenticated: boolean;

	@OneToMany(type => MatchRecord, MatchRecord => MatchRecord.player1 )
	recordsAsPlayer1: MatchRecord[];

	@OneToMany(type => MatchRecord, MatchRecord => MatchRecord.player2)
	recordsAsPlayer2: MatchRecord[];

	@OneToMany(type => Channel, ownChannel => ownChannel.owner)
	ownChannels: Channel[]

	@OneToMany(type => UserChannel, userChannels => userChannels.user, { cascade: true })
	userChannels: UserChannel[];

	@OneToMany(() => Block, blockList => blockList.blocker, { cascade: true })
	blockedUser: Block[];

	@OneToMany(() => Block, blockList => blockList.blocked, { cascade: true })
	blockedByUser: Block[];

	@OneToMany(() => Friend, blockList => blockList.subscriber, { cascade: true })
	Subscriber: Friend[];

	@OneToMany(() => Friend, blockList => blockList.subscribedUser, { cascade: true })
	SubscribedByUser: Friend[];

	@OneToMany(() => Achievement, achievement => achievement.user, { cascade: true, eager: true })
	achievement: Achievement[];
}
import { Users } from "src/users/entities/users.entity";
import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import { Channel } from "./channel.entity";

export enum eRole {
	OWNER = 'OWNER',
	ADMIN = 'ADMIN',
	MEMBER = 'MEMBER',
	BANNED = 'BANNED'
}

@Entity()
export class UserChannel extends BaseEntity {
	@PrimaryGeneratedColumn()
	id: number;

	@ManyToOne(() => Users, user => user.userChannels, {onDelete: 'CASCADE', eager : true})
	user: Users;

	@ManyToOne(() => Channel, channel => channel.userChannels, {onDelete: 'CASCADE', eager: true})
	channel: Channel;

	@Column()
	role: eRole;

	@Column({default: false})
	muted: boolean;

	@Column({default: false})
	banned: boolean;
}
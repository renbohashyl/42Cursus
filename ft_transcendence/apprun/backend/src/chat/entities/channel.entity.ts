import { BaseEntity, Column, Entity, ManyToOne, OneToMany, PrimaryGeneratedColumn } from "typeorm";
import { UserChannel } from "./userChannel.entity";
import { Users } from "src/users/entities/users.entity";

@Entity()
export class Channel extends BaseEntity {
	@PrimaryGeneratedColumn()
	id: number;

	@Column()
	roomID: number;

	@Column()
	roomIDstr: string;

	@Column()
	isProtected: boolean;

	@Column({default: true})
	isOpened: boolean;

	@Column()
	name: string;

	@Column()
	password: string
	
	@Column({default: 0})
	userCount: number;

	@Column({default: 0})
	banCount: number;

	@ManyToOne(type => Users, users => users.ownChannels, { onDelete: 'SET NULL', nullable: true, eager: true })
	owner: Users;

	@OneToMany(type => UserChannel, userChannels => userChannels.channel, { cascade: true })
	userChannels: UserChannel[];
}
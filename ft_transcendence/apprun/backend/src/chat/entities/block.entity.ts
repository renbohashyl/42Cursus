import { Users } from "src/users/entities/users.entity";
import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";

@Entity()
export class Block extends BaseEntity {
	@PrimaryGeneratedColumn()
	id: number;

	@ManyToOne(type=> Users, user => user.blockedUser, {onDelete: 'CASCADE', eager: true})
	blocker: Users;

	@ManyToOne(type=> Users, user => user.blockedByUser, {onDelete: 'CASCADE', eager: true})
	blocked: Users;

	@Column({nullable: true})
	reason: string;
}
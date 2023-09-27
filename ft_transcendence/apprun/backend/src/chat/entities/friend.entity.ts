import { Users } from "src/users/entities/users.entity";
import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";

@Entity()
export class Friend extends BaseEntity {
	@PrimaryGeneratedColumn()
	id: number;

	@ManyToOne(type=> Users, user => user.Subscriber, {onDelete: 'CASCADE', eager: true})
	subscriber: Users;

	@ManyToOne(type=> Users, user => user.SubscribedByUser, {onDelete: 'CASCADE', eager: true})
	subscribedUser: Users;
}
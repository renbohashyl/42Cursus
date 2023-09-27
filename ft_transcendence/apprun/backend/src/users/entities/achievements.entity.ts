import { Users } from "src/users/entities/users.entity";
import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";

@Entity()
export class Achievement extends BaseEntity {
	@PrimaryGeneratedColumn()
	id: number;

	@ManyToOne( type => Users, { onDelete: 'CASCADE' } )
	user: Users;

	@Column()
	achivementName: string;

	@Column({type: "timestamptz"})
	date: Date;
}
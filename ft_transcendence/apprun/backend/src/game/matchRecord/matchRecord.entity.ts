import { Users } from "src/users/entities/users.entity";
import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";

export enum eWinner {
	Player1 = 'Player1',
	Player2 = 'Player2',
	DRAW = 'Draw'
}

@Entity()
export class MatchRecord extends BaseEntity {
	@PrimaryGeneratedColumn()
	id: number;

	@Column({type: "timestamptz"})
	date: Date;

	@ManyToOne( type => Users, {onDelete: 'SET NULL'} )
	player1: Users;

	@ManyToOne( type => Users, {onDelete: 'SET NULL'} )
	player2: Users;

	@Column()
	winnerName: string;

	@Column()
	winnerID: string;

	@Column()
	winner: eWinner;

	@Column()
	matchType: string;

	@Column()
	player1Score: number;

	@Column()
	player2Score: number;
}
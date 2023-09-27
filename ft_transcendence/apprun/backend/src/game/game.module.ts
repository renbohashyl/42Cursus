import { Module } from '@nestjs/common';
import { GameGateway } from './game.gateway';
import { MatchRecordRepository } from 'src/game/matchRecord/matchRecord.repository';
import { MatchRecordService } from './matchRecord/matchRecord.service';
import { FriendRepository } from 'src/chat/repositories/friend.repository';
import { UsersModule } from 'src/users/users.module';

@Module({
	imports: [
		UsersModule
	],
	providers: [
		GameGateway,
		MatchRecordService,
		MatchRecordRepository,
		FriendRepository
	]
})
export class GameModule {}

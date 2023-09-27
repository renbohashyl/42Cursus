import { Module } from '@nestjs/common';
import { ChatGateway } from './chat.gateway';
import { UserRepository } from 'src/users/repositories/user.repository';
import { AuthModule } from 'src/auth/auth.module';
import { JwtService } from '@nestjs/jwt';
import * as config from 'config';
import { UserChannelsRepository } from './repositories/userChannel.repository';
import { ChannelRepository } from './repositories/Channel.repository';
import { BlockRepository } from './repositories/block.repository';
import { FriendRepository } from './repositories/friend.repository';

const jwtConfig = config.get('jwt');

@Module({
	imports: [
		AuthModule,
	],
	providers: [
		ChatGateway,
		UserRepository,
		UserChannelsRepository,
		ChannelRepository,
		BlockRepository,
		FriendRepository,
		JwtService,
	]
})
export class ChatModule {}

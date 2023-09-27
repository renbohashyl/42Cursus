import { Module } from '@nestjs/common';
import { UsersController } from './users.controller';
import { UsersService } from './users.service';
import { UserRepository } from './repositories/user.repository';
import { TypeOrmModule } from '@nestjs/typeorm';
import { MatchRecordService } from '../game/matchRecord/matchRecord.service';
import { MatchRecordRepository } from '../game/matchRecord/matchRecord.repository';
import { MulterModule } from '@nestjs/platform-express';
import { imageFileFilter, myDisk } from './multerOptions';
import { AchievementService } from './achievements.service';
import { AchievementRepository } from './repositories/achievements.repository';
import { AuthModule } from 'src/auth/auth.module';
import { JwtModule } from '@nestjs/jwt';

@Module({
	imports: [
		AuthModule,
		JwtModule,
		TypeOrmModule.forFeature([UserRepository]),
		TypeOrmModule.forFeature([AchievementRepository]),
		MulterModule.register({
			storage: myDisk,
			fileFilter: imageFileFilter,
			limits: {
				fileSize: 1024 * 1024
			}
		})
	],
	controllers: [UsersController],
	providers: [
		AchievementService, AchievementRepository,
		UsersService, UserRepository,
		MatchRecordService, MatchRecordRepository,
	],
	exports: [AchievementService, AchievementRepository,
			  UsersService, UserRepository]
})
export class UsersModule {}

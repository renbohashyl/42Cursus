import { Module } from '@nestjs/common';
import { AuthController } from './auth.controller';
import { AuthService } from './auth.service';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserRepository } from '../users/repositories/user.repository';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { ConfigModule } from '@nestjs/config';
import * as config from "config";
import { JwtAuthStrategy } from './jwtAuth.strategy';
import { OauthModule } from './oauth/oauth.module';
import { OauthService } from './oauth/oauth.service';
import { AchievementRepository } from 'src/users/repositories/achievements.repository';
import { AchievementService } from 'src/users/achievements.service';
import { UsersService } from 'src/users/users.service';
import { MatchRecordRepository } from 'src/game/matchRecord/matchRecord.repository';

export interface iJwtConfig{
  secret: string,
  expiresIn: number
}

export const jwtConfig = config.get<iJwtConfig>('jwt');

@Module({
  imports: [
    OauthModule,
    ConfigModule.forRoot({
      envFilePath: `${process.env.NODE_ENV}.env`,
      isGlobal: true
    }),
    PassportModule.register({ defaultStrategy: 'jwt' }),
    JwtModule.register({
        secret: jwtConfig.secret,
        signOptions: { expiresIn: process.env.JWT_EXP_TIME || jwtConfig.expiresIn }
    }),
    TypeOrmModule.forFeature([UserRepository]),
  ],
  controllers: [AuthController],
  providers: [
    OauthService,
    AuthService,
    UsersService, UserRepository,
    AchievementRepository, AchievementService,
    MatchRecordRepository,
    JwtAuthStrategy
  ],
  exports: [JwtAuthStrategy, PassportModule]
})
export class AuthModule {}

import { TypeOrmModuleOptions } from "@nestjs/typeorm";
import * as config from "config";

interface iDBConfig {
	type: 'postgres',
	port: number,
	database: string,
	host: string,
	username: string,
	password: string,
	synchronize: boolean
};

const dbConfig = config.get<iDBConfig>('db');

export const typeORMConfig : TypeOrmModuleOptions = {
	type: dbConfig.type,
	host: process.env.RDS_HOSTNAME || dbConfig.host,
	port: dbConfig.port,
	username: process.env.RDS_USERNAME || dbConfig.username,
	password: process.env.RDS_PASSWORD || dbConfig.password,
	database: process.env.RDS_DBNAME || dbConfig.database,
	autoLoadEntities: true,
	entities: [__dirname + '/../**/*.entity.{js,ts}'],
	synchronize: dbConfig.synchronize,
}
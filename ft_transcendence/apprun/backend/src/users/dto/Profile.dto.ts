import { Achievement } from "../entities/achievements.entity";
import { MatchRecordDTO } from "./MatchRecord.dto";

export class ProfileDTO {
	avatar: string;
	rank: number;
	bIsTFAEnabled: boolean;
	achivements: Achievement[];
	matchRecords: MatchRecordDTO[];
}
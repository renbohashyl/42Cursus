import { Controller, Get } from '@nestjs/common';

@Controller()
export class AppController {

	@Get('/healthcheck')
	helathcheck() : string {
		return ('i am healthy');
	}
}
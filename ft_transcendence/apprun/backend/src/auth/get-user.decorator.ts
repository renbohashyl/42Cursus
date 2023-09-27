import { ExecutionContext, createParamDecorator } from "@nestjs/common";
import { FTUserTypes } from "src/auth/oauth/dto/oauth_user.dto";

export const GetUser = createParamDecorator((data, ctx: ExecutionContext): FTUserTypes => {
	const req = ctx.switchToHttp().getRequest();
	return req.user;
})
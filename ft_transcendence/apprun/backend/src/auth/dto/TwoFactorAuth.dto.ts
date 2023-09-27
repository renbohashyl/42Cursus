export class TwoFactorAuthDTO
{
	secret: string;
	otpAuthUrl: string;
	code: string;
}
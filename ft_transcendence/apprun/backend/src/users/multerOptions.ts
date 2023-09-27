import { BadRequestException } from '@nestjs/common';
import { diskStorage } from 'multer';
import sizeOf from 'image-size';
import * as path from 'path';
import * as fs from 'fs';

export interface MulterOptions {
	dest?: string;
	storage: any;
	limits?: {};
	preservePath?: boolean;
	fileFilter?(
		req: any,
		file: {},
		callback: (error: Error | null, acceptFile: boolean) => void
	): void;
};

export const imagePath = path.join(process.cwd(), '/images');

//diskStorage
export const myDisk = diskStorage({
	destination: function (req, file, cb) {
		if(fs.existsSync(imagePath)) {
			fs.mkdirSync(imagePath, { recursive: true });
		}
		cb(null, imagePath)
	},
	filename: function (req, file, cb) {
		const uniqueSuffix = Date.now() + '-' + Math.round(Math.random() * 1E3)
		cb(null, uniqueSuffix)
	}
});

//imageFileFilter
export const imageFileFilter = (req, file: Express.Multer.File, callback) => {
	const allowedExt = ['.jpg', '.jpeg', '.png', '.gif'];
	const ext = path.extname(file.originalname);

	if (!allowedExt.includes(ext)) {
		callback(new BadRequestException('Only image files are allowed'), false);
	} else {
		callback(null, true);
	}
  
};
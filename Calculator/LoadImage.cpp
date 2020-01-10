#include "LoadImage.h"

My_LoadImage MyLoadImage;

IMAGE  My_LoadImage::setimage(int wigth, int height, COLORREF rgb, int a, int b)
{
	IMAGE blacks(wigth, height);	// 创建 img 对象

	SetWorkingImage(&blacks);		// 设置绘图目标为 img 对象
	setfillcolor(rgb);
	solidroundrect(0, 0, wigth, height, a, b);

	SetWorkingImage();				// 设置绘图目标为绘图窗口

	return blacks;
}
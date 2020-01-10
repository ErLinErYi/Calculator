#include "TransParent.h"

My_Putimage MyPutimage;

// copy img2 to img1
void My_Putimage::copy_img(IMAGE* img1, IMAGE* img2)
{
	IMAGE* now_working = GetWorkingImage();
	Resize(img1, img2->getwidth(), img2->getheight());
	SetWorkingImage(img2);
	getimage(img1, 0, 0, img1->getwidth(), img1->getheight());
	SetWorkingImage(now_working);
}

// 贴图函数
// 参数:
//		dstX,dstY:贴图横纵坐标
//		*pimg：图片指针
//		avoid_color：透明颜色
//		deviation：透明精细度
//		light：亮度加成（1 不变）
//		tp(transparency)：透明度，从 0 到 100
//		effect：效果（1 为反相，2 为黑白，其他为无）
void My_Putimage::my_putimage(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, double light, int tp, int effect)
{
	int x, y, num;
	int R, G, B;			// 记录贴图某点色彩
	// 记录排除颜色色彩
	int avoid_r = GetRValue(avoid_color);
	int avoid_g = GetGValue(avoid_color);
	int avoid_b = GetBValue(avoid_color);
	IMAGE pSrcImg;			// 背景图
	IMAGE tempimg;			// 临时贴图
	copy_img(&tempimg, pimg);
	SetWorkingImage(NULL);	// 对默认绘图窗口的绘图操作
	getimage(&pSrcImg, dstX, dstY, pimg->getwidth(), pimg->getheight());

	// 透明度容错
	if (tp < 0)tp = 0;
	else if (tp > 100)tp = 100;

	// 获取背景指向显存的指针
	DWORD* bk_pMem = GetImageBuffer(&pSrcImg);

	// 贴图指向显存的指针
	DWORD* pMem = GetImageBuffer(&tempimg);
	for (y = 0; y < pimg->getheight(); y++)
	{
		for (x = 0; x < pimg->getwidth(); x++)
		{
			num = y * pimg->getwidth() + x;
			R = GetRValue(pMem[num]);
			G = GetGValue(pMem[num]);
			B = GetBValue(pMem[num]);
			if ((abs(R - avoid_r) <= deviation) && (abs(G - avoid_g) <= deviation) && (abs(B - avoid_b) <= deviation))
			{
				pMem[num] = bk_pMem[num];
			}
			else
			{
				if (light > 0 && light < 1)
				{
					R = int(R * light);
					G = int(G * light);
					B = int(B * light);
				}
				else if (light > 1)
				{
					R = min(int(R * light), 255);
					G = min(int(G * light), 255);
					B = min(int(B * light), 255);
				}
				if (effect == 1)//反相
				{
					pMem[num] = 0xffffff - pMem[num];
					continue;
				}
				else if (effect == 2)//黑白
				{
					R = G = B = int(R * 0.299 + G * 0.587 + B * 0.114);
				}
				pMem[num] = RGB((R * tp + GetRValue(bk_pMem[num]) * (100 - tp)) / 100,
								(G * tp + GetGValue(bk_pMem[num]) * (100 - tp)) / 100,
								(B * tp + GetBValue(bk_pMem[num]) * (100 - tp)) / 100);
			}
		}
	}
	putimage(dstX, dstY, &tempimg);
}
#pragma once
#include<easyx.h>
#define MyChar TCHAR

class My_LoadImage
{

public:
	My_LoadImage() {};
	~My_LoadImage() {};
	// 指定绘图设备
	IMAGE setimage(int wigth, int height, COLORREF rgb, int a = 0, int b = 0);	
};

extern My_LoadImage MyLoadImage;

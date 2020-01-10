#pragma once
#include <math.h>
#include <conio.h>
#include <graphics.h>

class My_Putimage
{
private:
	// copy img2 to img1
	void copy_img(IMAGE* img1, IMAGE* img2);
public:
	My_Putimage() {};
	~My_Putimage() {};
	// 贴图函数
	// 参数:
	//		dstX,dstY:贴图横纵坐标
	//		*pimg：图片指针
	//		avoid_color：透明颜色
	//		deviation：透明精细度
	//		light：亮度加成（1 不变）
	//		tp(transparency)：透明度，从 0 到 100
	//		effect：效果（1 为反相，2 为黑白，其他为无）
	void my_putimage(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, double light, int tp, int effect);
};

extern My_Putimage MyPutimage;




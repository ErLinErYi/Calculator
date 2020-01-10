#pragma once
#include <stack>
#include <easyx.h>
#include <iostream>
#include "Option.h"
#include "Bignumber.h"
#include "WindowMessage.h"
#include "Transformation.h"

class Conversion
{
private:
	void conversion(MyChar *sss, long long x, int n);      //利用栈进行进制转换
	void memse();                                          //初始化
	bool input(int n);
	void everone(int n = 2);                               //分别计算各个进制
	void updatewithinput3();                               //进制转换：与输入有关的更新
	void showscreen3();                                    //进制转换：显示函数

public:
	void ConversionFuction(int &);
	void changecolor(
		int Left, int Right, int Top, int Bottom,
		float l = 0.0008f, float k = 1.0f,
		bool t = false
	);                                  //改变颜色
	void Setcolor(
		int Left, int Right, int Top, int Bottom,
		COLORREF rgb = RGB(50, 50, 50)
	);

private:

	MyChar S[65][100];                                    //记录输入的数字
	MyChar s0[19] = { _T("再玩就玩坏了！！！") };         //错误反馈
	int ZH = -1;                                          //输入数字的长度
	bool button3[10] = { true };                          //标记选择的是哪个进制
	bool button2[10] = { false };                         //标记选择的是哪个进制

};

extern Conversion conversion;
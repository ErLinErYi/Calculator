#pragma once
#include <cmath>
#include <cstdio>
#include <vector>
#include <easyx.h>
#include "Option.h"
#include "Standard.h"
#include "LoadImage.h"
#include "Conversion.h"
#include "TransParent.h"
#include "WindowMessage.h"
#include "Transformation.h"

class Bignumber
{
private:
	void bignumberadd();						                    // 超大数加法
	void bignumbersubtract();					                    // 超大数减法
	void bignumbermuit();						                    // 超大数乘法
	void bignumberdiv();						                    // 超大数除法
	void updatewithinput1();				                      	// 超大数：与输入有关的更新
	void showscreen1();							                    // 超大数：显示函数
	void memsenumber();
	void LsJJ(MyChar *s4, bool t);                                  // 整数部分加减一
	MyChar *numberaddx(MyChar *ss, MyChar *ss1);
	MyChar *numberadd(MyChar *ss, MyChar *ss1);
	MyChar *numbersub(MyChar *ss, MyChar *ss1);
	MyChar *numbersubx(MyChar *ss, MyChar *ss1);

public:
	void BignumberFuction(int &);

private:
	
	MyChar s6[100000];												// 存储结果（字符串显示）
	MyChar s4[100000] = { 0 }, s5[100000] = { 0 };					// 存储输入的两个字符串
	int a[100000] = { 0 }, b[100000] = { 0 };						// 存储字符串转换为数字
	int c[100000] = { 0 };											// 存储计算结果

public:
	bool button1[10] = { false };									// 判断计算的类型

};

extern Bignumber bignumber;
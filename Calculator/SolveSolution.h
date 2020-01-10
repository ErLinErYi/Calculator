#pragma once
#include <easyx.h>
#include "Option.h"
#include "Standard.h"
#include "Bignumber.h"
#include "Conversion.h"
#include "WindowMessage.h"
#include "Transformation.h"

class SolveSolution
{
private:
	void mem();								                    // 初始化函数
	void slovesolution();					                    // 解方程函数
	void updatewithinput2();				                    // 解方程：与输入有关的更新
	void showscreen2();						                    // 解方程：显示函数

public:
	SolveSolution() {};
	~SolveSolution() {};
	void SolveSolutionFuction(int &);

private:

	MyChar xzfc[10000] = { 0 };								     // 存储输入的字符串数字
	MyChar Zfc[10000] = { 0 };								     // 进行运算时的暂存
	MyChar s[10000] = { 0 };								     // 进行运算时的暂存
	MyChar name[100] = { 0 };								     // 存储未知数（变量）
	MyChar solution[10000] = { 0 };							     // 存储最后显示的结果
	long double bsum = 0, zsum = 0, xbsum = 0, fsum = 0;		 // 分别存储方程左右两边的正负数
	int n = 0;												     // 未知数的长度
	int E = -1;												     // 输入数的长度
	int blx = 0;										         // 保证变量为一种
	bool dyy = false;										     // 保证一个方程中只有一个等于号
	bool xxs = false;										     // 保证一个数中只有一个小数点
	int String_Move = 0;                             	         // 标记字符串多长就可以滑动
	int screenmove = 0;                      	                 // 由于算式不能完全显示。算式的左右移动像素
	bool Left_String_move = false, Right_String_move = false;    // 判断是否可以滑动
};

extern SolveSolution solvesolution;
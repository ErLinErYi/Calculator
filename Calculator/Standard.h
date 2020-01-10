#pragma once
#pragma comment(lib,"Comctl32.lib")
#include <stack>
#include <easyx.h>
#include "Option.h"
#include "LoadImage.h"
#include "TransParent.h"
#include "WindowMessage.h"
#include "Transformation.h"

class Standard
{
private:
	void change();								                 // 中缀表达式转换为后缀表达式
	void calculate();							                 // 计算后缀表达式的值
	void updatewithinput_();					                 // 普通计算：与输入有关的更新
	void showscreen_();							                 // 普通计算：显示函数
	void OperationFuction(int, int);                             // 操作函数
	void operation(MyChar C);
	
private:
	long double A = 10000000000;
	MyChar ZFC[10000] = { 0 };                 	                 // 记录输入的每一个数字
	MyChar ZFC1[10000] = { 0 };                	                 // 记录输入的算式
	MyChar ZFC2[10000] = { 0 };               	                 // 存储中缀表达式转换为后缀的结果
	MyChar ZFC3[10000] = { 0 };                                  // 记录计算结果
	int Number_Length = -1;                              	     // 输入数字的长度
	int String_Length = 0;                              	     // 输入的算式的长度
	int Left_Brackets = 0;                              	     // 计算左括号的数量
	int String_Move = 0;                             	         // 标记字符串多长就可以滑动
	bool Decimal_Point = false;                       	         // 判断是否可以按小数点
	bool FIRSTSHOW = false;                                      // 第一次显示
	bool CLEARN = false;

public:
	Standard();
	void screenmovehd();						                 // 字符串滑动动画
	void ConMove(MOUSEMSG);                                      // 控制滑动
	void StandardFuction(int &);

public:
	int fx = 0, fy = 0;                       	                 // 判断是否可以左或者有移动算式
	int color = 0, color1 = 0;                                 	 // 如果左或者右可以移动，颜色变化
	int screenmove = 0;                      	                 // 由于算式不能完全显示。算式的左右移动像素
	bool Left_String_move = false, Right_String_move = false;    // 判断是否可以滑动
	
};

extern Standard standard;

class My_Stack
{
private:
	typedef struct node                   		// 栈的结构体
	{
		MyChar data;
		struct node *next;
	}Stack;
	Stack *t = NULL;
public:
	// 入栈
	void push(MyChar c)	
	{
		Stack *s;
		s = (Stack*)malloc(sizeof(Stack));
		s->data = c;
		s->next = t;
		t = s;
	}
    // 判断栈是否为空
	bool empty()	
	{
		if (!t)return true;
		return false;
	}
    // 出栈
	void pop()		
	{
		Stack *s;
		if (!empty())
		{
			s = t->next;
			free(t);
			t = s;
		}
	}
    // 取栈顶元素
	MyChar top()	
	{
		MyChar s;
		s = '#';
		if (!empty()) s = t->data;
		return s;
	}
	// 清空栈
	void clearstack()	
	{
		Stack *s;
		while (!empty()) 
		{
			s = t->next;
			free(t);
			t = s;
		}
	}
};
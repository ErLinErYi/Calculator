#pragma once
#include <cmath>
#include <string>
#include <stack>
#include <easyx.h>
#include "Option.h"
#include "Standard.h"
#include "LoadImage.h"
#include "TransParent.h"
#include "WindowMessage.h"
#include "Transformation.h"

using std::stack;
using std::wstring;
using std::to_wstring;

class Science
{
private:
	constexpr static auto  Radian = 0.01745329251994329576923690768489;
	enum
	{
		Sqrt = 1,
		Square = 2,
		Log = 3,
		Ten_X = 4,
		Power_X_Y = 5,
		Sin = 6,
		Cos = 7,
		Tan = 8,

		E_X = 9,
		Cube = 10,
		Ln = 11,
		Mod = 12,
		Square_X_Y = 13,
		ArcSin = 14,
		ArcCos = 15,
		ArcTan = 16
	};
private:
	void updatewithinput();								   // 科学：与输入有关的更新
	void showscreen();									   // 科学：显示函数
	void RecordInput(int, int, bool PageTurn = false);     // 记录输入
	void ScienceCalculator(LPCTSTR, LPCTSTR);              // 算式显示
	void MiddleEquationToLast();                           // 中缀表达式转后缀
	void CalculatorLastEquation();                         // 计算后缀表达式
	void Calculator_Function(short);                       // 计算函数
	void StorageEquation_Show_Move();					   // 算式滑动
	void ConMove(MOUSEMSG);                                // 控制滑动

public:
	Science() {};
	~Science() {};
	void ScienceFuction(int &);
	void ShowLeftBrackets();                               // 显示左括号数目

private:
	wstring StorageEquation_Show;                          // 记录算式显示
	wstring StorageEquation_Calculator;                    // 记录算式计算
	wstring StorageEquation_Calculator_Last;               // 后缀表达式
	wstring StorageNumber;                                 // 记录数字
	wstring Number[3] = { _T("123"),_T("456"),_T("789") }; // 数字
	wstring Operator = _T("÷×-+");                       // 运算符
	long double PreNumber = 0;                             // 先前的数字1
	long double PreNumber_Two = 1;                         // 相亲的数字2
	int Calculator_TwoNumber = 0;                          // 标记计算两个数
	int Left_Brackets = 0;                                 // 计算左括号的数量
	bool Push = false;                                     // 是否进行加减
	bool PageTurn = false;                                 // 翻页（更换其他函数）
	bool FinshCalculate = false;                           // 计算是否完成
	bool DecimalPoint = false;                             // 是否可以用小数点
	bool Judge_Left_Can_Move = 0;                          // 判断是否可以左移动算式
	bool Judge_Right_Can_Move = 0;                         // 判断是否可以右移动算式
	bool Left_Clolor = 0;                                  // 鼠标移到位置颜色变化
	bool Right_Color = 0;
	bool Left_String_move = false;                         // 判断是否可以滑动
    bool Right_String_move = false;                     
	int Move_Number = 0;                                   // 移到数量
	int String_Move = 0;                             	   // 标记字符串多长就可以滑动

};

extern Science science;


#pragma once
#include <Windows.h>
#include "Set.h"
#include "Text.h"
#include "Option.h"
#include "Science.h"
#include "Standard.h"
#include "PassWord.h"
#include "LoadImage.h"
#include "Bignumber.h"
#include "Conversion.h"
#include "TransParent.h"
#include "SolveSolution.h"
#include "Transformation.h"


// 准备
class ReadyCalculator
{
public:
	enum
	{
		Option =    0,
		Stabdard =  1,
		Science =   2,
		BigNumber = 3,
		Equation =  4,
		Radix =     5,
		Profiles =  18,
		set =       19
	};

public:
	ReadyCalculator() {};
	~ReadyCalculator() {};
	void ReadyCalculatorFuction();
	void ReadyCalculatorPassWord();
};

void ReadyCalculator::ReadyCalculatorFuction()
{
	// 读取配置文件
	option.ReadFuction();

	// 窗口大小
	HWND hWnd = initgraph(406, 600);

	// 获取窗口边框宽高
	int cx = GetSystemMetrics(SM_CXFIXEDFRAME);
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);

	// 设置矩形区域
	HRGN rgn = CreateRoundRectRgn(5 + cx, 5 + cy, 412 + cx, 606 + cy, 2, 2);
	SetWindowRgn(hWnd, rgn, true);

	//设置透明窗体
	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, 0, option.Alpha, LWA_ALPHA);

	//设置窗口与位置
	SetWindowPos(hWnd, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - 400) / 2, (GetSystemMetrics(SM_CYSCREEN) - 600) / 2 - 70, 424, 640, SWP_SHOWWINDOW);
}

void ReadyCalculator::ReadyCalculatorPassWord()
{
	if (option.RecordPassWard)
	{
		password.LoadPassWord();                                             // 加载密码
		while (!password.PassWordRight())                                    // 密码正确进入下一步
		{
			password.FoundPassWord();                                        // 新建密码
			password.InputPassWordNumbers();                                 // 控制密码输入次数
			password.drawscreen();                                           // 显示界面
			password.update();                                               // 操作更新
			password.UpdatePassWordFuction();                                // 更改密码                           
			Sleep(option.Performance);
		}
	}
}

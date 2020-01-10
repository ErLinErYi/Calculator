#include "Option.h"

Option option;

Option::Option()
{
	Down_Button[0] = 0;
	Down_Button[1] = 1;
	Down_Button[2] = 0;
	Down_Button[3] = 2; 
	Down_Button[4] = 0;
	Down_Button[5] = 5;
}

Option::~Option() {}

void Option::updatewithinput17()
{
	MOUSEMSG m;	// 定义鼠标消息
	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();

		Window_Message.windowmessage(m, -1); //移动窗口

		for (int i = 0; i < 2; i++) // 密码开关
		{
			if (m.x > 100 + 50 * i&&m.x < 150 + 50 * i&&m.y>100 && m.y < 125)
			{
				if (m.uMsg == WM_LBUTTONUP) 
				{
					Down_Button[0] = i;
					if (i) RecordPassWard = true;
					else RecordPassWard = false;
				}
			}
		}
		for (int i = 0; i < 4; i++) // 绘制次数
		{
			if (m.x > 100 + 50 * i&&m.x < 150 + 50 * i&&m.y>150 && m.y < 175)
			{
				if (m.uMsg == WM_LBUTTONUP)
				{
					Down_Button[1] = i;
					if (i == 0)      DrawPasswordNumbers = 3;
					else if (i == 1) DrawPasswordNumbers = 5;
					else if (i == 2) DrawPasswordNumbers = 10;
					else if (i == 3) DrawPasswordNumbers = 900000;
				}
			}
		}
		for (int i = 0; i < 2; i++) // fps
		{
			if (m.x > 100 + 50 * i&&m.x < 300 + 50 * i&&m.y>300 && m.y < 325)
			{
				if (m.uMsg == WM_LBUTTONUP)
				{
					Down_Button[2] = i;
					if (i == 0)      Window_Message.showFPS = false;
					else if (i == 1) Window_Message.showFPS = true;
				}
			}
		}
		for (int i = 0; i < 4; i++) // 性能
		{
			if (m.x > 100 + 50 * i&&m.x < 150 + 50 * i&&m.y>350 && m.y < 375)
			{
				if (m.uMsg == WM_LBUTTONUP)
				{
					Down_Button[3] = i;
					if (i == 0)      Performance = 60;
					else if (i == 1) Performance = 35;
					else if (i == 2) Performance = 10;
					else if (i == 3) Performance = 0;
				}
			}
		}
		for (int i = 0; i < 5; i++) // 小数位数
		{
			if (m.x > 100 + 50 * i&&m.x < 150 + 50 * i&&m.y>400 && m.y < 425)
			{
				if (m.uMsg == WM_LBUTTONUP)
				{
					Down_Button[5] = i;
					if (!i)          DecimalDigit = 2;
					else if (i == 1) DecimalDigit = 5;
					else if (i == 2) DecimalDigit = 8;
					else if (i == 3) DecimalDigit = 10;
					else if (i == 4) DecimalDigit = 15;
				}
			}
		}
		if (m.x >= 110 && m.x <= 315 && m.y>502 && m.y < 522)// alpha
		{
			if (m.mkLButton)
			{
				M_X = m.x - 8;
				Alpha = m.x - 60;
			}
		}
		for (int i = 0; i < 3; i++) // 风格
		{
			if (m.x > 100 + 50 * i&&m.x < 150 + 50 * i&&m.y>550 && m.y < 575)
			{
				if (m.uMsg == WM_LBUTTONUP)
				{
					Down_Button[4] = i;
					if (!i)          WindowStyle = 0;
					else if (i == 1) WindowStyle = 1;
					else             WindowStyle = 2;
				}
			}
		}

		if (m.x > 310 && m.x <395  && m.y>570 && m.y < 590) // 保存配置
		{
			Down_Button[6] = 1;
			if (m.uMsg == WM_LBUTTONUP)
			{
				CaveFuction();
				transformation.software[0] = Window_Message.Recorde;
			}
		}
		else
			Down_Button[6] = 0;
	}
}

void Option::showscreen17()
{
	BeginBatchDraw();

	setbkmode(TRANSPARENT);

	if (!WindowStyle)          conversion.Setcolor(0, 406, 0, 600);
	else if (WindowStyle == 1) conversion.Setcolor(0, 406, 0, 600, RGB(180, 180, 180));
	else                       conversion.changecolor(0, 406, 0, 600);

	IMAGE black = MyLoadImage.setimage(406, 600, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	Window_Message.GetFunctionName(_T(""), -1);

	black = MyLoadImage.setimage(406, 20, RGB(0, 0, 0));	   // 设置绘图
	MyPutimage.my_putimage(0, 50, &black, RGB(255, 255, 255), 0, 1, 50, 0);

	settextstyle(19, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	settextcolor(RGB(150, 150, 150));
	outtextxy(20, 50, _T("安全设置"));

	// 密码 开关选项
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(10, 100, _T("密码"));
    black = MyLoadImage.setimage(103, 25, RGB(0, 0, 0));	   // 设置绘图
	MyPutimage.my_putimage(100, 100, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	setfillcolor(HSLtoRGB(195, 1, 0.5f));
	solidroundrect(102 + 50 * Down_Button[0], 102, 150 + 50 * Down_Button[0], 122, 3, 3);
	MyChar Name1[][5] = { {_T("关")},{_T("开")}};
	for (int i = 0; i < 2; i++) outtextxy(118 + 50 * i, 100, Name1[i]);
	settextstyle(17, 0, _T("微软雅黑"), 0, 0, 10, 0, 0, 0);
	outtextxy(320, 105, _T("重启程序生效"));

	// 密码解锁次数选项
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(10, 150, _T("解锁次数"));
	black = MyLoadImage.setimage(203, 25, RGB(0, 0, 0));	   // 设置绘图
	MyPutimage.my_putimage(100, 150, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	setfillcolor(HSLtoRGB(195, 1, 0.5f));
	solidroundrect(102 + 50 * Down_Button[1], 152, 150 + 50 * Down_Button[1], 172, 3, 3);
	MyChar Name2[][10] = { {_T("三次")},{_T("五次")},{_T("十次")},{_T("无穷")} };
	for (int i = 0; i < 4; i++) outtextxy(110 + 50 * i, 150, Name2[i]);
	settextstyle(17, 0, _T("微软雅黑"), 0, 0, 10, 0, 0, 0);
	outtextxy(320, 155, _T("重启程序生效"));
    
	// 显示fps选项
	black = MyLoadImage.setimage(406, 20, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 250, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	settextstyle(19, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	settextcolor(RGB(150, 150, 150));
	outtextxy(20, 250, _T("基础设置"));

	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(10, 300, _T("显示FPS"));
	black = MyLoadImage.setimage(103, 25, RGB(0, 0, 0));	   // 设置绘图
	MyPutimage.my_putimage(100, 300, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	setfillcolor(HSLtoRGB(195, 1, 0.5f));
	solidroundrect(102 + 50 * Down_Button[2], 302, 150 + 50 * Down_Button[2], 322, 3, 3);
	MyChar Name3[][5] = { {_T("关")},{_T("开")}};
	for (int i = 0; i < 2; i++) outtextxy(118 + 50 * i, 300, Name3[i]);

	// 性能选项
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(10, 350, _T("性能"));
	black = MyLoadImage.setimage(203, 25, RGB(0, 0, 0));	   // 设置绘图
	MyPutimage.my_putimage(100, 350, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	setfillcolor(HSLtoRGB(195, 1, 0.5f));
	solidroundrect(102 + 50 * Down_Button[3], 352, 150 + 50 * Down_Button[3], 372, 3, 3);
	MyChar Name4[][10] = { {_T("较低")},{_T("中等")},{_T("较高")},{_T("极限")} };
	for (int i = 0; i < 4; i++) outtextxy(110 + 50 * i, 350, Name4[i]);

	// 小数保留位数
	settextcolor(RGB(255, 255, 255));
	settextstyle(17, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(100, 430, _T("当计算结果的位数比设置的位数长时才有效"));
	settextstyle(23, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(10, 400, _T("数字位数"));
	black = MyLoadImage.setimage(253, 25, RGB(0, 0, 0));	   // 设置绘图
	MyPutimage.my_putimage(100, 400, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	setfillcolor(HSLtoRGB(195, 1, 0.5f));
	solidroundrect(102 + 50 * Down_Button[5], 402, 150 + 50 * Down_Button[5], 422, 3, 3);
	MyChar Name6[][10] = { {_T("2 位")},{_T("5 位")},{_T("8 位")},{_T("10位")},{_T("15位")} };
	for (int i = 0; i < 5; i++)
	{
		if (i == 3 || i == 4) outtextxy(110 + 50 * i - 5, 400, Name6[i]);
		else outtextxy(110 + 50 * i, 400, Name6[i]);
	}

	// 窗口选项
	black = MyLoadImage.setimage(406, 20, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 450, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	settextstyle(19, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	settextcolor(RGB(150, 150, 150));
	outtextxy(20, 450, _T("窗口设置"));
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(10, 500, _T("窗口透明度"));
	setlinestyle(PS_SOLID| PS_ENDCAP_ROUND, 5);
	setlinecolor(RGB(20,20,20));
	line(110, 512, 315, 512);
	setlinecolor(HSLtoRGB(250, 1, 0.5f));
	line(110, 512, M_X + 8, 512);
	setfillcolor(HSLtoRGB(195, 1, 0.5f));
	POINT pts[] = {  {M_X, 512},{10 + M_X, 502}, {20 + M_X, 512},{10 + M_X ,522} };
	solidpolygon(pts, 4);
	settextstyle(18, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	MyChar s[15];
	_stprintf_s(s, _T("Alpha: %d"), Alpha);
	outtextxy(335, 503, s);

	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(10, 550, _T("背景风格"));
	black = MyLoadImage.setimage(153, 25, RGB(0, 0, 0));	   // 设置绘图
	MyPutimage.my_putimage(100, 550, &black, RGB(255, 255, 255), 0, 1, 50, 0);
	setfillcolor(HSLtoRGB(195, 1, 0.5f));
	solidroundrect(102 + 50 * Down_Button[4], 552, 150 + 50 * Down_Button[4], 572, 3, 3);
	MyChar Name5[][10] = { {_T("黑灰")},{_T("银白")},{_T("幻彩")} };
	for (int i = 0; i < 3; i++)
		outtextxy(110 + 50 * i, 550, Name5[i]);

	// 确定
	if (Down_Button[6]) settextcolor(HSLtoRGB(195, 1, 0.5f));
	else                settextcolor(WHITE);
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	outtextxy(310, 570, _T("保存全部配置"));

	EndBatchDraw();
}

void Option::OptionFuction(int &k)
{
	while (true)
	{
		//设置透明窗体
		SetWindowLong(GetHWnd(), GWL_EXSTYLE, GetWindowLong(GetHWnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(GetHWnd(), 0, Alpha, LWA_ALPHA);

		showscreen17();
		updatewithinput17();

		if (k != transformation.software[0] + 1) 
			break;
		Sleep(Performance);						       // 延时
	}
}

void Option::ReadFuction()
{
	// 读取上一次的配置
	// 密码的开关
	RecordPassWard = GetPrivateProfileInt(_T("PassWard"), _T("RecordPassWard"), 0, _T(".\\important.ini"));
	// 绘制的次数
	DrawPasswordNumbers = GetPrivateProfileInt(_T("Draw"), _T("DrawPasswordNumbers"), 3, _T(".\\important.ini"));
	// 是否显示fps
	Window_Message.showFPS = GetPrivateProfileInt(_T("FPS"), _T("ShowFPS"), false, _T(".\\important.ini"));
	// 性能
	Performance = GetPrivateProfileInt(_T("Performance"), _T("performance"), 35, _T(".\\important.ini"));
	// 窗口透明度
	Alpha = GetPrivateProfileInt(_T("Alpha"), _T("alpha"), 255, _T(".\\important.ini"));
	// 背景颜色
	WindowStyle = GetPrivateProfileInt(_T("WindowStyle"), _T("windowstyle"), 0, _T(".\\important.ini"));
	// 小数位数
	DecimalDigit = GetPrivateProfileInt(_T("DecimalDigit"), _T("decimaldigit"), 15, _T(".\\important.ini"));

	InitFuction();
}

void Option::CaveFuction()
{
	// 保存坐标到配置文件
	MyChar s[20];
	// 密码的开关
	_stprintf_s(s, _T("%d"), RecordPassWard);
	::WritePrivateProfileString(_T("PassWard"), _T("RecordPassWard"), s, _T(".\\important.ini"));
	// 绘制的次数
	_stprintf_s(s, _T("%d"), DrawPasswordNumbers);
	::WritePrivateProfileString(_T("Draw"), _T("DrawPasswordNumbers"), s, _T(".\\important.ini"));
	// 是否显示fps
	_stprintf_s(s, _T("%d"), Window_Message.showFPS);
	::WritePrivateProfileString(_T("FPS"), _T("ShowFPS"), s, _T(".\\important.ini"));
	// 性能
	_stprintf_s(s, _T("%d"), Performance);
	::WritePrivateProfileString(_T("Performance"), _T("performance"), s, _T(".\\important.ini"));
	// 窗口透明度
	_stprintf_s(s, _T("%d"), Alpha);
	::WritePrivateProfileString(_T("Alpha"), _T("alpha"), s, _T(".\\important.ini"));
	// 背景颜色
	_stprintf_s(s, _T("%d"), WindowStyle);
	::WritePrivateProfileString(_T("WindowStyle"), _T("windowstyle"), s, _T(".\\important.ini"));
	// 背景颜色
	_stprintf_s(s, _T("%d"), DecimalDigit);
	::WritePrivateProfileString(_T("DecimalDigit"), _T("decimaldigit"), s, _T(".\\important.ini"));
}

void Option::InitFuction()
{
	Down_Button[0] = RecordPassWard;                             // 是否开启密码

	if      (DrawPasswordNumbers == 3)      Down_Button[1] = 0;  // 控制绘制次数
	else if (DrawPasswordNumbers == 5)      Down_Button[1] = 1;  // 控制绘制次数
	else if (DrawPasswordNumbers == 10)     Down_Button[1] = 2;  // 控制绘制次数
	else if (DrawPasswordNumbers == 900000) Down_Button[1] = 3;  // 控制绘制次数
	
	Down_Button[2] = Window_Message.showFPS;                     // 是否显示fps

	if      (Performance == 60)  Down_Button[3] = 0;             // 性能
	else if (Performance == 35)  Down_Button[3] = 1;
	else if (Performance == 10)  Down_Button[3] = 2;
	else if (Performance == 0)   Down_Button[3] = 3;

	M_X = Alpha + 60 - 8;                                        // 窗口透明度

	Down_Button[4] = WindowStyle;                                // 背景颜色

	if      (DecimalDigit == 2)  Down_Button[5] = 0;             // 小数位数
	else if (DecimalDigit == 5)  Down_Button[5] = 1;
	else if (DecimalDigit == 8)  Down_Button[5] = 2;
	else if (DecimalDigit == 10) Down_Button[5] = 3;
	else if (DecimalDigit == 15) Down_Button[5] = 4;
}
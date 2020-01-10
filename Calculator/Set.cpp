#include"Set.h"

Set set;
/****************************设置**************************************/

void Set::updatewithinput0()
{
	while (true)
	{
		bool BREAK = false;
		while (MouseHit())		// 检查是否有鼠标消息
		{
			MOUSEMSG m;				// 定义鼠标消息
			m = GetMouseMsg();

			Window_Message.windowmessage(m, true); //移动窗口

			if (m.uMsg == WM_MOUSEMOVE || m.uMsg == WM_MOUSEWHEEL)  //如果鼠标移动或滑动
			{
				if (m.x > 0 && m.x < 300 && m.y>80 && m.y < 600)
					start = clock();
			}
			for (int i = 2 + H_XS + 50; i < 21 + H_XS + 50; i++)
			{
				if (m.x > 0 && m.x<300 && m.y>(i - 50) * 40 && m.y < 40 + (i - 50) * 40 && m.y>80 && m.y < 600)
				{
					buttons[i] = true;
					if (m.uMsg == WM_LBUTTONUP)
					{
						if (i != 20 + H_XS + 50)
						{
							transformation.software[0] = i - 2 - H_XS - 50;
							transformation.software[1] = i - 2 - H_XS - 50;
							transformation.software[2] = i - H_XS - 50;
						}
						if (i == 20 + H_XS + 50)
						{
							buttons[100] = true;
							transformation.software[2] = i - H_XS - 50;
						}
						else buttons[100] = false;
					}
				}
				else buttons[i] = false;
			}

			if (m.x > 5 && m.x < 40 && m.y > 30 && m.y < 50)	// 设置
			{
				transformation.help[0] = true;
				if (m.uMsg == WM_LBUTTONUP)
				{
					transformation.software[0] = transformation.software[1];
					static int n;
					n++;
					if (n % 2)transformation.help[1] = false;
					else
					{
						transformation.help[1] = true;
						buttons[100] = false;
					}
				}
			}
			else
			{
				transformation.help[0] = false;
				if (m.uMsg == WM_LBUTTONUP && m.x > 300)
				{
					transformation.software[0] = transformation.software[1];
					transformation.help[1] = true;
					buttons[100] = false;
				}
			}
			if (m.uMsg == WM_MOUSEWHEEL && m.x > 0 && m.x < 300 && m.y>80 && m.y < 600)
			{
				if (m.wheel < 0)
					transformation.fly1 -= 40;
				else
					transformation.fly1 += 40;
			}
			BREAK = true;
		}

		if (transformation.fly1 > 0)
			transformation.fly1 -= transformation.fly1;
		if (transformation.fly1 < -240)
			transformation.fly1 += -(transformation.fly1 + 240);
		if (BREAK)break;
		Sleep(100);
	}
}


void Set::showscreen0()
{
	BeginBatchDraw();
	float H = float(colors++);	// 色相
	float S = 1;				// 饱和度
	float L = 0.4f;				// 亮度
	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 300, 50, 600); break;
	case 1:  conversion.Setcolor(0, 300, 50, 600, RGB(160, 160, 160)); break;
	default: 
		if (colors > 360)colors = 1;
		for (int y = 0; y < 300; y++)
		{
			L -= 0.001f;
			setlinecolor(HSLtoRGB(H, S, L));
			line(y, 50, y, 600);
		} 
		break;
	}
	
	for (int i = 2 + H_XS + 50; i < 21 + H_XS + 50; i++)
	{
		
		if (buttons[i])
		{
			switch (option.WindowStyle)
			{
			case 0:  setfillcolor(RGB(70, 70, 70)); break;
			case 1:  setfillcolor(RGB(100, 100, 100)); break;
			default: 
				float H = float((colors + 100) % 360);	// 色相
				setlinecolor(HSLtoRGB(50, 1, 0.5));
				setfillcolor(HSLtoRGB(H, 1, 0.5)); 
				break;
			}
		
			solidrectangle(0, 40 * (i - 50), 299, 40 + 40 * (i - 50));
		}
		for (int j = 0; j < 6; j++)
		{
			setlinestyle(PS_SOLID, 1, 0);
			setlinecolor(HSLtoRGB(60, 1, 0.5));
			line(j, 40 * transformation.software[2] + 5 + transformation.fly1, j, 35 + 40 * transformation.software[2] + transformation.fly1);
		}
	}
	end = clock();
	if (end - start < 800)setline(); //滑动条
	
	switch (option.WindowStyle)
	{
	case 0:  settextcolor(WHITE); break;
	case 1:  settextcolor(BLACK); break;
	}

	settextstyle(25, 0, _T("Calculator MDL2 Assets"), 0, 0, 1, false, false, false);
	outtextxy(15, 125 + transformation.fly1, 0xF196);
	outtextxy(15, 285 + transformation.fly1, 0xF20F);
	outtextxy(15, 485 + transformation.fly1, 0xE7A3);
	outtextxy(15, 525 + transformation.fly1, 0xEADA);
	outtextxy(15, 565 + transformation.fly1, 0xF4C1);
	outtextxy(15, 725 + transformation.fly1, 0xF515);

	settextstyle(25, 0, _T("Segoe MDL2 Assets"), 0, 0, 1, false, false, false);
	outtextxy(15, 87 + transformation.fly1, 0xE8EF);
	outtextxy(15, 165 + transformation.fly1, 0xE9A1);
	outtextxy(15, 205 + transformation.fly1, 0xE8F1);
	outtextxy(15, 245 + transformation.fly1, 0xE81E);
	outtextxy(15, 325 + transformation.fly1, 0xECC6);
	outtextxy(15, 365 + transformation.fly1, 0xE809);
	outtextxy(15, 405 + transformation.fly1, 0xF158);
	outtextxy(15, 445 + transformation.fly1, 0xE2AD);
	outtextxy(15, 645 + transformation.fly1, 0xE945);
	outtextxy(15, 605 + transformation.fly1, 0xECAD);
	outtextxy(15, 685 + transformation.fly1, 0xEC4A);
	outtextxy(15, 805 + transformation.fly1, 0xE946);
	outtextxy(15, 765 + transformation.fly1, 0xED0C);
	

	settextstyle(25, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
	outtextxy(20, 85 + transformation.fly1,  _T("      标准"));
	outtextxy(20, 125 + transformation.fly1, _T("      科学"));
	outtextxy(20, 165 + transformation.fly1, _T("      高精度运算"));
	outtextxy(20, 205 + transformation.fly1, _T("      解一元一次方程"));
	outtextxy(20, 245 + transformation.fly1, _T("      进制转换"));
	outtextxy(20, 285 + transformation.fly1, _T("      数据转换"));
	outtextxy(20, 325 + transformation.fly1, _T("      长度转换"));
	outtextxy(20, 365 + transformation.fly1, _T("      面积转换"));
	outtextxy(20, 405 + transformation.fly1, _T("      体积转换"));
	outtextxy(20, 445 + transformation.fly1, _T("      时间转换"));
	outtextxy(20, 485 + transformation.fly1, _T("      温度转换"));
	outtextxy(20, 525 + transformation.fly1, _T("      速度转换"));
	outtextxy(20, 565 + transformation.fly1, _T("      重量转换"));
	outtextxy(20, 605 + transformation.fly1, _T("      能量转换"));
	outtextxy(20, 645 + transformation.fly1, _T("      功率转换"));
	outtextxy(20, 685 + transformation.fly1, _T("      压力转换"));
	outtextxy(20, 725 + transformation.fly1, _T("      角度转换"));
	outtextxy(20, 765 + transformation.fly1, _T("      说明"));
	outtextxy(20, 805 + transformation.fly1, _T("      关于"));

	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 300, 0, 80); break;
	case 1:  conversion.Setcolor(0, 300, 0, 80, RGB(160, 160, 160)); break;
	default: 
		float l = 0.4f;					// 亮度
		for (int y = 0; y < 300; y++)
		{
			l -= 0.001f;
			setlinecolor(HSLtoRGB(H, S, l));
			line(y, 0, y, 80);
		}
		break;
	}
	
	Window_Message.GetFunctionName(_T(""), true);

	settextstyle(25, 0, _T("微软雅黑"));
	switch (option.WindowStyle)
	{
	case 0:  settextcolor(WHITE); break;
	case 1:  settextcolor(BLACK); break;
	}
	outtextxy(20, 55, _T("计算器"));

	if (buttons[100])
	{
		setlinestyle(PS_SOLID, 1, 0, 0);

		IMAGE black = MyLoadImage.setimage(350, 300, RGB(0, 0, 0));	// 设置绘图
		MyPutimage.my_putimage(0, 260, &black, RGB(255, 255, 255), 0, 1, 90, 0);
		setlinecolor(RGB(0, 238, 238));
		rectangle(0, 260, 350, 560);
		settextcolor(RGB(194, 203, 223));
		settextstyle(27, 0, _T("Consolas"));
		outtextxy(150, 270, _T("关于"));
		settextstyle(22, 0, _T("Consolas"));
		outtextxy(10, 320, _T("名    称：计算器"));
		outtextxy(10, 360, _T("作    者：尔灵尔亿"));
		outtextxy(10, 400, _T("编译环境：VS 2017 Community"));
		outtextxy(10, 440, _T("图 形 库：EasyX_20190219(beta)"));
		outtextxy(10, 480, _T("时    间：2019.1.20 — 2019.2.28"));
		outtextxy(10, 520, _T("最后修改：2019.2.28"));
	}
	else buttons[100] = false;

	EndBatchDraw();	// 结束批量绘图
}

void Set::setline()
{
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 3, 0, 0);
	line(297, 83 - transformation.fly1, 297, 355 - transformation.fly1);
}

void Set::SetFuction(int &k)
{
	while (true)
	{
		showscreen0();
		updatewithinput0();

		if (k != transformation.software[0] + 1)
			break;
		Sleep(option.Performance);						       // 延时
	}
}
#include"SolveSolution.h"

SolveSolution solvesolution;

void SolveSolution::updatewithinput2()
{
	MOUSEMSG m;	// 定义鼠标消息
	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();

		Window_Message.windowmessage(m); //移动窗口

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (m.x > i * 102 && m.x < i * 102 + 98 && m.y>340 + j * 52 && m.y < 388 + j * 52)
				{
					transformation.button[i][j] = true;
					if (m.uMsg == WM_LBUTTONUP)
					{
						if (solution[0] != '\0')memset(solution, 0, sizeof(solution));
						if (j == 3 && i == 0 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '1';
						else if (j == 3 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '2';
						else if (j == 3 && i == 2 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '3';
						else if (j == 2 && i == 0 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '4';
						else if (j == 2 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '5';
						else if (j == 2 && i == 2 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '6';
						else if (j == 1 && i == 0 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '7';
						else if (j == 1 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '8';
						else if (j == 1 && i == 2 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '9';
						else if (j == 0 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '0';
						else if (j == 2 && i == 3)
						{
							if (xzfc[E] != '-' && xzfc[E] != '+'&& xzfc[E] != '.')xzfc[++E] = '-';
							else xzfc[E] = '-';
							xxs = false;
						}
						else if (j == 3 && i == 3)
						{
							if (xzfc[E] != '-' && xzfc[E] != '+'&& xzfc[E] != '.')xzfc[++E] = '+';
							else xzfc[E] = '+';
							xxs = false;
						}
						else if (j == 4 && i == 1 && xzfc[E] != '.')
						{
							if (blx == 0 || blx == 2)
							{
								xzfc[++E] = 'b';
								blx = 2;
							}
						}
						else if (j == 4 && i == 0 && xzfc[E] != '.')
						{
							if (blx == 0 || blx == 1)
							{
								xzfc[++E] = 'a';
								blx = 1;
							}
						}
						else if (j == 4 && i == 2 && xzfc[E] != '.')
						{
							if (blx == 0 || blx == 3)
							{
								xzfc[++E] = 'c';
								blx = 3;
							}
						}
						else if (j == 4 && i == 3 && xzfc[E] != '.')
						{
							if (!dyy)xzfc[++E] = '=';
							dyy = true, xxs = false;
						}
						else if (j == 1 && i == 3) {
							if (!xxs&&xzfc[E] >= '0'&&xzfc[E] <= '9')
							{
								xzfc[++E] = '.';
								xxs = true;
							}
						}
						else if (j == 0 && i == 0)
						{
							memset(xzfc, 0, sizeof(xzfc));
							memset(solution, 0, sizeof(solution));
							E = -1, blx = 0, dyy = false, xxs = false;
							standard.screenmove = 0;
						}
						else if (j == 0 && i == 2)
						{
							if (xzfc[E] == 'a' || xzfc[E] == 'b' || xzfc[E] == 'c')blx = 0;
							if (xzfc[E] == '=')dyy = false;
							if (xzfc[E] == '.')xxs = false;
							if (E >= 0)xzfc[E--] = '\0';
						}
						else if (j == 0 && i == 3)
						{
							E = -1;
							blx = 0, dyy = false, xxs = false;
							slovesolution();
							memset(xzfc, 0, sizeof(xzfc));
						}
					}
				}
				else transformation.button[i][j] = false;
			}
		}

		if (m.x > 5 && m.x < 40 && m.y > 30 && m.y < 50)	// 设置
		{
			transformation.help[0] = true;
			if (m.uMsg == WM_LBUTTONUP)
			{
				transformation.software[0] = -1;
				transformation.software[2] = 5;
				standard.screenmove = 0;
				standard.fx = 0;
				standard.fy = 0;
			}
		}
		else transformation.help[0] = false;

		if (m.x > 350 && m.x < 380 && m.y>30 && m.y < 50)bignumber.button1[5] = true;
		else bignumber.button1[5] = false;

		if (m.x >= 5 && m.x < 40 && m.y>200 && m.y < 235 && standard.fx == 1)
		{
			standard.color = 1;
			if (m.uMsg == WM_LBUTTONUP)
				Left_String_move = true;
		}
		else standard.color = 0;

		if (m.x >= 375 && m.x < 395 && m.y>200 && m.y < 235 && standard.fy == 1)
		{
			standard.color1 = 1;
			if (m.uMsg == WM_LBUTTONUP)
				Right_String_move = true;
		}
		else standard.color1 = 0;
	}
}


void SolveSolution::showscreen2()
{
	BeginBatchDraw();	// 开始批量绘图

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	
	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 406, 0, 600); break;
	case 1:  conversion.Setcolor(0, 406, 0, 600, RGB(180, 180, 180)); break;
	default: conversion.changecolor(0, 406, 0, 600, 0.001f); break;
	}
	
	IMAGE black = MyLoadImage.setimage(406, 600, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	black = MyLoadImage.setimage(100, 50, RGB(0, 0, 0));	// 设置绘图

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j >= 1 && j < 4 && i <= 2 || j == 0 && i == 1)
			{
				if (!transformation.button[i][j])
					MyPutimage.my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 90, 0);
				else
					MyPutimage.my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
			}
			else
			{
				if (!transformation.button[i][j])
					MyPutimage.my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 70, 0);
				else
				{
					if (i == 3 && j == 4 || j == 0 && i == 2 || j == 0 && i == 0)
					{
						IMAGE black = MyLoadImage.setimage(100, 50, RGB(240, 0, 0));	// 设置绘图
						MyPutimage.my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
					else if (j <= 4 && j >= 2 && i == 3)
					{
						IMAGE green = MyLoadImage.setimage(100, 50, HSLtoRGB(195,1,0.5f));	// 设置绘图
						MyPutimage.my_putimage(i * 102, 340 + j * 52, &green, RGB(255, 255, 255), 0, 1, 50, 0);
					}
					else if (j == 0 && i == 3)
					{
						IMAGE black = MyLoadImage.setimage(100, 50, RGB(64, 0, 128));	// 设置绘图
						MyPutimage.my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
					else
					{
						IMAGE black = MyLoadImage.setimage(100, 50, RGB(225, 100, 26));	// 设置绘图
						MyPutimage.my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
				}
			}
		}
	}
	setlinestyle(PS_SOLID, 1, 0, 0);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, _T("Wingdings"), 0, 0, 1, false, false, false);
	outtextxy(235, 354, 0xD5);
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextstyle(23, 0, _T("Consolas"));
	outtextxy(325, 355, _T("result"));
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(34, 350, _T("CE"));
	outtextxy(142, 557, 'b');
	outtextxy(144, 350, '0');
	outtextxy(40, 557, 'a');
	outtextxy(40, 508, '1');
	outtextxy(142, 508, '2');
	outtextxy(244, 508, '3');
	outtextxy(40, 456, '4');
	outtextxy(142, 456, '5');
	outtextxy(244, 456, '6');
	outtextxy(40, 404, '7');
	outtextxy(142, 404, '8');
	outtextxy(244, 404, '9');
	outtextxy(244, 557, 'c');
	outtextxy(349, 400, '.');
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(347, 500, '+');
	outtextxy(347, 552, '=');
	settextstyle(40, 25, _T("Consolas"));
	outtextxy(344, 448, '-');

	Window_Message.GetFunctionName(_T("解一元一次方程"));
	
	if (Left_String_move && String_Move < 60)  { String_Move += 10;		     screenmove += 20; }
	if (String_Move >= 60)                     { Left_String_move = false;   String_Move = 0;  }
	if (Right_String_move && String_Move < 60) { String_Move += 10;		     screenmove -= 20; }
	if (String_Move >= 60)                     { Right_String_move = false;	 String_Move = 0;  }
	 
	if ((int)(textwidth(xzfc) + 10 * _tcslen(xzfc)) >= 380 + screenmove)standard.fx = 1;
	else standard.fx = 0;
	if (screenmove > 0)standard.fy = 1;
	else standard.fy = 0;
	
    settextstyle(50, 10, _T("微软雅黑"));
	settextcolor(WHITE);
	if (standard.fx != 0)
	{
		settextstyle(30, 0, _T("微软雅黑"));
		if (!standard.color)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(10, 208, _T("<"));
	}
	if (standard.fy != 0)
	{
		settextstyle(30, 0, _T("微软雅黑"));
		if (!standard.color1)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(370, 208, _T(">"));
	}

	settextcolor(WHITE);
	if (solution[0] == '\0')
	{
		if (E == -1)
		{
			RECT r1 = { 10,200 ,380,300 };
			settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
			drawtext('0', &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
		else
		{
			RECT r1 = { -10000 ,200 ,380 + screenmove,300 };
			transformation.callen(xzfc);	// 计算字符串长度
			drawtext(xzfc, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
	}
	else
	{
		RECT r1 = { 10,100 ,400,150 };
		if (_tcscmp(solution, _T("违规操作！请正确输入方程！ "))&& _tcscmp(solution, _T("违规操作！方程中无可解的未知量！ ")))
			transformation.callen(solution);
		else
			settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
		drawtext(solution, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	if (!bignumber.button1[5])
	{
		settextcolor(RED);
		settextstyle(25, 0, _T("Segoe MDL2 Assets"));
		outtextxy(350, 30, 0xE8BD);
	}
	else
	{
		settextcolor(BLACK);
		settextstyle(25, 0, _T("Segoe MDL2 Assets"));
		outtextxy(350, 30, 0xE8BD);

		IMAGE black = MyLoadImage.setimage(180, 130, RGB(0, 0, 0));	// 设置绘图
		MyPutimage.my_putimage(210, 50, &black, RGB(255, 255, 255), 0, 0, 80, 0);

		setlinecolor(RGB(0, 238, 238));
		rectangle(210, 50, 390, 180);
		settextcolor(RGB(194, 203, 223));
		settextstyle(22, 0, _T("微软雅黑"));
		outtextxy(220, 55, _T("由于个人能力和时间有"));
		outtextxy(220, 80, _T("限所以很遗憾暂时只支"));
		outtextxy(220, 105, _T("持解一元一次方程。a,"));
		outtextxy(220, 130, _T("b,c,是未知量。a,b,c，"));
		outtextxy(220, 155, _T("一个方程只限用一种。"));
	}

	EndBatchDraw();
}


void SolveSolution::mem()
{
	memset(Zfc, 0, sizeof(Zfc));
	memset(s, 0, sizeof(s));
	memset(name, 0, sizeof(name));
	memset(solution, 0, sizeof(solution));
	bsum = 0, zsum = 0, xbsum = 0, fsum = 0;
	E = -1, blx = 0;
}


void SolveSolution::slovesolution()
{
	mem();	// 初始化

	if (Zfc[0] != '-')
		for (int i = 0; i <= (int)(_tcslen(xzfc)); i++)
			Zfc[i + 1] = xzfc[i];
	Zfc[0] = '+';
	MyChar *p = NULL;
	p = _tcschr(Zfc, '=');
	if (p == NULL || Zfc[_tcslen(Zfc) - 1] == '=')
	{
		_tcscpy_s(solution, _T("违规操作！请正确输入方程！ "));
		return;
	}

	int flag(0);
	for (int i = 0; i < (int)(_tcslen(xzfc)); i++)
	{
		if (xzfc[i] == 'a' || xzfc[i] == 'b' || xzfc[i] == 'c')
		{
			flag = 1;
			break;
		}
	}

	if (!flag)
	{
		_tcscpy_s(solution, _T("违规操作！方程中无可解的未知量！ "));
		return;
	}

	for (int i = 0; i < p - Zfc; i++)
	{
		if (Zfc[i] == '+')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < p - Zfc; j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')flag = 1;
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[100];
				if (_tcslen(s) == 1)bsum += 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					bsum += t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				zsum += t;
			}
		}
		if (Zfc[i] == '-')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < p - Zfc; j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')
				{
					flag = 1;
					break;
				}
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[100];
				if (_tcslen(s) == 1)bsum -= 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)
						ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					bsum -= t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				zsum -= t;
			}
		}
	}
	if (Zfc[p - Zfc + 1] != '-')Zfc[p - Zfc] = '+';
	for (int i = (int)(p - Zfc); i < (int)(_tcslen(Zfc)); i++)
	{
		if (Zfc[i] == '+')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < (int)(_tcslen(Zfc)); j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')flag = 1;
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[100];
				if (_tcslen(s) == 1)xbsum += 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)
						ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					xbsum += t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				fsum += t;
			}
		}
		if (Zfc[i] == '-')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < (int)(_tcslen(Zfc)); j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')
				{
					flag = 1;
					break;
				}
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[100];
				if (_tcslen(s) == 1)xbsum -= 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)
						ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					xbsum -= t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				fsum -= t;
			}
		}
	}
	n = 0;
	memset(name, 0, sizeof(name));
	for (int i = 0; i < (int)(_tcslen(Zfc)); i++)
	{
		if (Zfc[i] >= 'a' && Zfc[i] <= 'z')
		{
			for (int j = i; j < (int)(_tcslen(Zfc)); j++)
			{
				if (Zfc[j] >= 'a' && Zfc[j] <= 'z')
					name[n++] = Zfc[j];
				else break;
			}
			if (n)break;
		}
	}

	name[n] = '\0';
	memset(solution, 0, sizeof(solution));
	_tcscat_s(solution, name);
	_tcscat_s(solution, _T("="));
	if (zsum - fsum == 0)
		_tcscat_s(solution, _T("0.00"));
	else
	{
		MyChar s[1000] = { 0 };
		_stprintf_s(s, _T("%.15Lg"), (zsum - fsum) / (xbsum - bsum));
		_tcscat_s(solution, s);
	}
}

void SolveSolution::SolveSolutionFuction(int &k)
{
	while (true)
	{
		showscreen2();
		updatewithinput2();

		if (k != transformation.software[0] + 1)
			break;
		Sleep(option.Performance);						       // 延时
	}
}
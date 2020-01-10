#include"Conversion.h"

Conversion conversion;
bool Conversion::input(int n) 
{
	for (int i = 8; i >= 0; i--) 
	{
		if (button3[i])
		{
			if (n < 10 - i)
				return true;
			else 
				return false;
		}
	}
	return false;
}

void Conversion::updatewithinput3()
{
	MOUSEMSG m;//定义鼠标消息
	while (MouseHit()) //检查是否有鼠标消息
	{
		m = GetMouseMsg();

		Window_Message.windowmessage(m); //移动窗口

		for (int i = 0; i < 4 && !bignumber.button1[7]; i++) 
		{
			for (int j = 0; j < 3; j++) 
			{
				if (m.x > i * 102 && m.x < i * 102 + 98 && m.y>445 + j * 52 && m.y < 498 + j * 52) 
				{
					transformation.button[i][j] = true;
					if (m.uMsg == WM_LBUTTONUP) 
					{
						if (ZH < 18 || ZH < 18 && button3[0] || ZH < 60 && button3[8] || ZH < 39 && button3[7] ||
							ZH < 30 && button3[6] || ZH < 26 && button3[5] || ZH < 23 && button3[4] || ZH < 21 && button3[3] ||
							ZH < 19 && button3[2]) 
						{
							if (j == 2 && i == 0)S[0][++ZH] = '1';
							else if (j == 2 && i == 1 && input(2))S[0][++ZH] = '2';
							else if (j == 2 && i == 2 && input(3))S[0][++ZH] = '3';
							else if (j == 1 && i == 0 && input(4))S[0][++ZH] = '4';
							else if (j == 1 && i == 1 && input(5))S[0][++ZH] = '5';
							else if (j == 1 && i == 2 && input(6))S[0][++ZH] = '6';
							else if (j == 0 && i == 0 && input(7))S[0][++ZH] = '7';
							else if (j == 0 && i == 1 && input(8))S[0][++ZH] = '8';
							else if (j == 0 && i == 2 && input(9))S[0][++ZH] = '9';
							else if (j == 1 && i == 3)S[0][++ZH] = '0';
							everone();
						}
						if (j == 0 && i == 3 && ZH >= 0) 
						{
							S[0][ZH--] = '\0';
							everone();
						}
						else if (j == 2 && i == 3)
						{
							memset(S[0], 0, sizeof(S[0]));
							everone();
							ZH = -1;
						}
					}
				}
				else transformation.button[i][j] = false;
			}
		}
		if (bignumber.button1[7])
		{
			for (int i = 0; i < 9; i++)
			{
				if (m.y >= 55 + 39 * i&&m.y <= 95 + 39 * i)
				{
					button2[i] = true;
					if (m.uMsg == WM_LBUTTONUP) {
						bignumber.button1[7] = false;
						button3[i] = true;
						memset(S[0], 0, sizeof(S[0]));
						everone();
						ZH = -1;
						for (int j = 0; j < 9; j++)
							if (i != j)
								button3[j] = false;
					}
				}
				else 
				{
					button2[i] = false;
					if (m.uMsg == WM_LBUTTONUP)
						bignumber.button1[7] = false;
				}
			}
			if (m.uMsg == WM_MOUSEWHEEL)
			{
				if (m.wheel < 0)
					transformation.fly1 -= 40;
				else
					transformation.fly1 += 40;
			}
		}
		if (m.x > 5 && m.x < 40 && m.y > 30 && m.y < 50) //设置
		{
			transformation.help[0] = true;
			if (m.uMsg == WM_LBUTTONUP) transformation.software[0] = -1, transformation.software[2] = 6;
		}
		else transformation.help[0] = false;

		if (m.x > 350 && m.x < 380 && m.y>30 && m.y < 50)bignumber.button1[5] = true;
		else bignumber.button1[5] = false;

		if (m.x > 382 && m.x < 400 && m.y>405 && m.y < 425) 
		{
			bignumber.button1[6] = true;
			if (m.uMsg == WM_LBUTTONUP) 
			{
				bignumber.button1[7] = true;
			}
		}
		else bignumber.button1[6] = false;
		if (m.uMsg == WM_MOUSEWHEEL && !bignumber.button1[7])
		{
			if (m.wheel < 0)
				transformation.fly -= 40;
			else
				transformation.fly += 40;
		}
	}
	if (transformation.fly > 0)
		transformation.fly -= (transformation.fly / 2);
	if (transformation.fly < -1480)
		transformation.fly += -(transformation.fly + 1480) / 2;

	if (transformation.fly1 > 0)
		transformation.fly1 -= (transformation.fly1 / 2);
	if (transformation.fly1 < 0)
		transformation.fly1 += -transformation.fly1 / 2;
}

void Conversion::showscreen3()
{
	BeginBatchDraw();//开始批量绘图

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	setlinestyle(PS_SOLID, 1, 0, 0);

	switch (option.WindowStyle)
	{
	case 0:  Setcolor(0, 406, 55, 400); break;
	case 1:  Setcolor(0, 406, 55, 400, RGB(180, 180, 180)); break;
	default: changecolor(0, 406, 55, 400, 0.0008f, 0.3f); break;
	}             

	settextcolor(WHITE);
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, 50, false, false, false);
	if (int(_tcslen(S[1]) < 45))outtextxy(5, 60 + transformation.fly, _T("  2 :"));
	else outtextxy(5, 56 + transformation.fly, _T("  2 :"));
	for (int i = 3; i < 63; i++) 
	{
		_stprintf_s(S[64], _T("%3d :"), i);
		outtextxy(5, 90 + 30 * (i - 3) + transformation.fly, S[64]);
	}

	if (S[0][0] == '\0') 
	{
		for (int i = 0; i < 61; i++)
			outtextxy(40, 60 + 30 * i + transformation.fly, _T("0"));
	}
	else {
		if (int(_tcslen(S[1]) < 44)) 
		{
			RECT r1 = { 40 ,60 + transformation.fly ,395,80 + transformation.fly };
			drawtext(S[1], &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
		else 
		{
			RECT r1 = { 40 ,55 + transformation.fly ,395,90 + transformation.fly };
			drawtext(S[1], &r1, DT_WORDBREAK | DT_INTERNAL);
		}
		for (int i = 0; i < 60; i++) 
		{
			RECT r1 = { 40,90 + i * 30 + transformation.fly,400,110 + i * 30 + transformation.fly };
			drawtext(S[i + 2], &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
	}

	if (bignumber.button1[7])
	{
		IMAGE blacks = MyLoadImage.setimage(406, 360, RGB(0, 0, 0));//设置绘图
		MyPutimage.my_putimage(0, 45, &blacks, RGB(255, 255, 255), 0, 1, 80, 0);

		settextstyle(25, 0, _T("微软雅黑"), 0, 0, 50, false, false, false);
		for (int i = 0; i < 9; i++) 
		{
			if (button3[i])
			{
				setfillcolor(RGB(100, 100, 100));
				setfillstyle(BS_SOLID);
				solidrectangle(2, transformation.fly1 + 52 + 39 * i, 403, transformation.fly1 + 90 + 39 * i);
			}
			
		}
		for (int i = 0; i < 9; i++)
		{
			if (button2[8 - i])
				settextcolor(HSLtoRGB(190, 1, 0.5));
			else
				settextcolor(WHITE);
			MyChar s[30];
			_stprintf_s(s, _T("输入%d进制数"), i + 2);
			outtextxy(150, 60 + 39 * (8 - i) + transformation.fly1, s);
		}
		setlinecolor(HSLtoRGB(190, 1, 0.5));
		rectangle(1, 56, 404, 399);
	}

	switch (option.WindowStyle)
	{
	case 0:  Setcolor(0, 406, 0, 55); break;
	case 1:  Setcolor(0, 406, 0, 55, RGB(180, 180, 180)); break;
	default: changecolor(0, 406, 0, 55, 0.0008f, 0.3f); break;
	}   

	IMAGE black = MyLoadImage.setimage(406, 55, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	switch (option.WindowStyle)
	{
	case 0:  Setcolor(0, 406, 400, 600); break;
	case 1:  Setcolor(0, 406, 400, 600, RGB(180, 180, 180));break;
	default: changecolor(0, 406, 400, 600, 0.0008f, 0.3f); break;
	}
	  
	black = MyLoadImage.setimage(406, 545, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 55, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	Window_Message.GetFunctionName(_T("进制转换"));

	IMAGE blacks = MyLoadImage.setimage(100, 50, RGB(0, 0, 0));//设置绘图

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j < 3 && i <= 2 || j == 1 && i == 3) 
			{
				if (!transformation.button[i][j])MyPutimage.my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 90, 0);
				else MyPutimage.my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 50, 0);
			}
			else
			{
				if (!transformation.button[i][j])MyPutimage.my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 70, 0);
				else
				{
					IMAGE black = MyLoadImage.setimage(100, 50, RGB(240, 0, 0));//设置绘图
					MyPutimage.my_putimage(i * 102, 444 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
				}
			}
		}
	}
	settextstyle(25, 0, _T("Wingdings"), 0, 0, 1, false, false, false);
	outtextxy(340, 458, 0xD5);
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(40, 560, '1');
	outtextxy(142, 560, '2');
	outtextxy(244, 560, '3');
	outtextxy(40, 508, '4');
	outtextxy(142, 508, '5');
	outtextxy(244, 508, '6');
	outtextxy(40, 456, '7');
	outtextxy(142, 456, '8');
	outtextxy(244, 456, '9');
	outtextxy(342, 560, _T("CE"));
	outtextxy(348, 508, '0');

	settextstyle(25, 0, _T("微软雅黑"), 0, 0, 50, false, false, false);
	if (!bignumber.button1[6])settextcolor(WHITE);
	else settextcolor(HSLtoRGB(190, 1, 0.5));
	if (!bignumber.button1[7])outtextxy(380, 405, _T("▲"));
	else outtextxy(380, 405, _T("▼"));

	if (ZH == -1) 
	{
		settextcolor(WHITE);
		RECT r1 = { 10,390 ,380,450 };
		settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
		drawtext('0', &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	else if (ZH < 18 || ZH < 18 && button3[0] || ZH < 60 && button3[8] || ZH < 39 && button3[7] ||
		ZH < 30 && button3[6] || ZH < 26 && button3[5] || ZH < 23 && button3[4] || ZH < 21 && button3[3] ||
		ZH < 19 && button3[2])
	{
		settextcolor(WHITE);
		RECT r1 = { 10 ,390 ,380,450 };
		transformation.callen1(S[0]);//计算字符串长度
		drawtext(S[0], &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	else
	{
		settextcolor(WHITE);
		RECT r1 = { 10 ,390 ,380,450 };
		settextstyle(35, 0, _T("微软雅黑"));
		drawtext(s0, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
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
		
		IMAGE blacks = MyLoadImage.setimage(180, 130, RGB(0, 0, 0));//设置绘图
		MyPutimage.my_putimage(210, 50, &blacks, RGB(255, 255, 255), 0, 0, 80, 0);

		setlinecolor(RGB(0, 238, 238));
		rectangle(210, 50, 390, 180);
		settextcolor(RGB(194, 203, 223));
		settextstyle(22, 0, _T("微软雅黑"));
		outtextxy(220, 55, _T("输入n进制数可以转换"));
		outtextxy(220, 80, _T("为其他进制的数( 2-62"));
		outtextxy(220, 105, _T("进制),用小写字母a-z"));
		outtextxy(220, 130, _T("表示10-35，大写字母"));
		outtextxy(220, 155, _T("A-Z表示36-61。"));
	}
	EndBatchDraw();
}

void Conversion::conversion(MyChar *sss, long long x, int n)
{

	std::stack<int> t;//声明栈

	while (x) 
	{
		t.push(x%n);//入栈
		x /= n;
	}
	memset(sss, 0, sizeof(sss));//初始化sss
	int i(0);
	while (!t.empty()) //如果不为空
	{
		int k = t.top();
		char s;
		t.pop();
		if (k <= 9)s = k + '0';
		else if (k > 9 && k <= 35)s = k - 10 + 'a';
		else s = k - 36 + 'A';
		if (i == 44)sss[i++] = '\n';
		sss[i++] = s;
	}
}

void Conversion::memse()//初始化函数
{
	for (int i = 1; i < 61; i++)
		memset(S[i], 0, sizeof(S[i]));
}

void Conversion::everone(int n)
{
	memse();

	int t(0);
	for (int i = 0; i < 9; i++)
	{
		if (button3[i]) 
		{
			t = i;
			break;
		}
	}
	long long sum(0);
	for (int i = 0; i < (int)_tcslen(S[0]); i++) 
	{
		sum += sum * (9 - t) + S[0][i] - '0';
	}
	for (int i = 1; i < 62; i++)
		conversion(S[i], sum, i + 1);//进制
}

void Conversion::changecolor(int Left, int Right, int Top, int Bottom, float l, float k, bool t)
{

	transformation.H += k;	    // 色相
	float S = 1;		        // 饱和度
	float L = 0.2f;		        // 亮度
	if (transformation.H > 360)transformation.H = 0;
	for (int y = Left; y < Right; y++) 
	{
		if (!t)
		{
			L += l;
			setlinecolor(HSLtoRGB(transformation.H, S, L));
		}
		else 
		{
			L += l;
			setlinecolor(HSLtoRGB(float(((int)transformation.H + 150) % 360), S, L));
		}
		line(y, Top, y, Bottom);
	}
}

void Conversion::Setcolor(int Left, int Right, int Top, int Bottom, COLORREF rgb)
{
	setfillcolor(rgb);
	solidrectangle(Left, Top, Right, Bottom);
}

void Conversion::ConversionFuction(int &k)
{
	while (true)
	{
		updatewithinput3();
		showscreen3();
		if (k != transformation.software[0] + 1) break;
		Sleep(option.Performance);     // 延时
	}
}

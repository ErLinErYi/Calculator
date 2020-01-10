#include"Standard.h"

using namespace std;

Standard standard;

Standard::Standard()
{
	int fx = 0, fy = 0;                       	                 // 判断是否可以左或者有移动算式
	int color = 0, color1 = 0;                                 	 // 如果左或者右可以移动，颜色变化
	int screenmove = 0;                      	                 // 由于算式不能完全显示。算式的左右移动像素
	bool Left_String_move = false, Right_String_move = false;    // 判断是否可以滑动
}

void Standard::screenmovehd()
{
	if (Left_String_move && String_Move < 60)		{		String_Move += 8;		    screenmove += 8;	     }
	if (String_Move >= 60)			                {		Left_String_move = false;   String_Move = 0;		 }
	if (Right_String_move && String_Move < 60)	    {		String_Move += 8;		    screenmove -= 8;	     }
	if (String_Move >= 60)			                {		Right_String_move = false;	String_Move = 0;		 }

	if ((int)(textwidth(ZFC1) + 11 * _tcslen(ZFC1)) >= 400 + screenmove)fx = 1;
	else fx = 0;
	if (screenmove > 0)fy = 1;
	else fy = 0;

	if (fx != 0)
	{
		settextstyle(30, 00, _T("微软雅黑"));
		if (!color)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(10, 83, _T("<"));
	}

	if (fy != 0)
	{
		settextstyle(30, 00, _T("微软雅黑"));
		if (!color1)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(370, 83, _T(">"));
	}
}

void Standard::ConMove(MOUSEMSG m)
{
	if (m.x >= 5 && m.x < 40 && m.y>80 && m.y < 110 && fx == 1)
	{
		color = 1;
		if (m.uMsg == WM_LBUTTONUP)
			Left_String_move = true;
	}
	else color = 0;

	if (m.x >= 375 && m.x < 395 && m.y>80 && m.y < 110 && fy == 1)
	{
		color1 = 1;
		if (m.uMsg == WM_LBUTTONUP)
			Right_String_move = true;
	}
	else color1 = 0;
}


void Standard::operation(MyChar C)
{
	if (Number_Length >= 0)
	{
		if(!String_Length&&!_tcslen(ZFC1)) String_Length += Number_Length;
		else String_Length += Number_Length + 1;
		_tcscat_s(ZFC1, ZFC);
		memset(ZFC, 0, sizeof(ZFC));
		Number_Length = -1;
		if (ZFC1[String_Length] != '+'&&ZFC1[String_Length] != '-'
			&&ZFC1[String_Length] != L'×'&&ZFC1[String_Length] != L'÷')
			ZFC1[++String_Length] = C;
		else
			ZFC1[String_Length] = C;
		ZFC1[String_Length + 1] = '\0';
		Decimal_Point = false;
	}		
	if (ZFC1[String_Length] == '+'||ZFC1[String_Length] == '-'
		||ZFC1[String_Length] == L'×'||ZFC1[String_Length] == L'÷')
		ZFC1[String_Length] = C;
	if (ZFC1[String_Length] == ')')
	{
		ZFC1[++String_Length] = C;
		ZFC1[String_Length + 1] = '\0';
	}
}

void Standard::OperationFuction(int i, int j)
{
	if (ZFC3[0] != '\0')
	{
		memset(ZFC, 0, sizeof(ZFC));
		memset(ZFC3, 0, sizeof(ZFC3));
	}
	if (Number_Length < 17)
	{
		if (ZFC1[String_Length] != ')')
		{
			if (j == 3 && i == 0)ZFC[++Number_Length] = '1';
			else if (j == 3 && i == 1)ZFC[++Number_Length] = '2';
			else if (j == 3 && i == 2)ZFC[++Number_Length] = '3';
			else if (j == 2 && i == 0)ZFC[++Number_Length] = '4';
			else if (j == 2 && i == 1)ZFC[++Number_Length] = '5';
			else if (j == 2 && i == 2)ZFC[++Number_Length] = '6';
			else if (j == 1 && i == 0)ZFC[++Number_Length] = '7';
			else if (j == 1 && i == 1)ZFC[++Number_Length] = '8';
			else if (j == 1 && i == 2)ZFC[++Number_Length] = '9';
			else if (j == 0 && i == 1)ZFC[++Number_Length] = '0';
		}
		if (j == 0 && i == 3 && ZFC[Number_Length] != '.')      operation(L'÷');
		else if (j == 1 && i == 3 && ZFC[Number_Length] != '.') operation(L'×');
		else if (j == 2 && i == 3 && ZFC[Number_Length] != '.')	operation('-');
		else if (j == 3 && i == 3 && ZFC[Number_Length] != '.') operation('+');
		else if (j == 4 && i == 1)
		{
			if (!Decimal_Point&&ZFC[Number_Length] >= '0'&&ZFC[Number_Length] <= '9')
			{
				ZFC[++Number_Length] = '.';
				Decimal_Point = true;
			}
		}
	}
	if (j == 4 && i == 0)
	{
		memset(ZFC, 0, sizeof(ZFC));
		Decimal_Point = false;
		Number_Length = -1;
		Left_Brackets++;
		if (!String_Length && !_tcslen(ZFC1))ZFC1[String_Length] = '(';
		else ZFC1[++String_Length] = '(';
		ZFC1[String_Length + 1] = '\0';
	}
	else if (j == 0 && i == 0)
	{
		memset(ZFC, 0, sizeof(ZFC));
		memset(ZFC1, 0, sizeof(ZFC1));
		memset(ZFC3, 0, sizeof(ZFC3));
		Number_Length = -1;
		String_Length = 0;
		Decimal_Point = false;
		Left_Brackets = 0;
		fx = 0, fy = 0;
		color = 0, color1 = 0;
		screenmove = 0;
		Left_String_move = false, Right_String_move = false;
	}
	else if (j == 0 && i == 2)
	{
		if (ZFC[Number_Length] == '.')Decimal_Point = false;
		if (Number_Length >= 0)ZFC[Number_Length--] = '\0';
	}
	else if (j == 4 && i == 2 && ZFC[Number_Length] != '.')
	{
		if (Left_Brackets > 0) {
			if (Number_Length == -1 && (ZFC1[String_Length] == '+' || ZFC1[String_Length] == '-' || ZFC1[String_Length] == L'×' || ZFC1[String_Length] == L'÷'));
			else
			{
				_tcscat_s(ZFC1, 10000, ZFC);
				String_Length += Number_Length + 1;
				Number_Length = -1;
				if (!_tcslen(ZFC))ZFC1[++String_Length] = '0';
				ZFC1[++String_Length] = ')';
				ZFC1[String_Length + 1] = '\0';
				Left_Brackets--;
				memset(ZFC, 0, sizeof(ZFC));
			}
		}
	}

	else if (j == 4 && i == 3 && ZFC[Number_Length] != '.' && !Left_Brackets)
	{
		if (ZFC1[String_Length] != L'÷' || ZFC1[String_Length] == L'÷' && _tcslen(ZFC))
		{
			fx = 0, fy = 0;
			screenmove = 0;
			_tcscat_s(ZFC1, ZFC);
			String_Length += Number_Length + 1;
			if (!(ZFC1[String_Length] >= '0'
				&&ZFC1[String_Length] <= '9')
				&& ZFC1[String_Length] != ')'
			    ) 
				ZFC1[++String_Length] = '0';

			if (String_Length != 0 && _tcslen(ZFC1)) change();
			String_Length = 0;
			Number_Length = -1;
			Decimal_Point = false;
			memset(ZFC1, 0, sizeof(ZFC1));
			memset(ZFC, 0, sizeof(ZFC));
		}
	}
}

void Standard::updatewithinput_()
{
	
	while (true)
	{
		bool BREAK = false;
		while (_kbhit())
		{
			switch (_getch())
			{
			case '1': OperationFuction(0, 3); transformation.button[0][3] = true; ; break;
			case '2': OperationFuction(1, 3); transformation.button[1][3] = true; ; break;
			case '3': OperationFuction(2, 3); transformation.button[2][3] = true; ; break;
			case '4': OperationFuction(0, 2); transformation.button[0][2] = true; ; break;
			case '5': OperationFuction(1, 2); transformation.button[1][2] = true; ; break;
			case '6': OperationFuction(2, 2); transformation.button[2][2] = true; ; break;
			case '7': OperationFuction(0, 1); transformation.button[0][1] = true; ; break;
			case '8': OperationFuction(1, 1); transformation.button[1][1] = true; ; break;
			case '9': OperationFuction(2, 1); transformation.button[2][1] = true; ; break;
			case '0': OperationFuction(1, 0); transformation.button[1][0] = true; ; break;
			case '.': OperationFuction(1, 4); transformation.button[1][4] = true; ; break;
			case 8  : OperationFuction(2, 0); transformation.button[2][0] = true; ; break;
			case '+': OperationFuction(3, 3); transformation.button[3][3] = true; ; break;
			case '-': OperationFuction(3, 2); transformation.button[3][2] = true; ; break;
			case '*': OperationFuction(3, 1); transformation.button[3][1] = true; ; break;
			case '/': OperationFuction(3, 0); transformation.button[3][0] = true; ; break;
			case 13 : OperationFuction(3, 4); transformation.button[3][4] = true; ; break;
			}
			BREAK = true;
		}
		
		while (MouseHit())	// 检查是否有鼠标消息
		{
			MOUSEMSG m;	// 定义鼠标消息
			m = GetMouseMsg();

			Window_Message.windowmessage(m); //移动窗口

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (m.x > i * 102 + 3 && m.x < i * 102 + 97 && m.y>340 + j * 52 && m.y < 390 + j * 52)
					{
						transformation.button[i][j] = true;
						if (m.uMsg == WM_LBUTTONUP)
						{
							OperationFuction(i, j);
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
					transformation.software[2] = 2;
					fx = 0, fy = 0;
					screenmove = 0;
				}
			}
			else transformation.help[0] = false;

			ConMove(m);
			BREAK = true;
		}
		
		if (BREAK)break;

		Sleep(50);

		if (GetHWnd() != GetForegroundWindow())
		{
			if (!CLEARN)
			{
				CLEARN = true;
				memset(Window_Message.ButtonId, 0, sizeof(Window_Message.ButtonId));
				memset(transformation.button, 0, sizeof(transformation.button));
				showscreen_();
			}
		}
		else CLEARN = false;
		if (!FIRSTSHOW)
		{
			FIRSTSHOW = true;
			showscreen_();
		}
		
		Sleep(200);
	}
}


void Standard::showscreen_()
{
	BeginBatchDraw();

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	
	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 406, 0, 600);                     break;
	case 1:  conversion.Setcolor(0, 406, 0, 600, RGB(180, 180, 180)); break;
	default: conversion.changecolor(0, 406, 0, 600);                  break;
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
					MyPutimage.my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 20, 0);
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
					else if (j == 4 && i == 0 || j == 4 && i == 2 || j <= 4 && j >= 0 && i == 3)
					{
						IMAGE green = MyLoadImage.setimage(100, 50, HSLtoRGB(195,1,0.5f));	// 设置绘图
						MyPutimage.my_putimage(i * 102, 340 + j * 52, &green, RGB(255, 255, 255), 0, 1, 50, 0);
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
	
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, _T("Wingdings"), 0, 0, 1, false, false, false);
	outtextxy(237, 354, 0xD5);

	Window_Message.GetFunctionName(_T("标准"));

	settextcolor(WHITE);
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextstyle(26, 0, _T("Consolas"));
	outtextxy(37, 352, _T("CE"));
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(142, 560, '.');
	outtextxy(142, 350, '0');
	outtextxy(36, 560, '(');
	outtextxy(40, 508, '1');
	outtextxy(142, 508, '2');
	outtextxy(244, 508, '3');
	outtextxy(40, 456, '4');
	outtextxy(142, 456, '5');
	outtextxy(244, 456, '6');
	outtextxy(40, 404, '7');
	outtextxy(142, 404, '8');
	outtextxy(244, 404, '9');
	outtextxy(248, 560, ')');
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(347, 500, '+');
	outtextxy(347, 344, _T("÷"));
	outtextxy(347, 396, _T("×"));
	outtextxy(347, 552, '=');
	settextstyle(40, 25, _T("Consolas"));
	outtextxy(344, 448, '-');

	settextstyle(15, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
	if (Left_Brackets > 0)
	{
		MyChar s[5];
		_stprintf_s(s, _T("%d"), Left_Brackets);
		outtextxy(55, 578, s);
	}

	screenmovehd();	// 字符串滑动动画
	

	settextcolor(WHITE);
	if (ZFC3[0] == '\0')
	{
		if (Number_Length == -1)
		{
			RECT r1 = { 10,200 ,380,300 };
			settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
			drawtext('0', &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
		else
		{
			RECT r1 = { 10,200 ,380,300 };
			transformation.callen(ZFC);	// 计算字符串长度
			drawtext(ZFC, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}

		if (String_Length >= 0)
		{
			RECT r1 = { -10010,100 ,400 + screenmove,150 };
			transformation.callen(ZFC1);// 计算字符串长度
			drawtext(ZFC1, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
	}
	else
	{
		RECT r1 = { 10,100 ,400,150 };
		transformation.callen2(ZFC3);
		drawtext(ZFC3, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	FlushBatchDraw();
}

void Standard::change()	// 中缀表达式变为后缀表达式
{
	My_Stack MyStack;
	MyStack.clearstack();
	int a = (int)_tcslen(ZFC1), k(0);
	memset(ZFC2, 0, sizeof(ZFC2));
	for (int i = 0; i < a; i++)
	{
		if (ZFC1[i] >= '0'&&ZFC1[i] <= '9' || ZFC1[i] == '.')ZFC2[k++] = ZFC1[i];
		else if (ZFC1[i] == '(')MyStack.push(ZFC1[i]), ZFC2[k++] = '#';
		else if (ZFC1[i] == '+' || ZFC1[i] == '-')
		{
			ZFC2[k++] = '#';
			while ((MyStack.top() == '-' || MyStack.top() == L'×' || MyStack.top() == L'÷' || MyStack.top() == '+')&&MyStack.top() != '(')
			{
				ZFC2[k++] = MyStack.top(), ZFC2[k++] = '#';
				MyStack.pop();
			}
			MyStack.push(ZFC1[i]);
		}
		else if (ZFC1[i] == L'×' || ZFC1[i] == L'÷')
		{
			ZFC2[k++] = '#';
			while (MyStack.top() == L'×' || MyStack.top() == L'÷'&&MyStack.top() != '(')
			{
				ZFC2[k++] = '#', ZFC2[k++] = MyStack.top();
				MyStack.pop();
			}
			MyStack.push(ZFC1[i]);
		}
		else if (ZFC1[i] == ')')
		{
			while (MyStack.top() != '(' && !MyStack.empty())
			{
				if (MyStack.top() >= '0'&&MyStack.top() <= '9')ZFC2[k++] = MyStack.top();
				else if (MyStack.top() == '+' || MyStack.top() == '-' || MyStack.top() == L'×' || MyStack.top() == L'÷')
				{
					ZFC2[k++] = '#';
					ZFC2[k++] = MyStack.top();
				}
				MyStack.pop();
			}
			MyStack.pop();
		}
	}
	while (!MyStack.empty())
	{
		ZFC2[k++] = '#';
		ZFC2[k++] = MyStack.top();
		MyStack.pop();
	}
	ZFC2[k++] = '#';

	calculate();  //计算
}

void Standard::calculate()	// 计算后缀表达式的值
{
	long double sum(A);
	MyChar s[1000];
	stack<long double> p;
	for (int i = 0; i < (int)(_tcslen(ZFC2)); i++)
	{
		if (ZFC2[i] >= '0'&&ZFC2[i] <= '9')
		{
			memset(s, 0, sizeof(s));
			int n(0);
			for (int j = i; j < (int)(_tcslen(ZFC2)); j++)
			{
				if (ZFC2[j] == '.' || ZFC2[j] >= '0'&&ZFC2[j] <= '9')
					s[n++] = ZFC2[j];
				else
				{
					i = j;
					break;
				}
			}
			s[n] = '\0';
			_stscanf_s(s, _T("%lg"), &sum);
		}
		if (ZFC2[i] == '#'&&sum != A)
		{
			p.push(sum);
			sum = A;
		}

		long double a, b;
		if (ZFC2[i] == '+')		{	a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(a + b);	}
		if (ZFC2[i] == '-')		{	a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(b - a);	}
		if (ZFC2[i] == L'×')   {   a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(a * b);  }
		if (ZFC2[i] == L'÷')   {	a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(b / a);	}
		
	}
	if (!p.empty())
	{
		long double x = p.top();
		
		_stprintf_s(ZFC3, _T("%.*lg"), option.DecimalDigit, x);
	}
	else _tcscpy_s(ZFC3, _T("违规操作！输入有误！请输入正确的算式！"));
}


void Standard::StandardFuction(int &k)
{
	while (true)
	{
		updatewithinput_();
		showscreen_();
		if (k != transformation.software[0] + 1) break;
		Sleep(option.Performance);     // 延时
	}
}
#include "Science.h"

Science science;
Standard Stad;

void Science::StorageEquation_Show_Move()
{
	if (Left_String_move && String_Move < 60)  { String_Move += 8;		    Move_Number += 8;  }
	if (String_Move >= 60)                     { Left_String_move = false;  String_Move = 0;   }
	if (Right_String_move && String_Move < 60) { String_Move += 8;		    Move_Number -= 8;  }
	if (String_Move >= 60)                     { Right_String_move = false;	String_Move = 0;   }

	if ((int)textwidth(StorageEquation_Show.c_str()) >= 390 + Move_Number)Judge_Left_Can_Move = 1;
	else Judge_Left_Can_Move = 0;
	if (Move_Number > 0)Judge_Right_Can_Move = 1;
	else Judge_Right_Can_Move = 0;

	if (Judge_Left_Can_Move != 0)
	{
		settextstyle(30, 0, _T("微软雅黑"));
		if (!Left_Clolor)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(0, 60, _T("<"));
	}

	if (Judge_Right_Can_Move != 0)
	{
		settextstyle(30, 0, _T("微软雅黑"));
		if (!Right_Color)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(390, 60, _T(">"));
	}
}

void Science::ConMove(MOUSEMSG m)
{
	if (m.x >= 0 && m.x < 20 && m.y>65 && m.y < 90 && Judge_Left_Can_Move == 1)
	{
		Left_Clolor = 1;
		if (m.uMsg == WM_LBUTTONUP)
			Left_String_move = true;
	}
	else Left_Clolor = 0;

	if (m.x >= 390 && m.x < 406 && m.y>65 && m.y < 90 && Judge_Right_Can_Move == 1)
	{
		Right_Color = 1;
		if (m.uMsg == WM_LBUTTONUP)
			Right_String_move = true;
	}
	else Right_Color = 0;
}

void Science::ShowLeftBrackets()
{
	if (Left_Brackets > 0 && PageTurn)
	{
		settextstyle(15, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
		MyChar s[5];
		_stprintf_s(s, _T("%d"), Left_Brackets);
		outtextxy(55, 578, s);
	}
}

void Science::RecordInput(int i, int j,bool page)
{
	// 翻页
	if (i == 0 && j == 2) PageTurn = (PageTurn == true) ? false : true;
	
	// 加减乘除
	else if (i == 3 && (j >= 2 &&j <= 5))
	{
		Push = true;
		DecimalPoint = false;
		// 计算x的y次方
		if (Calculator_TwoNumber)
		{
			if      (Calculator_TwoNumber == 1) Calculator_Function(Power_X_Y); // 计算
			else if (Calculator_TwoNumber == 2) Calculator_Function(Mod);       // 计算
			else if (Calculator_TwoNumber == 3) Calculator_Function(Square_X_Y);// 计算

			MyChar My[100];
			_stprintf_s(My, _T("%.15Lg"), PreNumber_Two);
			ScienceCalculator(_T(""), My); // 显示
			Calculator_TwoNumber = 0;
		}
		if (FinshCalculate)
		{
			StorageEquation_Calculator.clear();
			StorageEquation_Calculator_Last.clear();
			StorageEquation_Show.clear();
			StorageNumber.clear();
			FinshCalculate = false;
		}
		if (StorageNumber.empty()&& StorageEquation_Show.empty())StorageNumber += '0';
		if (!StorageNumber.empty()) // 不为空
		{
			if (StorageNumber.at(0) == '-')
			{
				StorageEquation_Calculator += '0';
				StorageEquation_Calculator += StorageNumber;
				StorageEquation_Calculator += Operator[j - 2];
			}
			else 
			{
				StorageEquation_Calculator += StorageNumber;
				StorageEquation_Calculator += Operator[j - 2];
			}
			StorageEquation_Show += StorageNumber;
			StorageEquation_Show += Operator[j - 2];

			StorageNumber.clear();
		}
		else
		{

			if (PreNumber)
			{
				PreNumber = 0;
				PreNumber_Two = 1;
				StorageEquation_Show += Operator[j - 2];
				StorageEquation_Calculator += Operator[j - 2];
			}
			if (StorageEquation_Show[StorageEquation_Show.size() - 1] == ')')
			{
				StorageEquation_Show += Operator[j - 2];
				StorageEquation_Calculator += Operator[j - 2];
			}
			if (StorageEquation_Show[StorageEquation_Show.size() - 1] == '+' ||
				StorageEquation_Show[StorageEquation_Show.size() - 1] == '-' ||
				StorageEquation_Show[StorageEquation_Show.size() - 1] == L'×' ||
				StorageEquation_Show[StorageEquation_Show.size() - 1] == L'÷'
				)
			{
				StorageEquation_Show[StorageEquation_Show.size() - 1] = Operator[j - 2];
				StorageEquation_Calculator[StorageEquation_Calculator.size() - 1] = Operator[j - 2];
			}
		}
		
	}
	// 清零
	else if (i == 1 && j == 2)
	{
		StorageNumber.clear();
		StorageEquation_Show.clear();
		StorageEquation_Calculator.clear();
		StorageEquation_Calculator_Last.clear();
		Judge_Left_Can_Move = 0;
		Judge_Right_Can_Move = 0;
		Calculator_TwoNumber = 0;
		String_Move = 0;
		Move_Number = 0;
		Left_Brackets = 0;
		PreNumber = 0;
		PreNumber_Two = 1;
		DecimalPoint = false;
		Push = false;
	}
	// 删除一位
	else if (i == 2 && j == 2)
	{
		if (!StorageNumber.empty())
		{
			if (StorageNumber[StorageNumber.size() - 1] == '.')
				DecimalPoint = false;
			StorageNumber.pop_back();
		}
	}
	
	// 等于
	else if (i == 3 && j == 6 && !Left_Brackets)
	{
		// 计算x的y次方
		if (Calculator_TwoNumber)
		{
			if (Calculator_TwoNumber == 1) Calculator_Function(Power_X_Y); // 计算
			else if (Calculator_TwoNumber == 2) Calculator_Function(Mod);       // 计算
			else if (Calculator_TwoNumber == 3) Calculator_Function(Square_X_Y);// 计算

			MyChar My[100];
			_stprintf_s(My, _T("%.15Lg"), PreNumber_Two);
			ScienceCalculator(_T(""), My); // 显示
			Calculator_TwoNumber = 0;
		}
		StorageEquation_Show += StorageNumber; // 显示
		StorageEquation_Show += '=';
		StorageEquation_Calculator += StorageNumber; // 计算
		MiddleEquationToLast();
		StorageEquation_Calculator.clear();
		StorageEquation_Calculator_Last.clear();
		Judge_Left_Can_Move = 0;
		Judge_Right_Can_Move = 0;
		Calculator_TwoNumber = 0;
		String_Move = 0;
		Move_Number = 0;
		PreNumber = 0;
		PreNumber_Two = 1;
		FinshCalculate = true;
		DecimalPoint = false;
		Push = false;
	}
	// 输入数字
	else if (j >= 3 && j <= 5 && i >= 0 && i <= 3 || j == 6 && i == 1)
	{
		if (FinshCalculate)
		{
			StorageEquation_Calculator.clear();
			StorageEquation_Calculator_Last.clear();
			StorageEquation_Show.clear();
			StorageNumber.clear();
			FinshCalculate = false;
		}
		if (StorageEquation_Show.empty() || (!StorageEquation_Show.empty() &&
			StorageEquation_Show[StorageEquation_Show.size() - 1] != ')'))
		{
			if (i == 1 && j == 6) StorageNumber += _T("0");
			else StorageNumber += Number[5 - j][i];
		}
	}

	if (!PageTurn)
	{
		// 开根号
		if (i == 0 && j == 1)
		{
			ScienceCalculator(_T("√("), _T(")")); // 显示
			Calculator_Function(Sqrt); // 计算
		}
		// 平方
		else if (i == 1 && j == 1)
		{
			ScienceCalculator(_T("("), _T(")²")); // 显示
			Calculator_Function(Square); // 计算
		}
		// log
		else if (i == 2 && j == 1)
		{
			ScienceCalculator(_T("log("), _T(")")); // 显示
			Calculator_Function(Log); // 计算
		}
		// 10的x次方
		else if (i == 3 && j == 1)
		{
			ScienceCalculator(_T("10^("), _T(")")); // 显示
			Calculator_Function(Ten_X); // 计算
		}
		// x的y次方
		else if (i == 0 && j == 0 && !PreNumber)
		{
			Calculator_TwoNumber = 1;
			ScienceCalculator(_T(""), _T("^")); // 显示
			Calculator_Function(Power_X_Y); // 计算 
			Push = true;
		}
		// sin
		else if (i == 1 && j == 0)
		{
			ScienceCalculator(_T("sin("), _T("°)")); // 显示
			Calculator_Function(Sin); // 计算 
		}
		// cos
		else if (i == 2 && j == 0)
		{
			ScienceCalculator(_T("cos("), _T("°)")); // 显示
			Calculator_Function(Cos); // 计算 
		}
		// Tan
		else if (i == 3 && j == 0)
		{
			ScienceCalculator(_T("tan("), _T("°)")); // 显示
			Calculator_Function(Tan); // 计算 
		}
		// 取反
		else if (i == 0 && j == 6)
		{
			if (!StorageNumber.empty())
				StorageNumber.at(0) == _T('-') ? StorageNumber.erase(0, 1) : StorageNumber.insert(0, _T("-"));
		}
		// 小数点
		else if (i == 2 && j == 6)
		{
			if (!DecimalPoint)
			{
				DecimalPoint = true;
				StorageNumber += _T(".");
			}
		}
	}
	else 
	{
		// E^X
		if (i == 0 && j == 1)
		{
			ScienceCalculator(_T("e^("), _T(")")); // 显示
			Calculator_Function(E_X); // 计算
		}
		// 三次方
		else if (i == 1 && j == 1)
		{
			ScienceCalculator(_T("("), _T(")³")); // 显示
			Calculator_Function(Cube); // 计算
		}
		// ln
		else if (i == 2 && j == 1)
		{
			ScienceCalculator(_T("ln("), _T(")")); // 显示
			Calculator_Function(Ln); // 计算
		}
		// Mod
		else if (i == 3 && j == 1 && !PreNumber)
		{
			Calculator_TwoNumber = 2;
			ScienceCalculator(_T(""), _T(" Mod ")); // 显示
			Calculator_Function(Mod); // 计算
			Push = true;
		}
		// x的y 根号
		else if (i == 0 && j == 0 && !PreNumber)
		{
			Calculator_TwoNumber = 3;
			ScienceCalculator(_T(""), _T(" yroot ")); // 显示
			Calculator_Function(Square_X_Y); // 计算 
			Push = true;
		}
		// sin⁻¹
		else if (i == 1 && j == 0)
		{
			ScienceCalculator(_T("sin⁻¹("), _T(")")); // 显示
			Calculator_Function(ArcSin); // 计算 
		}
		// cos⁻¹
		else if (i == 2 && j == 0)
		{
			ScienceCalculator(_T("cos⁻¹("), _T(")")); // 显示
			Calculator_Function(ArcCos); // 计算 
		}
		// Tan⁻¹
		else if (i == 3 && j == 0)
		{
			ScienceCalculator(_T("tan⁻¹("), _T(")")); // 显示
			Calculator_Function(ArcTan); // 计算 
		}
		// 左括号
		else if (i == 0 && j == 6)
		{
			StorageNumber.clear();
			Left_Brackets++;
			StorageEquation_Show += '(';
			StorageEquation_Calculator += '(';
		}
		// 右括号
		else if (i == 2 && j == 6)
		{
			if (Left_Brackets > 0)
			{
				Left_Brackets--;
				StorageEquation_Show += StorageNumber;
				StorageEquation_Calculator += StorageNumber;
				StorageEquation_Show += ')';
				StorageEquation_Calculator += ')';
				StorageNumber.clear();
			}
		}
	}
}

void Science::ScienceCalculator(LPCTSTR Str, LPCTSTR Str1)
{
	if (!StorageEquation_Show.empty()) // 算式不为空
	{
		if (FinshCalculate) StorageEquation_Show.pop_back();

		// 判断算式最后是否有运算符
		if (StorageEquation_Show[StorageEquation_Show.size() - 1] == '+'   ||
			StorageEquation_Show[StorageEquation_Show.size() - 1] == '-'   ||
			StorageEquation_Show[StorageEquation_Show.size() - 1] == L'×' ||
			StorageEquation_Show[StorageEquation_Show.size() - 1] == L'÷')
		{
			wstring Now_str(Str);
			if (StorageNumber.empty()) Now_str += '0';
			else Now_str += StorageNumber;
			StorageEquation_Show += Now_str;
			StorageEquation_Show += Str1;
		}
		else
		{
			// 查找最后一个运算符
			wstring::size_type position = StorageEquation_Show.find_last_of(_T("+-×÷"));
			if (position != StorageEquation_Show.npos)
			{
				StorageEquation_Show.insert(position + 1, Str);
				StorageEquation_Show += Str1;
			}
			else
			{
				StorageEquation_Show.insert(0, Str);
				StorageEquation_Show += Str1;
			}
		}
	}
	else
	{
		StorageEquation_Show.insert(0, Str);
		if (StorageNumber.empty()) StorageEquation_Show += '0';
		else StorageEquation_Show += StorageNumber;
		StorageEquation_Show += Str1; 
	}
}

void Science::Calculator_Function(short N)
{
	if (!StorageNumber.empty())
	{
		if (StorageNumber.at(0) == '-')
		{
			StorageNumber.clear();
			StorageNumber = _T("无效输入");
			StorageEquation_Calculator.clear();
			StorageEquation_Calculator_Last.clear();
			FinshCalculate = true;
			return;
		}
	}
	if (PreNumber && N == Power_X_Y)   _stscanf_s(StorageNumber.c_str(), _T("%Lg"), &PreNumber_Two);
	if (PreNumber && N == Mod)         _stscanf_s(StorageNumber.c_str(), _T("%Lg"), &PreNumber_Two);
	if (PreNumber && N == Square_X_Y)  _stscanf_s(StorageNumber.c_str(), _T("%Lg"), &PreNumber_Two);

	if (!PreNumber) _stscanf_s(StorageNumber.c_str(), _T("%Lg"), &PreNumber);
	if (N == Mod && PreNumber_Two == 1)PreNumber_Two = PreNumber + 1;

	// 查找最后一个运算符
	wstring::size_type position = StorageEquation_Calculator.find_last_of(_T("+-×÷"));
	(position != StorageEquation_Calculator.npos) ? StorageEquation_Calculator.erase(position + 1) : StorageEquation_Calculator.erase(0);
	
	switch (N)
	{
	case Sqrt:       PreNumber = sqrtl(PreNumber);                    break;            // 开根号
	case Square:     PreNumber = powl(PreNumber, 2);                  break;            // 平方
	case Log:        PreNumber = log10l(PreNumber);                   break;            // logx
	case Ten_X:      PreNumber = powl(10, PreNumber);                 break;            // 10的x次方
	case Power_X_Y:  PreNumber = powl(PreNumber, PreNumber_Two);      break;            // x的y次方
	case Sin:        PreNumber = sin(PreNumber*Radian);               break;            // sin
	case Cos:        PreNumber = cos(PreNumber*Radian);               break;            // cos
	case Tan:        PreNumber = tan(PreNumber*Radian);               break;            // sin
	case E_X:        PreNumber = expl(PreNumber);                     break;            // e^x
	case Cube:       PreNumber = powl(PreNumber, 3);                  break;            // x^3
	case Ln:         PreNumber = logl(PreNumber);                     break;            // ln
	case Mod:        PreNumber = fmodl(PreNumber, PreNumber_Two);     break;            // Mod
	case Square_X_Y: PreNumber = powl(PreNumber, 1 / PreNumber_Two);  break;            // x根号y次
	case ArcSin:     PreNumber = asinl(PreNumber)/Radian;             break;            // arcsin
	case ArcCos:     PreNumber = acosl(PreNumber)/Radian;             break;            // arccos
	case ArcTan:     PreNumber = atanl(PreNumber)/Radian;             break;            // arctan
	}
	
	if (PreNumber < 0) StorageEquation_Calculator += '0';
	MyChar My[1000];
    _stprintf_s(My, _T("%.17Lg"), PreNumber);
	
	if (_tcsstr(My, _T("in")))
	{
		StorageNumber = _T("违规操作！输入有误！");
		StorageEquation_Calculator.clear();
		StorageEquation_Calculator_Last.clear();
		PreNumber = 0;
		PreNumber_Two = 1;
		FinshCalculate = true;
	}
	else
	{
		if (Push)
		{
			StorageEquation_Calculator += My;
			Push = false;
		}
		else  StorageEquation_Calculator = My;
		StorageNumber.clear();
	}
}


void Science::MiddleEquationToLast()
{
	My_Stack MyStack;

	for (int i = 0; i < StorageEquation_Calculator.size(); i++)
	{
		if ((StorageEquation_Calculator[i] >= '0'&&StorageEquation_Calculator[i] <= '9') ||StorageEquation_Calculator[i] == '.'||StorageEquation_Calculator[i]=='e'||
			((StorageEquation_Calculator[i]=='+'|| StorageEquation_Calculator[i]=='-')&&StorageEquation_Calculator[i-1] == 'e'))
			StorageEquation_Calculator_Last += StorageEquation_Calculator[i];

		else if (StorageEquation_Calculator[i] == '(')
		{
			MyStack.push(StorageEquation_Calculator[i]);
			StorageEquation_Calculator_Last += '#';
		}

		else if (StorageEquation_Calculator[i] == '+' || StorageEquation_Calculator[i] == '-')
		{
			StorageEquation_Calculator_Last += '#';
			while ((MyStack.top() == '-') || MyStack.top() == L'×' || MyStack.top() == L'÷' || MyStack.top() == '+' && MyStack.top() != '(')
			{
				StorageEquation_Calculator_Last += MyStack.top();
				StorageEquation_Calculator_Last += '#';
				MyStack.pop();
			}
			MyStack.push(StorageEquation_Calculator[i]);
		}
		else if (StorageEquation_Calculator[i] == L'×' || StorageEquation_Calculator[i] == L'÷')
		{
			StorageEquation_Calculator_Last += '#';
			while (MyStack.top() == L'×' || MyStack.top() == L'÷'&&MyStack.top() != '(')
			{
				StorageEquation_Calculator_Last += '#';
				StorageEquation_Calculator_Last += MyStack.top();
				MyStack.pop();
			}
			MyStack.push(StorageEquation_Calculator[i]);
		}
		else if (StorageEquation_Calculator[i] == ')')
		{
			while (MyStack.top() != '(' && !MyStack.empty())
			{
				if (MyStack.top() >= '0'&&MyStack.top() <= '9')StorageEquation_Calculator_Last += MyStack.top();
				else if (MyStack.top() == '+' || MyStack.top() == '-' || MyStack.top() == L'×' || MyStack.top() == L'÷')
				{
					StorageEquation_Calculator_Last += '#';
					StorageEquation_Calculator_Last += MyStack.top();
				}
				MyStack.pop();
			}
			MyStack.pop();
		}
	}
	while (!MyStack.empty())
	{
		StorageEquation_Calculator_Last += '#';
		StorageEquation_Calculator_Last += MyStack.top();
		MyStack.pop();
	}
	StorageEquation_Calculator_Last += '#';
	
	CalculatorLastEquation();  //计算
}

void Science::CalculatorLastEquation()
{
	long double sum(1.0e+308);
	wstring Str;
	stack<long double> p;
	for (int i = 0; i < StorageEquation_Calculator_Last.size(); i++)
	{
		if (StorageEquation_Calculator_Last[i] >= '0'&&StorageEquation_Calculator_Last[i] <= '9')
		{
			Str.clear();
			for (int j = i; j < StorageEquation_Calculator_Last.size(); j++)
			{
				if (StorageEquation_Calculator_Last[j] == '.' || StorageEquation_Calculator_Last[j] >= '0'&&StorageEquation_Calculator_Last[j] <= '9' ||
					StorageEquation_Calculator_Last[j] == 'e' || ((StorageEquation_Calculator_Last[j] == '+' || StorageEquation_Calculator_Last[j] == '-') && StorageEquation_Calculator_Last[j - 1] == 'e'))
					Str += StorageEquation_Calculator_Last[j];
				else
				{
					i = j;
					break;
				}
			}
			_stscanf_s(Str.c_str(), _T("%Lg"), &sum);
		}
		else
			StorageNumber = _T("违规操作！输入有误！");

		if (StorageEquation_Calculator_Last[i] == '#'&&sum != 1.0e+308)
		{
			p.push(sum);
			sum = 1.0e+308;
		}

		long double a, b;
		if (StorageEquation_Calculator_Last[i] == '+')   { a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(a + b); }
		if (StorageEquation_Calculator_Last[i] == '-')   { a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(b - a); }
		if (StorageEquation_Calculator_Last[i] == L'×') { a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(a * b); }
		if (StorageEquation_Calculator_Last[i] == L'÷') { a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(b / a); }
	}
	if (!p.empty())
	{
		long double x = p.top();
		MyChar My[1000];
		_stprintf_s(My, _T("%.*Lg"), option.DecimalDigit, x);
		StorageNumber = My;
	}
	else StorageNumber = _T("违规操作！输入有误！");

	StorageEquation_Calculator_Last.clear(); // 清零
}

void Science::updatewithinput()	// 与输入有关的更新
{
	MOUSEMSG m;			// 定义鼠标消息
	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();

		Window_Message.windowmessage(m); //移动窗口

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (m.x > i * 102+2 && m.x < i * 102 + 98 && m.y>240 + j * 52 && m.y < 286 + j * 52)
				{
					transformation.button[i][j] = true;

					if (m.uMsg == WM_LBUTTONUP)	// 如果按下左键
					{
						if (!PageTurn)
							RecordInput(i, j);
						else
							RecordInput(i, j, true);
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
				transformation.software[2] = 3;
			}
		}
		else transformation.help[0] = false;

		ConMove(m);
	}
}

void Science::showscreen()
{
	BeginBatchDraw();	// 开始批量绘图

	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 406, 0, 600); break;
	case 1:  conversion.Setcolor(0, 406, 0, 600, RGB(180, 180, 180)); break;
	default: conversion.changecolor(0, 406, 0, 600); break;
	}              

	setfillstyle(BS_SOLID);
	IMAGE blacks = MyLoadImage.setimage(406, 600, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 0, &blacks, RGB(255, 255, 255), 0, 1, 30, 0);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j >= 3 && j < 6 && i <= 2 || j == 6 && i == 1)
			{
				blacks = MyLoadImage.setimage(100, 50, RGB(0, 0, 0));	// 设置绘图
				if (!transformation.button[i][j])
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 90, 0);
				else
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 20, 0);
			}
	
			else if (i == 3 && j == 6 || j == 2 && i == 2 || j == 2 && i == 1)
			{

				if (!transformation.button[i][j])
				{
					blacks = MyLoadImage.setimage(100, 50, RGB(0, 0, 0));	// 设置绘图
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 70, 0);
				}
				else
				{
					IMAGE Red = MyLoadImage.setimage(100, 50, RGB(240, 0, 0));	// 设置绘图
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &Red, RGB(255, 255, 255), 0, 1, 50, 0);
				}
			}

			else if (j == 6 && i == 0 || j == 6 && i == 2 || j <= 5 && j > 1 && i == 3)
			{
				if (!transformation.button[i][j])
				{
					blacks = MyLoadImage.setimage(100, 50, RGB(0, 0, 0));	// 设置绘图
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 70, 0);
				}
				else
				{
					IMAGE green = MyLoadImage.setimage(100, 50, HSLtoRGB(195, 1, 0.5f));	// 设置绘图
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &green, RGB(255, 255, 255), 0, 1, 50, 0);
				}
			}
		    else
			{
				if (!transformation.button[i][j])
				{
					blacks = MyLoadImage.setimage(100, 50, RGB(0, 0, 0));	// 设置绘图
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 70, 0);
				}
				else
				{
					IMAGE black = MyLoadImage.setimage(100, 50, RGB(225, 100, 26));	// 设置绘图
					MyPutimage.my_putimage(i * 102, 236 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
				}
			}

		}
	}
	printf("%d\n", Push);
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	
	ShowLeftBrackets();

	settextstyle(25, 0, _T("Wingdings"), 0, 0, 1, false, false, false);
	outtextxy(237, 354, 0xD5);

	Window_Message.GetFunctionName(_T("科学"));

	settextcolor(WHITE);
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextstyle(26, 0, _T("Consolas"));
	outtextxy(138, 354, _T("CE"));
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(142, 560, '0');
	outtextxy(40, 508, '1');
	outtextxy(142, 508, '2');
	outtextxy(244, 508, '3');
	outtextxy(40, 456, '4');
	outtextxy(142, 456, '5');
	outtextxy(244, 456, '6');
	outtextxy(40, 404, '7');
	outtextxy(142, 404, '8');
	outtextxy(244, 404, '9');
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(347, 500, '+');
	outtextxy(347, 344, _T("÷"));
	outtextxy(347, 396, _T("×"));
	outtextxy(347, 552, '=');
	settextstyle(40, 25, _T("Consolas"));
	outtextxy(344, 448, '-');
	settextstyle(28, 0, _T("Calculator MDL2 Assets"), 0, 0, 1, false, false, false);
	outtextxy(33, 352, 0xE752);

	if (!PageTurn)
	{
		settextstyle(22, 0, _T("Consolas"));
		outtextxy(237, 305, _T("log"));
		outtextxy(135, 252, _T("sin"));
		outtextxy(237, 252, _T("cos"));
		outtextxy(341, 252, _T("tan"));
		settextstyle(22, 0, _T("Calculator MDL2 Assets"));
		outtextxy(37, 305, 0xE94B);
		outtextxy(36, 252, 0xF7CA);
		outtextxy(139, 305, 0xF7C8);
		outtextxy(344, 305, 0xF7CC);
		settextstyle(30, 0, _T("Consolas"));
		outtextxy(40, 560, _T("±"));
		outtextxy(244, 558, _T("."));
	}
	else 
	{
		setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 3, 0, 0);
		setlinecolor(HSLtoRGB(195, 1, 0.5f));
		line(1, 388, 98, 388);
		settextstyle(22, 0, _T("Consolas"));
		outtextxy(241, 305, _T("ln"));
		outtextxy(342, 305, _T("Mod"));
		outtextxy(128, 252, _T("sin⁻¹"));
		outtextxy(230, 252, _T("cos⁻¹"));
		outtextxy(332, 252, _T("tan⁻¹"));
		settextstyle(22, 0, _T("Calculator MDL2 Assets"));
		outtextxy(38, 305, 0xF7CE);
		outtextxy(36, 252, 0xF7CD);
		outtextxy(139, 305, 0xF7CB);
		settextstyle(30, 0, _T("Consolas"));
		outtextxy(36, 560, _T("("));
		outtextxy(248, 560, _T(")"));
		
	}
	
	if (!StorageNumber.empty())
	{
		RECT r = { 10, 150 ,380, 200 };
		settextcolor(WHITE);
		if (StorageNumber.find(_T("输入")) != StorageNumber.npos)settextstyle(40, 0, _T("微软雅黑"));
		else transformation.callen((TCHAR *)StorageNumber.c_str());
		drawtext(StorageNumber.c_str(), &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	else
	{
		RECT r = { 10, 150 ,380, 200 };
		settextcolor(WHITE);
		settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
		drawtext(_T("0"), &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	if (!StorageEquation_Show.empty())
	{
		RECT r = { -10010,50 ,387 + Move_Number ,100 };
		settextcolor(WHITE);
		transformation.callen((TCHAR *)StorageEquation_Show.c_str());
		drawtext(StorageEquation_Show.c_str(), &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	if (Judge_Left_Can_Move != 0)
	{
		switch (option.WindowStyle)
		{
		case 0:  conversion.Setcolor(0, 20, 62, 90); break;
		case 1:  conversion.Setcolor(0, 20, 62, 90, RGB(180, 180, 180)); break;
		default: conversion.changecolor(0, 20, 62, 90); break;
		}
	}
	if (Judge_Right_Can_Move != 0)
	{
		switch (option.WindowStyle)
		{
		case 0:  conversion.Setcolor(386, 406, 62, 90); break;
		case 1:  conversion.Setcolor(386, 406, 62, 90, RGB(180, 180, 180)); break;
		default: conversion.changecolor(386, 406, 62, 90); break;
		}
	}

	StorageEquation_Show_Move();

	EndBatchDraw();
}

void Science::ScienceFuction(int &k)
{
	while (true)
	{
		showscreen();
		updatewithinput();
		if (k != transformation.software[0] + 1)
			break;
		Sleep(option.Performance);						       // 延时
	}
}
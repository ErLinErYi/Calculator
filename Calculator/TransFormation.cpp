#include "Transformation.h"

TransData transdata;
TransFormation transformation;

// 初始化
void TransFormation::MemStr()
{
	memset(Tra, 0, sizeof(Tra));
	memset(TraEd, 0, sizeof(TraEd));
	memset(Button, 0, sizeof(Button));
	memset(Button1, 0, sizeof(Button1));
	xs = false;
	Tranumber = 0;
	Tranumber1 = 0;
	ReTra = -1;
}

// 数据转换
void TransFormation::Transform()
{
	memset(TraEd, 0, sizeof(TraEd));
	long double TransFormationNumber(0);

	if (Tranumber > Tranumber1)	// 如果输入的单位大于输入的单位
	{
		if (Tranumber1 != 0)	// 如果输出的单位不是“位”的话
		{
			_stscanf_s(Tra, _T("%Lg"), &TransFormationNumber);
			for (int i = 0; i < Tranumber - Tranumber1; i++)
				TransFormationNumber *= 1024;
			_stprintf_s(TraEd, _T("%.*Lg"), option.DecimalDigit, TransFormationNumber);
		}
		if (Tranumber1 == 0)	// 如果输出的单位是“位”的话
		{
			_stscanf_s(Tra, _T("%Lg"), &TransFormationNumber);
			for (int i = 0; i < Tranumber - Tranumber1 - 1; i++)
				TransFormationNumber *= 1024;
			TransFormationNumber *= 8;
			_stprintf_s(TraEd, _T("%.*Lg"), option.DecimalDigit, TransFormationNumber);
		}
	}
	else  if (Tranumber == Tranumber1)	// 输入等于输出的单位时
	{
		_tcscpy_s(TraEd, _tcslen(Tra) + 1, Tra);
	}
	else	// 输入的单位小于输出的
	{
		if (Tranumber != 0)	// 如果输入的单位不是“位”的话
		{
			_stscanf_s(Tra, _T("%Lg"), &TransFormationNumber);
			for (int i = 0; i < Tranumber1 - Tranumber; i++)
				TransFormationNumber /= 1024;
			_stprintf_s(TraEd, _T("%.*Lg"), option.DecimalDigit, TransFormationNumber);
		}
		if (Tranumber == 0)	// 如果输入的单位是“位”的话
		{
			_stscanf_s(Tra, _T("%Lg"), &TransFormationNumber);
			for (int i = 0; i < Tranumber1 - Tranumber - 1; i++)
				TransFormationNumber /= 1024;
			_stprintf_s(TraEd, _T("%.*Lg"), option.DecimalDigit, TransFormationNumber);
		}
	}
}	

// 温度转换
void TransFormation::Transform2()
{
	memset(TraEd, 0, sizeof(TraEd));
	long double TransFormationNumber(0);
	
	if(Tranumber== Tranumber1)  _tcscpy_s(TraEd, _tcslen(Tra) + 1,Tra);
	else
	{
		_stscanf_s(Tra, _T("%Lg"), &TransFormationNumber);
		if (Tranumber == 0 && Tranumber1 == 1)      TransFormationNumber *= 1.8 + 32;
		else if (Tranumber == 0 && Tranumber1 == 2) TransFormationNumber += 273.15;
		else if (Tranumber == 0 && Tranumber1 == 3) TransFormationNumber = TransFormationNumber * 1.8 + 32 + 459.67;
		else if (Tranumber == 0 && Tranumber1 == 4) TransFormationNumber *= 0.8;
		else if (Tranumber == 1 && Tranumber1 == 0) TransFormationNumber = (TransFormationNumber - 32) / 1.8;
		else if (Tranumber == 1 && Tranumber1 == 2) TransFormationNumber = (TransFormationNumber + 459.67) / 1.8;
		else if (Tranumber == 1 && Tranumber1 == 3) TransFormationNumber += 459.67;
		else if (Tranumber == 1 && Tranumber1 == 4) TransFormationNumber = (TransFormationNumber - 32) / 2.25;
		else if (Tranumber == 2 && Tranumber1 == 0) TransFormationNumber -= 273.15;
		else if (Tranumber == 2 && Tranumber1 == 1) TransFormationNumber = TransFormationNumber * 1.8 - 459.67;
		else if (Tranumber == 2 && Tranumber1 == 3) TransFormationNumber *= 1.8;
		else if (Tranumber == 2 && Tranumber1 == 4) TransFormationNumber = (TransFormationNumber - 273.15) * 0.8;
		else if (Tranumber == 3 && Tranumber1 == 0) TransFormationNumber = (TransFormationNumber - 32 - 459.67) / 1.8;
		else if (Tranumber == 3 && Tranumber1 == 1) TransFormationNumber -= 459.67;
		else if (Tranumber == 3 && Tranumber1 == 2) TransFormationNumber /= 1.8;
		else if (Tranumber == 3 && Tranumber1 == 4) TransFormationNumber = (TransFormationNumber - 459.67 - 32) / 2.25;
		else if (Tranumber == 4 && Tranumber1 == 0) TransFormationNumber *= 1.25;
		else if (Tranumber == 4 && Tranumber1 == 1) TransFormationNumber = TransFormationNumber * 2.25 + 32;
		else if (Tranumber == 4 && Tranumber1 == 2) TransFormationNumber = TransFormationNumber * 1.25 + 273.15;
		else if (Tranumber == 4 && Tranumber1 == 3) TransFormationNumber = TransFormationNumber * 2.25 + 32 + 459.67;
		_stprintf_s(TraEd, _T("%.*Lg"), option.DecimalDigit, TransFormationNumber);
	}
}	// 温度转换

// 其他转换
void TransFormation::Transform1(int Number)
{
	memset(TraEd, 0, sizeof(TraEd));
	long double TransFormationNumber(0);
	_stscanf_s(Tra, _T("%Lg"), &TransFormationNumber);
	TransFormationNumber *= transdata.Str[Number][Tranumber1][Tranumber];
	_stprintf_s(TraEd, _T("%.*Lg"), option.DecimalDigit, TransFormationNumber);
}

// 判断转换
void TransFormation::WhatC(int lens)
{
	if		(lens == sizeof(TraS)  / sizeof(TraS[0])) Transform();	    // 数据
	else if (lens == sizeof(TraC)  / sizeof(TraC[0])) Transform1(0);	// 长度
	else if (lens == sizeof(TraM)  / sizeof(TraM[0])) Transform1(1);	// 面积
	else if (lens == sizeof(TraT)  / sizeof(TraT[0])) Transform1(2);	// 体积
	else if (lens == sizeof(TraSH) / sizeof(TraSH[0]))Transform1(3);	// 时间
	else if (lens == sizeof(TraW)  / sizeof(TraW[0])) Transform2();	    // 温度
	else if (lens == sizeof(TraSD) / sizeof(TraSD[0]))Transform1(4);	// 速度
	else if (lens == sizeof(TraZ)  / sizeof(TraZ[0])) Transform1(5);	// 重量
	else if (lens == sizeof(TraN)  / sizeof(TraN[0])) Transform1(6);	// 能量
	else if (lens == sizeof(TraG)  / sizeof(TraG[0])) Transform1(7);	// 功率
	else if (lens == sizeof(TraY)  / sizeof(TraY[0])) Transform1(8);	// 压力
	else if (lens == sizeof(TraJ)  / sizeof(TraJ[0])) Transform1(9);	// 角度
}


// 数据转换
void TransFormation::updatewithinput5()
{
	Input(sizeof(TraS) / sizeof(TraS[0]),7);
	int t = (int)(sizeof(TraS) / sizeof(TraS[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen5()
{
	BeginBatchDraw();	// 开始批量绘图
	Output1(TraS,_T("数据转换"));

	Output(13);

	EndBatchDraw();
}

// 长度转换
void TransFormation::updatewithinput6()
{
	Input(sizeof(TraC) / sizeof(TraC[0]), 8);
	int t = (int)(sizeof(TraC) / sizeof(TraC[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen6()
{
	BeginBatchDraw();	// 开始批量绘图
	Output1(TraC,_T("长度转换"));

	Output(sizeof(TraC) / sizeof(TraC[0]));

	EndBatchDraw();
}

// 面积转换
void TransFormation::updatewithinput7()
{
	Input(sizeof(TraM) / sizeof(TraM[0]), 9);
	int t = (int)(sizeof(TraM) / sizeof(TraM[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen7()
{
	BeginBatchDraw();	// 开始批量绘图
	Output1(TraM,_T("面积转换"));

	Output(sizeof(TraM) / sizeof(TraM[0]));

	EndBatchDraw();
}

// 体积转换
void TransFormation::updatewithinput8()
{
	Input(sizeof(TraT) / sizeof(TraT[0]),10);
	int t = (int)(sizeof(TraT) / sizeof(TraT[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen8()
{
	BeginBatchDraw();	// 开始批量绘图
	Output1(TraT,_T("体积转换"));

	Output(sizeof(TraT) / sizeof(TraT[0]));

	EndBatchDraw();
}

// 时间转换
void TransFormation::updatewithinput9()
{
	Input(sizeof(TraSH) / sizeof(TraSH[0]), 11);
	int t = (int)(sizeof(TraSH) / sizeof(TraSH[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen9()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraSH,_T("时间转换"));

	Output(sizeof(TraSH) / sizeof(TraSH[0]));

	EndBatchDraw();
}

// 温度转换
void TransFormation::updatewithinput10()
{
	Input(sizeof(TraW) / sizeof(TraW[0]), 12);
	int t = (int)(sizeof(TraW) / sizeof(TraW[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen10()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraW,_T("温度转换"));

	Output(sizeof(TraW) / sizeof(TraW[0]));

	EndBatchDraw();
}

// 速度转换
void TransFormation::updatewithinput11()
{
	Input(sizeof(TraSD) / sizeof(TraSD[0]), 13);
	int t = (int)(sizeof(TraSD) / sizeof(TraSD[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen11()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraSD,_T("速度转换"));

	Output(sizeof(TraSD) / sizeof(TraSD[0]));

	EndBatchDraw();
}

// 重量转换
void TransFormation::updatewithinput12()
{
	Input(sizeof(TraZ) / sizeof(TraZ[0]), 14);
	int t = (int)(sizeof(TraZ) / sizeof(TraZ[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen12()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraZ,_T("重量转换"));

	Output(sizeof(TraZ) / sizeof(TraZ[0]));

	EndBatchDraw();
}

// 能量转换
void TransFormation::updatewithinput13()
{
	Input(sizeof(TraN) / sizeof(TraN[0]),15);
	int t = (int)(sizeof(TraN) / sizeof(TraN[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen13()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraN,_T("能量转换"));

	Output(sizeof(TraN) / sizeof(TraN[0]));

	EndBatchDraw();
}

// 功率转换
void TransFormation::updatewithinput14()
{
	Input(sizeof(TraG) / sizeof(TraG[0]), 16);
	int t = (int)(sizeof(TraG) / sizeof(TraG[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen14()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraG,_T("功率转换"));

	Output(sizeof(TraG) / sizeof(TraG[0]));

	EndBatchDraw();
}

// 压力转换
void TransFormation::updatewithinput15()
{
	Input(sizeof(TraY) / sizeof(TraY[0]),17);
	int t = (int)(sizeof(TraY) / sizeof(TraY[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen15()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraY,_T("压力转换"));

	Output(sizeof(TraY) / sizeof(TraY[0]));

	EndBatchDraw();
}

// 角度转换
void TransFormation::updatewithinput16()
{
	Input(sizeof(TraJ) / sizeof(TraJ[0]), 18);
	int t = (int)(sizeof(TraJ) / sizeof(TraJ[0]) - 8) * 30;
	if (transformation.fly > 0)
		transformation.fly -= transformation.fly / 2;
	if (transformation.fly < -t)
		transformation.fly += -((transformation.fly + t) / 2);
}

void TransFormation::showscreen16()
{
	BeginBatchDraw();	// 开始批量绘图

	Output1(TraJ,_T("角度转换"));

	Output(sizeof(TraJ) / sizeof(TraJ[0]));

	EndBatchDraw();
}


// 输入
void TransFormation::Input(int lens, int number)
{
	MOUSEMSG m;	// 定义鼠标消息

	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();

		Window_Message.windowmessage(m); //移动窗口

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (m.x > i * 102 && m.x < i * 102 + 98 && m.y>445 + j * 52 && m.y < 498 + j * 52)
				{
					button[i][j] = true;
					if (m.uMsg == WM_LBUTTONUP && !Button[1] && !Button[3])
					{
						if (ReTra < 23)
						{
							if (j == 2 && i == 0)Tra[++ReTra] = '1';
							else if (j == 2 && i == 1)Tra[++ReTra] = '2';
							else if (j == 2 && i == 2)Tra[++ReTra] = '3';
							else if (j == 1 && i == 0)Tra[++ReTra] = '4';
							else if (j == 1 && i == 1)Tra[++ReTra] = '5';
							else if (j == 1 && i == 2)Tra[++ReTra] = '6';
							else if (j == 0 && i == 0)Tra[++ReTra] = '7';
							else if (j == 0 && i == 1)Tra[++ReTra] = '8';
							else if (j == 0 && i == 2)Tra[++ReTra] = '9';
							else if (j == 1 && i == 3)Tra[++ReTra] = '0';
							WhatC(lens);
						}
						if (j == 2 && i == 3 && ReTra != -1 && !xs)Tra[++ReTra] = '.', xs = true;
						if (j == 0 && i == 3 && ReTra >= 0)
						{
							if (Tra[ReTra] == '.')xs = false;
							Tra[ReTra--] = '\0';
							WhatC(lens);
						}
					}
					if (m.uMsg == WM_RBUTTONDOWN && !Button[1] && !Button[3])
					{
						if (j == 0 && i == 3)
						{
							memset(Tra, 0, sizeof(Tra));
							ReTra = -1; xs = false;
							WhatC(lens);
						}
						if (j == 2 && i == 3 && ReTra != -1)
						{
							if (Tra[0] != '-')
							{
								for (int i =  ReTra; i >=0; i--)
									Tra[i + 1] = Tra[i];
								Tra[0] = '-';
								ReTra++;
							}
							else
							{
								for(int i=1;i<= ReTra;i++)
									Tra[i - 1] = Tra[i];
								Tra[ReTra--] = '\0';
							}
							WhatC(lens);
						}
					}
				}
				else button[i][j] = false;
			}
		}

		if (m.x > 5 && m.x < 40 && m.y > 30 && m.y < 50)	// 设置
		{
			transformation.help[0] = true;
			if (m.uMsg == WM_LBUTTONUP) transformation.software[0] = -1, software[2] = number;
		}
		else transformation.help[0] = false;

		if (Button[1])	// 输入选择
		{
			for (int i = 0; i < lens; i++)
			{
				if (m.y > 55 + 30 * i + transformation.fly && m.y < 85 + 30 * i + transformation.fly && m.y > 50 && m.y < 300)
				{
					Button1[i] = true;
					if (m.uMsg == WM_LBUTTONUP)
					{
						Tranumber = i;
						Button[1] = false;
						WhatC(lens);
					}
				}
				else
				{
					Button1[i] = false;
					if (m.uMsg == WM_LBUTTONUP)
						Button[1] = false;
				}
			}

			if (m.uMsg == WM_MOUSEWHEEL && m.y >= 50 && m.y <= 300)
			{
				if (m.wheel < 0)
					transformation.fly -= 30;
				else
					transformation.fly += 30;
			}
		}

		if (Button[3])	// 输出选择
		{
			for (int i = 0; i < lens; i++)
			{
				if (m.y > 205 + 30 * i + transformation.fly && m.y < 235 + 30 * i + transformation.fly && m.y > 200 && m.y < 450)
				{
					Button1[i] = true;
					if (m.uMsg == WM_LBUTTONUP)
					{
						Tranumber1 = i;
						Button[3] = false;
						WhatC(lens);
					}
				}
				else
				{
					Button1[i] = false;
					if (m.uMsg == WM_LBUTTONUP)
						Button[3] = false;
				}
			}

			if (m.uMsg == WM_MOUSEWHEEL && m.y >= 200 && m.y <= 450)
			{
				if (m.wheel < 0)
					transformation.fly -= 30;
				else
					transformation.fly += 30;
			}
		}

		if (!Button[1] && !Button[3]) {
			if (m.x > 10 && m.x < 25 && m.y>175 && m.y < 190)	// 选择输入单位
			{
				Button[0] = true;
				if (m.uMsg == WM_LBUTTONUP)
				{
					Button[1] = true;
				}
			}
			else
				Button[0] = false;
			if (m.x > 10 && m.x < 25 && m.y>375 && m.y < 390)	// 选择输出单位
			{
				Button[2] = true;
				if (m.uMsg == WM_LBUTTONUP)
				{
					Button[3] = true;
				}
			}
			else
				Button[2] = false;
		}
	}
}


// 输出
void TransFormation::Output(int lens)
{
	IMAGE blacks = MyLoadImage.setimage(100, 50, RGB(0, 0, 0));	// 设置绘图

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j < 3 && i <= 2 || j == 1 && i == 3)
			{
				if (!button[i][j])MyPutimage.my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 90, 0);
				else MyPutimage.my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 50, 0);
			}
			else
			{
				if (!button[i][j])
					MyPutimage.my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 80, 0);
				else
				{
					IMAGE blacks = MyLoadImage.setimage(100, 50, RGB(240, 0, 0));	// 设置绘图
					MyPutimage.my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 60, 0);
				}
			}
		}
	}
	setlinestyle(PS_SOLID, 1, 0, 0);
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, _T("Wingdings"), 0, 0, 1, false, false, false);
	outtextxy(320, 459, 0xD5);
	settextstyle(28, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextstyle(26, 0, _T("Consolas"));
	outtextxy(349, 458, _T("/CE"));
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(142, 560, '2');
	outtextxy(40, 560, '1');
	outtextxy(244, 560, '3');
	outtextxy(40, 508, '4');
	outtextxy(142, 508, '5');
	outtextxy(244, 508, '6');
	outtextxy(40, 456, '7');
	outtextxy(142, 456, '8');
	outtextxy(244, 456, '9');
	outtextxy(330, 560, _T("./±"));
	outtextxy(348, 508, '0');

	if (ReTra == -1)
	{
		settextcolor(WHITE);
		RECT r1 = { 10,100 ,390,170 };
		settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
		drawtext('0', &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	else
	{
		settextcolor(WHITE);
		RECT r1 = { 10,100 ,390,170 };
		callen(Tra);	// 计算字符串长度
		drawtext(Tra, &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	if (Button[1])	// 出现选择输入单位页面
	{
		IMAGE blacks = MyLoadImage.setimage(406, 250, RGB(0, 0, 0));	// 设置绘图

		MyPutimage.my_putimage(0, 60, &blacks, 20, NULL, 1, 85, NULL);

		setlinecolor(HSLtoRGB(190, 1, 0.5));
        rectangle(1, 60, 404, 310);

		settextstyle(23, 0, _T("Consolas"), 0, 0, 20, false, false, false);
		for (int i = 0; i < lens; i++)
		{
			if (transformation.fly + 55 + 30 * i < 280  && transformation.fly + 55 + 30 * i > 50)
			{
				if (Tranumber == i)
				{
					setfillcolor(RGB(100,100,100));
					setfillstyle(BS_SOLID);
					solidrectangle(2, transformation.fly + 61 + 30 * i, 403, transformation.fly + 92 + 30 * i);
				}
				if (Button1[i]) settextcolor(HSLtoRGB(190, 1, 0.5));
				else  settextcolor(WHITE);

				if		(lens == sizeof(TraS) / sizeof(TraS[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraS[i]);
				else if (lens == sizeof(TraC) / sizeof(TraC[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraC[i]);
				else if (lens == sizeof(TraM) / sizeof(TraM[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraM[i]);
				else if (lens == sizeof(TraT) / sizeof(TraT[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraT[i]);
				else if (lens == sizeof(TraSH) / sizeof(TraSH[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraSH[i]);
				else if (lens == sizeof(TraW) / sizeof(TraW[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraW[i]);
				else if (lens == sizeof(TraSD) / sizeof(TraSD[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraSD[i]);
				else if (lens == sizeof(TraZ) / sizeof(TraZ[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraZ[i]);
				else if (lens == sizeof(TraN) / sizeof(TraN[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraN[i]);
				else if (lens == sizeof(TraG) / sizeof(TraG[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraG[i]);
				else if (lens == sizeof(TraY) / sizeof(TraY[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraY[i]);
				else if (lens == sizeof(TraJ) / sizeof(TraJ[0]))		outtextxy(12, 65 + 30 * i + transformation.fly, TraJ[i]);
			}
		}
	}

	if (ReTra == -1)
	{
		settextcolor(WHITE);
		RECT r1 = { 10,300 ,390,370 };
		settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
		drawtext('0', &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	else
	{
		settextcolor(WHITE);
		RECT r1 = { 10,300 ,390,370 };
		callen2(TraEd);	// 计算字符串长度
		drawtext(TraEd, &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	if (Button[3])	// 出现选择输出单位页面
	{
		IMAGE blacks = MyLoadImage.setimage(406, 250, RGB(0, 0, 0));	// 设置绘图
		MyPutimage.my_putimage(0, 200, &blacks, 20, NULL, 1, 80, NULL);
		setlinecolor(HSLtoRGB(190, 1, 0.5));
		rectangle(1, 200, 404, 450);

		settextstyle(23, 0, _T("Consolas"), 0, 0, 20, false, false, false);
		for (int i = 0; i < lens; i++)
		{
			if (transformation.fly + 205 + 30 * i < 435 && transformation.fly + 205 + 30 * i>200)
			{
				if (Tranumber1 == i)
				{
					setfillcolor(RGB(100, 100, 100));
					setfillstyle(BS_SOLID);
					solidrectangle(2, transformation.fly + 201 + 30 * i, 403, transformation.fly + 232 + 30 * i);
				}
				if (Button1[i]) settextcolor(HSLtoRGB(190, 1, 0.5));
				else  settextcolor(WHITE);

				if		(lens == sizeof(TraS) / sizeof(TraS[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraS[i]);
				else if (lens == sizeof(TraC) / sizeof(TraC[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraC[i]);
				else if (lens == sizeof(TraM) / sizeof(TraM[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraM[i]);
				else if (lens == sizeof(TraT) / sizeof(TraT[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraT[i]);
				else if (lens == sizeof(TraSH) / sizeof(TraSH[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraSH[i]);
				else if (lens == sizeof(TraW) / sizeof(TraW[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraW[i]);
				else if (lens == sizeof(TraSD) / sizeof(TraSD[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraSD[i]);
				else if (lens == sizeof(TraZ) / sizeof(TraZ[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraZ[i]);
				else if (lens == sizeof(TraN) / sizeof(TraN[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraN[i]);
				else if (lens == sizeof(TraG) / sizeof(TraG[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraG[i]);
				else if (lens == sizeof(TraY) / sizeof(TraY[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraY[i]);
				else if (lens == sizeof(TraJ) / sizeof(TraJ[0]))		outtextxy(12, 205 + 30 * i + transformation.fly, TraJ[i]);
			}
		}
	}
}


void TransFormation::Output1(MyChar Tra[][40], LPCTSTR s)
{
	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);

	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 406, 0, 600); break;
	case 1:  conversion.Setcolor(0, 406, 0, 600, RGB(180, 180, 180)); break;
	default: conversion.changecolor(0, 406, 0, 600); break;
	}             

	IMAGE blacks = MyLoadImage.setimage(406, 600, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 0, &blacks, RGB(255, 255, 255), 0, 1, 20, 0);

	Window_Message.GetFunctionName(s);

	settextcolor(WHITE);
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, 20, false, false, false);
	outtextxy(30, 175, Tra[Tranumber]);
	if (Button[0])settextcolor(HSLtoRGB(190, 1, 0.5));
	else settextcolor(WHITE);
	outtextxy(10, 175, _T("▼"));

	settextcolor(WHITE);
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, 20, false, false, false);
	outtextxy(30, 375, Tra[Tranumber1]);
	if (Button[2])settextcolor(HSLtoRGB(190, 1, 0.5));
	else settextcolor(WHITE);
	outtextxy(10, 375, _T("▼"));
}

void TransFormation::callen(MyChar *zfc)
{
	int k = (int)_tcslen(zfc);
	if (k <= 13)settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 14)settextstyle(55, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 16)settextstyle(50, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 17)settextstyle(45, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else settextstyle(32, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
}

void TransFormation::callen1(MyChar *zfc)
{
	int k = (int)_tcslen(zfc);
	if (k <= 13)settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 14)settextstyle(55, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 16)settextstyle(50, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 17)settextstyle(45, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 23)settextstyle(32, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 40)settextstyle(20, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else settextstyle(15, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
}

void TransFormation::callen2(MyChar *zfc)
{
	int k = (int)_tcslen(zfc);
	if (k <= 13)settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 14)settextstyle(55, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 16)settextstyle(50, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 17)settextstyle(45, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 23)settextstyle(32, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else if (k <= 40)settextstyle(25, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	else settextstyle(20, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
}

void TransFormation::TransFormationFuction(int &k)
{
	MemStr();		                                           // 初始化转换关系

	switch (k)
	{
	case 6 : DataTransFormationFuction(k);        break;
	case 7 : LengthTransFormationFuction(k);      break;
	case 8 : AreaTransFormationFuction(k);        break;
	case 9 : VolumeTransFormationFuction(k);      break;
	case 10: TimeTransFormationFuction(k);        break;
	case 11: TemperatureTransFormationFuction(k); break;
	case 12: SpeedTransFormationFuction(k);       break;
	case 13: WeightTransFormationFuction(k);      break;
	case 14: EnergyTransFormationFuction(k);      break;
	case 15: PowerTransFormationFuction(k);       break;
	case 16: PressureTransFormationFuction(k);    break;
	case 17: AngleTransFormationFuction(k);       break;
	}
}

void TransFormation::DataTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen5();
		updatewithinput5();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::LengthTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen6();
		updatewithinput6();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::AreaTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen7();
		updatewithinput7();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::VolumeTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen8();
		updatewithinput8();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::TimeTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen9();
		updatewithinput9();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::TemperatureTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen10();
		updatewithinput10();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::SpeedTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen11();
		updatewithinput11();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::WeightTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen12();
		updatewithinput12();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::EnergyTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen13();
		updatewithinput13();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::PowerTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen14();
		updatewithinput14();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::PressureTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen15();
		updatewithinput15();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

void TransFormation::AngleTransFormationFuction(int &k)
{
	while (true)
	{
		showscreen16();
		updatewithinput16();
		if (k != transformation.software[0] + 1)break;
		Sleep(option.Performance);						       // 延时
	}
}

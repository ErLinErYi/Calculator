#include"PassWord.h"

PassWord password(200, 1, 0.5);

PassWord::PassWord()
{
	memset(buttons, 0, sizeof(buttons));                    // 按键初始化
	memset(point, 0, sizeof(point));                        // 点初始化
	H = 190; S = 1; L = 0.5f;                               // 颜色变量初始化
	number = 0;                                             // 点编号初始化
	move = 400;                                             // 点移动坐标初始化
	mouse_isdown = false;                                   // 鼠标是否按下初始化
	passwordcorrect = false;                                // 密码是否正确初始化  
	start = end = 0;                                        // 计时变量初始化
	control = false;                                        // 控制初始化
	control_1 = false;
	DrawPassWordNumber = 0;                                 // 绘制密码次数
	memset(StandardPassWord, 0, sizeof(StandardPassWord));  // 存储密码变量初始化
	memset(inputprompt, 0, sizeof(inputprompt));            // 存储输入提示变量初始化
	memset(initpassword1, 0, sizeof(initpassword1));        // 暂存密码变量初始化
	memset(initpassword2, 0, sizeof(initpassword2));
    memset(on_button, 0, sizeof(on_button));                // 鼠标是否在按键上变量
	memset(down_button, 0, sizeof(on_button));
	inputnumber = 0;                                        // 建立密码的次数
	UpdatePassWord = false;                                 // 是否进行更改密码
	No_UpdatePassWord = false;                              // 取消更改密码
}
	
PassWord::PassWord(float h, float s, float l)
{
	H = h; S = s; L = l;
	memset(buttons, 0, sizeof(buttons));                    // 按键初始化
	memset(point, 0, sizeof(point));                        // 点初始化
	number = 0;                                             // 点编号初始化
	move = 400;                                             // 点移动坐标初始化
	mouse_isdown = false;                                   // 鼠标是否按下初始化
	passwordcorrect = false;                                // 密码是否正确初始化 
	start = end = 0;                                        // 计时变量初始化
	control = false;                                        // 控制初始化
	control_1 = false;
	DrawPassWordNumber = 0;                                 // 绘制密码次数
	memset(StandardPassWord, 0, sizeof(StandardPassWord));  // 存储密码变量初始化
	memset(inputprompt, 0, sizeof(inputprompt));            // 存储输入提示变量初始化
	memset(initpassword1, 0, sizeof(initpassword1));        // 暂存密码变量初始化
	memset(initpassword2, 0, sizeof(initpassword2));
	memset(on_button, 0, sizeof(on_button));                // 鼠标是否在按键上变量
	memset(down_button, 0, sizeof(on_button));
	inputnumber = 0;                                        // 建立密码的次数
	UpdatePassWord = false;                                 // 是否进行更改密码
	No_UpdatePassWord = false;                              // 取消更改密码
}

void PassWord::drawcolor()
{
	float l(0.8f);
	for (int y = 0; y <= 600; y++)
	{
		l -= 0.0008f;
		setlinecolor(HSLtoRGB(H, S, l));
		line(0, y, 406, y);
	}
}

void PassWord::update(int k)
{
	// 定义鼠标消息
	MOUSEMSG m;	
	// 检查是否有鼠标消息
	while (MouseHit())	
	{
		m = GetMouseMsg();

		for (int i = 0; i < 3; i++) 
		{
			for (int j = 0; j < 3; j++)
			{
				if (m.x > 92 + 100 * i &&m.x < 110 + 100 * i && m.y>250 + 100 * j && m.y < 265 + 100 * j)
				{
					if(!buttons[i][j].mouse_down)  // 如果没有按下鼠标
						buttons[i][j].button= true;
					
					if (m.mkLButton) // 左键按下
					{
						mouse_isdown = true; //鼠标按下
						if (!buttons[i][j].mouse_down)// 没有按过
						{
							buttons[i][j].pointnumber = number++; // 点的编号
							buttons[i][j].mouse_down = true; // 这个点鼠标按下
							
							X = 92 + 100 * i + 9; //记录选中点的坐标
							Y = 250 + 100 * j + 9;
							point[buttons[i][j].pointnumber].X = X; // 按顺序记录鼠标按下的点的坐标
							point[buttons[i][j].pointnumber].Y = Y;
						}
					}
				}
				else
					buttons[i][j].button= false;

				if (buttons[i][j].mouse_down) // 鼠标按下 
				{
					m_X = m.x; // 记录鼠标坐标
					m_Y = m.y;
				}

				if (!m.mkLButton&&mouse_isdown)
				{
					mouse_isdown = false;
					CheckPassWord();
					DrawPassWordNumber++;
					start = clock(); // 计时开始
					control = true;
					if(!passwordcorrect)control_1 = true;
				}
			}
		}
		if (m.x > 225 && m.x < 285 && m.y>545 && m.y < 565)
		{
			on_button[2] = true;
			if (m.uMsg == WM_LBUTTONUP)
			{
				UpdatePassWord = true;
				No_UpdatePassWord = false;
			}
		}
		else on_button[2] = false;

		if (k == -1)
		{
			if (m.x > 150 && m.x < 250 && m.y>520 && m.y < 550)
			{
				on_button[4] = true;
				if (m.uMsg == WM_LBUTTONUP)
				{
					No_UpdatePassWord = true;
					UpdatePassWord = false;
				}
			}
			else on_button[4] = false;
		}

		if (k != -1)
		{
			//关闭窗口
			if (m.x > 376 && m.x < 406 && m.y>0 && m.y < 30)
			{
				on_button[5] = true;
				if (m.uMsg == WM_LBUTTONUP)
				{
					SendMessage(GetHWnd(), WM_CLOSE, 0, 0);// 发送关闭窗口消息
				}
			}
			else
				on_button[5] = false;
		}
	}

	//点向上移动
	move = move > 0 ? move - 50 : move;
}

void PassWord::drawscreen(int k)
{
	BeginBatchDraw();

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);

	PassWord::drawcolor();  // 绘背景色

	IMAGE black = MyLoadImage.setimage(406, 600, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 20, 0);

	settextcolor(WHITE);
	settextstyle(25, 0, _T("微软雅黑"), 0, 0, 400, 0, 0, 0);
	RECT r = { 0, 100 + move, 400, 200 + move };
	if (mouse_isdown)
		drawtext(_T("绘制完成后请松开按键"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	else
		if (!DrawPassWordNumber)
			drawtext(_T("请绘制您的解锁图案"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		else
			drawtext(inputprompt, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 8); // 设置线的格式
	if (mouse_isdown || end - start < 1000) {
		if (!mouse_isdown&&control)
		{
			end = clock();
			passwordcorrect == false ? setlinecolor(RGB(250, 0, 250)) : setlinecolor(WHITE);
			if (passwordcorrect)move -= 40;
		}
		else
			setlinecolor(WHITE);
		for (int i = 0; i < 8; i++)
		{
			if (point[i].X&&point[i + 1].X)
				line(point[i].X, point[i].Y + move, point[i + 1].X, point[i + 1].Y + move);
		}
	}
	if (mouse_isdown)
	{
		setlinecolor(WHITE);
		line(X, Y, m_X, m_Y);// 画线
	}
	if (end - start > 900 && control)
	{
		control = false;
		memset(initpassword1, 0, sizeof(initpassword1));        // 临时存储密码变量初始化
		memset(buttons, 0, sizeof(buttons));                    // 按键初始化
		memset(point, 0, sizeof(point));                        // 点初始化
		number = 0;                                             // 点编号初始化
		mouse_isdown = false;                                   // 鼠标是否按下初始化  
	}

	settextstyle(18, 0, _T("Segoe MDL2 Assets"), 0, 0, 900, false, false, false);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//设置点的颜色
			COLORREF rgb = (buttons[i][j].button == true) ? RGB(250, 0, 250) : WHITE;
			settextcolor(rgb);
			outtextxy(92 + 100 * i, 250 + 100 * j + move, 0xE1F5); // 输出点
		}
	}

	if (k != -1)
	{
		//设置点的颜色
		on_button[3] == true ? settextcolor(HSLtoRGB(190, 1, 0.5f)) : settextcolor(WHITE);
		settextstyle(18, 0, _T("微软雅黑"), 0, 0, 100, 0, 1, 0);
		RECT r1 = { 100, 530 + move, 200, 580 + move };
		drawtext(_T("忘记密码"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		(on_button[2] == true) ? settextcolor(HSLtoRGB(190, 1, 0.5f)) : settextcolor(WHITE);
		RECT r2 = { 210, 530 + move, 300, 580 + move };
		drawtext(_T("修改密码"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (on_button[5])
		{
			IMAGE Red = MyLoadImage.setimage(30, 30, RED);	        // 设置绘图
			putimage(370, 0, &Red);
		}
		settextcolor(WHITE);
		settextstyle(15, 0, _T("Segoe MDL2 Assets"), 0, 0, 100, false, false, false);
		outtextxy(378, 7, 0xE106);                      // 退出图标
	}

	if (k > 0)
	{
		settextstyle(20, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
		MyChar ZFC[10], ZFC1[40];
		_stprintf(ZFC, _T("%d"), k);
		_tcscpy(ZFC1, _T("您绘制的错误次数太多，请 "));
		_tcscat(ZFC1, ZFC);
		_tcscat(ZFC1, _T(" 秒后再试"));
		RECT r2 = { 0, 100 + move, 400, 300 + move };
		drawtext(ZFC1, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if (k == -1)
	{
		settextcolor(WHITE);
		settextstyle(20, 0, _T("微软雅黑"), 0, 0, 100, 0, 0, 0);
		RECT r2 = { 0, 100 + move, 400, 300 + move };
		drawtext(_T("请输入旧密码"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		settextstyle(25, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
		MyChar ButtonText[] = { _T("取消") };
		on_button[4] == false ? setfillcolor(HSLtoRGB(200, 1, 0.5)) : setfillcolor(HSLtoRGB(180, 1, 0.5));
		solidroundrect(150, 520, 250, 550, 5, 5);
		settextcolor(WHITE);
		outtextxy(183 , 523, ButtonText);
	}

	EndBatchDraw();
}

void PassWord::LoadPassWord()
{
	FILE *p;
	if (!_tfopen_s(&p, _T(address), _T("r")))  // 打开文件
	{ 
		fwscanf(p, _T("%s"), StandardPassWord);// 读取
		fclose(p);
	}
}

void PassWord::CheckPassWord()
{
	for (int i = 0; i < 9; i++)
	{
		MyChar ZFC[30];
		_stprintf(ZFC, _T("%d"), point[i].X * 10 + point[i].Y * 2);
		_tcscat(initpassword1, ZFC);
		
	}
	if (_tcscmp(initpassword1, StandardPassWord) == 0) // 输入的密码正确
	{
		_tcscpy(inputprompt, _T("恭喜您，图案绘制正确"));
		passwordcorrect = true;
		memset(initpassword1, 0, sizeof(initpassword1));
		if (UpdatePassWord)  // 要更换密码
		{
			inputnumber = 0;
			memset(StandardPassWord, 0, sizeof(StandardPassWord));
			initfunction(0);
		}
	}
	else // 输入的密码错误
	{
		_tcscpy(inputprompt, _T("图案绘制错误，请重试"));
		passwordcorrect = false;
	}
}

void PassWord::SavePassWord()
{
	if (!_tcslen(StandardPassWord)) // 如果没有密码
	{
		for (int i = 0; i < 9; i++)
		{
			MyChar ZFC[30];
			_stprintf(ZFC, _T("%d"), point[i].X * 10 + point[i].Y * 2);
			_tcscat(StandardPassWord, ZFC);
		}
		//建立新密码
		FILE *p;
		if (!_tfopen_s(&p, _T(address), _T("w"))) // 打开文件
		{
			fwprintf(p, _T("%s"), StandardPassWord);
			fclose(p);
		}
	}
}

bool PassWord::Check()
{
	return _tcslen(StandardPassWord) == 0 ? true : false;
}

void PassWord::update_establish_password()
{
	// 定义鼠标消息
	MOUSEMSG m;
	// 检查是否有鼠标消息
	while (MouseHit())
	{
		m = GetMouseMsg();
		
		for (int i = 0; i < 2; i++)
		{
			if (m.x > 80 + 140 * i&&m.x < 180 + 140 * i&&m.y>520 && m.y < 550)
			{
				if (!i || (i&&number >= 2))
				{
					on_button[i] = true;
					if (m.uMsg == WM_LBUTTONUP)
					{
						down_button[i] = true;
						if (i == 1)
							initpassword();
						initfunction(i);
					}
				}
			}
			else
				on_button[i] = false;
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (m.x > 92 + 100 * i &&m.x < 110 + 100 * i && m.y>250 + 100 * j && m.y < 265 + 100 * j)
				{
					if (!buttons[i][j].mouse_down)  // 如果没有按下鼠标
						buttons[i][j].button = true;

					if (m.mkLButton) // 左键按下
					{
						mouse_isdown = true; //鼠标按下
						if (!buttons[i][j].mouse_down)// 没有按过
						{
							buttons[i][j].pointnumber = number++; // 点的编号
							buttons[i][j].mouse_down = true; // 这个点鼠标按下

							X = 92 + 100 * i + 9; //记录选中点的坐标
							Y = 250 + 100 * j + 9;
							point[buttons[i][j].pointnumber].X = X; // 按顺序记录鼠标按下的点的坐标
							point[buttons[i][j].pointnumber].Y = Y;
						}
					}
				}
				else
					buttons[i][j].button = false;

				if (buttons[i][j].mouse_down) // 鼠标按下 
				{
					m_X = m.x; // 记录鼠标坐标
					m_Y = m.y;
				}

				if (!m.mkLButton&&mouse_isdown)
				{
					mouse_isdown = false;
				}
			}
		}
	}

	//点向上移动
	move = move > 0 ? move - 50 : move;
}

void PassWord::show_establish_password()
{
	BeginBatchDraw();

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);

	PassWord::drawcolor();  // 绘背景色

	IMAGE black = MyLoadImage.setimage(406, 600, RGB(0, 0, 0));	// 设置绘图
	MyPutimage.my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 20, 0);

	settextstyle(18, 0, _T("Segoe MDL2 Assets"), 0, 0, 900, false, false, false);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//设置点的颜色
			COLORREF rgb = (buttons[i][j].button == true) ? RGB(250, 0, 250) : WHITE;
			settextcolor(rgb);
			outtextxy(92 + 100 * i, 250 + 100 * j + move, 0xE1F5); // 输出点
		}
	}

    settextcolor(WHITE);
	settextstyle(25, 0, _T("微软雅黑"), 0, 0, 400, 0, 0, 0);
	RECT r = { 0, 100 + move, 400, 200 + move };
	if (inputnumber == 1)
	{
		if (mouse_isdown)
			drawtext(_T("绘制完成后请松开按键"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		else
			drawtext(inputprompt, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	}
	else if (inputnumber == 2)
	{
		drawtext(_T("解锁图案新建成功！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		static int a(0);
		a++;
		if (a > 25)inputnumber = 3;
	}
	else
	{
		if (mouse_isdown)
			drawtext(_T("绘制完成后请松开按键"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		else
			drawtext(_T("请绘制您新的解锁图案，请至少连接两个点"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	RECT r1 = { 0, 130 + move, 400, 230 + move };
	settextstyle(18, 0, _T("微软雅黑"), 0, 0, 400, 0, 0, 0);
	drawtext(_T("请牢记您的密码，忘记后将无法找回"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 8); // 设置线的格式
	if (mouse_isdown)
	{
		setlinecolor(WHITE);
		line(X, Y, m_X, m_Y);// 画线
	}

	if (!down_button[0] && !down_button[1])
	{
		for (int i = 0; i < 8; i++)
		{
			setlinecolor(WHITE);
			if (point[i].X&&point[i + 1].X)
				line(point[i].X, point[i].Y, point[i + 1].X, point[i + 1].Y);
		}
	}
	settextstyle(25, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1); // 设置线的格式
	MyChar ButtonText[][5] = { {_T("重绘")},{_T("确定")} };
	for (int i = 0; i < 2; i++)
	{
		COLORREF rgb = (on_button[i]==false) ? HSLtoRGB(200, 1, 0.5) : HSLtoRGB(180, 1, 0.5);
		setfillcolor(rgb);
		solidroundrect(80 + 140 * i, 520 + move, 180 + 140 * i, 550 + move, 5, 5);
		settextcolor(WHITE);
		outtextxy(112 + 140 * i, 523 + move, ButtonText[i]);

	}
	
	EndBatchDraw();
}

void PassWord::initpassword()
{
	for (int i = 0; i < 9; i++)
	{
		MyChar ZFC[50];
		_stprintf(ZFC, _T("%d"), point[i].X * 10 + point[i].Y * 2);
		if(!inputnumber) _tcscat(initpassword1, ZFC);
		else _tcscat(initpassword2, ZFC);
	}

	if (inputnumber)
	{
		if (_tcscmp(initpassword1, initpassword2) == 0) // 两次输入相同
		{
			SavePassWord(); // 保存密码
			inputnumber = 2;
		}
		else
		{
			inputnumber = 1;
			_tcscpy(inputprompt, _T("两次绘制的图案不相同，请重新绘制。"));
		}
	}

	if (!inputnumber) {
		inputnumber = 1;
		_tcscpy(inputprompt, _T("请再次绘制图案进行确认"));
	}
}

void PassWord::initfunction(int num)
{
	memset(buttons, 0, sizeof(buttons));                    // 按键初始化
	memset(point, 0, sizeof(point));                        // 点初始化
	number = 0;                                             // 点编号初始化
	mouse_isdown = false;                                   // 鼠标是否按下初始化               
	memset(on_button, 0, sizeof(bool) * 2);                 // 鼠标是否在按键上变量
	memset(down_button, 0, sizeof(bool) * 2);                              
	if (!inputnumber || inputnumber == 1)                   //第一次输入
		memset(initpassword2, 0, sizeof(initpassword2));    // 暂存第二次输入的密码
	if (inputnumber == 2)
	{
		memset(inputprompt, 0, sizeof(inputprompt));        // 初始化输入提示
		memset(initpassword1, 0, sizeof(initpassword1));    // 暂存密码变量初始化
		memset(initpassword2, 0, sizeof(initpassword2));    // 结束使命
		DrawPassWordNumber = 0;                             // 绘制次数初始化
	}
	if (!num) //按重绘按钮
	{
		inputnumber = 0;                                    // 建立密码的次数
		memset(initpassword1, 0, sizeof(initpassword1));    // 暂存密码变量初始化
	    memset(initpassword2, 0, sizeof(initpassword2));
	}
}

void PassWord::InputPassWordNumbers()
{
	if (DrawPassWordNumber > option.DrawPasswordNumbers && control_1)
	{
		control_1 = false;
		static int a(-1); a++;
		int second[10] = { 10,30,60,180,500,1800,3600,3600 * 24,3600 * 24 * 24,3600 * 24 * 24 * 24 * 24 };
		clock_t start(0), end(0), sum(0);
		start = clock();
		while (true)
		{
			end = clock();
			sum = (end - start) / 1000;
			drawscreen(second[a] - sum);
			if (sum > second[a])
				break;
			Sleep(option.Performance);
		}
	}
}

void PassWord::UpdatePassWordFuction()
{
	if (UpdatePassWord)                           // 更新密码
	{
		while (true)
		{
			drawscreen(-1);                       // 显示界面
			update(-1);                           // 操作更新
			if (passwordcorrect ||No_UpdatePassWord)
				break;
			Sleep(option.Performance);
		}
		passwordcorrect = false;
		DrawPassWordNumber = 0;
	}
}

void PassWord::FoundPassWord()
{
	if (Check())                                      // 没有密码
	{
		UpdatePassWord = false;
		while (inputnumber <= 2)                      // 建立新密码
		{
			update_establish_password();
			show_establish_password();
			Sleep(option.Performance);
		}
	}
}

bool PassWord::PassWordRight()
{
	if (passwordcorrect &&                            // 密码正确
		!control &&                             
		!UpdatePassWord)                              // 不更换密码
		 return true;
	else return false;
}
#pragma once
#include <ctime>
#include <easyx.h>
#include "LoadImage.h"
#include "Transformation.h"
#pragma warning(disable:4996)

#define address "calculator.dat"

//密码类
class PassWord
{
private:
	//按键结构体
	struct buttons
	{
		// 检测鼠标是否在点上
		bool button;
		// 鼠标是否按下某个按键
		bool mouse_down;
		// 选中的点的编号
		int pointnumber;
	}buttons[3][3];
	// 点坐标结构体
	struct point
	{
		int X, Y;
	}point[9];

	// H:色相饱 
	// S:和度 
	// L:亮度
	float H, S, L;
	// 点编号
	int number;
	// 向上移动
	int move;
	// 鼠标的坐标
	int  m_X, m_Y;
	// 按键的坐标
	int X, Y;
	// 鼠标是否按下
	bool mouse_isdown;
	// 计时变量
	clock_t start, end;  
	// 标准密码
	MyChar StandardPassWord[50];
	// 密码是否正确
	bool passwordcorrect;
	bool control;
	bool control_1;
	// 绘制密码的次数
	int DrawPassWordNumber;  
	// 绘制背景颜色
	void drawcolor();
	
public:
	 
	// 构造函数
	PassWord();
	PassWord(float, float, float);
	// 析构函数
	~PassWord(void) {};
	// 更新
	void update(int k = 0);;
	// 绘制界面
	void drawscreen(int k = 0);
	// 加载密码
	void LoadPassWord();
	// 检查密码
	void CheckPassWord();

private:
	// 输入提示
	MyChar inputprompt[50];
	// 暂存密码变量
	MyChar initpassword1[50], initpassword2[50];

	// 鼠标是在按键上
	bool on_button[6];
	bool down_button[6];
	
	// 初始化函数
	void initfunction(int);
	// 暂存密码
	void initpassword();
	// 保存密码
	void SavePassWord();
	// 输入的次数
	int inputnumber;
	// 检测是否有密码
	bool Check();
	// 更新建立密码
	void update_establish_password();
	// 显示建立密码
	void show_establish_password();
	// 更新密码
	bool UpdatePassWord;
	// 取消更新密码
	bool No_UpdatePassWord;

public:
	// 新建密码
	void FoundPassWord();
	// 更新密码函数
	void UpdatePassWordFuction();
	// 输入密码正确
	bool PassWordRight();
	// 密码输入次数控制
	void InputPassWordNumbers();
};

extern PassWord password;
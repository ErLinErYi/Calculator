#pragma once
#include <easyx.h>
#include "Standard.h"
#include "LoadImage.h"
#include "WindowMessage.h"
#include "Transformation.h"


// 选项类
class Option
{
private:
	int Down_Button[10];
	// 鼠标坐标
	int M_X = 307;

private:
	// 与输入无关的更新
	void updatewithinput17();
	// 绘图
	void showscreen17();
	// 初始化
	void InitFuction();
public:
	// 构造函数
	Option();
	// 析构函数
	~Option();

	// 选项函数
	void OptionFuction(int &);
	// 保存配置文件
	void CaveFuction();
	// 读取配置文件
	void ReadFuction();

public:
	// 记录是否开启密码
	bool RecordPassWard = 0;
	// 控制绘制次数
	int DrawPasswordNumbers = 3;
	// 透明度
	int Alpha = 255;
	// 性能
	int Performance = 0;
	// 窗口风格
	int WindowStyle = 0;
	// 小数保留位数
	int DecimalDigit = 15;
};

extern Option option;
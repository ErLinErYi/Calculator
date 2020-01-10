#pragma once
#include <cmath>
#include <ctime>
#include <easyx.h>
#include "Option.h"
#include "Standard.h"
#include "LoadImage.h"
#include "TransParent.h"
#include "WindowMessage.h"
#include "Transformation.h"

class Set
{
private:
	// 处理上下滑动所致的坐标不精确
#define H_XS (int)round(transformation.fly1/(double)40)			
    // 选择哪个功能的标志
	bool buttons[101] = { false };
	// 随机颜色变量						
	int colors = 0;
	// 计时变量									
	clock_t start = 0, end = 0;
	// 设置：与输入有关的更新
	void updatewithinput0();
	// 设置：显示函数							
	void showscreen0();
	// 设置滑动条									
	void setline();
public:
	Set() {};
	~Set() {};
	void SetFuction(int &);
};

extern Set set;

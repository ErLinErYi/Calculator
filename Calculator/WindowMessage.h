#pragma once
#include <time.h>
#include <easyx.h>
#include "LoadImage.h"
#include "TransParent.h"
#include "TransFormation.h"

class WindowMessage
{
public:
	int Recorde = -100;                                          // 记录
    bool showFPS = false;                                        // 显示fps	
    bool ButtonId[4];                                            // 关闭与最小化按钮

private:
	float GetFps();								                 // 计算 fps
	
public:
	void windowmessage(MOUSEMSG &m, int t = 0);                  // 移动窗口
	void GetFunctionName(LPCTSTR Name, int t = 0);               // 获取功能名称
};

extern WindowMessage Window_Message;
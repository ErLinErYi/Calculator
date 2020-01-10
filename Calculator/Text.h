#pragma once
#include <easyx.h>
#include "Option.h"
#include "LoadImage.h"
#include "Conversion.h"
#include "TransParent.h"
#include "WindowMessage.h"
#include "Transformation.h"

class Text
{
private:
	// 缓存文件
	MyChar SS[100000] = { 0 };
	// 帮助：与输入有关的更新
	void updatewithinput4();
	// 帮助：显示函数                         
	void showscreen4(); 
	// 加载文件                                   
	void loadtext();  
public:
	Text() {};
	~Text() {};
	void TextFuction(int &);
};

extern Text text;

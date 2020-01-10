/************************************************************
 项目名称：计算器
 编译环境：Visual Studio 2017 Community + EasyX_20190219(beta)
 作　　者：尔灵尔亿
 邮　　箱：2117610943@qq.com
 最后修改：2019-3-15
*************************************************************/

#include "ReadyCalculator.h"

int main()
{ 
	ReadyCalculator readycalculator;
	readycalculator.ReadyCalculatorFuction();
	readycalculator.ReadyCalculatorPassWord();
	
	while (true)
	{
		int Number = transformation.software[0] + 1;
		switch (Number)
		{
		case readycalculator.Option :    set.SetFuction(Number);                       break;        // 选项
		case readycalculator.Stabdard:   standard.StandardFuction(Number);             break;        // 标准
		case readycalculator.Science:    science.ScienceFuction(Number);               break;        // 科学
		case readycalculator.BigNumber:  bignumber.BignumberFuction(Number);           break;        // 大数
		case readycalculator.Equation:   solvesolution.SolveSolutionFuction(Number);   break;        // 方程
		case readycalculator.Radix:      conversion.ConversionFuction(Number);         break;        // 进制
		case readycalculator.Profiles:   text.TextFuction(Number);                     break;        // 简介
		case readycalculator.set:        option.OptionFuction(Number);                 break;        // 设置           
		default:                         transformation.TransFormationFuction(Number); break;        // 转换
		}
	}
	return 0;
}
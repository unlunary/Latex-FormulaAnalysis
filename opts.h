//定义已知的操作符
#pragma once

#include "opt.h"
#include <map>

extern map<string,opt> string_to_opt;

//extern map<string,string>CONSTANTS;


/*存在的问题：
     * 1. 确认各运算符优先级客观正确
     * 2. 角度DEGREE的优先级如何处理？
     * 3.
     * */
opt FRAC("\\frac", 0, 2, 0, 0, 0);
//根指数为2可不写，此时ParaNum=1
opt SQRT("\\sqrt", 0, 2, 0, 0, 0);
//?负号，解析时如何与minus区分？
opt NEGSIGN("-", 0, 1, 0, 0, 0);

//三角函数
opt SIN("\\sin", 0, 1, 0, 0, 0);
opt COS("\\cos", 0, 1, 0, 0, 0);
opt TAN("\\tan", 0, 1, 0, 0, 0);
opt COT("\\cot", 0, 1, 0, 0, 0);
opt SEC("\\sec", 0, 1, 0, 0, 0);
opt CSC("\\csc", 0, 1, 0, 0, 0);

opt DEGREE("^\\circ", 1, 1, 0, 0, 0);

//加、减、乘、除、乘方
opt ADD("+", 1, 2, 1, 1, 5);
opt MINUS("-", 1, 2, 0, 0, 5);
opt MULTIPLY("\\times", 1, 2, 1, 1, 6);
opt DIVIDE("\\div", 1, 2, 0, 0, 6);
opt POWER("^", 1, 2, 0, 0, 7);

opt NOT("\\neg", 0, 1, 0, 0, 0);
//逻辑运算符:与/或/异或/蕴含/等价
opt AND("\\cap", 1, 2, 1, 1, 3);
opt OR("\\cup", 1, 2, 1, 1, 2);
opt XOR("\\oplus", 1, 2, 1, 1, 4);
opt IMPLY("\\implies", 1, 2, 0, 0, 1);
opt IFF("\\iff", 1, 2, 1, 1, 0);

opt opts[21] = {FRAC, SQRT, NEGSIGN, SIN, COS, TAN, COT, SEC, CSC, DEGREE, ADD, MINUS, MULTIPLY, DIVIDE, POWER, NOT,
				AND, OR, XOR, IMPLY, IFF};



//定义公式解析
#pragma once

#include "opt.h"

#include <vector>
#include <regex>

class bitnode
{
public:
	string Element;//元素
	/*↑这里要不要用模板？存opt类，或者运算数值*/
	int paranum;
	bitnode *lchild, *rchild;
};

template<class T>
class testNode
{
public:
	T Element;//元素
	int paranum;
	testNode *lchild, *rchild;
};

void pushEle(const string &ele, vector<opt> &r_opt, vector<string> &r_val);

void split(string str, vector<opt> &opt, vector<string> &result);

void markPriority(vector<opt> &opt, vector<string> &ele);

bitnode *CreateBitree(string ele);

bitnode *FormulaAnalysis(string str);

void SetPriority();


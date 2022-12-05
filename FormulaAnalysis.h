//定义公式解析
#pragma once

#include "opt.h"

#include <vector>

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

void split(string str, const string &pattern, vector<string> &result);

void markPriority(const string &str);

bitnode *CreateBitree(string ele);

bitnode *FormulaAnalysis(string str);

void SetPriority();


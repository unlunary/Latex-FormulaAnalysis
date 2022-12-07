//定义公式解析
#pragma once

#include "opt.h"

#include <vector>
#include<map>

extern int resSign;
extern map<string,string> resAndSrc;

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

string resMatching(string str);

void parenthesesMatching(string &str);

//void parenthesesMatching(string &str,vector<string> &res);

bitnode *CreateBitree(string ele);

bitnode *CreateFormulaTree(string str);

void func(bitnode *root);//错误的递归函数，先留着

void SetPriority();


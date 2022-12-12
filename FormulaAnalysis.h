//定义公式解析
#pragma once

#include "opt.h"
#include <algorithm>
#include <vector>
#include<map>

//1210
#include<list>

extern int resSign;
extern map<string,string> resAndSrc;

class bitnode
{
public:
	string Element;//元素
	int paranum;
	bitnode *lchild, *rchild;
    list<bitnode*> paranode;
};

template<class T>
class testNode
{
public:
	T Element;//元素
	int paranum;
	testNode *lchild, *rchild;
};

/*解析1*/
void parenthesesMatching(string &str);

string resMatching(string str);

bitnode *CreateFormulaTree(string str);

void func(bitnode *root);//错误的递归函数，先留着

/*解析2*/
void split(string str, const string &pattern, vector<string> &result);

void markPriority(const string &str);



/*BASIC*/
void SetPriority();

void SetConstants(map<string,string>&CONSTANTS);

bitnode *CreateBitree(string ele);

/*结合律*/
void set_string_to_opt();

void set_asstree(bitnode *root);

void Associativity(bitnode *root);

void print_ass_tree(bitnode *root);

/*叶子节点替换*/
void ReplaceLeafToX(bitnode* root,map<string,string>&CONSTANTS);

/*交换律*/
void SetOrder(map<string,string>&CONSTANTS,vector<string> &ordervec);

void Commutativity(vector<string> ordervec,bitnode* root);

void SetParanumMap(vector<string> ordervec,map<string,int> &toParanum);

void SetOrderMap(vector<string> ordervec,map<string,int> &toOrder);

list<int> print_cmt_tree(map<string,int> toParanum,map<string,int> &toOrder,bitnode* root);
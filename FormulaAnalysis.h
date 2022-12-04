#pragma once

#include "opt.h"
#include "opts.h"

class bitnode{
public:
    string Element;//元素
    /*↑这里要不要用模板？存opt类，或者运算数值*/
    int paranum;
    bitnode *lchild,*rchild;
};

template <class T>
class testNode
{
public:
    T Element;//元素
    int paranum;
    testNode* lchild, *rchild;
};

bitnode* CreateBitree(string ele);
bitnode* FormulaAnalysis(string str);
void SetPriority();


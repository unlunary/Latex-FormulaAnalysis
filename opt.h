//定义操作符opt类
#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define ALPHA "\\alpha"
#define BETA "\\beta"
#define GAMMA "\\gamma"
#define LAMBDA "\\lambda"
#define PI "\\pi"
#define TAU "\\tau"




class opt{
public:
    opt(const string &optString, bool isPrior, int paraNum, bool isAssociative, bool isCommutative, float priority)
            : OptString(optString), IsPrior(isPrior), ParaNum(paraNum), IsAssociative(isAssociative),
              IsCommutative(isCommutative), Priority(priority) {}



    virtual ~opt() {
    }
    opt(){}



    const string &getOptString() const;

    void setOptString(const string &optString);

    bool isPrior() const;

    void setIsPrior(bool isPrior);

    int getParaNum() const;

    void setParaNum(int paraNum);

    bool isAssociative() const;

    void setIsAssociative(bool isAssociative);

    bool isCommutative() const;

    void setIsCommutative(bool isCommutative);

    float getPriority() const;

    void setPriority(float priority);

private:
    string OptString;
    bool IsPrior;//是否为前缀0,中缀1
    int ParaNum;//参数数量
    bool IsAssociative;//可结合1
    bool IsCommutative;//可交换1
    float Priority;//运算符优先级
};

//树节点暂放于此处定义
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



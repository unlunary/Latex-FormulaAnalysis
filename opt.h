#ifndef FORMULAANALYSIS_OPT_H
#define FORMULAANALYSIS_OPT_H
#endif //FORMULAANALYSIS_OPT_H

#include <iostream>
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
    string OptString;
    bool IsPrior;//是否为前缀0,中缀1
    int ParaNum;//参数数量
    bool IsAssociative;//可结合1
    bool IsCommutative;//可交换1
    int Priority;//运算符优先级

    opt(const string &optString, bool isPrior, int paraNum, bool isAssociative, bool isCommutative, int priority)
            : OptString(optString), IsPrior(isPrior), ParaNum(paraNum), IsAssociative(isAssociative),
              IsCommutative(isCommutative), Priority(priority) {

    }

    virtual ~opt() {
    }


    void setOptString(const string &optString) {
        OptString = optString;
    }

    void setIsPrior(bool isPrior) {
        IsPrior = isPrior;
    }

    void setParaNum(int paraNum) {
        ParaNum = paraNum;
    }

    void setIsAssociative(bool isAssociative) {
        IsAssociative = isAssociative;
    }

    void setIsCommutative(bool isCommutative) {
        IsCommutative = isCommutative;
    }

    void setPriority(int priority) {
        Priority = priority;
    }


    const string &getOptString() const {
        return OptString;
    }

    bool isPrior() const {
        return IsPrior;
    }

    int getParaNum() const {
        return ParaNum;
    }

    bool isAssociative() const {
        return IsAssociative;
    }

    bool isCommutative() const {
        return IsCommutative;
    }

    int getPriority() const {
        return Priority;
    }

};

class bitnode{
public:
    string Element;//元素
    /*↑这里要不要用模板？存opt类，或者运算数值*/
    bitnode *lchild,*rchild;
};

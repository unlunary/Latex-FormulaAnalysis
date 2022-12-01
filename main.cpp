#include "opt.h"

/*
 * string OptString;
bool IsPrior;//是否为前缀0,中缀1
int ParaNum;//参数数量
bool IsAssociative;//可结合1
bool IsCommutative;//可交换1
int Priority;//运算符优先级
* */

int main() {
    opt FRAC("\\frac",0,2,0,0,0);
    //根指数为2可不写，此时ParaNum=1
    opt SQRT("\\sqrt",0,2,0,0,0);
    //?符号，如何与minus区分？
    opt NEGSIGN("-",0,1,0,0,0);

    //三角函数
    opt SIN("\\sin",0,1,0,0,0);
    opt COS("\\cos",0,1,0,0,0);
    opt TAN("\\tan",0,1,0,0,0);
    opt COT("\\cot",0,1,0,0,0);
    opt SEC("\\sec",0,1,0,0,0);
    opt CSC("\\csc",0,1,0,0,0);

    opt DEGREE ("^\\circ",1,1,0,0,0);

    //加、减、乘、除、乘方
    opt ADD("+",1,2,1,1,0);
    opt MINUS("-",1,2,0,0,0);
    opt MULTIPLY("\\times",1,2,1,1,0);
    opt DIVIDE("\\div",1,2,0,0,0);
    opt POWER("^",1,2,0,0,0);

    opt NOT("\\neg",0,1,0,0,0);
    //逻辑运算符:与/或/异或/蕴含/等价
    opt AND("\\cap",1,2,1,1,0);
    opt OR("\\cup",1,2,1,1,0);
    opt XOR("\\oplus",1,2,1,1,0);
    opt IMPLY("\\implies",1,2,0,0,0);
    opt IFF("\\iff",1,2,1,1,0);


    cout<<"alpha:"<<ALPHA<<endl;
    FRAC.setPriority(5);
    cout<<"pri:"<<FRAC.getPriority()<<endl;
    cout<<"paranum:"<<FRAC.getParaNum()<<endl;

    /*string symbolstring;
    cin >> symbolstring;*/

    return 0;
}

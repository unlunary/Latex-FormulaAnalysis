#include "opt.h"

/*
 * string OptString;
bool IsPrior;//是否为前缀0,中缀1
int ParaNum;//参数数量
bool IsAssociative;//可结合1
bool IsCommutative;//可交换1
int Priority;//运算符优先级
* */

/*解析要点：
 * 1. 解析规范性：括号/dollar是否配对？
 * */
void FormulaAnalysis(string str){

}


int main() {
    /*存在的问题：
     * 1. 确认各运算符优先级客观正确
     * 2. 角度DEGREE的优先级如何处理？
     * 3.
     * */
    opt FRAC("\\frac",0,2,0,0,0);
    //根指数为2可不写，此时ParaNum=1
    opt SQRT("\\sqrt",0,2,0,0,0);
    //?负号，解析时如何与minus区分？
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
    opt ADD("+",1,2,1,1,5);
    opt MINUS("-",1,2,0,0,5);
    opt MULTIPLY("\\times",1,2,1,1,6);
    opt DIVIDE("\\div",1,2,0,0,6);
    opt POWER("^",1,2,0,0,7);

    opt NOT("\\neg",0,1,0,0,0);
    //逻辑运算符:与/或/异或/蕴含/等价
    opt AND("\\cap",1,2,1,1,3);
    opt OR("\\cup",1,2,1,1,2);
    opt XOR("\\oplus",1,2,1,1,4);
    opt IMPLY("\\implies",1,2,0,0,1);
    opt IFF("\\iff",1,2,1,1,0);

    //set priority
    int MaxMidPriority=POWER.getPriority();
    int FrtPriority=MaxMidPriority+1;
    opt opts[21]={FRAC,SQRT,NEGSIGN,SIN,COS,TAN,COT,SEC,CSC,DEGREE,ADD,MINUS,MULTIPLY,DIVIDE,POWER,NOT,AND,OR,XOR,IMPLY,IFF};
    for(int i=0;i<21;i++){
        if(opts[i].isPrior()==0){
            opts[i].setPriority(FrtPriority);
        }
    }
    //DEGREE的priority暂时处理为前缀
    DEGREE.setPriority(FrtPriority);

/*    string symbolstring;
    cin >> symbolstring;*/

    return 0;
}

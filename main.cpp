#include "opt.h"
#include<vector>
#include <string>

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

opt opts[21]={FRAC,SQRT,NEGSIGN,SIN,COS,TAN,COT,SEC,CSC,DEGREE,ADD,MINUS,MULTIPLY,DIVIDE,POWER,NOT,AND,OR,XOR,IMPLY,IFF};

bitnode* CreateBitree(string ele){
    bitnode* T=new bitnode;
    T->Element=ele;
    T->lchild=NULL;
    T->rchild=NULL;
    return T;
}

/*解析要点：
 * 1. 解析规范性：括号/dollar是否配对？
 * */
bitnode* FormulaAnalysis(string str){
    bitnode* T=new bitnode;
    int optNum=0;
    int lowestPriority=256;
    int rootPosition;
    opt root;
    for(int i=0;i<21;i++){
        if(str.find(opts[i].getOptString(),0)!=string::npos){
            int pos_findrpt=0;
            /*针对测试示例2*/
            while((pos_findrpt=str.find(opts[i].getOptString(),pos_findrpt))!=string::npos)
            {
                //cout<<"pos_findpt "<<optNum<<" : "<<pos_findrpt<<endl;
                pos_findrpt++;
                optNum++;
            }

            if(opts[i].getPriority()<=lowestPriority){
                lowestPriority=opts[i].getPriority();
                rootPosition=str.find(opts[i].getOptString(),0);
                root=opts[i];
            }
        }
    }
    if(optNum==0){
        T=CreateBitree(str);
        cout<<"T-ele:"<<T->Element<<endl;
        return T;
    }
    else{
        T=CreateBitree(root.getOptString());
        string leftstr=str.substr(0,rootPosition);
        string rightstr=str.substr(rootPosition+root.getOptString().length(),str.length());
        T->lchild= FormulaAnalysis(leftstr);
        T->rchild= FormulaAnalysis(rightstr);
        return T;
    }
}




void SetPriority(){
    int MaxMidPriority=0;
    for(int i=0;i<21;i++){
        if(opts[i].getPriority()>MaxMidPriority){
            MaxMidPriority=opts[i].getPriority();
        }
    }
    int FrtPriority=MaxMidPriority+1;
    for(int i=0;i<21;i++){
        if(opts[i].isPrior()==0){
            opts[i].setPriority(FrtPriority);
        }
    }
    //DEGREE的priority暂时处理为前缀
    DEGREE.setPriority(FrtPriority);
}


int main() {
    SetPriority();
    string symbolstring;
    cin >> symbolstring;
    symbolstring=symbolstring.substr(1,symbolstring.length()-2);//先假设其符合dollar规范
    bitnode *root;
    root=FormulaAnalysis(symbolstring);
    /*fortest:
     * $\alpha$
     * $(\alpha+\beta)+\pi$
     * $\frac{(\alpha+\beta)+\pi}{2+3}$ FAILED
     * $\frac{{\alpha}*{(\beta+\pi})}{2+3}$
     * */

    return 0;
}

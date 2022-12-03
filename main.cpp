#include "opt.h"
#include "opts.h"


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

#include "FormulaAnalysis.h"

int resSign=0;
map<string,string> resAndSrc;
map<string,string>CONSTANTS;
map<string,opt> string_to_opt;

int main()
{
    /*初始化*/
	SetPriority2();
    SetConstants(CONSTANTS);

	string symbolstring;
    symbolstring="\\sin{(x+y)}";
    cout<<"symbolstring:"<<symbolstring<<endl;

    //step1:括号匹配-将含有括号的部分转化为"res+i"并放入res中，使symbolstring中不含有任何“()”
    parenthesesMatching(symbolstring);

    //补充：前缀匹配-将含有前缀的子串以相同方式处理
    prefixMatching(symbolstring);

    //step2：取symbolstring中最低优先级的部分递归成为根结点
	bitnode *root;
	root = CreateFormulaTree(symbolstring);
    cout<<"T-root"<<root->Element<<endl;

    //结合律
    set_string_to_opt();
    set_asstree(root);
    Associativity(root);
    cout<<"T-root"<<root->Element<<endl;

    //替换叶子结点
    ReplaceLeafToX(root,CONSTANTS);
    cout<<"T-root"<<root->Element<<endl;

    //交换律
    vector<string> ordervec;
    map<string,int> toParanum;
    map<string,int> toOrder;
    SetOrder(CONSTANTS,ordervec);
    SetParanumMap(ordervec,toParanum);
    SetOrderMap(ordervec,toOrder);
    Commutativity(ordervec,root);

    //打印orderList,操作符的参数数量是n还是1/2？
    list<int>orderList=print_cmt_tree(toParanum,toOrder,root);
    cout<<endl<<"tree to string:";
    list<int>::const_iterator i=orderList.begin();
    for(;i!=orderList.end();i++){
        cout<<*i;
    }
    cout<<endl;

    //索引创建
    list<string>index=PrintTree(root,toParanum);
    cout<<endl<<"print tree's index:";
    list<string>::const_iterator it=index.begin();
    for(;it!=index.end();it++){
        cout<<*it;
    }
    cout<<endl<<endl<<"indexes: "<<endl;

    //兄弟树组合 索引
    PrintIndexes(root,toParanum);





    /*fortest:
     * SUCCEED:
     * ${(4+((\alpha+2)+3))}\times{3}+{(4+((1+\beta)+3))}$
     * ${\frac{{\alpha}\times{\frac{2}{3}}}{2+3}}+{\frac{(\alpha+\beta)+\pi}{2+3}}$
     * $\sin{(\alpha-\beta)}\implies{{\sin{\alpha}}\times{\cos{\beta}}-{{\cos{\alpha}\times{\sin{\beta}}}}}$
     * ${((-4)-((\alpha+(-2))+3))}\times{(-3)}+{(4+(((-1)+\beta)-3))}$
     * ${\tan{(\alpha-\beta)}}\implies{\frac{{\tan{\alpha}}-{\tan{\beta}}}{{1}+{{\tan{\alpha}}\times{\tan{\beta}}}}}$
     * $\frac{{\alpha}\times{(\beta+\pi)}}{2+3}$
     * $\frac{\sin{(x+y)}}{2+3}$
     * $1+{(\frac{1}{1-{x}^{2}})}^{3}$
     *
     * FAILED:
	 * 天生需要括号的运算符优先级不需要提高?
	 * $\sin(x+y)$ //如下，改为\sin{(x+y)}
	 * $\frac{\sin(x+y)}{2+3}$//解不出来，三角函数后面还是跟{}，变成“\frac{\sin{(x+y)}}{2+3}”则可解
	 * */


	/* 乘方运算未考虑
	 * 左右大型括号需求待定（例如分数的幂）
	 * $1 + (\frac{1}{1-x^2})^3$  //改为： 1 + {(\frac{1}{1-{x}^{2}})}^{3}
	 */


	return 0;
}


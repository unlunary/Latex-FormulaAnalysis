#include "FormulaAnalysis.h"
#include <list>


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
    symbolstring="{\\tan{(\\alpha-\\beta)}}\\implies{\\frac{{\\tan{\\alpha}}-{\\tan{\\beta}}}{{1}+{{\\tan{\\alpha}}\\times{\\tan{\\beta}}}}}";
    //有操作数为1的前缀：{\frac{{\alpha}\times{(\sqrt[3]{2}+5)}}{2+3}}+{\frac{(\alpha+\beta)+\pi}{2+3}}
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
     * ${(4+((1+2)+3))}\times{3}+{(4+((1+2)+3))}$
     * 单前缀示例：\frac{(\alpha+\beta)+\pi}{2+3}
     * {\frac{{\alpha}\times{\frac{2}{3}}}{2+3}}+{\frac{(\alpha+\beta)+\pi}{2+3}}
     * \sin{(\alpha-\beta)}\implies{{\sin{\alpha}}\times{\cos{\beta}}-{{\cos{\alpha}\times{\sin{\beta}}}}}
     *
     *
     * FAILED:
	 * $\alpha$,${3}$,${a}$ //流程需符合解析要求
     * ${\frac{{\alpha}\times{(\sqrt[3]{2}+5)}}{2+3}}+{\frac{(\alpha+\beta)+\pi}{2+3}}$
	 * $\alpha+\beta+\pi$
	 * $\frac{(\alpha+\beta)+\pi}{2+3}$ FAILED HERE
	 * $\frac{{\alpha}*{(\beta+\pi})}{2+3}$
	 * $(2+(\alpha+\beta))\times\pi$
	 * 天生需要括号的运算符优先级不需要提高?
	 * $\sin(x+y)$
	 * $\frac{\sin(x+y)}{2+3}$
	 * */


	/* 乘方运算未考虑
	 * 左右大型括号需求待定（例如分数的幂）
	 * $1 + (\frac{1}{1-x^2})^3$
	 * $1 + \left(\frac{1}{1-x^2}\right)^3$
	 */


	return 0;
}

/*
 *1. 前缀的问题：转化为中缀处理；在最前面/在中间，如何识别它的运算元素？
 *2. 若遇到括号先当作整体处理，在它的里面进行递归解析;写几个示例
 *3. 乘方运算：优先级是不是应该高于前缀？把它看成一个数，又或者使它跟前缀同级。
 *
 * */

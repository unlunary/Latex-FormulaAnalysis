#include "FormulaAnalysis.h"
#include <list>


int resSign=0;
map<string,string> resAndSrc;
map<string,opt> string_to_opt;
list<bitnode*>asstree;


int main()
{
	SetPriority();
	string symbolstring;
    symbolstring="${(4+((1+2)+3))}\\times{3}+{(4+((1+2)+3))}$";

    //step1:将含有括号的部分转化为"res+i"并放入res中，使symbolstring中不含有任何“()”
    parenthesesMatching(symbolstring);

    //step2：取symbolstring中最低优先级的部分递归成为根结点
	bitnode *root;
	root = CreateFormulaTree(symbolstring);
    //cout<<"T-root"<<root->Element<<endl;

    //结合律
    set_string_to_opt();
    set_asstree(root);
    Associativity(root);
    cout<<"T-root"<<root->Element<<endl;


    /*fortest:
	 * $\alpha$
	 * $\alpha+\beta+\pi$
	 * $\frac{(\alpha+\beta)+\pi}{2+3}$ FAILED
	 * $\frac{{\alpha}*{(\beta+\pi})}{2+3}$
	 * $(2+(\alpha+\beta))*\pi$
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

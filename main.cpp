#include "FormulaAnalysis.h"
#include <list>
#include "opts.h"//

int resSign=0;
map<string,string> resAndSrc;
map<string,opt> string_to_opt;
list<bitnode*>asstree;

//将opt的string表达与类opt映射
void set_string_to_opt(){
    for(int i=0;i<21;i++){
        string_to_opt.insert(pair<string,opt>(opts[i].getOptString(),opts[i]));
    }
}

//将左右子树插入其list<bitnode*>中
void set_asstree(bitnode *root){
    if(root){
        root->paranode.push_back (root->lchild);
        root->paranode.push_back (root->rchild);
        set_asstree(root->lchild);
        set_asstree(root->rchild);
    }
}

void Associativity(bitnode *root){
    set_string_to_opt();
    set_asstree(root);
    list<bitnode*> nodes;
    nodes.push_back (root);
    while(nodes.empty()!=0)
    {
        for(auto it=nodes.begin();it!=nodes.end();it++)
        {
            //取出list中首结点，ele可能为常量符号/运算符
            list<bitnode*>::iterator it_temp=nodes.begin();
            bitnode * currentNode=*it_temp;

            opt currentOpt;//当前操作符对象
            bool currentNode_type=1;//0为操作符，1为常量符号
            bool is_associative=0;//0,则默认不可结合

            //确定ele类型，若为操作符，则使用map映射
            for(int i=0;i<21;i++)
            {
                if(currentNode->Element==opts[i].getOptString())
                {
                    map<string,opt>::iterator it2;
                    it2=string_to_opt.find(currentNode->Element);
                    currentOpt=it2->second;
                    is_associative=currentOpt.isAssociative();
                    currentNode_type=0;
                    break;
                }
            }

            //根据ele类型进行处理
            if(currentNode_type==1)
            {//常量则直接删去
                nodes.pop_front();
            }
            else if(currentNode_type==0&&is_associative==0)
            {//不可结合操作符
                nodes.pop_front();
                //将该操作符的list<paranode>都push进list<nodes>后面
                for(auto itt=currentNode->paranode.begin();itt!=currentNode->paranode.end();itt++)
                {
                    nodes.push_back (*itt);
                }
            }
            else{//可交换的操作符
                for(auto itt=currentNode->paranode.begin();itt!=currentNode->paranode.end();itt++)
                {
                    bitnode* subnode=*itt;
                    if(currentNode->Element==subnode->Element)
                    {//若是当前运算符与子树中的运算符相同，则删除子树，并将子树的子树插入当前树结点
                        currentNode->paranode.erase(itt);
                        currentNode->paranode.insert(itt,subnode->paranode.begin(),subnode->paranode.end());
                    }
                }
            }
        }
    }
}





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

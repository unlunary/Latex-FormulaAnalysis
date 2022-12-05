#include "FormulaAnalysis.h"
#include<map>

int resSign=0;
map<string,string> resAndSrc;

void parenthesesMatching(string &str,map<string,string> &resAndSrc){//vector<string> &res,
    for(int i=0;i<str.length();i++){//length是不是边处理边变化？
        string replaceSign="res";
        if(str[i]=='('){
            int depth=-1;
            for(int j=i+1;j<str.length();j++){
                if(str[j]=='('){
                    depth--;
                }
                else if(str[j]==')'){
                    depth++;
                }
                if(depth==0){
                    string s=str.substr(i,j-i+1);
                    //res.push_back(s);
                    replaceSign+=to_string(resSign);
                    resSign++;
                    //cout<<replaceSign<<endl;
                    resAndSrc.insert(pair<string,string>(replaceSign,s));
                    str.replace(i,j-i+1,replaceSign);
                    break;
                }
            }
            i=i+replaceSign.length()-1;
        }
    }
}

void func(bitnode *root){//含有res在叶子的解析树 ,,vector<string> &res
    if(root){//该树非空
        if(root->lchild==NULL&&root->rchild==NULL){//叶子
            string str=root->Element;
            if(str.find("res",0)!=string::npos){
                //string res_id;
                string map_res;
                int pos=str.find("res",0);
                for(int i=pos;i<str.length();i++){
                    if(str[i]=='}'){
                        //res_id=str.substr(pos+3,i-pos);
                        map_res=str.substr(pos,i-pos);
                    }
                }
                /*int id=atoi(res_id.c_str());
                parenthesesMatching(res[id],)*/
                map<string,string>::iterator it;
                it=resAndSrc.find(map_res);
                string map_src=it->second;//取出该res对应的含括号的原公式
                root->Element=map_src.substr(1, map_src.length() - 2);
                parenthesesMatching(root->Element,resAndSrc);
                root=CreateFormulaTree(root->Element);
                //func(root);
            }

        }
        else{
            func(root->lchild);
            func(root->rchild);
        }
    }
}


int main()
{
	SetPriority();
	string symbolstring;
    symbolstring="${(4+((1+2)+3))}\\times{3}+{(4+((1+2)+3))}$";
    symbolstring = symbolstring.substr(1, symbolstring.length() - 2);//先假设其符合dollar规范

	/*//对公式字符串首先进行一次语义分割，剥离出符号、运算数等后再进入解析
	vector<string> result;
	split(symbolstring, "+", result);
	for (int i = 0; i < result.size(); i++)
	{
		cout << i << ": " << result[i] << endl;
	}*/

    //step1:将含有括号的部分转化为"res+i"并放入res中，使symbolstring中不含有任何“()”
    vector<string>res;
    parenthesesMatching(symbolstring,resAndSrc);

    //step2：取symbolstring中最低优先级的部分递归成为根结点
	bitnode *root;
	root = CreateFormulaTree(symbolstring);
    cout<<"T-root"<<root->Element<<endl;

    //step3：处理叶子结点处的"res+i",再次对其进行递归解析
    func(root);
    func(root);
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

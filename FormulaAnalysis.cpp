#include "FormulaAnalysis.h"
#include "opts.h"

#define ADDER 10


bitnode *CreateBitree(string ele)
{
	bitnode *T = new bitnode;
	T->Element = ele;
	T->lchild = NULL;
	T->rchild = NULL;
	return T;
}

void split(string str, const string &pattern, vector<string> &result)
{
	str += pattern;//扩展字符串以方便操作
	for (int i = 0; i < str.size(); i++)
	{
		int pos = str.find(pattern, i);
		if (pos < str.size())
		{
			string s = str.substr(i, pos - i);
			if (!s.empty())
				result.push_back(s);
			result.push_back(pattern);
			i = pos + pattern.size() - 1;
		}
	}
	result.pop_back();
}

void markPriority(const string &str)
{
	//遍历srt，每遇到一个(，就把接下来的)之前的所有运算符的优先级加ADDER(10)
	//每遇到一个)，就把接下来的(之前的所有运算符的优先级减ADDER(10)
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			for (int j = i + 1; j < str.length(); j++)
			{
				if (str[j] == ')')
				{
					break;
				} //else if ()
			}
		} else if (str[i] == ')')
		{
			for (int j = i + 1; j < str.length(); j++)
			{
				if (str[j] == '(')
				{
					break;
				} else
				{
					//for (int k = 0; k < opts.size(); k++) {
					//    if (str[j] == opts[k].getOptString()[0]) {
					//        opts[k].setPriority(opts[k].getPriority() - ADDER);
				}
			}
		}
	}
}

void parenthesesMatching(string &str){//vector<string> &res,,map<string,string> &resAndSrc
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

string resMatching(string str){
    //先判断是否有运算符
    for (int i = 0; i < 21; i++)
    {
        if (str.find(opts[i].getOptString(), 0) != string::npos)
        {
            return str;
        }
    }
    //以下仅含res或其他常量/变量符号
    if(str.find("res",0)!=string::npos){
        int pos=str.find("res",0);
        string map_res;//=map_res.substr(pos, map_res.length() - 2);
        for(int i=pos;i<str.length();i++){
            if(str[i]==')'||str[i]=='}'){
                //res_id=str.substr(pos+3,i-pos);
                map_res=str.substr(pos,i-pos);
                break;
            }
            if(i==str.length()-1){
                map_res=str.substr(pos,str.length()-pos);
            }
        }
        map<string,string>::iterator it;
        it=resAndSrc.find(map_res);
        string map_src=it->second;//取出该res对应的含括号的原公式
        map_src=map_src.substr(1, map_src.length() - 2);
        parenthesesMatching(map_src);
        return '{'+map_src+'}';
    }
    else{
        return str;
    }
}

/*解析要点：
 * 其余公式的合法性可在解析时检查，抛出异常即可
 * */
bitnode *CreateFormulaTree(string str)
{
    bitnode *T = new bitnode;
    int optNum = 0;
    int lowestPriority = 256;
    int rootPosition;
    opt root;
    for (int i = 0; i < 21; i++)
    {
        //step1：先处理括号：

        //step2：再处理运算符优先级：
        if (str.find(opts[i].getOptString(), 0) != string::npos)
        {
            int pos_findrpt = 0;
            /*针对测试示例2*/
            while ((pos_findrpt = str.find(opts[i].getOptString(), pos_findrpt)) != string::npos)
            {
                //cout<<"pos_findpt "<<optNum<<" : "<<pos_findrpt<<endl;
                pos_findrpt++;
                optNum++;
            }

            if (opts[i].getPriority() <= lowestPriority)
            {
                lowestPriority = opts[i].getPriority();
                rootPosition = str.find(opts[i].getOptString(), 0);
                root = opts[i];
            }
        }
    }
    if (optNum == 0)
    {
        T = CreateBitree(str);
        cout << "T-ele:" << T->Element << endl;
        return T;
    }

    else
    {
        T = CreateBitree(root.getOptString());
        string leftstr=str.substr(0, rootPosition);
        string rightstr=str.substr(rootPosition + root.getOptString().length(), str.length());
        //先判断它的类型
        leftstr = resMatching(leftstr);
        rightstr = resMatching(rightstr);
/*        parenthesesMatching(leftstr);
        parenthesesMatching(rightstr);*/
        T->lchild = CreateFormulaTree(leftstr);
        T->rchild = CreateFormulaTree(rightstr);
        return T;
    }
}

void func(bitnode *root){//错误的递归函数，先留着
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
                parenthesesMatching(root->Element);
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

void SetPriority()
{
	int MaxMidPriority = 0;
	for (int i = 0; i < 21; i++)
	{
		if (opts[i].getPriority() > MaxMidPriority)
		{
			MaxMidPriority = opts[i].getPriority();
		}
	}
	int FrtPriority = MaxMidPriority + 1;
	for (int i = 0; i < 21; i++)
	{
		if (opts[i].isPrior() == 0)
		{
			opts[i].setPriority(FrtPriority);
		}
	}
	//DEGREE的priority暂时处理为前缀
	DEGREE.setPriority(FrtPriority);
}

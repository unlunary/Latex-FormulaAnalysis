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

/*解析要点：
 * 1. 解析规范性：括号/dollar是否配对？
 * 其余公式的合法性可在解析时检查，抛出异常即可
 * */
bitnode *FormulaAnalysis(string str)
{
	bitnode *T = new bitnode;
	int optNum = 0;
	int lowestPriority = 256;
	int rootPosition;
	opt root;
	for (int i = 0; i < 21; i++)
	{
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
		string leftstr = str.substr(0, rootPosition);
		string rightstr = str.substr(rootPosition + root.getOptString().length(), str.length());
		T->lchild = FormulaAnalysis(leftstr);
		T->rchild = FormulaAnalysis(rightstr);
		return T;
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

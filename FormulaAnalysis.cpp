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

void pushEle(const string &ele, vector<opt> &r_opt, vector<string> &r_val)
{
	static int optnum = 0;
	for (int i = 0; i < OPTNUM; ++i)
	{
		if (ele == opts[i].getOptString())
		{
			r_opt.push_back(opts[i]);
			r_val.emplace_back("opt" + to_string(optnum++));
			return;
		}
	}
	r_val.push_back(ele);
}

//语义分割
//要求：公式不得有空格
void split(string str, vector<opt> &opt, vector<string> &result)
{
	string pattern = R"((\+|\-|\^|\(|\{)[a-z](?=\+|\-|\^|\)|\})|[0-9]+|\+|\-|\^|\(|\)|\{|\}|\[|\]|\\+[a-z]*)";
	regex reg(pattern);
	smatch sm;
	while (regex_search(str, sm, reg))
	{
		string pattern2 = R"((\+|\-|\*|\(|\{|\[|\^)(?=[a-z]|[A-Z]))";
		regex reg2(pattern2);
		smatch sm2;
		string temp = sm[0];
		regex_search(temp, sm2, reg2);
		if (sm2[0] != "")
		{
			pushEle(sm2[0], opt, result);
			temp = temp.substr(1);
			pushEle(temp, opt, result);
		} else
		{
			pushEle(sm[0], opt, result);
		}
		str = sm.suffix();
	}
}

void markPriority(vector<opt> &opt, vector<string> &ele)
{
	//遍历srt，每遇到一个(，就把接下来的同级)之前的所有运算符的优先级加ADDER(10)
	for (int i = 0; i < ele.size(); i++)
	{
		if (ele[i] == "(")
		{
			int depth = 1;
			for (int j = i + 1; j < ele.size(); j++)
			{
				if (ele[j] == "(") depth++;
				else if (ele[j] == ")") depth--;
				if (depth == 0) break;
				if (ele[j].substr(0, 3) == "opt")
				{
					int optIndex = stoi(ele[j].substr(3));
					opt[optIndex].setPriority(opt[optIndex].getPriority() + ADDER);
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
	} else
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

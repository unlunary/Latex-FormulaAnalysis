#include "FormulaAnalysis.h"
#include <regex>

int main()
{
	//SetPriority();
	string symbolstring;
	cout << "Please input the symbol string:";
	cin >> symbolstring;

	//对公式字符串首先进行一次语义分割，剥离出符号、运算数等后再进入解析
	vector<string> result;
	split(symbolstring, result);
	for (int i = 0; i < result.size(); i++)
	{
		cout << i << ": " << result[i] << endl;
	}

	//symbolstring = symbolstring.substr(1, symbolstring.length() - 2);//先假设其符合dollar规范
	//bitnode *root;
	//root = FormulaAnalysis(symbolstring);
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

	/*string pattern = R"((\+|\-|\^|\(|\{)[a-z](?=\+|\-|\^|\)|\})|[0-9]|\+|\-|\^|\(|\)|\{|\}|\[|\]|\\+[a-z]*)";
	string str;
	cout << "Please input the symbol string:";
	cin >> str;
	regex reg(pattern);
	smatch sm;
	while (regex_search(str, sm, reg))
	{
		cout << sm[0] << endl;
		str = sm.suffix();
	}*/


	return 0;
}

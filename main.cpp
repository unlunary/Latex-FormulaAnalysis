#include "FormulaAnalysis.h"

int main()
{
	//SetPriority();
	string symbolstring;
	cout << "Please input the symbol string:";
	cin >> symbolstring;

	//对公式字符串首先进行一次语义分割，剥离出符号、运算数等后再进入解析
	//完成语义分割后，ele_result存储将运算符替换为标识符的公式，ele_opt存储运算符
	//执行标定后，ele_opt中的运算符将与公式中的运算符按顺序依次对应，且各自拥有正确的优先级
	vector<opt> ele_opt;
	vector<string> ele_result;
	split(symbolstring, ele_opt, ele_result);
	for (int i = 0; i < ele_result.size(); i++)
	{
		cout << ele_result[i] << ' ';
	}
	cout << endl;
	for (auto &i: ele_opt)
	{
		cout << i.getOptString() << ':' << i.getPriority() << ' ';
	}
	cout << endl;
	markPriority(ele_opt, ele_result);
	for (auto &i: ele_opt)
	{
		cout << i.getOptString() << ':' << i.getPriority() << ' ';
	}

	//symbolstring = symbolstring.substr(1, symbolstring.length() - 2);//先假设其符合dollar规范
	//bitnode *root;
	//root = FormulaAnalysis(symbolstring);
	/*fortest:
	 * $\alpha$
	 * $\alpha+\beta+\pi$
	 * $\frac{(\alpha+\beta)+\pi}{2+3}$ FAILED
	 * $\frac{{\alpha}\times{(\beta+\pi})}{2+3}$
	 * $(2+(\alpha+\beta))\times\pi$
	 * 天生需要括号的运算符优先级不需要提高?
	 * $\sin(x+y)$
	 * $\frac{\sin(x+y)}{2+3}$
	 * */

	/* 乘方运算未考虑 -->已解决
	 * 左右大型括号需求待定（例如分数的幂） -->暂不考虑
	 * $1+(\frac{1}{1-x^2})^3$
	 * $1+\left(\frac{1}{1-x^2}\right)^3$ -->去掉
	 */


	return 0;
}

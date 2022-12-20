//定义操作符opt类
#pragma once

#include <iostream>
#include <string>

using namespace std;

class opt
{
public:
	opt(const string &optString, bool isPrior, int paraNum, bool isAssociative, bool isCommutative, float priority)
			: OptString(optString), IsPrior(isPrior), ParaNum(paraNum), IsAssociative(isAssociative),
			  IsCommutative(isCommutative), Priority(priority) {}

	virtual ~opt() {}

	opt() {}

	const string &getOptString() const;

	void setOptString(const string &optString);

	bool isPrior() const;

	void setIsPrior(bool isPrior);

	int getParaNum() const;

	void setParaNum(int paraNum);

	bool isAssociative() const;

	void setIsAssociative(bool isAssociative);

	bool isCommutative() const;

	void setIsCommutative(bool isCommutative);

	float getPriority() const;

	void setPriority(float priority);

private:
	string OptString;
	bool IsPrior;//前缀0,中缀1
	int ParaNum;//参数数量
	bool IsAssociative;//可结合1
	bool IsCommutative;//可交换1
	float Priority;//运算符优先级
};

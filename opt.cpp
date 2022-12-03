#include "opt.h"

const string &opt::getOptString() const {
    return OptString;
}

void opt::setOptString(const string &optString) {
    OptString = optString;
}

bool opt::isPrior() const {
    return IsPrior;
}

void opt::setIsPrior(bool isPrior) {
    IsPrior = isPrior;
}

int opt::getParaNum() const {
    return ParaNum;
}

void opt::setParaNum(int paraNum) {
    ParaNum = paraNum;
}

bool opt::isAssociative() const {
    return IsAssociative;
}

void opt::setIsAssociative(bool isAssociative) {
    IsAssociative = isAssociative;
}

bool opt::isCommutative() const {
    return IsCommutative;
}

void opt::setIsCommutative(bool isCommutative) {
    IsCommutative = isCommutative;
}

float opt::getPriority() const {
    return Priority;
}

void opt::setPriority(float priority) {
    Priority = priority;
}

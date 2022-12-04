#include "FormulaAnalysis.h"

int main() {
    SetPriority();
    string symbolstring;
    cin >> symbolstring;
    symbolstring=symbolstring.substr(1,symbolstring.length()-2);//先假设其符合dollar规范
    bitnode *root;
    root=FormulaAnalysis(symbolstring);
    /*fortest:
     * $\alpha$
     * $(\alpha+\beta)+\pi$
     * $\frac{(\alpha+\beta)+\pi}{2+3}$ FAILED
     * $\frac{{\alpha}*{(\beta+\pi})}{2+3}$
     *
     *
     * */

    return 0;
}

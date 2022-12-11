#include <algorithm>
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

//其余公式的合法性可在解析时检查，抛出异常即可
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
        //cout << "T-ele:" << T->Element << endl;
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

//将opt的string表达与类opt映射
void set_string_to_opt(){
    for(int i=0;i<21;i++){
        string_to_opt.insert(pair<string,opt>(opts[i].getOptString(),opts[i]));
    }
}

//将左右子树插入其list<bitnode*>中
void set_asstree(bitnode *root){
    if(root){
        if(root->lchild!=NULL){
            root->paranode.push_back (root->lchild);
        }
        if(root->rchild!=NULL){
            root->paranode.push_back (root->rchild);
        }

        set_asstree(root->lchild);
        set_asstree(root->rchild);
    }
}

void Associativity(bitnode *root){

    list<bitnode*> nodes;
    nodes.push_back (root);//根节点初始化nodes链表
    bitnode * currentNode;

    auto end=nodes.begin();
    for(auto it=nodes.begin();it!=nodes.end();it++)
    {
        //取出list中首结点，ele可能为常量符号/运算符
        list<bitnode*>::iterator it_temp=nodes.begin();
        currentNode=*it_temp;
        if(currentNode==NULL){break;}

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
        {//不可交换操作符
            nodes.pop_front();
            //将该操作符的list<paranode>都push进list<nodes>后面
            for(auto itt=currentNode->paranode.begin();itt!=currentNode->paranode.end();itt++)
            {
                nodes.push_back (*itt);
            }
        }
        else{//可交换的操作符
            auto front=currentNode->paranode.begin();
            for(auto itt=currentNode->paranode.begin();itt!=currentNode->paranode.end();itt++)
            {
                bitnode* subnode=*itt;
                if(currentNode->Element==subnode->Element)
                {//若是当前运算符与子树中的运算符相同，则删除子树，并将子树的子树插入当前树结点
                    currentNode->paranode.splice(itt,subnode->paranode);
                    currentNode->paranode.erase(itt);
                    itt=front;
                }
                front=itt;
            }
            //auto it_copy=it;
            nodes.splice(it,currentNode->paranode);
            //nodes.erase(it);
            //it=it_copy;
        }
        end=it;
    }
    if(nodes.empty()==0){
        nodes.erase(end);//看一下nodes
    }
    if(root->paranode.empty()==0){
        root->paranode.clear();
    }
    root->paranode=nodes;
    //cout<<"!T-ele"<<root->Element<<endl;
    for(auto it=root->paranode.begin();it!=root->paranode.end();it++){
        Associativity(*it);
    }
}

/*多叉树无法中序遍历,大概用不到*/
void print_ass_tree(bitnode *root){
    if(root){
        for(auto it=root->paranode.begin();it!=root->paranode.end();it++){
            bitnode *currentNODE=*it;
            bool currentNode_type=1;//0为操作符，1为常量符号
            //确定ele类型
            for(int i=0;i<21;i++)
            {
                if(currentNODE->Element==opts[i].getOptString())
                {
                    currentNode_type=0;
                    break;
                }
            }
            if(currentNode_type==0){
                print_ass_tree(*it);
            }

            else{
                //cout<<currentNODE->Element<<root->Element;
            }
        }
    }
}

/*步骤四：叶子结点替换*/
void SetConstants(map<string,string>&CONSTANTS){
    CONSTANTS.insert(pair<string,string>("ALPHA","\\alpha"));
    CONSTANTS.insert(pair<string,string>("BETA","\\beta"));
    CONSTANTS.insert(pair<string,string>("GAMMA","\\gamma"));
    CONSTANTS.insert(pair<string,string>("LAMBDA","\\lambda"));
    CONSTANTS.insert(pair<string,string>("PI","\\pi"));
    CONSTANTS.insert(pair<string,string>("TAU","\\tau"));
}

//再检查一下，常量/变量的单字符输入，框架参照交换律
void ReplaceLeafToX(bitnode* root,map<string,string>&CONSTANTS){
    list<bitnode*>nodes;
    for(auto i=root->paranode.begin();i!=root->paranode.end();i++){
        bitnode* currentNode=*i;
        bool is_opt=0;
        bool is_constant=0;
        for(int j=0;j<21;j++){
            if(currentNode->Element==opts[j].getOptString()){
                is_opt=1;
                ReplaceLeafToX(currentNode,CONSTANTS);
                break;
            }
        }
        if(is_opt==0){//不为操作符
            for(auto j=CONSTANTS.begin();j!=CONSTANTS.end();j++){

                if(currentNode->Element.find(j->second,0)!=string::npos){
                    is_constant=1;
                    currentNode->Element=j->second;
                    break;
                }
            }
            if(is_constant==0){
                currentNode->Element="X";
            }
        }
        nodes.push_back(currentNode);
    }
    root->paranode=nodes;
}


/*步骤三：交换律*/

//排序规则是否符合要求？
void sort_string(string *in_array, int n, string *out_array)
{
    vector<string> strArray;
    int i,j = 0;
    for (int i = 0; i < n; i++)
    {
        strArray.push_back(in_array[i]);
    }
    sort(strArray.begin(), strArray.end());
    vector<string>::iterator st;
    for (st = strArray.begin(); st != strArray.end(); st++)
    {
        //cout << *st << endl;//打印结果
        out_array[j++] = *st;
    }
}

//分段重排。明天再写
void SetOrder(map<string,string>&CONSTANTS){//vector<map<string,int>>ordervector
    string symbols_ini[28],symbols[28];
    int i=0;
    for(i=0;i<21;i++){
        symbols_ini[i]=opts[i].getOptString();
    }
    for(auto it=CONSTANTS.begin();it!=CONSTANTS.end();it++){
        symbols_ini[i++]=it->second;
    }
    symbols_ini[27]="X";
    sort_string(symbols_ini,28,symbols);

}

void Commutativity(string *symbols,bitnode* root){
    bool is_opt=0;
    for(int i=0;i<21;i++){
        if(root->Element==opts[i].getOptString()){
            is_opt=1;
            break;
        }
    }
    if(is_opt==1){
        list<bitnode*>nodes;
        for(int j=0;j<28;j++){
            for(auto i=root->paranode.begin();i!=root->paranode.end();i++){
                bitnode* currentNode=*i;
                if(symbols[j]==currentNode->Element){
                    nodes.push_back(currentNode);
                }
            }
        }
        root->paranode=nodes;
    }
    for(auto i=root->paranode.begin();i!=root->paranode.end();i++){
        Commutativity(symbols,*i);
    }
}





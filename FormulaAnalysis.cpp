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

//"{\\frac{{\\alpha}\\times{res0}}{2+3}}+{\\frac{res1+\\pi}{2+3}}"
//"\\frac{{\\alpha}\\times{res0}}{2+3}"
void prefixMatching(string &str)
{
    for(int i=0;i<21;i++)
    {
        string replaceSign="res";
        int pos=0;
        if(opts[i].isPrior()==0&&str.find(opts[i].getOptString(),0)!=string::npos)
        {//在str中找到前缀运算符
            bool is_disposed=1;//默认已经处理过
            pos=str.find(opts[i].getOptString(),0);
            int pos_begin1=0,pos_end1=0,pos_begin2=0,pos_end2=0;
            pos_begin1=pos+opts[i].getOptString().length();
            if(str[pos_begin1]=='{')
            {
                if(opts[i].getParaNum()==1){
                    is_disposed=0;
                }
                int depth=-1;
                for(int j=pos_begin1+1;j<str.length();j++)
                {
                    if(str[j]=='{')
                    {
                        depth--;
                    }
                    else if(str[j]=='}')
                    {
                        depth++;
                    }
                    if(depth==0)
                    {//前缀的第一个参数识别完成
                        pos_end1=j;
                        if(opts[i].getParaNum()==1){
                            //"(\\sqrt[3]{2}+5)"？
                            //需要参照下面修复，参数/操作符，在树中如何排列？将其以怎样的格式返回？
                            if(pos_end1-pos+1==str.length()){//symbolString为单纯的前缀表达式，且参数数量为1
                                return;
                            }
                            string s=str.substr(pos,pos_end1-pos+1);
                            replaceSign+=to_string(resSign);
                            resSign++;
                            resAndSrc.insert(pair<string,string>(replaceSign,s));
                            str.replace(pos,pos_end1-pos+1,replaceSign);
                        }
                        else if(opts[i].getParaNum()==2)
                        {//开始截取第二个参数
                            pos_begin2=pos_end1+1;
                            if(str[pos_begin2]=='{')
                            {
                                is_disposed=0;
                                depth=-1;
                            }
                            for(int k=pos_begin2+1;k<str.length();k++)
                            {
                                if(str[k]=='{')
                                {
                                    depth--;
                                }
                                else if(str[k]=='}')
                                {
                                    depth++;
                                }
                                if(depth==0)
                                {
                                    pos_end2=k;
                                    if(pos_end2-pos+1==str.length()){//symbolString为单纯的前缀表达式，且参数数量为2
                                        string s1=opts[i].getOptString();
                                        string s2=str.substr (pos_begin1,pos_end1-pos_begin1+1);
                                        string s3=str.substr (pos_begin2,pos_end2-pos_begin2+1);
                                        string s=s2+s1+s3;
                                        str=s;
                                        return;
                                    }
                                    //string s=str.substr(pos,pos_end2-pos+1);
                                    string s1=opts[i].getOptString();
                                    string s2=str.substr (pos_begin1,pos_end1-pos_begin1+1);
                                    string s3=str.substr (pos_begin2,pos_end2-pos_begin2+1);
                                    string s=s2+s1+s3;
                                    replaceSign+=to_string(resSign);
                                    resSign++;
                                    resAndSrc.insert(pair<string,string>(replaceSign,s));
                                    str.replace (pos,pos_end2-pos+1,replaceSign);
                                    break;
                                }
                            }
                        }
                        break;//参数识别完成，继续识别下一个前缀
                    }
                }
            }
            if(is_disposed==0){i=-1;}
        }

    }
}

//应该是优先处理括号，再处理前缀吧？
//编写一些 单独前缀，括号+前缀的样例
string resMatching(string str){
    //若仍有运算符，则仍然常规生成树。与第三种情况的区别：(e.g. res+3)。以防进入情况2
    for (int i = 0; i < 21; i++)
    {
        if (str.find(opts[i].getOptString(), 0) != string::npos)
        {
            return str;
        }
    }
    //仅含res
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

        //parenthesesMatching(map_src);
        //prefixMatching(str);

        if(map_src[0]=='('&&map_src[map_src.length()-1]==')'){//去除最外层括号。比如将{res0}转化为{res1+4}
            map_src=map_src.substr(1, map_src.length() - 2);
        }
        parenthesesMatching(map_src);
        for(int i=0;i<21;i++){
            if(opts[i].isPrior()==0&&map_src.find(opts[i].getOptString(),0)!=string::npos){
                prefixMatching(map_src);
            }
        }


        return '{'+map_src+'}';
    }
    //仅含其他常量/变量符号
    else{
        return str;
    }
}

//其余公式的合法性可在解析时检查，抛出异常即可
//先处理括号,再处理运算符优先级
bitnode *CreateFormulaTree(string str)
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
        if(root.isPrior()==1||root.getParaNum()==2){
            string leftstr=str.substr(0, rootPosition);
            string rightstr=str.substr(rootPosition + root.getOptString().length(), str.length());
            //先判断它的类型
            leftstr = resMatching(leftstr);
            rightstr = resMatching(rightstr);
            if(leftstr!=""){T->lchild = CreateFormulaTree(leftstr);}
            if(rightstr!=""){T->rchild = CreateFormulaTree(rightstr);}
        }
        else{
            string rightstr=str.substr(rootPosition + root.getOptString().length(), str.length());
            rightstr = resMatching(rightstr);
            if(rightstr!=""){T->rchild = CreateFormulaTree(rightstr);}
        }
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

//将前缀运算符的优先级设置为中缀MAX+1
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

//将前缀运算符的优先级设置为中缀MIN-1
void SetPriority2()
{
    int MinMidPriority = 0;
    for (int i = 0; i < 21; i++)
    {
        if (opts[i].getPriority() < MinMidPriority)
        {
            MinMidPriority = opts[i].getPriority();
        }
    }
    int FrtPriority = MinMidPriority - 1;
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

//将所有结点的左右子树插入其list<bitnode*>中
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

void Associativity(bitnode* &root){
    bool root_is_opt=0;
    for(int i=0;i<21;i++) {
        if (root->Element == opts[i].getOptString ()){
            root_is_opt=1;
            break;
        }
    }
    if(root_is_opt==0){
        return;
    }
    else
    {
        //对该操作符判断是否符合交换律
        bitnode * currentNode=new bitnode();
        list<bitnode*> nodes;//当前函数根节点的新paranode
        nodes.push_back (root);//根节点初始化nodes链表
        bool SET_FRONT=0;
        for(auto it=nodes.begin();it!=nodes.end();it++)
        {
            if(SET_FRONT==1)
            {
                it=nodes.begin();
                SET_FRONT=0;
            }
            /*确认结点的操作符类型及是否可结合*/
            opt currentOpt;//当前操作符对象
            bool is_associative=0;//0,则默认不可结合
            currentNode=*it;
            map<string,opt>::iterator it2;
            it2=string_to_opt.find(currentNode->Element);
            currentOpt=it2->second;
            is_associative=currentOpt.isAssociative();

            if(is_associative==0)
            {
                nodes.pop_front();
                break;
                //将该操作符的list<paranode>都push进list<nodes>后面
                /*for(auto itt=currentNode->paranode.begin();itt!=currentNode->paranode.end();itt++)
                {
                    SET_FRONT=1;
                    nodes.push_back (*itt);
                }*/
            }
            else//可结合，则需要检测其当前paranode序列是否有与其相同操作符的结点
            {
                bool return_FRONT=0;
                auto front=currentNode->paranode.begin();
                for(auto itt=currentNode->paranode.begin();itt!=currentNode->paranode.end();itt++)
                {
                    bitnode* subnode=*itt;
                    if(currentNode->Element==subnode->Element)
                    {
                        if(*itt==*currentNode->paranode.begin())
                        {
                            return_FRONT=1;
                            currentNode->paranode.splice(itt,subnode->paranode);
                            currentNode->paranode.erase(itt);
                            itt=currentNode->paranode.begin();
                            front=currentNode->paranode.begin();
                        }
                        else{
                            currentNode->paranode.splice(itt,subnode->paranode);
                            currentNode->paranode.erase(itt);
                            itt=front;
                        }
                    }
                    front=itt;
                }

            }
        }
        root->paranode=currentNode->paranode;
        root->paranum=currentNode->paranode.size();
        for(auto it=root->paranode.begin();it!=root->paranode.end();it++){
            Associativity(*it);
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

//注意：数字也处理为X了，若有时间可修复
void ReplaceLeafToX(bitnode* root,map<string,string>&CONSTANTS){
    bool root_is_opt=0;
    for(int i=0;i<21;i++) {
        if (root->Element == opts[i].getOptString ()){
            root_is_opt=1;
            break;
        }
    }
    if(root_is_opt==1){
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
}


/*步骤三：交换律*/
void SetOrder(map<string,string>&CONSTANTS,vector<string> &ordervec){
    for(auto it=CONSTANTS.begin();it!=CONSTANTS.end();it++){
        ordervec.push_back(it->second);
    }
    sort(ordervec.begin(),ordervec.end());

    ordervec.push_back("X");

    vector<string> vec_tmp;
    for(int i =0;i<21;i++){
        vec_tmp.push_back(opts[i].getOptString());
    }
    sort(vec_tmp.begin(),vec_tmp.end());
    for(int i =0;i<21;i++){
        ordervec.push_back(vec_tmp[i]);
    }
}

void Commutativity(vector<string> ordervec,bitnode* root){//string *symbols
    bool is_opt=0;
    bool is_commutative=0;
    for(int i=0;i<21;i++){
        if(root->Element==opts[i].getOptString()){
            is_opt=1;
            is_commutative=opts[i].isCommutative();
            break;
        }
    }
    if(is_opt==1&&is_commutative==1){
        list<bitnode*>nodes;
        for(int j=0;j<28;j++){
            for(auto i=root->paranode.begin();i!=root->paranode.end();i++){
                bitnode* currentNode=*i;
                if(ordervec[j]==currentNode->Element){
                    nodes.push_back(currentNode);
                }
            }
        }
        root->paranode=nodes;
    }
    for(auto i=root->paranode.begin();i!=root->paranode.end();i++){
        Commutativity(ordervec,*i);
    }
}

void SetParanumMap(vector<string> ordervec,map<string,int> &toParanum){
    for(int i=0;i<7;i++){
        toParanum.insert(pair<string,int>(ordervec[i],0));
    }
    for(int i=7;i<28;i++){
        for(int j=0;j<21;j++){
            if(ordervec[i]==opts[j].getOptString()){
                toParanum.insert(pair<string,int>(ordervec[i],opts[j].getParaNum()));
            }
        }
    }
}

void SetOrderMap(vector<string> ordervec,map<string,int> &toOrder){
    for(int i=0;i<28;i++){
        toOrder.insert(pair<string,int>(ordervec[i],i));
    }
}

//序：6个变量符号(内部字母序)>X>操作符序(内部字母序)，使用SetOrder函数设定序
list<int> print_cmt_tree(map<string,int> toParanum,map<string,int> &toOrder,bitnode* &root){
    list<bitnode*>nodes;
    list<int>orderList;//记录结点order和paranum
    if(root){
        nodes.push_back (root);
        while(!nodes.empty()){
            //第一步：push该操作符在“toOrdervec”中的顺序
            bitnode * currentNode=nodes.front();
            map<string,int>::iterator it;
            it=toOrder.find(currentNode->Element);
            int ORDER=it->second;
            orderList.push_back (ORDER);

            //第二步：push符号对应的操作数paranum
            bool is_opt=0;
            for(int i=0;i<21;i++){
                if(currentNode->Element==opts[i].getOptString()){
                    is_opt=1;
                    break;
                }
            }
            if(is_opt==1){
                orderList.push_back (currentNode->paranum);
            }
            else{
                map<string,int>::iterator it2;
                it2=toParanum.find(currentNode->Element);
                int PARANUM=it2->second;
                orderList.push_back (PARANUM);
            }

            nodes.pop_front();
            for(auto i=currentNode->paranode.begin();i!=currentNode->paranode.end();i++){
                nodes.push_back (*i);
            }

        }
    }
    return orderList;
}

list<string> PrintTree(bitnode* &root,map<string,int> toParanum){
    list<string>index;
    bool is_opt=0;
    for(int i=0;i<21;i++){
        if(root->Element==opts[i].getOptString()){
            is_opt=1;
            break;
        }
    }
    if(is_opt==0){
        index.push_back(root->Element);
    }
    else {
        index.push_back (root->Element);
        index.push_back ("(");

        bitnode *currentNode=new bitnode();
        currentNode=root;

        //选项1：push操作符原操作数
        /*map<string, int>::iterator it2;
        it2 = toParanum.find (currentNode->Element);
        int PARANUM = it2->second;
        index.push_back (to_string (PARANUM));*/

        //选项2：push该结点实际的操作数
        index.push_back(to_string(currentNode->paranum));

        index.push_back (")");

        list<bitnode *> paranodes = root->paranode;
        for (auto i = paranodes.begin (); i != paranodes.end (); i++) {
            index.push_back ("{");
            list<string>temp=PrintTree (*i, toParanum);
            index.splice(index.end(),temp);
            index.push_back ("}");
        }



    }
    return index;
}

void PrintIndexes(bitnode *& root,map<string,int> toParanum){
    bool is_opt=0;
    opt currentOpt;
    for(int i=0;i<21;i++){
        if(root->Element==opts[i].getOptString()){
            is_opt=1;
            currentOpt=opts[i];
            break;
        }
    }
    if(currentOpt.isCommutative()==1&&currentOpt.isAssociative()==1){
        int sum=root->paranode.size();
        vector<int>nums;
        for(int i=0;i<sum;i++){
            nums.push_back(i);
        }
        Subset subset;
        vector<vector<int>> ans_ini=subset.subsets (nums);
        vector<vector<int>> ans;//保存了各组兄弟公式树的序号
        for(auto it=ans_ini.begin();it!=ans_ini.end();it++){
            vector<int> sub_ans=*it;
            if(sub_ans.size()>1){
                ans.push_back (sub_ans);
            }
        }
        for(auto i=ans.begin();i!=ans.end();i++){//ans中包含多组子树序号
            vector<int> sub_ans=*i;
            bitnode * newroot=new bitnode;//新的公式树
            newroot->Element=root->Element;
            for(auto itt=sub_ans.begin();itt!=sub_ans.end();itt++){//遍历该组子树的序号，将序号对应的子树插入newroot的paranode
                int tree_num=*itt;
                list<bitnode*>::iterator itr=root->paranode.begin();
                if(tree_num==0){
                    newroot->paranode.push_back (*itr);
                }
                else{
                    for(int j=0;j<tree_num;j++){
                        itr++;//使其指向序号tree_num指向的子树
                    }
                    newroot->paranode.push_back (*itr);
                }
            }
            newroot->paranum=newroot->paranode.size();
            for(auto itt=sub_ans.begin();itt!=sub_ans.end();itt++){
                int tree_num=*itt;
                cout<<"t"<<tree_num+1;
                if((itt+1)!=sub_ans.end()){
                    cout<<"+";
                }
            }
            cout<<": ";
            list<string>indexes=PrintTree(newroot,toParanum);
            list<string>::const_iterator it=indexes.begin();
            for(;it!=indexes.end();it++){
                cout<<*it;
            }
            cout<<endl;
        }
    }
    //该结点不符合交换律和结合律：
    else{
        list<string>index=PrintTree(root,toParanum);
        list<string>::const_iterator it=index.begin();
        for(;it!=index.end();it++){
            cout<<*it;
        }
        cout<<endl;
    }

}























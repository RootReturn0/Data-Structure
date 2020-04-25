#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;
map<char,int> isp,icp;


void setValue()//设置运算符优先级
{
    isp['(']=1;
    isp['*']=isp['/']=isp['%']=5;
    isp['+']=isp['-']=3;
    isp[')']=6;
    isp['#']=0;

    icp['(']=6;
    icp['*']=icp['/']=icp['%']=4;
    icp['+']=icp['-']=2;
    icp[')']=1;
}

void postfix(string exp)//完成中缀表达式到后缀表达式的转换
{
	stack<char> s;
    s.push('#');//栈底
    for(int i=0;i<exp.size();i++)
    {
        if((exp[i]>='0'&&exp[i]<='9')
        ||(exp[i]=='-'&&exp[i+1]>='0'&&exp[i+1]<='9')
        ||exp[i]=='.'||exp[i]==' ')//若为数字直接输出，包括数字后空格
            cout<<exp[i];
        else if(exp[i]=='+'&&exp[i+1]>='0'&&exp[i+1]<='9')//带正数符号的正数不输出符号
            cout<<exp[++i];
        else if(exp[i]==')')//遇到')'输出栈中运算符直到栈顶为'('
        {
            while(s.top()!='(')
            {
                cout<<s.top()<<" ";
                s.pop();
            }
            s.pop();
            i++;//跳过')'后的空格
        }
        else if(isp[s.top()]<icp[exp[i]])//栈内优先级低于栈外当前运算符优先级，入栈
        {
                s.push(exp[i++]);
        }
        else if(isp[s.top()]>icp[exp[i]])//栈内优先级高于栈外当前运算符优先级，出栈
        {
            cout<<s.top()<<" ";
            s.pop();
            i--;//下一循环依旧指向当前运算符
        }     
    }
    while(s.top()!='#')//输出栈内所有剩余操作符
    {
        if(exp[exp.size()-1]!=')')
        {
            cout<<" "<<s.top();
            s.pop();
        }
        else
        {
            cout<<s.top();
            s.pop();
            if(s.top()!='#')
                cout<<" ";
        }
    }
}
int main()
{
	string a;	

    setValue();
	getline(cin,a);
    postfix(a);

    return 0;
 } 


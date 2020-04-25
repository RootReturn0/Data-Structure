#include <vector>
#include <iostream>

using namespace std;

bool isEven(int a);
void initial();
void list(const vector<int> &, const vector<int> &, const int);

int num = 0;
//使用vector作为队列容器
vector<int> odd;
vector<int> even;

int main()
{
	while(1)
	{
	initial();

	cout<<"业务完成的顺序为：";
	if (num)
	{
		list(odd, even, num);
		break;
	}
	else
	{
		cout<<"退出系统！"<<endl;
		break;
	}
	}
	
	return 0;
}

bool isEven(int a) //判断编号奇偶，确认应入队列
{
	if (a % 2 == 0)
		return true;
	else
		return false;
}

void initial()//读取数据
{
	cout << "请输入顾客总数和到达银行的顾客序列！（数字间以空格分隔，输入总数为0退出系统）" << endl;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		int temp;
		cin >> temp;
		if (isEven(temp))
			even.push_back(temp);
		else
			odd.push_back(temp);
	}
}

void list(const vector<int> &quick, const vector<int> &slow, const int len)//输出业务完成的顾客序列
{
	int qFlag = 1, sFlag = 1;//窗口有人时标记为1，否则为0
	int qLine = 0, sLine = 0;//指向排队者的编号

	if (quick.size() == 0) qFlag = 0;
	if (slow.size() == 0) sFlag = 0;

	cout << "业务完成的顺序为：";
	while (qFlag&&sFlag)//两窗口均有业务需要办理
	{
		if (qLine < quick.size())
			cout << quick[qLine++] << " ";
		if (qLine == quick.size())//较快窗口业务办理完成
		{
			qFlag = 0;
			break;
		}
		if (qLine < quick.size())
			cout << quick[qLine++] << " ";
		if (qLine == quick.size())
		{
			qFlag = 0;
			break;
		}

		if (sLine < slow.size())
			cout << slow[sLine++] << " ";
		if (sLine == slow.size())//较慢窗口业务办理完成
		{
			sFlag = 0;
			break;
		}
	}

	if (qFlag)//仅较快窗口在办理业务
	{
		for (; qLine < quick.size() - 1; qLine++)
			cout << quick[qLine] << " ";
		cout << quick[qLine] << endl;//最后一名顾客
	}
	else//仅较慢窗口在办理业务
	{
		for (; sLine < slow.size() - 1; sLine++)
			cout << slow[sLine] << " ";
		cout << slow[sLine] << endl;
	}
}


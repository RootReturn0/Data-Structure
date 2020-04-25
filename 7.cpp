#include <iostream>
#include <queue>

using namespace std;

int main()
{
	int num;
	unsigned long long cost = 0;
	priority_queue <int,vector<int>,greater<int> > huff;//使用升序优先级队列模拟Huffman Tree的WPL计算

	//输入数据
	cin>>num;
	for(int i=0;i<num;i++)
	{
		int temp;
		cin>>temp;
		huff.push(temp);
	}

	//计算总花费
	if(huff.size()==1)
		cost=huff.top();
	else
		while(huff.size()!=1)//仅剩一项时即为哈夫曼树根节点的值
		{
			int add=0;//最小和次小花费之和
			add+=huff.top();
			huff.pop();
			add+=huff.top();
			huff.pop();
			huff.push(add);//将合成的所需木块长度压入队列
			cost+=add;
		}
	cout<<cost;

	return 0;
}
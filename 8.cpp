#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>

using namespace std;

struct graphNode//图节点
{
	string fp = " ";
	string sp = " ";
	int edge = 0;
	int taken = 0;
};

bool operator<(const graphNode &a, const graphNode &b)
{
	return a.fp < b.fp;
}

void welcome()//初始化系统界面
{
	cout << "**          电网造价模拟系统          **\n"
		<< "========================================\n"
		<< "**          A --- 创建电网顶点        **\n"
		<< "**          B --- 添加电网的边        **\n"
		<< "**          C --- 构造最小生成树      **\n"
		<< "**          D --- 显示最小生成树      **\n"
		<< "**          E --- 退出程序            **\n"
		<< "========================================\n"
		<< endl;
}

class minTree//最小生成树类
{
public:
	void initPoint();//初始化顶点
	void initEdge();//初始化边/图
	void Prim();//prim最小生成树算法
	void display();//显示结果

private:
	vector<string> point;//存储顶点
	vector<graphNode> graph;//存储点和边
	vector<graphNode> prim;//存储最小生成树
	int num;//存储顶点数
};

void minTree::initPoint()
{
	string s;

	cout << "请输入顶点的个数：";
	cin >> num;
	while (num < 1)
	{
		cout << "顶点个数必须为正整数！请重新输入：";
		cin >> num;
	}
	cout << "请依次输入各顶点的名称：";
	for (int i = 0; i < num; i++)
	{
		cin >> s;
		point.push_back(s);
	}
}

void minTree::initEdge()
{
	graphNode node;

	if (point.empty()) cout << "您尚未创建电网顶点！" << endl;
	else
		while (1)
		{
			string a, b;
			int e;
			int flagA = 0;
			int flagB = 0;
			cout << "请输入两个顶点及边（边为0时退出操作）：";
			cin >> a >> b >> e;
			if (b < a) swap(a, b);
			if (!e) break;//边为0时退出操作
			if (e < 0)
			{
				cout << "花费应为正整数，请确认数据后重新输入！" << endl;
				continue;
			}

						  //检查输入的顶点是否正确以防程序错误
			for (int i = 0; i < point.size(); i++)
			{
				if (a == point[i]) flagA = 1;
				else if (b == point[i]) flagB = 1;
			}
			if (!(flagA&&flagB))
			{
				cout << "您输入的顶点不在已知顶点内，请确认数据后重新输入！" << endl;
				continue;
			}
			int flag = 0;
			for (int i = 0; i < graph.size(); i++)
			{
				if (a == graph[i].fp&&b == graph[i].sp)
				{
					flag = 1;
					break;
				}
			}
			if(flag)
			{
				cout << "您输入的边已存在，请确认数据后重新输入！" << endl;
				continue;
			}
			else
			{
				node.fp = a;
				node.sp = b;
				node.edge = e;
				graph.push_back(node);
			}
		}
}

void minTree::Prim()
{
	if (graph.empty()) cout << "您尚未添加电网的边！" << endl;
	else
	{

		int index = 0;//test
		int min = 2147483647;
		stack<graphNode> s;
		vector<string> visit;//已访问结点
		visit.push_back(point[0]);//起点	
		//测试有向图是否连通
		for (int i = 0; i < visit.size(); i++)
		{
			for (int j = 0; j < graph.size(); j++)
			{
				int flag = 1;
				if (graph[j].fp == visit[i])
				{
					for (int k = 0; k < visit.size(); k++)
						if (graph[j].sp == visit[k] && k != i)
							flag = 0;
					if (flag)
						visit.push_back(graph[j].sp);
					continue;
				}
				if (graph[j].sp == visit[i])
				{
					for (int k = 0; k < visit.size(); k++)
						if (graph[j].fp == visit[k] && k != i)
							flag = 0;
					if (flag)
						visit.push_back(graph[j].fp);
				}
			}
			if (visit.size() == point.size()) break;
		}
		if (visit.size() != point.size())
			cout << "生成最小生成树失败！存在小区未连通！" << endl;
		else
		{
			for (int i = 1; i < visit.size(); i++)
				visit.pop_back();
			sort(prim.begin(), prim.end());
			while (prim.size() != num - 1)//最小生成树覆盖全图
			{
				for (int i = 0; i < graph.size(); i++)
				{
					if (graph[i].taken == 1) continue;//结点已被获取，跳过

					int flagF = 0;
					int flagS = 0;
					//作权值比较的边有且仅有一个结点被访问

					for (int j = 0; j < visit.size(); j++)
					{
						if ((graph[i].sp == visit[j]))
						{
							flagS = 1;
							break;
						}
						else if ((graph[i].fp == visit[j]))
						{
							flagF = 1;
							break;
						}
					}
					if (flagF&&flagS) continue;
					if (min > graph[i].edge)
					{
						min = graph[i].edge;
						index = i;
					}
				}

				prim.push_back(graph[index]);
				graph[index].taken = 1;
				int flagF = 0;
				int flagS = 0;
				//未加入过的结点加入访问数组
				for (int i = 0; i < visit.size(); i++)
				{
					if (graph[index].fp == visit[i]) flagF = 1;
					else if (graph[index].sp == visit[i]) flagS = 1;
				}
				if (!flagF) visit.push_back(graph[index].fp);
				if (!flagS) visit.push_back(graph[index].sp);

				min = 2147483647;
			}
			cout << "生成Prim最小生成树成功！" << endl;
		}
	}
}

void minTree::display()
{
	if (prim.empty()) cout << "您尚未构造最小生成树！" << endl;
	else
	{
		sort(prim.begin(), prim.end());//按结点名称顺序输出
		cout << "最小生成树的顶点及边为：" << endl;
		for (int i = 0; i < prim.size(); i++)
		{
			cout << prim[i].fp << "-<" << prim[i].edge << ">->" << prim[i].sp << "\t";
		}
	}
}

int main()
{
	char op;
	minTree min;
	welcome();

	while (1)
	{
		int flag = 0;
		cout << "请选择操作：";
		cin >> op;
		switch (op)
		{
		case 'A':
			min.initPoint();
			cout << endl;
			break;
		case 'B':
			min.initEdge();
			cout << endl;
			break;
		case 'C':
			min.Prim();
			cout << endl;
			break;
		case 'D':
			min.display();
			cout << endl;
			break;
		case 'E':
			flag = 1;
			cout << "退出系统！" << endl;
			break;
		default:
			cout << "您输入的操作码不合法！请重新输入！\n" << endl;
		}

		if (flag) break;
	}

	return 0;
}
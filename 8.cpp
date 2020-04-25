#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>

using namespace std;

struct graphNode//ͼ�ڵ�
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

void welcome()//��ʼ��ϵͳ����
{
	cout << "**          �������ģ��ϵͳ          **\n"
		<< "========================================\n"
		<< "**          A --- ������������        **\n"
		<< "**          B --- ��ӵ����ı�        **\n"
		<< "**          C --- ������С������      **\n"
		<< "**          D --- ��ʾ��С������      **\n"
		<< "**          E --- �˳�����            **\n"
		<< "========================================\n"
		<< endl;
}

class minTree//��С��������
{
public:
	void initPoint();//��ʼ������
	void initEdge();//��ʼ����/ͼ
	void Prim();//prim��С�������㷨
	void display();//��ʾ���

private:
	vector<string> point;//�洢����
	vector<graphNode> graph;//�洢��ͱ�
	vector<graphNode> prim;//�洢��С������
	int num;//�洢������
};

void minTree::initPoint()
{
	string s;

	cout << "�����붥��ĸ�����";
	cin >> num;
	while (num < 1)
	{
		cout << "�����������Ϊ�����������������룺";
		cin >> num;
	}
	cout << "�������������������ƣ�";
	for (int i = 0; i < num; i++)
	{
		cin >> s;
		point.push_back(s);
	}
}

void minTree::initEdge()
{
	graphNode node;

	if (point.empty()) cout << "����δ�����������㣡" << endl;
	else
		while (1)
		{
			string a, b;
			int e;
			int flagA = 0;
			int flagB = 0;
			cout << "�������������㼰�ߣ���Ϊ0ʱ�˳���������";
			cin >> a >> b >> e;
			if (b < a) swap(a, b);
			if (!e) break;//��Ϊ0ʱ�˳�����
			if (e < 0)
			{
				cout << "����ӦΪ����������ȷ�����ݺ��������룡" << endl;
				continue;
			}

						  //�������Ķ����Ƿ���ȷ�Է��������
			for (int i = 0; i < point.size(); i++)
			{
				if (a == point[i]) flagA = 1;
				else if (b == point[i]) flagB = 1;
			}
			if (!(flagA&&flagB))
			{
				cout << "������Ķ��㲻����֪�����ڣ���ȷ�����ݺ��������룡" << endl;
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
				cout << "������ı��Ѵ��ڣ���ȷ�����ݺ��������룡" << endl;
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
	if (graph.empty()) cout << "����δ��ӵ����ıߣ�" << endl;
	else
	{

		int index = 0;//test
		int min = 2147483647;
		stack<graphNode> s;
		vector<string> visit;//�ѷ��ʽ��
		visit.push_back(point[0]);//���	
		//��������ͼ�Ƿ���ͨ
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
			cout << "������С������ʧ�ܣ�����С��δ��ͨ��" << endl;
		else
		{
			for (int i = 1; i < visit.size(); i++)
				visit.pop_back();
			sort(prim.begin(), prim.end());
			while (prim.size() != num - 1)//��С����������ȫͼ
			{
				for (int i = 0; i < graph.size(); i++)
				{
					if (graph[i].taken == 1) continue;//����ѱ���ȡ������

					int flagF = 0;
					int flagS = 0;
					//��Ȩֵ�Ƚϵı����ҽ���һ����㱻����

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
				//δ������Ľ������������
				for (int i = 0; i < visit.size(); i++)
				{
					if (graph[index].fp == visit[i]) flagF = 1;
					else if (graph[index].sp == visit[i]) flagS = 1;
				}
				if (!flagF) visit.push_back(graph[index].fp);
				if (!flagS) visit.push_back(graph[index].sp);

				min = 2147483647;
			}
			cout << "����Prim��С�������ɹ���" << endl;
		}
	}
}

void minTree::display()
{
	if (prim.empty()) cout << "����δ������С��������" << endl;
	else
	{
		sort(prim.begin(), prim.end());//���������˳�����
		cout << "��С�������Ķ��㼰��Ϊ��" << endl;
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
		cout << "��ѡ�������";
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
			cout << "�˳�ϵͳ��" << endl;
			break;
		default:
			cout << "������Ĳ����벻�Ϸ������������룡\n" << endl;
		}

		if (flag) break;
	}

	return 0;
}
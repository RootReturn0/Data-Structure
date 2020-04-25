#include <iostream>
using namespace std;

struct linkNode//链表节点
{
	int data = -1;
	linkNode *next = NULL;
};

class linkList//链表类
{
public:
	linkList();
	~linkList();
	void initial(linkNode*);//初始化指定链表
	void initial();//初始化s1和s2
	void intersection();//查找交集
	void empty(linkNode*);
	void display(linkNode*) const;//输出某一链表
	void display() const;//无参数默认输出s3，即交集结果
private:
	linkNode * s1;//S1表头节点
	linkNode *s2;//S2表头节点
	linkNode *s3;//S1和S2的交集新链表S3表头节点
};

linkList::linkList()
{
	s1 = new linkNode;
	s2 = new linkNode;
	s3 = new linkNode;
}

linkList::~linkList()
{
	empty(s1);
	empty(s2);
	empty(s3);
}

void linkList::initial(linkNode* first)
{
	linkNode *current = first;
	int temp = -1;
	while (1)
	{
		cin >> current->data;
		if (current->data == -1) break;
		else if (current->data < 1&&current->data!=-1)
		{
			cout << "这个数不是正整数！请确认数据后重新输入：";
			continue;
		}
		else if (current->data < temp)
		{
			cout << "这个数比前一个数小！输入应为非降序序列！请确认数据后重新输入：";
			continue;
		}
		else
		{
			temp = current->data;
			current->next = new linkNode;
			current = current->next;
		}
	}
}

void linkList::initial()
{
	initial(s1);
	//display(s1);
	//cout<<endl;
	initial(s2);
	//display(s2);
	//cout<<endl;
}

void linkList::intersection()
{
	linkNode *cur1 = s1, *cur2 = s2, *cur3 = s3;
	while (1)
	{
		if (cur1->data == -1 || cur2->data == -1)//链表遍历至末尾，退出循环
		{
			cur3->data = -1;
			break;
		}
		if (cur1->data == cur2->data)//找到交集元素加入新链表
		{
			cur3->data = cur1->data;
			cur1 = cur1->next;
			cur2 = cur2->next;
			cur3->next = new linkNode;
			cur3 = cur3->next;
		}
		//从元素较小的链表向另一链表比较
		else if (cur1->data < cur2->data) cur1 = cur1->next;
		else if (cur1->data > cur2->data) cur2 = cur2->next;
	}
}

void linkList::empty(linkNode *first)
{
	linkNode *temp;
	while (first != NULL)
	{
		temp = first->next;
		delete first;
		first = temp;
	}
}

void linkList::display(linkNode *first) const
{
	linkNode *current = first;
	if (current->data == -1) cout << "NULL";
	else
		while (1)
		{
			cout << current->data;
			current = current->next;
			if (current->data == -1) break;
			cout << " ";
		}
}

void linkList::display() const
{
	display(s3);
}

int main()
{
	linkList list;

	cout << "请输入非降序链表序列S1和S2:" << endl;
	list.initial();
	list.intersection();
	list.display();

	return 0;
}
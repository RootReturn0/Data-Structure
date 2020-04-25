#include <iostream>
using namespace std;

struct linkNode//����ڵ�
{
	int data = -1;
	linkNode *next = NULL;
};

class linkList//������
{
public:
	linkList();
	~linkList();
	void initial(linkNode*);//��ʼ��ָ������
	void initial();//��ʼ��s1��s2
	void intersection();//���ҽ���
	void empty(linkNode*);
	void display(linkNode*) const;//���ĳһ����
	void display() const;//�޲���Ĭ�����s3�����������
private:
	linkNode * s1;//S1��ͷ�ڵ�
	linkNode *s2;//S2��ͷ�ڵ�
	linkNode *s3;//S1��S2�Ľ���������S3��ͷ�ڵ�
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
			cout << "�������������������ȷ�����ݺ��������룺";
			continue;
		}
		else if (current->data < temp)
		{
			cout << "�������ǰһ����С������ӦΪ�ǽ������У���ȷ�����ݺ��������룺";
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
		if (cur1->data == -1 || cur2->data == -1)//���������ĩβ���˳�ѭ��
		{
			cur3->data = -1;
			break;
		}
		if (cur1->data == cur2->data)//�ҵ�����Ԫ�ؼ���������
		{
			cur3->data = cur1->data;
			cur1 = cur1->next;
			cur2 = cur2->next;
			cur3->next = new linkNode;
			cur3 = cur3->next;
		}
		//��Ԫ�ؽ�С����������һ����Ƚ�
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

	cout << "������ǽ�����������S1��S2:" << endl;
	list.initial();
	list.intersection();
	list.display();

	return 0;
}
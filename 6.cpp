#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
//������ʾ�ɸĽ�
struct treeNode
{
	string name = " ";
	treeNode *firstChild = NULL;
	treeNode *sibling = NULL;
	treeNode *parent = NULL;//������չʱ��������������
	int depth = 0;//������
};

class familyTree
{
public:
	familyTree();//familyTree�Ĺ��캯�������ڴ��������ռ䲢ʹrootָ��ͷ���
	void init();//��ʼ������
	void find() const;//���Ҽ�ͥ
	treeNode* find(const string) const;//�������
	void set();//������ͥ
	void add();//��Ӽ�ͥ��Ա
	void mod();//�޸ĳ�Ա����
	void del();//ɾ������
	void display(const string) const;//��ʾ��Ա����
private:
	treeNode * root;
};

familyTree::familyTree()
{
	root = new treeNode;
}

void familyTree::init()
{
	cout << "���Ƚ���һ����ͥ��" << endl;
	cout << "���������ȵ�������";
	cin >> root->name;
	cout << "�˼��׵������ǣ�" << root->name << endl;
}

void familyTree::find() const
{
	string name;
	cout << "������Ҫ���ҵļ�ͥ���˵�������";
	cin >> name;

	display(name);
}

treeNode* familyTree::find(string name) const
{
	treeNode* current = root;
	stack<treeNode*> s;
	if (current->name == name) return current;
	if (current->firstChild != NULL)//���ӽ�㲻�ر���
		while (1)
		{
			current = current->firstChild;
			if (current->name == name)  break;
			if (current->firstChild != NULL) s.push(current);//�����ӽ�㣬��ջ
			while (current->sibling != NULL)
			{
				current = current->sibling;//���ֵ�����
				if (current->name == name)  break;
				if (current->firstChild != NULL) s.push(current);//�����ӽ�㣬��ջ
			}

			if (current->name == name)  break;
			if (s.empty())//ջ�գ���������
			{
				current = NULL;
				break;
			}
			current = s.top();
			s.pop();
		}
	else current = NULL;

	return current;
}

void familyTree::set()
{
	int num;
	string name;

	cout << "������Ҫ������ͥ���˵�������";
	cin >> name;
	treeNode *current = find(name);//��λ��������Ӧ���
	if (current == NULL)
		cout << "���޴��ˣ���ȷ�����������½��в�����" << endl;
	else
	{
		cout << "������" << name << "�Ķ�Ů������";
		cin >> num;
		cout << "����������" << name << "�Ķ�Ů��������";

		treeNode *parent = find(name);

		if (current->firstChild != NULL)
		{
			current = current->firstChild;
			for (int i = 0; i < num; i++)
			{
				current->sibling = new treeNode;
				current->sibling->depth = current->depth;
				current = current->sibling;
				cin >> current->name;
				current->parent = parent;
			}
		}
		else
		{
			//��һ����Ů
			current->firstChild = new treeNode;
			current->firstChild->depth = current->depth + 1;
			current = current->firstChild;
			cin >> current->name;
			current->parent = parent;
			//������Ů
			for (int i = 1; i < num; i++)
			{
				current->sibling = new treeNode;
				current->sibling->depth = current->depth;
				current = current->sibling;
				cin >> current->name;
				current->parent = parent;
			}
		}
		display(name);
	}
}

void familyTree::add()
{
	string name, pName;
	cout << "������Ҫ��Ӷ�Ů���˵�������";
	cin >> pName;
	treeNode* current = find(pName);//��λ��������Ӧ���
	if (current == NULL)
		cout << "���޴��ˣ���ȷ�����������½��в�����" << endl;
	else
	{
		treeNode *parent = find(pName);
		cout << "������" << name << "����ӵĶ��ӣ���Ů������������";
		cin >> name;
		if (current->firstChild == NULL)//����Ů
		{
			current->firstChild = new treeNode;
			current->firstChild->name = name;
			current->firstChild->parent = parent;
			current->firstChild->depth = current->depth + 1;
		}
		else//������Ů
		{
			current = current->firstChild;
			while (current->sibling != NULL)
			{
				current = current->sibling;
			}
			current->sibling = new treeNode;
			current->sibling->name = name;
			current->sibling->parent = parent;
			current->sibling->depth = parent->depth + 1;
		}
		display(pName);
	}
}

void familyTree::mod()
{
	string name;
	cout << "������Ҫ���ĵ��˵�Ŀǰ������";
	cin >> name;
	treeNode* current = find(name);//��λ��������Ӧ���
	if (current == NULL)
		cout << "���޴��ˣ���ȷ�����������½��в�����" << endl;
	else
	{
		cout << "��������ĺ��������";
		cin >> name;
		cout << current->name << "�Ѹ���Ϊ";
		current->name = name;
		cout << current->name << endl;
	}
}

void familyTree::del()
{
	string name;
	cout << "������Ҫ��ɢ��ͥ���˵�Ŀǰ������";
	cin >> name;
	treeNode* current = find(name);//��λ��������Ӧ���
	if (current == NULL)
		cout << "���޴��ˣ���ȷ�����������½��в�����" << endl;
	else
	{
		display(name);
		stack<treeNode*> s;
		queue<treeNode*> q;
		if (current->firstChild != NULL)
		{
			while (1)
			{
				current = current->firstChild;
				q.push(current);
				if (current->firstChild != NULL)
					s.push(current);
				while (current->sibling != NULL)
				{
					current = current->sibling;
					q.push(current);
					if (current->firstChild != NULL) s.push(current);
				}

				if (s.empty()) break;
				current = s.top();
				s.pop();
			}
			while (!q.empty())
			{
				delete q.front();
				//q.front() = NULL;
				q.pop();
			}
			//�����Ůָ��
			current = find(name);
			current->firstChild = NULL;
		}
	}
}

void familyTree::display(const string name) const
{
	treeNode* temp = find(name);
	treeNode* current = find(name);
	int count;
	int flag = 1;
	queue<treeNode*> s;
	queue<treeNode*> q;

	if (current == NULL)
		cout << "���޴��ˣ���ȷ�����������½��в�����" << endl;
	else
	{
		if (current->firstChild != NULL)
			while (1)
			{
				current = current->firstChild;
				q.push(current);//�������
				count = current->depth - temp->depth;
				if (current->firstChild != NULL) s.push(current);//���ӽ�㣬��ӵȴ�����
				while (current->sibling != NULL)
				{
					current = current->sibling;
					q.push(current);
					count = current->depth - temp->depth;
					if (current->firstChild != NULL) s.push(current);
				}

				if (s.empty()) break;//�ӽ��ӿգ���������
				current = s.front();
				s.pop();
			}

		if (q.empty()) cout << name << "û�����" << endl;
		else
		{
			int dep = q.front()->depth;
			for (int i = 1; i <= count; i++)
			{
				cout << name << "�ĵ�" << i << "�����";
				while (1)
				{
					cout << q.front()->name << " ";
					q.pop();
					if (q.empty()) break;
					if (q.front()->depth != dep)
					{
						dep = q.front()->depth;
						break;
					}
				}
				cout << endl;
			}
		}
	}
}

void welcome()
{
	cout << "**              ���׹���ϵͳ                     **\n"
		<< "===================================================\n"
		<< "**           ��ѡ��Ҫִ�еĲ�����                **\n"
		<< "**              A --- ���Ƽ�ͥ                   **\n"
		<< "**              B --- ��Ӽ�ͥ��Ա               **\n"
		<< "**              C --- ��ɢ�ֲ���ͥ               **\n"
		<< "**              D --- ���ļ�ͥ��Ա����           **\n"
		<< "**              E --- ���Ҿֲ���ͥ               **\n"
		<< "**              F --- �˳�����                   **\n"
		<< "===================================================\n"
		<< endl;
}

int main()
{
	char index;
	int flag = 1;
	familyTree family;
	welcome();
	family.init();
	while (flag)
	{
		cout << "\n��ѡ��Ҫִ�еĲ�����";
		cin >> index;
		switch (index)
		{
		case 'A':
			family.set();
			break;
		case 'B':
			family.add();
			break;
		case 'C':
			family.del();
			break;
		case 'D':
			family.mod();
			break;
		case 'E':
			family.find();
			break;
		case 'F':
			flag = 0;
			cout << "�˳�����" << endl;
			break;
		default:
			cout << "�����벻�Ϸ������������룡" << endl;
		}
	}

	return 0;
}

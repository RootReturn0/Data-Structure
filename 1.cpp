#include <iostream>
#include <string>
using namespace std;
//代码格式及边界测试未完成
struct linkNode//结点结构体
{
	string ID = "";
	string name = "";
	string gender = "";
	string age = "";
	string category = "";

	linkNode *next = NULL;

	friend istream& operator>>(istream&is, linkNode *node)
	{
		is >> node->ID >> node->name >> node->gender >> node->age >> node->category;
		return is;
	}

	friend ostream& operator<<(ostream&os, const linkNode *node)
	{
		os << node->ID << "   \t"
			<< node->name << "\t"
			<< node->gender << "  \t"
			<< node->age << "  \t"
			<< node->category << endl;
		return os;
	}
};

class linkList//链表类
{
public:
	linkList();//linkList的构造函数，在内存分配头结点空间并使first指向头结点
	~linkList();//linkList的析构函数，通过调用Empty()实现对内存的回收
	void Empty();//回收链表所占的内存，防止内存泄漏
	bool Initial();//建立链表，输入数据
	bool Insert();//在链表中插入一个结点
	bool Delete();//在链表中删除一个结点
	bool Find() const;//在链表中查找一个结点
	bool Modify();//在链表中修改一个结点
	void Display() const;//显示链表所存储的数据

private:
	linkNode * first;//头结点
	int length;//链表长度
};

linkList::linkList()
{
	first = new linkNode;
}

linkList::~linkList()
{
	Empty();
}

void linkList::Empty()
{
	linkNode *temp;
	while (first != NULL)
	{
		temp = first->next;
		delete first;
		first = temp;
	}
}

bool linkList::Initial()
{
	linkNode *current = first;
	cout << "首先请建立考生信息系统！\n"
		<< "请输入考生人数：";
	cin >> length;
	while (length <= 0)
	{
		cout << "考生人数必须为正整数！请重新输入：";
		cin >> length;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;

	cin >> current;
	while (current->ID == "0")
	{
		cout << "考生的考号不能为0！\n"
			<< "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
		cin >> current;
	}
	for (int i = 1; i < length; i++)
	{
		current->next = new linkNode;
		current = current->next;
		cin >> current;
		while (current->ID == "0")
		{
			cout << "考生的考号不能为0！\n"
				<< "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
			cin >> current;
		}
	}

	cout << endl;
	Display();
	return true;
}

bool linkList::Insert()
{
	int index;
	int flag = 1;
	linkNode *current = first;

	cout << "请输入要插入的考生的位置：";
	cin >> index;
	if (index == 0)//0为中断操作
	{
		cout << "中断操作！" << endl;
		return true;
	}
	for (int i = 1; i < index; i++)//寻找要插入位置的前一个结点
	{
		if (current == NULL)
		{
			flag = 0;
			break;
		}
		else
			if (i < index - 1) current = current->next;
	}

	//进行插入操作
	if (flag)
	{
		linkNode *temp = new linkNode;
		cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
		cin >> temp->ID;
		if (temp->ID == "0")
		{
			cout << "中断操作（考生的考号不能为0）！" << endl;//0为返回上一级的指令
			char c;
			while ((c = getchar()) != '\n' && c != EOF);//清空输入缓存区，防止操作混乱及程序崩溃
			return true;
		}
		cin >> temp->name >> temp->gender >> temp->age >> temp->category;
		if (index == 1)//插入位置为第一个则更改头结点
		{
			temp->next = first;
			first = temp;
		}
		else
		{
			temp->next = current->next;
			current->next = temp;
		}
		length++;

		cout << endl;
		Display();
		return true;
	}
	//插入位置有误
	cout << "您输入的位置不合法！请重新输入！" << endl;
	return false;
}

bool linkList::Delete()
{
	string ID;
	linkNode *current = first;

	cout << "请输入要删除的考生的考号：";
	cin >> ID;
	if (ID == "0")
	{
		cout << "中断操作！" << endl;
		return true;
	}

	if (first->ID == ID)
	{
		current = first->next;
		cout << "您删除的考生信息是：" << first;
		delete first;
		first = current;

		cout << endl;
		Display();
		return true;
	}
	else
		while (current->next != NULL)
		{
			if (current->next->ID == ID)//寻找要删除结点的前一个结点
			{
				linkNode *temp = current->next;
				current->next = temp->next;
				cout << "您删除的考生信息是：" << temp;
				delete temp;
				temp = NULL;

				cout << endl;
				Display();
				return true;
			}
			else
				current = current->next;
		}

	cout << "您要删除的考生的考号不存在！请重新输入！" << endl;
	return false;
}

bool linkList::Find() const
{
	string ID;
	linkNode *current = first;

	cout << "请输入要查找的考生的考号：";
	cin >> ID;

	if (ID == "0")//0为中断操作
	{
		cout << "中断操作！" << endl;
		return true;
	}

	while (current != NULL)
	{
		if (current->ID == ID)
		{
			cout << current << endl;
			return true;
		}
		else
			current = current->next;
	}

	//未找到考生考号
	cout << "您要查找的考生的考号不存在！请重新输入！" << endl;
	return false;
}

bool linkList::Modify()
{
	string ID;
	linkNode *current = first;

	cout << "请输入要修改的考生的考号：";
	cin >> ID;
	if (ID == "0")//0为中断操作
	{
		cout << "中断操作！" << endl;
		return true;
	}
	while (current != NULL)
	{
		if (current->ID == ID)
		{
			cout << "请依次输入修改后的考生的考号，姓名，性别，年龄及报考类别！" << endl;
			cin >> ID;
			if (ID == "0")
			{
				cout << "中断操作（考生的考号不能为0）！" << endl;
				char c;
				while ((c = getchar()) != '\n' && c != EOF);//清空缓存区，防止操作混乱
				return true;
			}
			current->ID = ID;
			cin >> current->name >> current->gender >> current->age >> current->category;

			cout << endl;
			Display();
			return true;
		}
		else
			current = current->next;
	}

	//未找到考生考号
	cout << "您要修改的考生的考号不存在！请重新输入！" << endl;
	return false;
}

void linkList::Display() const
{
	linkNode *current = first;

	cout << "考号\t姓名\t性别\t年龄\t报考种类" << endl;

	while (current != NULL)
	{
		cout << current;
		current = current->next;
	}
}

bool todo();
linkList list;

int main()
{
	int index;

	list.Initial();

	while (1)//操作码必须有效，否则不断要求输入合法的操作码！
	{
		if (todo()) break;
	}

	return 0;
}

bool todo()
{
	int index;

	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作或退出本系统）：";
	cin >> index;
	switch (index)
	{
	case 1:
		while (1)//插入成功则结束
		{
			if (!list.Insert())
				continue;
			else
				break;
		}
		break;
	case 2:
		while (1)//删除成功则结束
		{
			if (!list.Delete())
				continue;
			else
				break;
		}
		break;
	case 3:
		while (1)//查找成功则结束
		{
			if (!list.Find())
				continue;
			else
				break;
		}
		break;
	case 4:
		while (1)//修改成功则结束
		{
			if (!list.Modify())
				continue;
			else
				break;
		}
		break;
	case 5:
		list.Display();
		break;
	case 0:
		cout << "退出操作界面！" << endl;
		return true;
	default:
		cout << "您想要的操作不存在！请重新输入！" << endl;
		return false;
	}

	return false;
}

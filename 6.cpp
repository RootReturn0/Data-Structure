#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
//祖先显示可改进
struct treeNode
{
	string name = " ";
	treeNode *firstChild = NULL;
	treeNode *sibling = NULL;
	treeNode *parent = NULL;//功能拓展时可用于搜索祖先
	int depth = 0;//结点深度
};

class familyTree
{
public:
	familyTree();//familyTree的构造函数，在内存分配根结点空间并使root指向头结点
	void init();//初始化家谱
	void find() const;//查找家庭
	treeNode* find(const string) const;//搜索结点
	void set();//建立家庭
	void add();//添加家庭成员
	void mod();//修改成员名字
	void del();//删除子树
	void display(const string) const;//显示成员子孙
private:
	treeNode * root;
};

familyTree::familyTree()
{
	root = new treeNode;
}

void familyTree::init()
{
	cout << "首先建立一个家庭！" << endl;
	cout << "请输入祖先的姓名：";
	cin >> root->name;
	cout << "此家谱的祖先是：" << root->name << endl;
}

void familyTree::find() const
{
	string name;
	cout << "请输入要查找的家庭的人的姓名：";
	cin >> name;

	display(name);
}

treeNode* familyTree::find(string name) const
{
	treeNode* current = root;
	stack<treeNode*> s;
	if (current->name == name) return current;
	if (current->firstChild != NULL)//无子结点不必遍历
		while (1)
		{
			current = current->firstChild;
			if (current->name == name)  break;
			if (current->firstChild != NULL) s.push(current);//存在子结点，入栈
			while (current->sibling != NULL)
			{
				current = current->sibling;//向兄弟搜索
				if (current->name == name)  break;
				if (current->firstChild != NULL) s.push(current);//存在子结点，入栈
			}

			if (current->name == name)  break;
			if (s.empty())//栈空，遍历结束
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

	cout << "请输入要建立家庭的人的姓名：";
	cin >> name;
	treeNode *current = find(name);//定位至姓名对应结点
	if (current == NULL)
		cout << "查无此人！请确认姓名后重新进行操作！" << endl;
	else
	{
		cout << "请输入" << name << "的儿女人数：";
		cin >> num;
		cout << "请依次输入" << name << "的儿女的姓名：";

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
			//第一个子女
			current->firstChild = new treeNode;
			current->firstChild->depth = current->depth + 1;
			current = current->firstChild;
			cin >> current->name;
			current->parent = parent;
			//其他子女
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
	cout << "请输入要添加儿女的人的姓名：";
	cin >> pName;
	treeNode* current = find(pName);//定位至姓名对应结点
	if (current == NULL)
		cout << "查无此人！请确认姓名后重新进行操作！" << endl;
	else
	{
		treeNode *parent = find(pName);
		cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
		cin >> name;
		if (current->firstChild == NULL)//无子女
		{
			current->firstChild = new treeNode;
			current->firstChild->name = name;
			current->firstChild->parent = parent;
			current->firstChild->depth = current->depth + 1;
		}
		else//已有子女
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
	cout << "请输入要更改的人的目前姓名：";
	cin >> name;
	treeNode* current = find(name);//定位至姓名对应结点
	if (current == NULL)
		cout << "查无此人！请确认姓名后重新进行操作！" << endl;
	else
	{
		cout << "请输入更改后的姓名：";
		cin >> name;
		cout << current->name << "已更名为";
		current->name = name;
		cout << current->name << endl;
	}
}

void familyTree::del()
{
	string name;
	cout << "请输入要解散家庭的人的目前姓名：";
	cin >> name;
	treeNode* current = find(name);//定位至姓名对应结点
	if (current == NULL)
		cout << "查无此人！请确认姓名后重新进行操作！" << endl;
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
			//清除子女指针
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
		cout << "查无此人！请确认姓名后重新进行操作！" << endl;
	else
	{
		if (current->firstChild != NULL)
			while (1)
			{
				current = current->firstChild;
				q.push(current);//子孙入队
				count = current->depth - temp->depth;
				if (current->firstChild != NULL) s.push(current);//有子结点，入队等待处理
				while (current->sibling != NULL)
				{
					current = current->sibling;
					q.push(current);
					count = current->depth - temp->depth;
					if (current->firstChild != NULL) s.push(current);
				}

				if (s.empty()) break;//子结点队空，遍历结束
				current = s.front();
				s.pop();
			}

		if (q.empty()) cout << name << "没有子孙！" << endl;
		else
		{
			int dep = q.front()->depth;
			for (int i = 1; i <= count; i++)
			{
				cout << name << "的第" << i << "代子孙：";
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
	cout << "**              家谱管理系统                     **\n"
		<< "===================================================\n"
		<< "**           请选择要执行的操作：                **\n"
		<< "**              A --- 完善家庭                   **\n"
		<< "**              B --- 添加家庭成员               **\n"
		<< "**              C --- 解散局部家庭               **\n"
		<< "**              D --- 更改家庭成员姓名           **\n"
		<< "**              E --- 查找局部家庭               **\n"
		<< "**              F --- 退出程序                   **\n"
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
		cout << "\n请选择要执行的操作：";
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
			cout << "退出程序！" << endl;
			break;
		default:
			cout << "操作码不合法！请重新输入！" << endl;
		}
	}

	return 0;
}

#include <iostream>
#include <string>
using namespace std;
//�����ʽ���߽����δ���
struct linkNode//���ṹ��
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

class linkList//������
{
public:
	linkList();//linkList�Ĺ��캯�������ڴ����ͷ���ռ䲢ʹfirstָ��ͷ���
	~linkList();//linkList������������ͨ������Empty()ʵ�ֶ��ڴ�Ļ���
	void Empty();//����������ռ���ڴ棬��ֹ�ڴ�й©
	bool Initial();//����������������
	bool Insert();//�������в���һ�����
	bool Delete();//��������ɾ��һ�����
	bool Find() const;//�������в���һ�����
	bool Modify();//���������޸�һ�����
	void Display() const;//��ʾ�������洢������

private:
	linkNode * first;//ͷ���
	int length;//������
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
	cout << "�����뽨��������Ϣϵͳ��\n"
		<< "�����뿼��������";
	cin >> length;
	while (length <= 0)
	{
		cout << "������������Ϊ�����������������룺";
		cin >> length;
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;

	cin >> current;
	while (current->ID == "0")
	{
		cout << "�����Ŀ��Ų���Ϊ0��\n"
			<< "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
		cin >> current;
	}
	for (int i = 1; i < length; i++)
	{
		current->next = new linkNode;
		current = current->next;
		cin >> current;
		while (current->ID == "0")
		{
			cout << "�����Ŀ��Ų���Ϊ0��\n"
				<< "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
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

	cout << "������Ҫ����Ŀ�����λ�ã�";
	cin >> index;
	if (index == 0)//0Ϊ�жϲ���
	{
		cout << "�жϲ�����" << endl;
		return true;
	}
	for (int i = 1; i < index; i++)//Ѱ��Ҫ����λ�õ�ǰһ�����
	{
		if (current == NULL)
		{
			flag = 0;
			break;
		}
		else
			if (i < index - 1) current = current->next;
	}

	//���в������
	if (flag)
	{
		linkNode *temp = new linkNode;
		cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
		cin >> temp->ID;
		if (temp->ID == "0")
		{
			cout << "�жϲ����������Ŀ��Ų���Ϊ0����" << endl;//0Ϊ������һ����ָ��
			char c;
			while ((c = getchar()) != '\n' && c != EOF);//������뻺��������ֹ�������Ҽ��������
			return true;
		}
		cin >> temp->name >> temp->gender >> temp->age >> temp->category;
		if (index == 1)//����λ��Ϊ��һ�������ͷ���
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
	//����λ������
	cout << "�������λ�ò��Ϸ������������룡" << endl;
	return false;
}

bool linkList::Delete()
{
	string ID;
	linkNode *current = first;

	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
	cin >> ID;
	if (ID == "0")
	{
		cout << "�жϲ�����" << endl;
		return true;
	}

	if (first->ID == ID)
	{
		current = first->next;
		cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << first;
		delete first;
		first = current;

		cout << endl;
		Display();
		return true;
	}
	else
		while (current->next != NULL)
		{
			if (current->next->ID == ID)//Ѱ��Ҫɾ������ǰһ�����
			{
				linkNode *temp = current->next;
				current->next = temp->next;
				cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << temp;
				delete temp;
				temp = NULL;

				cout << endl;
				Display();
				return true;
			}
			else
				current = current->next;
		}

	cout << "��Ҫɾ���Ŀ����Ŀ��Ų����ڣ����������룡" << endl;
	return false;
}

bool linkList::Find() const
{
	string ID;
	linkNode *current = first;

	cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
	cin >> ID;

	if (ID == "0")//0Ϊ�жϲ���
	{
		cout << "�жϲ�����" << endl;
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

	//δ�ҵ���������
	cout << "��Ҫ���ҵĿ����Ŀ��Ų����ڣ����������룡" << endl;
	return false;
}

bool linkList::Modify()
{
	string ID;
	linkNode *current = first;

	cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
	cin >> ID;
	if (ID == "0")//0Ϊ�жϲ���
	{
		cout << "�жϲ�����" << endl;
		return true;
	}
	while (current != NULL)
	{
		if (current->ID == ID)
		{
			cout << "�����������޸ĺ�Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
			cin >> ID;
			if (ID == "0")
			{
				cout << "�жϲ����������Ŀ��Ų���Ϊ0����" << endl;
				char c;
				while ((c = getchar()) != '\n' && c != EOF);//��ջ���������ֹ��������
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

	//δ�ҵ���������
	cout << "��Ҫ�޸ĵĿ����Ŀ��Ų����ڣ����������룡" << endl;
	return false;
}

void linkList::Display() const
{
	linkNode *current = first;

	cout << "����\t����\t�Ա�\t����\t��������" << endl;

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

	while (1)//�����������Ч�����򲻶�Ҫ������Ϸ��Ĳ����룡
	{
		if (todo()) break;
	}

	return 0;
}

bool todo()
{
	int index;

	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ���������˳���ϵͳ����";
	cin >> index;
	switch (index)
	{
	case 1:
		while (1)//����ɹ������
		{
			if (!list.Insert())
				continue;
			else
				break;
		}
		break;
	case 2:
		while (1)//ɾ���ɹ������
		{
			if (!list.Delete())
				continue;
			else
				break;
		}
		break;
	case 3:
		while (1)//���ҳɹ������
		{
			if (!list.Find())
				continue;
			else
				break;
		}
		break;
	case 4:
		while (1)//�޸ĳɹ������
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
		cout << "�˳��������棡" << endl;
		return true;
	default:
		cout << "����Ҫ�Ĳ��������ڣ����������룡" << endl;
		return false;
	}

	return false;
}

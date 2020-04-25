#include <iostream>
#include <vector>
#include <ctime>
#include <stack>

using namespace std;

void display(unsigned int list[], const int num)
{
	for (int i = 0; i < num; i++)
		cout << i << " " << list[i] << endl;
}

unsigned int* init(int &num)
{
	cout << "**            排 序 算 法 比 较                 **\n"
		<< "==================================================\n"
		<< "**            1 --- 快速排序                    **\n"
		<< "**            2 --- 直接插入排序                **\n"
		<< "**            3 --- 冒泡排序                    **\n"
		<< "**            4 --- 选择排序                    **\n"
		<< "**            5 --- 退出程序                    **\n"
		<< "==================================================\n"
		<< endl;
	cout << "请输入要产生的随机数个数(正整数)：";
	cin >> num;
	while (num <= 0)
	{
		cout << "随机数个数必须为正整数！请重新输入：";
		cin >> num;
	}
	unsigned int* list = new unsigned int[num];
	srand((unsigned)time(NULL));//随机数种子
	for (int i = 0; i < num; i++)
	{
		list[i] = rand();
	}

	return list;
}

int quickSort(unsigned int list[], const int num, const int left, const int right)
{
	int pivot = list[right];
	int l = left;
	for (int j = left; j < right; j++)
	{
		if (list[j] <= pivot)//比基准小，放到左区间
		{
			swap(list[l], list[j]);
			l++;
		}
	}
	swap(list[l], list[right]);//l所在位置左侧为较小数，右侧及本身为较大数
	return l;
}
//避免交换或比较次数较大时对计时产生影响
int quickSort(unsigned int list[], const int num, const int left, const int right, unsigned long long &count, unsigned long long &comp)//计数
{
	int pivot = list[right];
	int l = left;
	for (int j = left; j < right; j++)
	{
		if (list[j] <= pivot)
		{
			swap(list[l], list[j]);
			++count;
			l++;
		}
		++comp;
	}
	swap(list[l], list[right]);
	++count;
	return l;
}

void quickSortTime(const unsigned int oList[], const int num)//计时
{
	int l = 0;
	int r = num - 1;
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	stack<int> s;
	quickSort(list, num, l, r);
	s.push(l);
	s.push(r);
	while (!s.empty())//栈不为空
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();

		int index = quickSort(list, num, left, right);

		if (index - 1 > left)//左子序列
		{
			s.push(left);
			s.push(index - 1);
		}
		if (index + 1 < right)//右子序列
		{
			s.push(index + 1);
			s.push(right);
		}
	}
	//display(list,num);
}

void quickSortCount(const unsigned int oList[], const int num)//计数
{
	unsigned long long count = 0;
	unsigned long long comp = 0;
	int l = 0;
	int r = num - 1;
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	stack<int> s;
	quickSort(list, num, l, r, count, comp);
	s.push(l);
	s.push(r);
	while (!s.empty())//栈不为空
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();

		int index = quickSort(list, num, left, right, count, comp);

		if (index - 1 > left)//左子序列
		{
			s.push(left);
			s.push(index - 1);
		}
		if (index + 1 < right)//右子序列
		{
			s.push(index + 1);
			s.push(right);
		}
	}

	cout << "快速排序交换次数：" << count << endl;
	cout << "快速排序比较次数：" << comp << endl;
	//display(list);
}

void insertionSortTime(const unsigned int oList[], const int num)//计时
{
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	for (int i = 0; i < num; i++)//需要num次遍历
	{
		int key = list[i];
		int j = i - 1;//第i个数与i-1个数进行直接插入排序
		while (j >= 0 && list[j] > key)
		{
			list[j + 1] = list[j];//比第i个数大，后移一位
			j--;
		}
		list[j + 1] = key;//插入
	}

	//display(list,num);
}

void insertionSortCount(const unsigned int oList[], const int num)//计数
{
	unsigned long long count = 0;
	unsigned long long comp = 0;
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	for (int i = 0; i < num; i++)
	{
		int key = list[i];
		int j = i - 1;
		while (j >= 0 && list[j] > key)
		{
			++comp;
			list[j + 1] = list[j];
			++count;
			j--;
		}
		++comp;
		list[j + 1] = key;
		++count;
	}

	cout << "直接插入排序交换次数：" << count << endl;
	cout << "直接插入排序比较次数：" << comp << endl;
	//display(list);
}

void bubbleSortTime(const unsigned int oList[], const int num)//计时
{
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	for (int i = 1; i < num; i++)
		for (int j = 0; j < num - 1; j++)
			if (list[j + 1] < list[j])
				swap(list[j], list[j + 1]);//逆序交换

	//display(list,num);
}

void bubbleSortCount(const unsigned int oList[], const int num)//计数
{
	unsigned long long count = 0;
	unsigned long long comp = 0;
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	for (int i = 1; i < num; i++)
		for (int j = 0; j < num - 1; j++)
		{
			if (list[j + 1] < list[j])
			{
				swap(list[j], list[j + 1]);
				++count;
			}
			++comp;
		}

	cout << "冒泡排序交换次数：" << count << endl;
	cout << "冒泡排序比较次数：" << comp << endl;
	//display(list);
}

void selectSortTime(const unsigned int oList[], const int num)//计时
{
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	for (int i = 0; i < num; i++)
	{
		int index = i;
		for (int j = i + 1; j < num; j++)//寻找剩余序列中最小数的序号
		{
			if (list[j] < list[index])
				index = j;
		}
		swap(list[i], list[index]);//放置到序列头部
	}

	//display(list,num);
}

void selectSortCount(const unsigned int oList[], const int num)//计数
{
	unsigned long long count = 0;
	unsigned long long comp = 0;
	unsigned int *list = new unsigned int[num];
	memcpy(list, oList, sizeof(int)*num);

	for (int i = 0; i < num; i++)
	{
		int index = i;
		for (int j = i + 1; j < num; j++)
		{
			if (list[j] < list[index])
				index = j;
			++comp;
		}
		swap(list[i], list[index]);
		++count;
	}

	cout << "选择排序交换次数：" << count << endl;
	cout << "选择排序比较次数：" << count << endl;
	//display(list);
}

int main()
{
	int num;
	int index;
	unsigned int *list = init(num);
	clock_t start, finish;

	//display(list,num);

	while (1)
	{
		int flag = 0;
		cout << "\n请选择排序算法：";
		cin >> index;
		switch (index)
		{
		case 1:
			//若个数较少，则无法得出有效时间，必须多次排序取平均值
			if (num <= 1000)
			{
				start = clock();
				for (int i = 0; i < 1000; i++)
					quickSortTime(list, num);
				finish = clock();
				cout << "快速排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC / 1000 << endl;
			}
			else
			{
				start = clock();
				quickSortTime(list, num);
				finish = clock();
				cout << "快速排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
			}
			quickSortCount(list, num);
			break;
		case 2:
			if (num <= 1000)
			{
				start = clock();
				for (int i = 0; i < 1000; i++)
					insertionSortTime(list, num);
				finish = clock();
				cout << "直接插入排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC / 1000 << endl;
			}
			else
			{
				start = clock();
				insertionSortTime(list, num);
				finish = clock();
				cout << "直接插入排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
			}
			insertionSortCount(list, num);
			break;
		case 3:
			if (num <= 1000)
			{
				start = clock();
				for (int i = 0; i < 1000; i++)
					bubbleSortTime(list, num);
				finish = clock();
				cout << "冒泡排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC / 1000 << endl;
			}
			else
			{
				start = clock();
				bubbleSortTime(list, num);
				finish = clock();
				cout << "冒泡排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
			}
			bubbleSortCount(list, num);
			break;
		case 4:
			if (num <= 1000)
			{
				start = clock();
				for (int i = 0; i < 1000; i++)
					selectSortTime(list, num);
				finish = clock();
				cout << "选择排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC / 1000 << endl;
			}
			else
			{
				start = clock();
				selectSortTime(list, num);
				finish = clock();
				cout << "选择排序所用时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
			}
			selectSortCount(list, num);
			break;
		case 5:
			flag = 1;
			break;
		default:
			cout << "操作码不合法！请重新输入！" << endl;
		}
		if (flag) break;
	}

	return 0;
}
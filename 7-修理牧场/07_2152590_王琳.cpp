/*2152590 王琳*/
#include<iostream>
using namespace std;

//最小堆,还必须得用数组，因为要使用他的下标的特性，能够直接获取，计算
template<class T>
class MinHeap
{
public:
	MinHeap(int maxSize);
	MinHeap(T arr[], int n);//构造函数
	//~MinHeap(delete[]heap)//析构函数
	bool Insert(const T& x);//插入函数
	bool RemoveMin(T& x);//删除最小元素
	bool IsEmpty()const { return CurrentSize == 0; }
	bool IsFull()const { return CurrentSize == MaxHeapSize; }
	void MakeEmpty() { CurrentSize = 0; }
	int MinCost();
private:
	enum { DefaultSize = 10 };
	T* heap; //最小堆数组头指针
	int CurrentSize;
	int MaxHeapSize;
	void FilterDown(int start, int EndOfHeap);//下滑调整，删除之后的调整
	void FilterUp(int start);//向上调整，插入后调整

};
template<class T>
MinHeap<T>::MinHeap(int maxSize)
{
	//根据给定大小maxSize，建立堆对象
	MaxHeapSize = DefaultSize < maxSize ? maxSize : DefaultSize;//确定堆的大小
	heap = new T[MaxHeapSize]; //创建堆大小的数组，heap为数组头指针
	CurrentSize = 0;//当前数组大小为0
}

template<class T>
MinHeap<T>::MinHeap(T arr[], int n)
{
	//根据给定数组中的数据和大小,建立堆对象
	MaxHeapSize = DefaultSize < n ? n : DefaultSize; //选大的
	heap = new T[MaxHeapSize];
	heap = arr;//数组直接复制
	CurrentSize = n;//当前堆大小
	int currentPos = (CurrentSize - 2) / 2;	//最后一个非叶子结点的位置
	while (currentPos >= 0)//从下到上逐步扩大，形成堆
	{
		FilterDown(currentPos, CurrentSize - 1);
		//从currentPos开始，到CurrentSize为止，调整
		--currentPos;
	}
}

//最小堆的自上向下调整算法
template<class T>
void MinHeap<T>::FilterDown(int start, int EndOfHeap)
{
	int i = start, j = 2 * i + 1; //j是i的左子女
	while (j <= EndOfHeap)//当j在堆大小的范围内
	{
		T temp = heap[i]; //更新temp
		if (j<EndOfHeap && heap[j]>heap[j + 1])//如果左子女大于右子女值，两子女中选小的
			++j;
		if (temp <= heap[j])//如果关键码值符合最小堆规律
			break;
		else//不符合,把子女中小的给当前结点进行赋值
		{
			heap[i] = heap[j];
			//以子女为当前结点继续往下循环调整
			i = j;
			j = 2 * i + 1;
		}
		heap[i] = temp;//现在的i位置即为原来子女的位置
	}
}

template<class T>
bool MinHeap<T>::Insert(const T& x)
{
	if (CurrentSize == MaxHeapSize)
	{
		cout << "堆已满" << endl;
		return false;
	}
	heap[CurrentSize] = x; //插在表尾
	FilterUp(CurrentSize); //向上调整为堆
	++CurrentSize;  //堆元素加1
	return true;

}

template <class T>
void MinHeap<T>::FilterUp(int start)
{
	//从start开始，向上直到0，调整堆
	int j = start, i = (j - 1) / 2; //i是j的双亲
	while (j > 0)
	{
		T temp = heap[j]; //更新temp
		if (heap[i] <= temp)//如果双亲小于子女，符合最小堆规律
			break;
		else //如果不符合
		{
			heap[j] = heap[i];//将双亲结点放到子女结点的位置
			j = i;
			i = (j - 1) / 2;
		}
		heap[i] = temp;
	}
}

template<class T>
bool MinHeap<T>::RemoveMin(T& x)
{
	if (CurrentSize == 0)
	{
		cout << "堆已空" << endl;
		return false;
	}
	x = heap[0]; //删除堆顶元素
	heap[0] = heap[CurrentSize - 1];//用最后一个元素填补
	--CurrentSize;
	FilterDown(0, CurrentSize - 1); //从0号位置开始自顶向下调整为堆
	return true;
}

template<class T>
int MinHeap<T>::MinCost()
{
	int min_fir;//最小的
	int min_sec;//次小的
	int count = 0;//花费
	int sum;//两两合并的和
	while (CurrentSize != 1)
	{
		RemoveMin(min_fir);
		RemoveMin(min_sec);
		count += min_fir + min_sec;
		sum = min_fir + min_sec;
		Insert(sum); //将两两合并的和放入最小堆中
	}


	return count;
}

int main()
{
	int num;//记录木头要切成几块
	int money;//最小花费
	//用最小堆来求解每次的最小的和次小的；
	cout << "请输入要将木头锯成几块：";
	//进行输入错误处理
	while (1)
	{
		cin >> num;
		if (num <= 0 || cin.fail())
		{
			cout << "输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	int* arr = new int[num];//动态开辟数组
	int temp;//用来暂存输入数据
	cout << "请输入" << num << "个正整数，表示每块木头的长度:" << endl;
	while (1)
	{
		int count = 0;
		for (int i = 0; i < num; ++i)
		{
			cin >> temp;
			if (temp <= 0 || cin.fail())
			{
				cout << "输入第" << i + 1 << "段木头的长度错误！" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				++count;
				cout << "请重新输入所有木头长度！" << endl;
				break;
			}
			else
				arr[i] = temp;				
		}
		if (count == 0)
			break;
	}
	MinHeap<int> wood(arr,num); //创建堆对象，初始化
	money=wood.MinCost();

	cout << "最小花费为："<<money<<endl;
	return 0;
}


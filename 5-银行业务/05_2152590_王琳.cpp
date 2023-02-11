/*2152590 王琳*/
#include<iostream>
using namespace std;
//链式队列，在单链表的基础上修改一下
template<class T>
class Queue;

template<class T>
class QueueNode {

	template<class T>
	friend class Queue; //声明Queue类为友元类

public:
	QueueNode(QueueNode<T>* ptr = nullptr) { link = ptr; } 	//仅初始化指针成员的构造函数

	QueueNode(const T& item, QueueNode<T>* ptr = nullptr) :data(item), link(ptr) {}	//初始化数据与指针成员的构造函数

private:

	T data;
	QueueNode<T>* link; //链指针域

};
template<class T>
class Queue {
public:
	Queue() :rear(NULL), front(NULL) {} //无参构造函数
	~Queue() { MakeEmpty(); } //析构函数

	/*链表的公共操作*/

	void EnQueue(const T& x);	//进队列

	bool DeQueue(T& x);	//出队列

	bool GetFront(T& x);//读取队头元素

	void MakeEmpty();//将队列清空

	bool IsEmpty()const { return front == NULL; }	//判断队列是否为空

	int GetSize()const;//读取队列大小

private:
	QueueNode<T>* front; //队列头指针,指向头元素
	QueueNode<T>* rear;//队列尾指针，指向尾元素

};

template <class T>
int Queue<T>::GetSize()const
{
	//因为队列用的链式，所以不能直接头尾指针相减
	int count = 0;
	QueueNode<T>* p = front;
	while (p != NULL && IsEmpty() == 0)//队列不为空
	{
		++count;
		p = p->link;
	}
	return count;


}
//进队列
template <class T>
void Queue<T>::EnQueue(const T& x) {

	//如果队列为空
	if (front == NULL)
	{
		front = rear = new QueueNode<T>(x, NULL);
	}
	//如果队列不为空
	else
	{
		rear->link = new QueueNode<T>(x, NULL);//创建一个新结点链到队尾
		rear = rear->link;//更新队尾指针
	}

}



//出队列
template <class T>
bool Queue<T>::DeQueue(T& x) {

	if (IsEmpty() == 0)//队列不为空
	{
		QueueNode<T>* p = front;
		x = front->data;
		front = front->link;
		delete p;

		return true;

	}

	return false;
}

//清空队列
template <class T>
void Queue<T>::MakeEmpty() {
	QueueNode<T>* p;
	while (front != NULL)//队头指针不为空，说明还有元素
	{
		p = front;
		front = front->link;//队头指针后移一格
		delete p;//删除原来的队头结点
	}
}


template <class T>
bool Queue<T>::GetFront(T& x)
{
	//若队列不空，则函数返回队头元素的值及true。
	if (IsEmpty() == true)return false;//若队列空，则函数返回false；
	x = front->data;
	return true;
}



int main()
{
	Queue<int> A;//A窗口
	Queue<int> B;//B窗口
	cout << "请输入一行正整数 ，其中第一数字N为顾客总数，后面跟着N位顾客的编号：" << endl;

	int num;
	while (1)
	{
		cin >> num;//先将总数读入
		if (cin.fail() || num <= 0)
		{
			cout << "总数错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else
			break;
	}
	
	//输入部分
	while (1)
	{
		int temp;
		cin >> temp;
		//健壮性处理
		if (cin.fail())
		{
			cout << "顾客编号输入错误，请重新输入！" << endl;
			B.MakeEmpty();
			A.MakeEmpty();//将前面已经输入的清空
			cin.clear();
			cin.ignore(1024,'\n');	
			continue;
		}

		if (temp % 2 == 0)//为偶数,进B窗口
			B.EnQueue(temp);
		else              //为奇数，进A窗口
			A.EnQueue(temp);

		int ret=getchar();//读空格或者回车，判断结束
		if (ret == 10)
			break;
		else
			continue;


	}
	//count用来计数,控制最后一个编号没有空格
	int out;//用来记录输出
	for (int count = 0; count < num;)
	{
		//A窗口先输出
		if (A.GetSize()>=2)
		{
			if (count == num - 2)//最后两个个元素
			{
				A.DeQueue(out);
				cout << out << ' ';
				++count;//输出一个+1
				A.DeQueue(out);
				cout << out;
				++count;//输出一个+1
			}
			else
			{
				for (int i = 0; i < 2; ++i)
				{
					A.DeQueue(out);
					cout << out << ' ';
					++count;//输出一个+1
				}

			}
		}
		else if(A.GetSize()==1) //A还剩一位顾客
		{
			if (count == num - 1) //最后一位顾客
			{

				A.DeQueue(out);
				cout << out;
				++count;//输出一个+1	

			}
			else
			{
				A.DeQueue(out);
				cout << out << ' ';
				++count;//输出一个+1

			}

		}
		//B窗口后输出
		if (B.GetSize() >0)
		{
			if (count == num - 1)//最后1个元素
			{
				B.DeQueue(out);
				cout << out;
				++count;//输出一个+1
				
			}
			else
			{
				B.DeQueue(out);
				cout << out<<' ';
				++count;//输出一个+1
			}
		}
		
		

	}


	return 0;
}




/*2152590 王琳*/
#include<iostream>
using namespace std;

template<class T>
class List;

template<class T>
class LinkNode {

	template<class T>
	friend class List; //声明List类为友元类

public:
	LinkNode(LinkNode<T>* ptr = nullptr) { link = ptr; data = 0; } 	//仅初始化指针成员的构造函数

	LinkNode(const T& item, LinkNode<T>* ptr = nullptr) { data = item; link = ptr; }	//初始化数据与指针成员的构造函数

private:

	T data;
	LinkNode<T>* link; //链指针域

};
template<class T>
class List {
public:
	List() { first = new LinkNode<T>(0); } //构造函数
	List(const T& x) { first = new LinkNode<T>(x); } //构造函数，给头结点附上一个值
	List(List<T>& L); //复制构造函数
	~List() { makeEmpty(); delete first; } //析构函数,清空然后把头结点也删除掉

	/*链表的公共操作*/

	LinkNode<T>* Insert(int i, T& x);	//在第i个元素后面插入元素

	LinkNode<T>* Remove(int i);	//删除第i个元素，x返回该元素的值？

	bool IsEmpty()const { return first->link == nullptr ? true : false; }	//判断链表是否为空

	//void Sort(); //排序
	LinkNode<T>* input(); //后插法建立链表 呢为啥后插法建立链表他不会出了函数就没有了

	void display()const; //输出
	bool makeEmpty(); //将链表置为空表，收回链表所占的内存，防止内存泄漏
	int Length()const; //计算链表的长度
	LinkNode<T>* getHead()const { return first; } //返回头结点地址
	LinkNode<T>* setHead(LinkNode<T>* p) { first = p; return first; } //设置头结点地址
	int Search(T x); //搜索结点
	LinkNode<T>* Locate(int i); //搜索第i个元素的地址
	T getData(int i); //取出第i个元素的值
	void setData(T& x, LinkNode<T>*& current); //用X修改第i个元素的值
private:
	LinkNode<T>* first; //链表头指针


};


template <class T>
LinkNode<T>* List<T>::Insert(int i, T& x) {

	LinkNode<T>* current = Locate(i);//要插入位置的前一个

	LinkNode<T>* newnode = new LinkNode<T>(x); //创建一个值为x的新结点

	newnode->link = current->link;
	current->link = newnode;

	return current->link; //插入成功,返回当前结点
}

//复制构造函数
template <class T>
List<T>::List(List<T>& L) {

	T value;
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* destptr = first = new LinkNode<T>; //创建一个新结点作为头结点，

	while (srcptr->link != nullptr) {
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link; //两个指针往后移
	}

	destptr->link = NULL;//尾结点

}

//删除第i个元素
template <class T>
LinkNode<T>* List<T>::Remove(int i) {

	LinkNode<T>* current = Locate(i);//要删除的位置的前一个

	//特殊判断
	if (current->link == NULL)return NULL;//删除不成功

	LinkNode<T>* tem = current->link; //暂存

	current->link = tem->link;

	delete tem;

	return current->link; //更新current,返回下一个结点的位置

}

//将链表置为空表，因为链表是从头开始遍历，所以没法从后往前删，可以说是头结点删除法，相应的逆序还有头结点插入法
template <class T>
bool List<T>::makeEmpty() {
	LinkNode<T>* tem;
	//头结点的link域不为空
	while (first->link != NULL) {

		tem = first->link;
		first->link = tem->link;  //表头链接下一个结点
		delete tem;          //删除碎片
		//tem = NULL;
	}
	return true;
}

//计算链表的长度，通过循环count++
template <class T>
int List<T>::Length()const {
	LinkNode<T>* current = first->link; //用于遍历的指针
	int count = 0; //用来计数

	while (current != NULL) {
		++count;
		current = current->link; //current更新
	}
	return count;
}


//查找结点，遍历链表，然后找到x值，返回结点地址(查找的是第一个)
template <class T>
int List<T>::Search(T x) {
	int count = 0; //用来记录位置
	LinkNode<T>* current = first->link;
	for (; current != nullptr; current = current->link) {
		++count;
		if (current->data == x) return count;
	}
	return -1; //没有搜索到
}

//搜索第i个元素的地址
template <class T>
LinkNode<T>* List<T>::Locate(int i) {

	//问题：如果是要删除的是第1个，那么你上来就是从第一个开始
	LinkNode<T>* current = first;
	int count = 0;
	//通过循环进行遍历，然后到要插入/删除的位置的前一个就停止
	for (; current->link != nullptr; current = current->link) {

		if (count + 1 != i)++count;
		else
			break;

	}
	return current;
}


template <class T>
void List<T>::setData(T& x, LinkNode<T>*& current) {
	//错误处理
	if (current == NULL)return; //i值太大
	else
	{
		current->data = x;
	}

}

//后插法建立链表
template <class T>
LinkNode<T>* List<T>::input() {

	LinkNode <T>* current = new LinkNode<T>; //创建一个新结点
	LinkNode <T>* tem = first;
	while (tem->link != nullptr)
		tem = tem->link;
	tem->link = current; //与前面一个结点进行连接
	cin >> current->data;
	return current;
}

//取出第i个元素的值
template <class T>
T List<T>::getData(int i) {

	LinkNode <T>* current = Locate(i + 1);

	return current->data;
}


template <class T>
//输出函数
void List<T>::display()const
{
	//不用创建头指针，本身就有
	LinkNode <T>* current = first->link;
	while (current != NULL)
	{
		if (current->link != NULL) //没到最后一个
			cout << current->data << ' ';
		else
			cout << current->data;
		current = current->link; //指针往后移一个
	}
}

void qujiao(List<int>fir,List<int>sec,List<int>&result)
{

	int fir_size = fir.Length();
	int sec_size = sec.Length();
	int count = 1;
	if (fir_size == 0 || sec_size == 0)return; //其中一个序列为空
	
	for (int i = 1,j=1; ;)
	{
	
		if (fir.getData(i) == sec.getData(j)) //有交集
		{
			int res = fir.getData(i);
			result.Insert(i,res);
			if ((i == fir_size) && (j == sec_size))//同时遍历到最后一个结束循环
				break;
			if(i != fir_size)
				++i;
			if(j != sec_size)
				++j; //均往后移

		}
		else if (fir.getData(i) > sec.getData(j)) //如果fir大
		{
			if (j != sec_size)
				++j; //小的往后移，因为不可能有相等的
			else
				break;
		}
		else //如果sec大
		{
			if (i != fir_size)
				++i;
			else
				break;
		}

	}
}
int main()
{
	cout << "请输入两个非降序链表序列S1和S2，输入分两行，数字用空格间隔，用-1表示序列的结尾" << endl;

	List<int> list_fir,list_sec,list_result; //实例化第一第二和结果链表
	//输入正确性检查
	while (1)
	{
		list_fir.input();
		int in = list_fir.getData(list_fir.Length());
		if (in == -1)
			break;
		else
		{
			if (cin.fail())
			{
				cout << "输入错误，请重新输入S1" << endl;
				cin.clear();
				cin.ignore(1024,'\n');
				//cout <<"cin的状态" << cin.good() << endl;
				//system("pause");
				list_fir.makeEmpty(); //清空输入进去的
			}
		}
	}
	//把-1删除
	list_fir.Remove(list_fir.Length());

	while (2)
	{
		list_sec.input();
		int in = list_sec.getData(list_sec.Length());
		if (in == -1)
			break;
		else
		{
			//如果是一些数字之外的符号就要进行处理，那怎么控制范围呢
			if (cin.fail())
			{
				cout << "输入错误，请重新输入S2" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				list_sec.makeEmpty(); //清空输入进去的
			}
		}
	}
	//把-1删除
	list_sec.Remove(list_sec.Length());

	if (list_fir.Length() == 0 || list_sec.Length() == 0) //其中一个序列为空
	{
		cout << "NULL";
	}
	else
	{
		qujiao(list_fir, list_sec, list_result);
		if (list_result.Length() != 0)
			list_result.display(); 
		else
			cout << "NULL";
	}

	return 0;
}
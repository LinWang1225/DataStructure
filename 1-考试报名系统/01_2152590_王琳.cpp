/*2152590 王琳*/
#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
using namespace std;
//链表类实现
template<class T>
class List;

template<class T>
class LinkNode {

	template<class T>
	friend class List; //声明List类为友元类

public:
	LinkNode(LinkNode<T>* ptr = nullptr) { link = ptr; } 	//仅初始化指针成员的构造函数

	LinkNode(const T& item, LinkNode<T>* ptr = nullptr) { data = item; link = ptr; }	//初始化数据与指针成员的构造函数

private:

	T data;
	LinkNode<T>* link; //链指针域

};
template<class T>
class List {
public:
	List() { first = new LinkNode<T>(0); } //构造函数，开辟一个头结点
	List(const T& x) { first = new LinkNode<T>(x); } //构造函数，给头结点附上一个值
	List(List<T>& L); //复制构造函数
	~List() { makeEmpty(); delete first; } //析构函数,清空然后把头结点也删除掉

	/*链表的公共操作*/
	LinkNode<T>* Insert(int i, T& x);	//在第i个元素后面插入元素

	LinkNode<T>* Remove(int i);	//删除第i个元素，x返回该元素的值？

	bool IsEmpty()const { return first->link == nullptr ? true : false; }	//判断链表是否为空

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

	//因为已经实例化了一个链表，它本身就有自己的头结点了,但是还要自己一个一个创建结点，不是直接就可以往里面放
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

//输出函数
template <class T>
void List<T>::display()const
{
	//不用创建头指针，本身就有
	LinkNode <T>* current = first->link;
	while (current != NULL)
	{
		cout << current->data << endl;
		current = current->link; //指针往后移一个
	}
}

//string类实现
class String {

public:
	String(); //无参构造函数，字符串长度为1，有尾零
	String(const char* str);      //构造函数
	String(const String& S); //复制构造函数
	~String();  //析构函数
	String& operator = (const String& s);//重载赋值运算符

	int Length()const { return sizeof(*sptr) / sizeof(char); }
	//char* c_str()const;
	//友元函数，重载输入输出流
	friend ostream& operator << (ostream& out, String& s);
	friend istream& operator>>(istream& in, String& s);
	bool operator!=(const char* s2);//！=运算符重载，参数只能一个，双目运算符本身有一个了

private:
	char* sptr;      //存储数组
	int maxsize = 50;
	int curLength; //数组现在的长度
};

//无参构造函数
String::String() {
	sptr = new char[maxsize];
	*sptr = '\0';
	curLength = 0;
	maxsize = 0;
}

//构造函数
String::String(const char* str) {

	//错误处理,空串要开辟多大的数组呢？
	if (!str) {

		sptr = new char[1];
		*sptr = '\0';
		curLength = 0;
		maxsize = 0;
	}
	else {
		curLength = strlen(str);
		maxsize = curLength + 1;
		sptr = new char[maxsize];//动态开辟数组

		//因为使用的是数组，需要连续的存储空间，所以要判断开辟成不成功
		if (sptr == nullptr) {
			cerr << "分配不成功！" << endl;
			return;
		}
		strcpy(sptr, str);
	}
}

//复制构造函数
String::String(const String& s) {

	curLength = strlen(s.sptr);
	maxsize = curLength + 1;
	sptr = new char[maxsize];
	strcpy(sptr, s.sptr);
}

//重载赋值运算符
String& String:: operator = (const String& s)
{
	if (this == &s)
		return *this;
	if (sptr != NULL)
	{
		delete[]sptr;
		sptr = NULL;
	}
	curLength = s.curLength;
	sptr = new char[curLength + 1];
	strcpy(sptr, s.sptr);
	return *this;
}
ostream& operator << (ostream& out, String& s)
{
	out << s.sptr;
	return out;
}
istream& operator>>(istream& in, String& s)
{
	in >> s.sptr;
	return in;
}

String::~String()
{
	delete[]sptr;
	sptr = NULL;
}
//!=运算符重载，如果不相等，则返回的是true，相等返回false
bool String::operator!=(const char* s2)
{

	if (Length() + 1 != strlen(s2))
		return true;
	else
	{
		for (int i = 0; i < Length(); ++i)
		{
			if (sptr[i] != s2[i])
				return true;
		}
		return false;
	}
}
struct student {
	int number = 0; //考号
	String name; //姓名
	String sex; //性别
	int age = 0; //年龄
	String type; //报考类型

	friend istream& operator >>(istream& in, student& stu) {
		while (1)
		{
			in >> stu.number;
			if (stu.number < 0 || in.fail())
			{
				cerr << "考号输入错误，请重新输入考号以及之后的信息！" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}
		in >> stu.name;
		while (2)
		{
			in >> stu.sex;
			if ((stu.sex != "男") && (stu.sex != "女"))
			{
				cerr << "性别输入错误，请重新输入性别以及之后的信息！" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}

		while (3)
		{
			in >> stu.age;
			if (stu.age < 0 || in.fail())
			{
				cerr << "年龄输入错误，请重新输入年龄以及之后的信息！" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}
		in >> stu.type;
		return in;
	}
	friend ostream& operator <<(ostream& out, student& stu) {
		out << stu.number << "      " << stu.name << "    " << stu.sex << "    " << stu.age << "     " << stu.type;
		return out;
	}
};

int main()
{
	int stu_num;
	int choice;
	cout << "首先请建立考生信息系统!" << endl;
	cout << "请输入考生人数:" ;
	while (cin >> stu_num)
	{
		//非法输入处理
		if (stu_num < 0)
		{
			cout << "非法输入,请重新输入" << endl;
		}
		else
			break;
	}
	cout << "请依次输入考生的考号,姓名,性别,年龄及报考类别!" << endl;

	//创造一个结构体用于输入，后插法创建链表
	//先创建一个类对象实例化，然后调用输入函数，一个个输入
	List<student> registerlist;
	for (int i = 0; i < stu_num; ++i)
	{
		registerlist.input();  //一开始输入每位考生信息，但没有对这个进行检查
	}
	cout << endl;
	cout << "考号   姓名   性别   年龄    报考类别" << endl;
	registerlist.display();
	while (1)
	{
		cout << endl<<"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
		cout << endl;
		cout << "请选择您要进行的操作：";
		while (cin >> choice)
		{
			//非法输入处理
			if ((choice >= 0) && (choice <= 5))
			{
				break;
			}
			else
				cout << "非法输入,请重新输入" << endl;

		}
		switch (choice) {

		case 0:
			return 0;
		case 1: {
			cout << "请输入你要插入的考生的位置：";
			int position;
			while (cin >> position)
			{
				//非法输入处理
				if ((position > 0) && (position <= registerlist.Length() + 1))
				{
					break;
				}
				else
					cout << "非法输入,请重新输入" << endl;
			}
			cout << "请依次输入要插入的考生的学号，姓名，性别，年龄及报考类别！" << endl;
			struct student push_stu;
			cin >> push_stu;
			registerlist.Insert(position, push_stu);//插入操作
			cout << endl;
			cout << "考号   姓名   性别   年龄    报考类别" << endl;
			registerlist.display();
			break;
		}
		case 2: {
			cout << "请输入你要删除的考生的考号：";
			int position;
			while (cin >> position)
			{				
				if ((position > 0) && (position <= registerlist.Length()))
				{
					break;
				}
				else
					cout << "非法输入,请重新输入" << endl;
			}
			struct student pop_stu = registerlist.getData(position);
			cout << "你要删除的考生信息是：" << pop_stu << endl;
			cout << "考号   姓名   性别   年龄    报考类别" << endl;
			registerlist.Remove(position);//删除操作
			registerlist.display();
			break;
		}
		case 3: {
			cout << "请输入你要查找的考生的考号：";
			int position;
			while (cin >> position)
			{
				//非法输入处理
				if ((position > 0) && (position <= registerlist.Length()))
				{
					break;
				}
				else
					cout << "非法输入,请重新输入" << endl;
			}
			struct student search_stu = registerlist.getData(position);//查找得到数据操作
			cout << endl;
			cout << "考号   姓名   性别   年龄    报考类别" << endl;
			cout << search_stu << endl;
			break;
		}
		case 4:
		{
			cout << "请输入你要修改的考生的考号：";
			int position;
			while (cin >> position)
			{
				//非法输入处理
				if ((position > 0) && (position <= registerlist.Length()))
				{
					break;
				}
				else
					cout << "非法输入,请重新输入" << endl;
			}
			cout << "请依次输入修改后的考生的学号，姓名，性别，年龄及报考类别！" << endl;
			struct student set_stu;
			cin >> set_stu;
			LinkNode<student>* pos = registerlist.Locate(position + 1); //搜索第i个元素的地址
			registerlist.setData(set_stu, pos);//修改操作
			cout << endl;
			cout << "考号   姓名   性别   年龄    报考类别" << endl;
			registerlist.display();
			break;
		}
		default:
			break;

		}
	}
		
	
	
		return 0;

}
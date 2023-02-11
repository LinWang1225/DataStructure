#pragma once
/*2152590 王琳*/
#include<iostream>
#include<stdio.h>
using namespace std;

template<class T>
class ListStack;

template<class T>
class StackNode {

	template<class T>
	friend class ListStack; //声明ListStack类为友元类

public:
	StackNode(StackNode<T>* ptr = nullptr) { link = ptr; } 	//仅初始化指针成员的构造函数
	StackNode(const T& item, StackNode<T>* ptr = nullptr) { data = item; link = ptr; }	//初始化数据与指针成员的构造函数

private:

	T data;
	StackNode<T>* link; //链指针域

};
template<class T>
class ListStack {
public:
	ListStack() :top(NULL) {}//构造函数，置空栈
	~ListStack() {}//析构函数
	void Push(const T& x);//进栈
	StackNode<T>* Pop(T& x);//退栈
	T getTop(T& x)const;//读取栈顶元素
	bool IsEmpty()const { return (top == NULL) ? true : false; }
	int getSize();//求栈的元素个数


private:
	StackNode<T>* top; //栈顶指针


};

//退栈,更新一下栈顶元素
template <class T>
StackNode<T>* ListStack<T>::Pop(T& x) {

	if (IsEmpty() == true)return NULL;
	else
	{
		StackNode <T>* tem = top;
		top = top->link;
		x = tem->data; //这个地方存一下，因为用引用是可以的
		delete tem;
		return top;
	}

}

template<class T>
T ListStack<T>::getTop(T& x)const
{
	if (IsEmpty() == true)return x;
	else
	{
		x = top->data;
		return x;
	}
}

template <class T>
int ListStack<T>::getSize()
{
	int count = 0;
	StackNode<T>* fir = top;
	while (fir != NULL)
	{
		++count;
		fir = fir->link;
	}
	return count;
}
template<class T>
void ListStack<T>::Push(const T& x)
{
	//没有栈满的情况
	top = new StackNode<T>(x, top); //创建新的含x结点,他的指针域指向原来的栈顶头指针，现在他变成新的头结点
	if (top == NULL)
		cout << "创建新结点失败" << endl;
}
/*算术操作符优先级
					  操作符    （   *，/       +，-    ）  #
in stack priority(栈内优先级)    1     5         3      6   0
in coming priority(栈外优先级)   6     4         2      1   0

加入#号相当于为了进行操作的时候进行初始化，不至于是空栈
为了同级直接出栈，除了括号进栈之后降到最低，其他的优先级都降一个

*/
#include<map>

//中缀转化为后缀
void infix_to_postfix()
{
	ListStack<string> operator_stack;//算术运算符顺序栈
	//栈内操作符优先级
	map<string, int>in_stack_priority;
	in_stack_priority.insert(pair<string, int>("#", 0));
	in_stack_priority.insert(pair<string, int>("(", 1));
	in_stack_priority.insert(pair<string, int>("*", 5));
	in_stack_priority.insert(pair<string, int>("/", 5));
	in_stack_priority.insert(pair<string, int>("+", 3));
	in_stack_priority.insert(pair<string, int>("-", 3));
	in_stack_priority.insert(pair<string, int>(")", 6));
	//栈外操作符优先级
	map<string, int>in_coming_priority;
	in_coming_priority.insert(pair<string, int>("(", 6));
	in_coming_priority.insert(pair<string, int>("*", 4));
	in_coming_priority.insert(pair<string, int>("/", 4));
	in_coming_priority.insert(pair<string, int>("+", 2));
	in_coming_priority.insert(pair<string, int>("-", 2));
	in_coming_priority.insert(pair<string, int>(")", 1));

	operator_stack.Push("#");
	string top;
	string ch;//用来存放输入ch
	int tem;//存放getchar返回值
	string temp;//用来暂存
	int judge = 1;//用来判断是否到达结尾，消除空格输出，并结束循环
	while (judge)
	{
		cin >> ch;//遇到空格/回车跳过
		tem = getchar(); //将空格读入，并且处理回车终止
		if (tem == 10)//回车结束输入
			judge = 0;
		//如果是算数运算符
		if (ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "(" || ch == ")")
		{
			top = operator_stack.getTop(temp);  
			//先判断运算符优先级，如果运算级高就进栈
			if (in_coming_priority[ch] > in_stack_priority[top])
				operator_stack.Push(ch); //进栈
			//如果小于,栈顶就退栈,并输出，后进栈
			else if (in_coming_priority[ch] < in_stack_priority[top])
			{
				if (ch == ")")//如果是右括号就删除多次，直到把左括号删除
				{
					while (operator_stack.getTop(top) != "(")
					{
						operator_stack.Pop(temp);
						if (judge == 1)
							cout << temp << ' ';
						else
							cout << temp;
					}
					operator_stack.Pop(temp);//删除左括号
				}
				else
				{
					while ((in_coming_priority[ch] < in_stack_priority[operator_stack.getTop(top)])&& operator_stack.getSize()!=1)
					{
						operator_stack.Pop(temp);
						cout << temp << ' ';
					}
					operator_stack.Push(ch);

				}

			}//end of else -if
			//只有左右括号时才有可能相等
			else
			{
				operator_stack.Pop(ch);
			}
		}//end of 1-if
		//如果是数字直接输出,控制结尾无多余空格
		else
		{
			if (judge == 1 || operator_stack.getSize() != 1)
			{

				if (ch[0] == '+')	//如果是正数，就不输出正号
				{
					for (int i = 1; i < int(ch.length()); ++i)
					{
						cout << ch[i];
					}

					cout << ' ';
				}
				else				//如果是负数需要将负号也输出
					cout << ch << ' ';
			}
				
			else
			{
				if (ch[0] == '+')
				{
					for (int i = 1; i < int(ch.length()); ++i)
					{
						cout << ch[i];
					}
				}
				cout << ch;
			}
				
		}
	}
	//如果栈不为空，将元素依次退栈
	while (operator_stack.getSize()>1)
	{
		if (operator_stack.getSize() == 2)
		{
			operator_stack.Pop(temp);
			cout << temp;
		}
		else
		{
			operator_stack.Pop(temp);
			cout << temp << ' ';
		}
		
	}
	
}

int main()
{
	cout << "输入一行以空格分割不同对象的中缀表达式，可包含+,-,*,/以及左右括号(英文字符)，表达式不超过20个字符(不包含空格)" << endl;
	infix_to_postfix();
	return 0;
}



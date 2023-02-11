/*2152590 王琳*/
#include<iostream>
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
	void Pop(T& x);//退栈
	bool getTop(T& x)const;//读取栈顶元素
	bool IsEmpty()const { return (top == NULL) ? true : false; }
	int getSize();//求栈的元素个数


private:
	StackNode<T>* top; //栈顶指针


};

//退栈
template <class T>
void ListStack<T>::Pop(T& x) {

	if (IsEmpty() == true)return;
	else
	{
		StackNode <T>* tem = top;
		top = top->link;
		x = tem->data; //这个地方存一下，因为用引用是可以的
		delete tem;
	}

}

template<class T>
bool ListStack<T>::getTop(T& x)const
{
	if (IsEmpty() == NULL)return false;
	else
	{
		x = top->data;
		return true;
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
//移动方向
struct direction {
	int x, y;//分别是x,y方向的偏移
	//char* dir;//dir是当前位置前进的方向，便于该方向不通的时候回溯找下一个方向；
	friend ostream& operator <<(ostream& out, direction& dir) {
		out <<'<' << dir.x << ',' << dir.y <<'>';
		return out;
	}
};
//遵循右下左上的顺序试探,定义一个存放在某一位置向四个方向前进的数组
direction Direct[4] = { {0,1},{1,0},{0,-1},{-1,0} };
//存放路径的栈
ListStack<direction> path;
direction temp;
//给定一个6*6的迷宫地图，给定一个数组存放
//入口为（1，1），出口为（5，5）；
char maze[7][7] = {
	'#','#','#','#','#','#','#',
	'#','0','#','0','0','0','#',
	'#','0','#','0','#','#','#',
	'#','0','0','0','#','0','#',
	'#','0','#','0','0','0','#',
	'#','0','#','0','#','0','#',
	'#','#','#','#','#','#','#'
};
int dest_x = 5, dest_y = 5;//规定出口


//递归寻找路径思路：从入口开始试探，每个最多只有四个试探方向，然后每层函数试探四个方向，一个方向不行下一个方向，知道找到合适的方向，然后继续调用递归函数
//进入到下一层之后，如果进入死胡同，说明找不到有效路径，那就return false到上一层函数，即返回到上一个位置，然后继续从其他方向遍历；
bool SeekPath(int x, int y)
{
	int tem_x, tem_y; //记录位置信息
	if ((x == dest_x)&&(y == dest_y))//到达出口，递归终止条件
		return true;

	//最多只有四个方向循环找能走的路，如果是边界的话，只有三个方向
	for (int i = 0; i < 4; ++i)
	{
		//所以前面要加上判断条件
		tem_x = x + Direct[i].x;
		tem_y = y + Direct[i].y;//将坐标加上偏移量
		//有了偏移量之后，可能会产生非法访问，数组越界，所以要进行判断
		if (tem_x <= 0 || tem_y <= 0)//如果有到墙壁或者出去了的情况就直接跳过这个方向
			continue;
		if (maze[tem_x][tem_y] == '0')//如果该位置可以走，并且没有走过
		{
			maze[tem_x][tem_y] = 'x';//标记为访问过
			if (SeekPath(tem_x, tem_y)) {//继续递归，如果找到能继续下去的路径返回值为true；
				temp = { tem_x,tem_y };
				path.Push(temp);//将其插入链表后面
				return true;
			}
		}	
	}
	
	//如果四个方向都不满足，说明找不到有效路径
	return false;

}
int main()
{
	
	//刚开始将入口标记为1
	maze[1][1] = 'x';
	//将入口处压入栈中
	if (SeekPath(1, 1))//调用递归函数,如果找到有效路径直接输出
	{
		cout << "迷宫地图：" << endl;
		cout << "      0列   1列   2列   3列   4列   5列   6列" << endl;
		for (int i = 0; i < 7; ++i)
		{
			cout << i << "行    ";
			for (int j = 0; j < 7; ++j)
			{
				cout << maze[i][j]<<"     ";

			}
			cout << endl<<endl;
		}

		cout << endl;
		cout << "迷宫路径：" << endl;
		temp = { 1,1 };
		cout << temp<< " ---> ";
		while (path.getSize())
		{
			path.Pop(temp);
			cout << temp;
			if (path.getSize() != 0)
				cout << " ---> ";
			else
				cout << endl;
		}
		return 0;
	}
	else
	{
		cout << "没有找到有效路径！" << endl;
	}
	return 0;
}



/*2152590 王琳*/
#include<iostream>
using namespace std;

template<class T>
class Queue;
template<class T>
class Tree;

template<class T>
class TreeNode {

	template<class T>
	friend class Tree;
private:
	T data; //结点数据
	TreeNode<T>* firstChild = NULL, * nextSibling = NULL;//第一子女及兄弟指针,先初始化
	TreeNode(T value = 0, TreeNode<T>* fc = NULL, TreeNode<T>* ns = NULL) :data(value), firstChild(fc), nextSibling(ns) {};//构造函数

};

template<class T>
class Tree {

private:
	TreeNode<T>* root = NULL, * current = NULL;
	bool Find(TreeNode<T>* p, T value);             //在以p为根的树中搜索value
	void RemovesubTree(TreeNode<T>* p);             //删除以p为根的子树
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);//寻找双亲结点
public:
	//Tree() { root = current = NULL; }
	void BuildRoot(T rootVal);                  //建立树的根结点，并使之成为当前结点
	bool Root();                               //寻找根，使之成为当前结点
	bool IsEmpty() { return root == NULL; }    //判空树
	bool FirstChild();                         //寻找当前结点的第一个子女，使之成为当前结点
	bool NextSibling();                        //寻找当前结点的下一个兄弟，使之成为当前结点
	bool Parent();							  //寻找当前结点的双亲结点，使之成为当前结点
	bool Find(T target);					  //在树中搜索含有target的结点，使之成为当前结点
	//树的其他公共操作
	TreeNode<T>* Buildfir_Child(T value);	  //创建第一子女结点,链到双亲结点上
	TreeNode<T>* BuildnextSibling(T value);
	bool display_child();					 //输出子孙链，即从第一子女开始一直从第一子女一右到底输出,从当前结点开始
	void addchild();						 //创建家庭
	void add();								//添加子女
	void remove();							//解散家庭，删除子树所有
	bool setdata();							//设置/修改结点信息
};
template<class T>
bool Tree<T>::setdata()
{
	string name; //要组建家庭的人的姓名
	cout << "请输入要更改姓名的人的目前名字：";
	cin >> name;
	if (Find(name))
	{
		cout << "请输入更改后的名字：";
		string change_name;
		cin >> change_name;
		//操作
		current->data = change_name;
		cout << name << "已更名为" << change_name;
		return true;
	}
	cout << "家谱中不存在此人！" << endl;
	return false;
}

template<class T>
void Tree<T>::remove()
{
	string name; //要组建家庭的人的姓名
	string child_name; //存放子女的姓名
	cout << "请输入要解散的家庭的人的姓名：";
	cin >> name;
	if (!Find(name)) //查无此人
	{
		cout << "家谱中不存在此人！" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << name << endl;
	cout << name << "的第一代子孙是：";
	if (FirstChild())//判断不为空的同时，第一子女作为当前节点
	{
		display_child();
		Find(name);//使要解散的家庭的人成为当前结点（根结点）
		//删除孩子结点，不能只改变指针，防止生成碎片
		RemovesubTree(current);
		Find(name);//把当前指针调回	
		current->firstChild = NULL; //主要是这边把他断开了，但是碎片没有删干净！
	}
	else
		cout << "该人没有子女可解散！" << endl;
}


template<class T>
void Tree<T>::add()
{
	string name; //要组建家庭的人的姓名
	string child_name; //存放子女的姓名
	cout << "请输入要添加儿子(或女儿)的人的姓名：";
	cin >> name;
	if (!Find(name)) //查无此人
	{
		cout << "家谱中不存在此人！" << endl;
		return;
	}
	cout << "请输入" << name << "新添加的儿子(或女儿)的姓名：";
	cin >> child_name;
	if (FirstChild())//如果有第一子女
	{
		while (current->nextSibling != NULL)
			current = current->nextSibling; //指向下一个兄弟
		BuildnextSibling(child_name);
	}
	else//没有第一子女就直接创建
	{
		Find(name);//先在树中找到该结点
		Buildfir_Child(child_name);
	}
	Find(name);
	cout << name << "的第一代子孙是：";
	if (FirstChild())//判断不为空的同时，第一子女作为当前节点
		display_child();

}
template<class T>
void Tree<T>::addchild()
{
	string name; //要组建家庭的人的姓名
	string child_name; //存放子女的姓名
	cout << "请输入要建立家庭的人的姓名：";
	cin >> name;
	if (!Find(name)) //查无此人
	{
		cout << "家谱中不存在此人！" << endl;
		return;
	}
	FirstChild();
	if (current != NULL)//如果他已经有家庭了
	{
		cout << "此人已经组建家庭！" << endl;
		return;
	}
	cout << "请输入" << name << "的儿女人数：";
	int num;//儿女数目
	while (1)
	{
		cin >> num;
		if (num <= 0 || cin.fail())
		{
			cout << "输入人数不正确，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	Find(name);
	cout << "请依次输入" << name << "的儿女的姓名：";
	for (int i = 0; i < num; ++i)
	{
		cin >> child_name;
		if (i == 0)//第一个子女
		{
			Buildfir_Child(child_name);
		}
		else//不是第一个子女就链到第一个子女的右子树上！
		{
			BuildnextSibling(child_name);
		}

	}
	Find(name);
	//cout <<"此处打印的是打印之前的查找：" << Find(name) << endl;
	cout << name << "的第一代子孙是：";
	if (FirstChild())//判断不为空的同时，第一子女作为当前节点
		display_child();

}
template<class T>
bool Tree<T>::display_child()
{
	//同时更新当前结点
	if (current != NULL)
	{
		while (current != NULL)
		{
			cout << current->data << ' ';
			current = current->nextSibling; //指向下一个兄弟
		}
		cout << endl;
		return true;
	}

	return false;
}
template<class T>
void Tree<T>::RemovesubTree(TreeNode<T>* p)
{
	//用队列的方法依次删除
	Queue<TreeNode<T>*> delete_queue;		//删除队列
	if (FirstChild())
	{
		//按顺序把子女结点依次放入队列当中
		while (current != NULL)
		{
			delete_queue.EnQueue(current);
			current = current->nextSibling;
		}
	}
	//队列不为空，出队列，同时把出队列的结点的子女再放进队列当中
	while (delete_queue.GetSize() != 0)
	{
		TreeNode<T>* temp;
		delete_queue.DeQueue(temp);
		current = temp;
		if (FirstChild())//如果出队列的结点有孩子，依次进队列
		{
			while (current != NULL)
			{
				delete_queue.EnQueue(current);
				current = current->nextSibling;
			}
		}
		delete temp;//出队列就删除
	}

}
template<class T>
bool Tree<T>::Root()
{
	//让树的根结点成为树的当前结点
	if (root == NULL)
	{
		current = NULL;
		return false;
	}

	else
	{
		current = root;
		return true;
	}
}

template<class T>
bool Tree<T>::Parent()
{
	//在树中找当前结点的父结点，使之成为当前结点

	TreeNode<T>* p = current;
	if (current == NULL || current == root) //如果是空树或者已经是根结点了，没有父结点，返回false
	{
		current = NULL;
		return false;
	}
	return FindParent(root, p);//从根开始找*p的父结点

}

template<class T>
bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p)
{
	//在根为*t的树中找*p的父结点，并使之成为当前结点
	TreeNode<T>* q = t->firstChild; //从第一个子女开始搜索
	//递归搜索
	while (q != NULL && q != p) //循根的长子的兄弟链，搜索
	{
		if (FindParent(q, p) == true)return true;//以q为根结点，找到p
		q = q->nextSibling; //没找到就以下一个兄弟结点为根结点进行循环
	}
	if (q != NULL && q == p) //如果q不为空且是该结点
	{
		current = t;//t即为当前结点的父结点
		return true;
	}
	else //未找到父结点
	{
		current = NULL;
		return false;
	}
}

template<class T>
bool Tree<T>::FirstChild()
{
	//在树中找到当前结点的长子，并使之成为当前结点
	if (current != NULL && current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
}

template<class T>
bool Tree<T>::NextSibling()
{
	//在树中找到当前结点的兄弟，并使之成为当前结点
	if (current != NULL && current->nextSibling != NULL)
	{
		current = current->nextSibling;
		return true;
	}
	current = NULL;
	return false;
}

//函数重载

template<class T>
bool Tree<T>::Find(T value)
{
	if (IsEmpty())return false;//树为空
	return Find(root, value);//调用私有函数从根结点开始进行查找
}

template<class T>
bool Tree<T>::Find(TreeNode<T>* p, T value)
{
	//在根为*p的树中找值为value的结点，找到后该结点成为当前结点，否则当前结点不变
	if (p->data == value)
	{
		current = p;
		return true;//搜索成功
	}
	else
	{
		TreeNode<T>* q = p->firstChild;
		while (q != NULL && !Find(q, value))//如果没找到，循环递归寻找
			q = q->nextSibling;
		if (q == NULL)
			return false;
		else
			return true;
	}
}


template<class T>
void Tree<T>::BuildRoot(T rootVal)
{
	//创建一个新结点，使之成为树的根结点，并使之成为树的当前结点
	root = current = new TreeNode<T>(rootVal);
}

template<class T>
TreeNode<T>* Tree<T>::BuildnextSibling(T value)
{
	TreeNode<T>* sibling = new TreeNode<T>(value);
	current->nextSibling = sibling;//将其他子女作为第一子女的左兄弟
	current = sibling;//更新当前结点为创建的结点
	return current;
}
template<class T>
TreeNode<T>* Tree<T>::Buildfir_Child(T value)
{

	TreeNode<T>* child = new TreeNode<T>(value);
	current->firstChild = child;//将第一子女作为父结点[当前结点]的左子女
	current = child;//更新当前结点为创建的结点
	return current;
}


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
	cout << "**		家谱管理系统		   **" << endl;
	cout << "=============================================" << endl;
	cout << "**	       请选择要执行的操作：        **" << endl;
	cout << "**		A --- 完善家谱		   **" << endl;
	cout << "**		B --- 添加家庭成员	   **" << endl;
	cout << "**		C --- 解散局部家庭	   **" << endl;
	cout << "**		D --- 更改家庭成员姓名     **" << endl;
	cout << "**              E --- 退出程序             **" << endl;
	cout << "=============================================" << endl;
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string ancestor;  //家谱的祖先
	char choice; //执行的操作选项
	cin >> ancestor;
	cout << "此家谱的祖先是：" << ancestor<<endl<<endl;
	Tree<string> family_tree;//创建一棵家族树
	family_tree.BuildRoot(ancestor); //创建根结点为给定名称
	while (1)
	{
		cout << "请选择要执行的操作：";
		while (1)
		{
			cin >> choice;
			if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E')
			{
				cout << "输入错误，请重新输入！" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}
		switch (choice)
		{
		case 'A':
			//完善家谱
			family_tree.addchild();
			break;
		case 'B':
			//添加操作
			family_tree.add();
			break;
		case 'C':
			family_tree.remove();
			break;
		case 'D':
			family_tree.setdata();
			break;
		case 'E':
			return 0;
			break;
		default:
			break;
		}
		cout << endl << endl;
	}
	
}



/*2152590 王琳*/

# define DefaultVertices 100
# define maxWeight 1e4 + 10 //  用于表示不连通的两点的距离
#include<iostream>
using namespace std;
template<class T,class E>
struct Edge {
	int dest;  //另一顶点的位置
	E cost; //边上的权值
	Edge<T, E>* link; //下一条边链指针
	Edge():dest(-1),cost(maxWeight),link(NULL){}
	Edge(int num,E weight):dest(num),cost(weight),link(NULL){}//构造函数
	bool operator !=(Edge<T, E>& R)const { return (dest != R.dest) ? true : false; }//判断边是否相等

};

//顶点的定义
template <class T,class E>
struct Vertex {
	T data; //顶点名字
	Edge<T, E>* adj; //边链表的头指针
};

//邻接表表示的图类
template<class T,class E>
class Graphlnk{
public:
	Graphlnk(int sz = DefaultVertices);//构造函数
	~Graphlnk();//析构函数
	T getValue(int i) {return(i > 0 && i < numVertices) ? NodeTable[i].data : 0;} // 取位置为i的顶点中的值	
	E getWeight(int v1,int v2); // 返回边(vl, v2)上的权值
	bool insertVertex(const T &vertex);//在图中插人一个顶点vertex	
	bool removeVertex(int v);//在图中删除一个顶点v
	bool insertEdge(int v1, int v2,E weight);	//在图中插人--条边(v1,v2)
	bool removeEdge(int v1 ,int v2);//在图中删除一条边(v1,v2)
	int getFirstNeighbor(int v);//取顶点v的第一个邻接顶点
	int getNextNeighbor(int v ,int w);//取v的邻接顶点w的下一邻接顶点
	bool TopologicalSort();//拓扑排序
	void CriticalPath();
	int NumberOfVertices()const { return numVertices; }
	void inputEdge();
private:
	Vertex<T, E>* NodeTable;//顶点表〔各边链表的头结点)
	int getVertexPos(const T vertex) {  // 给出顶点vertex在图中的位置
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex) return i;
		return -1;
	}
	int maxVertices; //图中最大顶点个数
	int numEdges;        //当前边数
	int numVertices;  //当前顶点数
	int* count; //入度数组兼入度为零顶点栈
};
template <class T, class E>
void Graphlnk<T, E>::inputEdge()
{
	int i;
	int V1,V2,weight;
	int top = -1; //入度为零顶点的栈初始化
	int enumber, vnumber; //e边结点个数，v顶点个数
	cout << "请输入任务交接点的数量：";
	cin >> vnumber;
	//检验输入的合法性，对输入错误处理：
	while (cin.fail() || vnumber <= 0) {
		cout << "任务交接点数量只能是正整数!" << endl;
		cout << "请重新输入任务交接点数量:";
		cin.clear();
		cin.ignore(1024, '\n');
		cin >> vnumber;
	}
	cout << "请输入子任务的数量：";
	cin >> enumber;
	int MaxEdgeNum = vnumber * (vnumber - 1) / 2;
	while (cin.fail() || enumber <= 0 || (enumber > MaxEdgeNum)) {
		//首先对边数的输入错误进行处理
		if (enumber <= 0 || cin.fail())
			cout << "子任务的个数只能是正整数!" << endl;
		//其次对当前边数进行判断，防止边数超过最大限制
		else if (enumber > MaxEdgeNum)
			cout << "子任务的数量超过最大值!" << endl;
		cout << "请重新输入子任务个数:";
		cin.clear();
		cin.ignore(1024, '\n');
		cin >> enumber;
	}
	//初始化顶点
	for (i = 1; i < vnumber+1; ++i)
	{
		insertVertex(i);
	}
	count = new int[vnumber];
	for (i = 0; i < vnumber; i++) count[i] = 0;// 初始化
	cout << "请输入3个正整数，分别是该任务开始和完成设计的交接点编号以及完成该任务所需要的时间，整数间用空格分隔：" << endl;
	for (i = 0; i < enumber; ++i)
	{
		while (true) {
			//cout << "请输入两个顶点及边：";
			cin >> V1 >> V2 >> weight;
			//获取位置
			int v1 = getVertexPos(V1);
			int v2 = getVertexPos(V2);
			//检验输入的合法性，对输入错误处理：
			if (cin.fail())
				cout << "输入非法！";
			else if (v1 == v2)
				cout << "输入的两个顶点相同！";
			else if (v1 == -1)
				cout << "第一个顶点不存在!";
			else if (v2 == -1)
				cout << "第二个顶点不存在!";
			//对边权重的合法性检查
			else if (weight <= 0)
				cout << "每一条边的代价必须是正整数！";
			else {
				insertEdge(v1, v2, weight); // 插入边
				++count[v2];            //记录顶点入度
				break;//继续循环输入
			}
			cin.clear();
			cin.ignore(1024, '\n');
			cout << endl;
			cout << "请重新输入两个顶点及边：";
		}
	}
	if (TopologicalSort())
		CriticalPath();
	else
		cout << 0 << endl;
	return;
}

//拓扑排序
template <class T, class E>
bool Graphlnk<T,E>::TopologicalSort() 
{
	int top = -1; //入度为零顶点的栈初始化
	int n = NumberOfVertices(); 
	int i;
	for (i = 0; i < n; i++)
	{//检查网络所有顶点
		if (count[i] == 0) { count[i] = top; top = i; }
	}		//入度为零的顶点进栈
	for (i = 0; i < n; i++) //期望输出n个顶点
	{
		if (top == -1) //中途栈空,转出
		{
			return false;
		}
		else 
		{  //继续拓扑排序
			int v = top;
			top = count[top]; 	//退栈v
			Edge<T, E>* w = NodeTable[v].adj;
			while (w)
			{
				int k = w->dest;
				if (--count[k] == 0)
				{
					count[k] = top;
					top = k;
				}
				w = w->link;
			}
		}

	}
	return true;
}


//关键路径法求关键活动
template <class T, class E>
void Graphlnk<T, E>::CriticalPath() {
	int i, j, k;
	E Ae, Al, w;
	int n = NumberOfVertices();
	E* Ve = new E[n];
	E* Vl = new E[n];
	for (i = 0; i < n; i++)Ve[i] = 0;
	for (i = 0; i < n; i++) {  //正向计算Ve[]
		j = getFirstNeighbor(i);
		while (j != -1) {
			w = getWeight(i, j);
			if (Ve[i] + w > Ve[j]) Ve[j] = Ve[i] + w;
			j = getNextNeighbor(i, j);
		}
	}
	Vl[n-1] = Ve[n -1];
	for (j = n - 2; j > 0; j--) {	/// 逆向计算Vl[]
		k = getFirstNeighbor(j);
		Vl[j] = Ve[n - 1];
		while (k != -1) {
			w = getWeight(j, k);
			if (Vl[k] - w < Vl[j])Vl[j] = Vl[k] - w;
			k = getNextNeighbor(j, k);
		}
	}
	cout << "完成整个项目所需要的时间：" << Ve[n - 1] << endl;
	for (i = 0; i < n; i++) {  //求各活动的e,l

		j = getFirstNeighbor(i);
		while (j != -1) {
			Ae = Ve[i];
			Al = Vl[j] - getWeight(i, j);
			if (Al == Ae) //关键活动
			{
				cout << i+1 << "->" << j +1<< endl;
			}
			j = getNextNeighbor(i, j);
		}

	}
	delete[] Ve;
	delete[] Vl;
};



template <class T,class E>
Graphlnk<T, E>::Graphlnk(int sz) {// 构造函数:建立一个空的邻接表

	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertices];//创建顶点表数组
	if (NodeTable == NULL) { cerr << "存储分配错!" << endl; exit(1); }
	for (int i = 0; i < maxVertices; i++ )
		NodeTable[i].adj = NULL;
}

template <class T,class E>
Graphlnk<T, E>::~Graphlnk(){     //析构函数:删除一个邻接表
	for (int i = 0; i < numVertices; i++) {  // 删除各边链表中的结点
		
		Edge<T, E> *p = NodeTable[i].adj; // 找到其对应边链表的首结点
		while (p != NULL)// 不断地删除第一个结点
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;//删除顶点表数组
	delete[]count;
};

template <class T,class E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {  //给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回一1。

	if (v != -1) {  //顶点v存在
		
		Edge<T, E>* p = NodeTable[v].adj; //对应边链表第一个边结点	
		if (p != NULL)  //存在，返回第一个邻接顶点
			return p -> dest;
	}
	//第 1个邻接顶点不存在
	return -1;
}

//给出顶点v的邻接顶点w的下一个邻接顶点的位置，若没有下一个邻接顶点，则函数返回一1。
template <class T,class E>
int Graphlnk<T, E> ::getNextNeighbor(int v ,int w) {
	
	if (v != -1) { //顶点v存在

		Edge<T, E>* p = NodeTable[v].adj; //对应边链表第一个边结点
		while (p != NULL && p->dest != w) //寻找邻接顶点w
			p = p ->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;	//返回下一个邻接顶点
	}
	return -1; //不存在下一邻接顶点
}

//函数返回边(v1,v2)上的权值，若该边不在图中，则函数返回权值0。
template <class T,class E > 
E Graphlnk<T, E> ::getWeight(int v1, int v2) {  

	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj; //v1的第一条关联的边
		while (p != NULL && p -> dest != v2) // 寻找邻接顶点v2
			p = p ->link;
		if (p != NULL) return p ->cost; //找到此边,返回权值
	};
	return 0; //边(v1,v2)不存在
}

//在图的顶点表中插入一个新顶点vertex。若插入成功,函数返回 true，否则返回false。
template <class T,class E>
bool Graphlnk<T, E> :: insertVertex(const T& vertex) {
	if (numVertices == maxVertices) return false; //顶点表满,不能插入
	NodeTable[numVertices].data = vertex;
	//插入在表的最后
	numVertices++; 
	return true;
};

//在图中删除一个指定顶点v，v是顶点号。若删除成功，函数返回true，否则返回false。
template <class T,class E>
bool Graphlnk<T, E>::removeVertex(int v) {
	if (numVertices == 1 || v < 0 || v >= numVertices) return false; //表空或顶点号超出范围
	
	Edge<T, E> *p,* s,*t;//t用于暂存
	int i,k;
	//删除第v个边链表中所有结点
	while (NodeTable[v].adj != NULL) {
		p = NodeTable[v].adj;
		k = p -> dest; //取邻接顶点k
		s = NodeTable[k].adj;
		t == NULL;
		//找对称存放的边结点（双向边）
		while (s != NULL && s->dest != v) {
			t = s;
			s = s->link;
		}
		if (s != NULL) {
			//删除对称存放的边结点
			if (t == NULL)NodeTable[k].adj = s->link; //更新头指针
			else t -> link = s ->link;
			delete s;
		}
		NodeTable[v].adj = p->link; //清除顶点v的边链表结点
		delete p;
		numEdges--; //与顶点v相关联的边数减1
		numVertices--; //图的顶点个数减1
		NodeTable[v].data = NodeTable[numVertices].data;//用最后一个元素填补
		p = NodeTable[v].adj = NodeTable[numVertices].adj;
		while (p != NULL){
			s = NodeTable[p->dest].adj;
			while (s != NULL)
			{
				if (s->dest == numVertices) { s->dest = v; break; }
				else s = s->link;
			}
		}
	}
	return true;
}

// 插入边（v1,v2）---头插法
template <class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {//合法顶点数据
		Edge<T, E>* p = NodeTable[v1].adj; // v1对应的边链表头指针
		while (p != NULL) {  // 寻找邻接顶点v2
			if (p->dest == v2)
				return false;//已存在此边，插入失败，返回false
			else
				p = p->link;
		}
		p = new Edge<T, E>; // 创建新结点
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj; // 链入v1边链表的头结点的位置
		NodeTable[v1].adj = p;
		numEdges++;
		return true;
	}
	//顶点参数不合法，函数返回false
	return false;
}

//在图中删除--条边(v1，v2)
template <class T,class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2) { 
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj, * q = NULL, * s = p;
		while (p != NULL && p->dest != v2)  //vl对应边链表中找被删边
		{
			q = p; p = p->link;
		}
		if (p != NULL) { //找到被删边结点
			if (p == s)NodeTable[v1].adj = p->link; //该结点是边链表首结点
			else q->link = p->link; //不是，重新链接
			delete p;
		}
		else return false; 	//没有找到被删边结点
		p = NodeTable[v2].adj;
		q = NULL, s = p; //v2对应边链表中删除

		while (p->dest != v1) { q = p; p = p->link; } // 寻找被删边结点
		if (p == s)NodeTable[v2].adj = p->link; //该结点是边链表首结点
		else q->link = p->link; //不是,重新链接
		delete p;
		return true;
	}
	return false; /// 没有找到结点

}


int main()
{
	Graphlnk<int, int>task; //实例化
	task.inputEdge();
	return 0;
}



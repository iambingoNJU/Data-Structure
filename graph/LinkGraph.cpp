#include <iostream>
using namespace std;

#include <assert.h>
#include "../queue/LinkedQueue/LinkedQueue.cpp"
const int DefaultVertices = 30;

template <class T, class E>
struct Edge 
{
	int dest;
	E cost;
	Edge<T,E> *next;
	Edge() {}
	Edge(int num, E weight) : dest(num), cost(weight), next(NULL) {}
	bool operator!=(Edge<T,E>& R) const { return dest != R.dest; }
};

template <class T, class E>
struct Vertex
{
	T data;
	Edge<T,E> *adj;
};

/* This is a defination of directed graph class, storing with linklist. */
template <class T, class E>
class LinkGraph
{
private:
	int numVertices, maxVertices;
	int numEdges;
	Vertex<T,E> *NodeTable;
	int getVertexPos(const T vertex) { 
		for(int i=0; i<numVertices; i++)
			if(NodeTable[i].data == vertex)	return i;
		return -1;
	}
	void DFS(int v, bool visited[]);

public:
	LinkGraph(int sz=DefaultVertices);
	~LinkGraph();
	T getValue(int i) { assert(i>=0 && i<numVertices);	return NodeTable[i].data; }
	E getWeight(int v1, int v2);
	E getWeight(T v1, T v2) { return getWeight(getVertexPos(v1), getVertexPos(v2)); }
	bool insertVertex(T vertex);
	bool removeVertex(int v);
	bool removeVertex(T vertex) { return removeVertex(getVertexPos(vertex)); }
	bool insertEdge(int v1, int v2, E cost);
	bool insertEdge(T v1, T v2, E cost) { return insertEdge(getVertexPos(v1), getVertexPos(v2), cost); }
	bool removeEdge(int v1, int v2);
	bool removeEdge(T v1, T v2) { return removeEdge(getVertexPos(v1), getVertexPos(v2)); }
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	void showVertex();
	void showEdge();
	void show() { showVertex(); showEdge(); }
	void DFS(T v);
	void BFS(T v);
};


template <class T, class E>
LinkGraph<T,E>::LinkGraph(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex<T,E>[maxVertices];
	assert(NodeTable!=NULL);
	for(int i=0; i<maxVertices; i++)	NodeTable[i].adj = NULL;
}

template <class T, class E>
LinkGraph<T,E>::~LinkGraph()
{
	for(int i=0; i<numVertices; i++)
	{
		Edge<T,E> *temp = NodeTable[i].adj;
		while(temp) {
			NodeTable[i].adj = temp->next;
			delete temp;
			temp = NodeTable[i].adj;
		}
	}

	delete []NodeTable;
}

template <class T, class E>
int LinkGraph<T,E>::getFirstNeighbor(int v)
{
	if(v>=0 && v<numVertices)
	{
		Edge<T,E> *temp = NodeTable[v].adj;
		if(temp)	return temp->dest;
	}

	return -1;
}

template <class T, class E>
int LinkGraph<T,E>::getNextNeighbor(int v, int w)
{
	if(v>=0 && v<numVertices)
	{
		Edge<T,E> *temp = NodeTable[v].adj;
		while(temp && temp->dest!=w)	temp=temp->next;
		if(temp && temp->next)	return temp->next->dest;
	}

	return -1;
}

template <class T, class E>
E LinkGraph<T,E>::getWeight(int v1, int v2)
{
	if(v1>=0 && v1<numVertices && v2>=0 && v2<numVertices)
	{
		Edge<T,E> *temp = NodeTable[v1].adj;
		while(temp && temp->dest!=v2)	temp = temp->next;
		if(temp)	return temp->cost;
	}

	return 0;
}

template <class T, class E>
bool LinkGraph<T,E>::insertVertex(T vertex)
{
	if(numVertices == maxVertices)	return false;
	for(int i=0; i<numVertices; i++)
		if(NodeTable[i].data == vertex)
		{
			cout<<"Vertex '"<<vertex<<"' already existed."<<endl;
			return false;
		}
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}

template <class T, class E>
bool LinkGraph<T,E>::removeVertex(int v)
{
	if(v<0 || v>=numVertices)	return false;

	/* Remove all edges from v. */
	Edge<T,E> *temp1, *temp2;
	while(NodeTable[v].adj)
	{
		temp1 = NodeTable[v].adj;
		NodeTable[v].adj = temp1->next;
		delete temp1;
		numEdges--;
	}

	numVertices--;
	
	/* Fill the deleted empty position with the last one. This makes vertices in NodeTable out of order. */
	NodeTable[v].data = NodeTable[numVertices].data;
	NodeTable[v].adj = NodeTable[numVertices].adj;
	for(int k = 0; k<=numVertices; k++)
	{
		/* Remove all edges linking to v. */
		temp2 = NULL, temp1 = NodeTable[k].adj;
		while(temp1 && temp1->dest!=v)
		{
			temp2 = temp1;
			temp1 = temp1->next;
		}
		if(temp1)
		{
			if(temp2)
				temp2->next = temp1->next;
			else
				NodeTable[k].adj = temp1->next;
			delete temp1;
			numEdges--;
		}

		/* Change edges' dest if it links to the last one. */ 
		temp1 = NodeTable[k].adj;
		while(temp1)
		{
			if(temp1->dest == numVertices)
			{
				temp1->dest = v;
				break;
			}
			else
				temp1 = temp1->next;
		}
	}

	return true;
}

template <class T, class E>
bool LinkGraph<T,E>::insertEdge(int v1, int v2, E weight)
{
	if(v1>=0 && v1<numVertices && v2>=0 && v2<numVertices)
	{
		Edge<T,E> *temp1 = NULL, *temp2 = NodeTable[v1].adj;
		while(temp2 && temp2->dest<v2)
		{
			temp1 = temp2;
			temp2 = temp2->next;
		}
		if(temp2 && temp2->dest==v2) 
		{
			cout<<"Edge '"<<NodeTable[v1].data<<"-->"<<NodeTable[v2].data<<"' already existed."<<endl;
			return false;		//Already exsited!
		}
		else
		{
			/* Insert to linklist to keep order. */
			if(temp1==NULL)
			{
				NodeTable[v1].adj = new Edge<T,E>(v2,weight);
				NodeTable[v1].adj->next = temp2;
			}
			else
			{
				temp1->next = new Edge<T,E>(v2,weight);
				temp1->next->next = temp2;
			}

			numEdges++;
			return true;
		}
	}

	/* No such vertex. */
	return false;
}

template <class T, class E>
bool LinkGraph<T,E>::removeEdge(int v1, int v2)
{
	if(v1>=0 && v1<numVertices && v2>=0 && v2<numVertices)
	{
		Edge<T,E> *temp1 = NULL, *temp2 = NodeTable[v1].adj;
		while(temp2 && temp2->dest!=v2)
		{
			temp1 = temp2;
			temp2 = temp2->next;
		}
		if(temp2)
		{
			if(temp1==NULL)
				NodeTable[v1].adj = temp2->next;
			else
				temp1->next = temp2->next;
			delete temp2;
			numEdges--;
			return true;
		}
	}
	return false;
}

template <class T, class E>
void LinkGraph<T,E>::showVertex()
{
	cout<<"There are "<<numVertices<<" vertices:\n";
	for(int i=0; i<numVertices; i++)
		cout<<NodeTable[i].data<<" ";
	cout<<endl;
}

template <class T, class E>
void LinkGraph<T,E>::showEdge()
{
	if(numEdges==0)
	{
		cout<<"No edges."<<endl;
		return;
	}
	else
		cout<<"There are "<<numEdges<<" edges:\n";
	Edge<T,E> *temp;
	int dest;
	for(int i=0; i<numVertices; i++)
	{
		temp = NodeTable[i].adj;
		while(temp)
		{
			cout<<NodeTable[i].data<<"->"<<NodeTable[temp->dest].data<<'('<<temp->cost<<')'<<"\t";
			temp = temp->next;
		}
		cout<<endl;
	}
}

template <class T, class E>
void LinkGraph<T,E>::DFS(T v)
{
	bool *visited = new bool[numVertices];
	for(int i=0; i<numVertices; i++)	visited[i] = false;
	DFS(getVertexPos(v), visited);
	delete []visited;
	cout<<"\b\b  "<<endl;
}

template <class T, class E>
void LinkGraph<T,E>::DFS(int v, bool visited[])
{
	cout<<getValue(v)<<"->";
	visited[v] = true;
	int w = getFirstNeighbor(v);
	while(w!=-1)
	{
		if(visited[w] == false)	DFS(w,visited);
		w = getNextNeighbor(v,w);
	}
}

template <class T, class E>
void LinkGraph<T,E>::BFS(T v)
{
	bool *visited = new bool[numVertices];
	for(int i=0; i<numVertices; i++)	visited[i] = false;
	int loc = getVertexPos(v), w;
	cout<<v<<"->";
	visited[loc] = true;
	LinkedQueue<int> Q;
	Q.enQueue(loc);
	while(Q.deQueue(loc))
	{
		w = getFirstNeighbor(loc);
		while(w != -1)
		{
			if(visited[w] == false)
			{
				cout<<getValue(w)<<"->";
				visited[w] = true;
				Q.enQueue(w);
			}
			w = getNextNeighbor(loc, w);
		}
	}

	cout<<"\b\b  "<<endl;
	delete []visited;
}


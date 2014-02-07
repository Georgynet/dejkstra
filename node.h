#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

class Node
{
	int number;				// порядковый номер
	int dist;				// расстояние до текущей вершины
	bool visited;			// метка посещенности (устанавливается после того как просмотрены все соседи ноды)
	Node *prevNode;			// предыдущая нода
	std::vector<Node*>neighbor;	// соседи ноды
	std::vector<int>nbdist;	// растояние до соседней ноды
public:
	Node(int number);
	void addNeighbor(Node &nb, int d);
	static int Node::getMinDist(std::vector<Node*>&vnode, int numNode);

	// get- и set- методы
	int getNumber(){ return number; }
	int getDist(){ return dist; }
	int getNbDist(int i){ return nbdist[i]; }
	bool getVisited(){ return visited; }
	std::vector<Node*> getNeighbor(){ return neighbor; }
	Node getPrevNode(){ return *prevNode; }

	void setNumber(int num){ number = num; }
	void setDist(int d){ dist = d; }
	void setVisited(bool visit){ visited = visit; }
	void setPrevNode(Node &pn){ prevNode = &pn; }
	void setNbDist(int i, int val){ nbdist[i] = val; }
};

#endif // NODE_H
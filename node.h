#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

class Node
{
	int number;				// ���������� �����
	int dist;				// ���������� �� ������� �������
	bool visited;			// ����� ������������ (��������������� ����� ���� ��� ����������� ��� ������ ����)
	Node *prevNode;			// ���������� ����
	std::vector<Node*>neighbor;	// ������ ����
	std::vector<int>nbdist;	// ��������� �� �������� ����
public:
	Node(int number);
	void addNeighbor(Node &nb, int d);
	static int Node::getMinDist(std::vector<Node*>&vnode, int numNode);

	// get- � set- ������
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
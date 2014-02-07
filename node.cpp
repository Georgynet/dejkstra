#include <iostream>
#include <vector>
#include "node.h"

Node::Node(int num)
	:number(num), dist(-1), visited(false)
{}

void Node::addNeighbor(Node &nb, int d)
{
	nb.setDist(-1);
	nbdist.push_back(d);
	neighbor.push_back(&nb);
}

int Node::getMinDist(std::vector<Node*>&vnode, int numNode)
{
	int imin = 0;
	for(int i=0;i < numNode;i++)
	{
		if(vnode[imin]->getVisited() == true || vnode[imin]->getDist() == -1)
			imin++;

		if(vnode[i]->getDist() <= vnode[imin]->getDist() && vnode[i]->getDist() != -1 && vnode[i]->getVisited() == false)
			imin=i;
	}
	return imin;
}
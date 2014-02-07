#include <xml/pugixml.hpp>
#include <xml/pugixml.cpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "node.h"

int main()
{
	setlocale(0, "");

	std::vector<Node*>vnode;

//:- чтение xml и создание карты соседей
	pugi::xml_document doc;
	doc.load_file("map.xml");

	// всего узлов
	pugi::xpath_node map = doc.select_single_node("/map");
	int numNode = atoi(map.node().attribute("nodes").value());
	int numStartNode = atoi(map.node().attribute("start").value())-1;
	int numFinishNode = atoi(map.node().attribute("finish").value())-1;

	// чтение xml
	for(int i=1;i <= numNode;i++)
	{
		Node *temp = new Node(i);
		vnode.push_back(temp);
	}
	
	pugi::xpath_node_set tools = doc.select_nodes("/map/node");

    // Формирование узлов с их соседями
    for (pugi::xpath_node_set::const_iterator it = tools.begin(); it != tools.end(); ++it)
    {
        pugi::xpath_node node = *it;
        int num = atoi(node.node().attribute("num").value());
		
		pugi::xpath_node_set neighbor = node.node().select_nodes("neighbor");
		for (pugi::xpath_node_set::const_iterator nit = neighbor.begin(); nit != neighbor.end(); ++nit)
		{
			pugi::xpath_node nb = *nit;
			vnode[num-1]->addNeighbor(*vnode[atoi(nb.node().child_value())-1], atoi(nb.node().attribute("dist").value()) );
		}
    }
//:~

//:- поиск кратчайшего пути
	vnode[numStartNode]->setDist(0);
	for(;;)
	{
		int i = Node::getMinDist(vnode, numNode);
		for(int j=0;j<vnode[i]->getNeighbor().size();j++)
		{
			if(vnode[i]->getNeighbor().at(j)->getDist() < 0 || vnode[i]->getNeighbor().at(j)->getDist() > (vnode[i]->getNbDist(j) + vnode[i]->getDist())){
				vnode[i]->getNeighbor().at(j)->setDist(vnode[i]->getNbDist(j) + vnode[i]->getDist());
				vnode[i]->getNeighbor().at(j)->setPrevNode(*vnode[i]);
			}
		}
		vnode[i]->setVisited(true);
		
		// путь найден, выход из цикла
		if(i == numFinishNode)
			break;
	}
//:~

	// дистанция до конечной точки и запись в файл
	std::ofstream out("path.xml");
	out << "<?xml version='1.0' encoding='UTF-8'>" << std::endl;
	out << "<path distantion='" << vnode[numFinishNode]->getDist() << "'>" << std::endl;

	int prevNumNode = vnode[numFinishNode]->getPrevNode().getNumber();
	out << "<node>" << vnode[numFinishNode]->getNumber() << "</node>" << std::endl;
	out << "<node>" << prevNumNode << "</node>" << std::endl;
	while((prevNumNode-1) != numStartNode)
	{
		prevNumNode = vnode[prevNumNode-1]->getPrevNode().getNumber();
		out << "<node>" << prevNumNode << "</node>" << std::endl;
	}
	out << "</path>";
	out.close();
	
	system("pause");
	return 0;
}
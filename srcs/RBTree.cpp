#include "RBTree.hpp"

int main()
{
	ft::RBTree< int, int > bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.insert(3);
	bst.insert(10);
	bst.deleteNode(25);
	bst.deleteNode(5);
	bst.deleteNode(17);
	//bst.deleteNode(18);
	bst.prettyPrint();
	std::cout << "rooot :D" << bst.getRoot()->data << std::endl;
	bst.freeNodes(bst.getRoot());
	return 0;
}
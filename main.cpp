#include "Red-Black-tree.hpp"

int main()
{
	RB	tree;

	tree.insertion(10);
	tree.insertion(15);
	tree.insertion(20);
	tree.insertion(5);
	tree.insertion(7);
	tree.insertion(8);
	tree.printInOrder();
	tree.deletion(15);
	std::cout << "##########################################################" <<std::endl;
	tree.printInOrder();
	// tree.insertion(25);
	// tree.insertion(15);
	// tree.insertion(65);
	// tree.insertion(5);
	// std::cout << tree.search(30)->key << std::endl;
}
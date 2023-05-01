#include "Red-Black-tree.hpp"

RB::~RB()
{
	delete nil;
}

RB::RB()
{
	nil = new(node);
	nil->color = false;
	nil->left = nil;
	nil->right = nil;
	nil->p = nil;
	nil->key = 0;
	root = nullptr;
}

node	*RB::newNode(int key)
{
	node	*neww = new(node);
	neww->color = true;
	neww->left = nil;
	neww->right = nil;
	neww->key = key;
	return (neww);
}
///////////////////////////////////------PRINT------/////////////////////////////////////////////

void	RB::print(node	*node)
{
	if (!node || node == nil)
		return;
	
	print(node->left);
	if (node == root)
		std::cout << "Root == [" << node->key << "]" << std::endl;
	else
		std::cout << "Node == [" << node->key << "]" << std::endl;
	if (node->color)
		std::cout << "Color == [RED]" << std::endl;
	else
		std::cout << "Color == [BLACK]" << std::endl;
	std::cout << "#----------------------------#" << std::endl;
	print(node->right);
}

void	RB::printInOrder()
{
	if (!root)
		std::cout << "empty tree!!!" << std::endl;
	else
		print(root);
}

///////////////////////////////////------SEARCH------////////////////////////////////////////////
node	*RB::search(int key)
{
	node *nde = root;
	if (!root)
		return (nullptr);
	if (nde->left == nil && nde->right == nil)
		return (root);
	node *n = findNode(nde, key);
	if (n == nil)
	{
		std::cout << "no such a node-";
		return (nullptr);
	}
	return (n);
}

node *RB::findNode(node *node, int key)
{
	if (key == node->key)
		return (node);
	if (node == nil)
		return (nil);
	if (key < node->key)
		return(findNode(node->left, key));
	else if(key > node->key)
		return (findNode(node->right, key));
	return (nil);
}
///////////////////////////////////------insertion-----//////////////////////////////////////////

void	RB::Lrotate(node *nde)
{
	node *y = nde->right;
	nde->right = y->left;
	if (y->left != nil)
		y->left->p = nde;
	y->p = nde->p;
	if (nde->p == nil)
		root = y;
	else if (nde == nde->p->left)
		nde->p->left = y;
	else
		nde->p->right = y;
	y->left = nde;
	nde->p = y; 
}

void	RB::Rrotate(node *nde)
{
	node *y = nde->left;
	nde->left = y->right;
	if (y->right != nil)
		y->right->p = nde;
	y->p = nde->p;
	if (nde->p == nil)
		root = y;
	else if (nde->p && nde == nde->p->right)
		nde->p->right = y;
	else if (nde->p)
		nde->p->left = y;
	y->right = nde;
	nde->p = y;
}

void	RB::checkProperities(node *nde, int key)
{
	node	*neww = search(key);
	if (neww != nil && neww != root)
	{
		int i = 0;
		while (neww != nil && neww->p != nil && neww->p->p && neww->p->color)
		{
			if (neww->p->p != nil && neww->p == neww->p->p->left)
			{
				if (neww->p->p->right->color)
				{
					neww->p->color = false;
					neww->p->p->color = true;
					neww->p->p->right->color = false;
					neww = neww->p->p;
				}
				else 
				{
					if (neww->p->p && neww == neww->p->right)
					{
						neww = neww->p;
						Lrotate(neww);
					}
					neww->p->color = false;
					neww->p->p->color = true;
					Rrotate(neww->p->p);
				}
			}
			else
			{
				if (neww->p->p->left->color)
				{
					neww->p->color = false;
					neww->p->p->color = true;
					neww->p->p->left->color = false;
					neww = neww->p->p;
				}
				else
				{ 
					if (neww->p->p && neww == neww->p->left)
					{
						neww = neww->p;
						Rrotate(neww);
					}
					neww->p->color = false;
					neww->p->p->color = true;
					Lrotate(neww->p->p);
				}
			}
			i++;
		}
	}
	root->color = false;
	nil->color = false;
}

node	*RB::insertNode(node *nde, int key)
{
	if (!nde)
	{
		root = newNode(key);
		root->p = nil;
		root->color = false;
	}
	else if (nde == nil)
	{
		nde = newNode(key);
		return (nde);
	}
	else if (nde->key > key)
	{
		nde->left = insertNode(nde->left, key);
		nde->left->p = nde;
	}
	else if (nde->key < key)
	{
		nde->right = insertNode(nde->right, key);
		nde->right->p = nde;
	}
	return (nde);
}


void	RB::insertion(int key)
{
	node	*node = root;
	insertNode(node, key);
	checkProperities(root, key);
}

///////////////////////////////////------deletion-----//////////////////////////////////////////

void	RB::transPlant(node *n, node *v)
{
	if (n->p == nil)
		v = root;
	else if (n == n->p->left)
		n->p->left = v;
	else
		n->p->right = v;
	v->p = n->p;
}

node	*RB::minimum(node *n)
{
	node *s = n;
	while (s->left != nil)
		s = s->left;
	return (s);
}

void	RB::deletion(int key)
{
	node	*n = search(key);
	if (n == nil)
	{
		std::cout << "there is no such a node to delete!!!" << std::endl;
		return ;
	}
	node	*x;
	node	*y;
	y = n;
	bool	oy = y->color;
	if (n->left == nil)
	{
		x = n->right;
		transPlant(n, n->right);
	}
	else if (n->right == nil)
	{
		x = n->left;
		transPlant(n, n->left);
	}
	else
	{
		y = minimum(n->right);
		oy = y->color;
		x = y->right;
		if (y->p == n)
			x->p = y;
		else
		{
			transPlant(y, y->right);
			y->right = n->right;
			y->right->p = y;	
		}
		transPlant(n, y);
		y->left = n->left;
		y->left->p = y;
		y->color = n->color;
	}
	// if (oy == false)
	// 	delFix();
}
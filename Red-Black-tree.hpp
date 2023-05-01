#pragma once

#include <iostream>

struct node
{
	bool	color;
	int		key;
	node	*p;
	node	*left;
	node	*right;
};

class	RB
{
	node	*root;
	node	*nil;
	node	*newNode(int key);
	node 	*findNode(node *node, int key);
	node	*insertNode(node *node, int key);
	void	print(node	*node);
	void	checkProperities(node *node, int key);
	void	Lrotate(node *node);
	void	Rrotate(node *nde);
	void	transPlant(node *n, node *v);
	node	*minimum(node *n);

public:
	RB();
	~RB();
	node	*search(int	key);
	void	insertion(int key);
	void	printInOrder();
	void	deletion(int key);
};

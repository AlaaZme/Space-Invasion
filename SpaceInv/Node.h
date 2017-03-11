#pragma once
class Node
{
public:
	Node::Node();
	Node(Node*);
	~Node();

	int speed;
	int x;
	int y;
	int kind;
	int shoot;
	bool Alive;
};


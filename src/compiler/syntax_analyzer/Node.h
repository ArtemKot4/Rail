#ifndef NODE_H
#define NODE_H

struct Node {
public:
	int line;
	int column;
	Node(int line, int column) : line(line), column(column) {};
};

#endif
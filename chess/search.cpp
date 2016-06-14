#include <ctime>

#include "search.h"
#include "node.h"

void 
Search::recurse(Node& n,int d)
{
	std::vector<Node> nodes;
	std::vector<std::string> moves = n.gen_moves();
	if (d > 0) {
		for (size_t x = 0; x < moves.size(); ++x) {
			nodes.push_back(Node(n));
			this->recurse(nodes.back(), d - 1);
		}
	}
	else if (d == 0) {

	}
}

void 
Search::tcurse(Node& n, int d) {
	clock_t t = clock();
	this->recurse(n,d);
	std::cout << "time: " << (clock() - t)/1000.0 << std::endl;
}
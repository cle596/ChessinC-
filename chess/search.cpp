#include "search.h"

void Search::recurse(Node* n)
{
	std::vector<Node> nodes;
	std::vector<std::string> moves = n->gen_moves();
	for (size_t x = 0; x < moves.size(); ++x) {
		//
	}
}

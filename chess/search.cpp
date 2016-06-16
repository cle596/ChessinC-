#include <ctime>

#include "search.h"
#include "node.h"

int
Search::recurse(Node& n,int d,int max,int min)
{
	n.gen_moves();
	if (d > 0) {
		for (size_t x = 0; x < n.moves.size(); ++x) {
			Node nn = Node(n);
			nn.update_board(n.moves.at(x));
			nn.flips();
			nn.nscore = recurse(nn, d - 1, max, min);
			if (nn.nscore<max || //not equal seems better
				nn.nscore>min) {
				break;
			}
			else if (nn.nscore > max &&
				n.turn.compare("white")==0) {
				max = nn.nscore;
			}
			else if (nn.nscore < min &&
				n.turn.compare("black")==0) {
				min = nn.nscore;
				if (d == depth) {
					bmove.assign(n.moves.at(x));
				}
			}
		}
		if (n.turn.compare("white")==0) {
			return max;
		}
		else{
			return min;
		}
	}
	else if (d == 0) {
		return n.score(); 
	}
}

void 
Search::tcurse(Node& n) {
	int max = depth;
	depth = 1;
	int inf = 100000;
	clock_t t = clock();
	while (depth <= max) {
		std::cout << depth << std::endl;
		recurse(n, depth, -inf, inf);
		std::cout << bmove << std::endl;
		depth += 1;
	}
	std::cout << "time: " << (clock() - t)/1000.0 << std::endl;
}


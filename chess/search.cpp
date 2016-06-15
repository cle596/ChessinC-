#include <ctime>

#include "search.h"
#include "node.h"

int
Search::recurse(Node& n,int d,int max,int min)
{
	int score;
	n.gen_moves();
	if (d > 0) {
		for (size_t x = 0; x < n.moves.size(); ++x) {
			Node nn = Node(n);
			nn.flip_turn();
			nn.flip_foe();
			nn.update_board(n.moves.at(x));
			//nn.print();
			//std::cout << nn.score() << std::endl;
			score = this->recurse(nn, d - 1, max, min);
			if (score<max || //not equal seems better
				score>min) {
				break;
			}
			else if (score > max &&
				n.turn.compare("white")==0) {
				max = score;
				if (d == 3) {
					this->bmove.assign(n.moves.at(x));
				}
			}
			else if (score < min &&
				n.turn.compare("black")==0) {
				min = score;
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
Search::tcurse(Node& n, int d) {
	int inf = 100000;
	clock_t t = clock();
	this->recurse(n,d,-inf,inf);
	std::cout << "time: " << (clock() - t)/1000.0 << std::endl;
}
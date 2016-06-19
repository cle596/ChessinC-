#include <ctime>
#include <algorithm>

#include "search.h"
#include "node.h"

int
Search::recurse(Node& n,int d,int max,int min)
{
	n.gen_moves();
	if (int(history.size()) > depth - d) {
		sort(n.moves, history.at(depth - d));
	}
	if (d > 0) {
		for (size_t x = 0; x < n.moves.size(); ++x) {
			Node nn = Node(n);
			nn.update_board(n.moves.at(x));
			nn.flips();
			nn.nscore = recurse(nn, d - 1, max, min);
			if (nn.nscore >= min && n.turn == "white") {
				return min;
			}
			else if (nn.nscore <= max && n.turn == "black") {
				return max;
			}
			else if (nn.nscore > max &&
				n.turn=="white") {
				max = nn.nscore;
			}
			else if (nn.nscore < min &&
				n.turn=="black") {
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
	else /*if (d == 0)*/ {
		n.nscore = n.score();
		return n.nscore; 
	}
}

int Search::guess(Node& n,int g) {
	//int guess = 0;
	int inf = 100000;
	int upper = inf;
	int lower = -inf;
	int b = 0;
	while (lower < upper) {
		b = std::max(g, lower + 1);
		g = recurse(n, depth, b - 1, b);
		std::cout << "guess: " << g
			<< " upper: " << upper
			<< " lower: " << lower
			<< std::endl;
		if (g < b) {
			upper = g;
		}
		else {
			lower = g;
		}
	}
	return g;
}

void 
Search::tcurse(Node& n) {
	int max = depth;
	std::cout << "max: " << max << std::endl;
	depth = 1;
	int inf = 100000;
	int g = 0;
	while (depth <= max) {
		//std::cout << depth << std::endl;
		//std::cout << guess(n) << std::endl;
		//g = guess(n,g);
		//std::cout << g << std::endl;
		clock_t t = clock();
		std::cout << "ab score: " << recurse(n, depth, -inf, inf) << std::endl;
		std::cout << "time: " << (clock() - t) / 1000.0 << std::endl;
		std::cout << "best move: " << Game::pos_to_move(bmove) << std::endl;
		if (int(history.size()) >= depth) {
			history.at(depth-1) = bmove;
		}
		else {
			history.push_back(bmove);
		}
		depth += 1;
	}
	if (depth > max) {
		depth -= 1;
	}
}

void
Search::sort(std::vector<std::string>& moves,std::string move) {
	for (size_t x = 0; x < moves.size(); ++x) {
		if (moves.at(x) == move) {
			moves.at(x) = moves.at(0);
			moves.at(0) = move;
			return;
		}
	}
}
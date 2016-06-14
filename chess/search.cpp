#include <ctime>

#include "search.h"
#include "node.h"

int
Search::recurse(Node& n,int d,int max,int min)
{
	int score;
	std::vector<Node> nodes;
	std::vector<std::string> moves = n.gen_moves();
	if (d > 0) {
		for (size_t x = 0; x < moves.size(); ++x) {
			Node nn = Node(n);
			if (n.turn.compare("white") == 0) {
				nn.turn = "black";
			}
			else {
				n.turn = "white";
			}
			nn.update_board(moves.at(x));
			nodes.push_back(nn);
			score = this->recurse(nodes.back(), d - 1, max, min);
			if (score<=max ||
				score>=min) {
				break;
			}
			else if (score > max &&
				nodes.back().turn.compare("white")==0) {
				max = score;
				//to be removed
				if (d == 2) {
					this->bmove.assign(moves.at(x));
				}
			}
			else if (score < min &&
				nodes.back().turn.compare("black")==0) {
				min = score;
			}
		}
		if (nodes.back().turn.compare("white")==0) {
			return max;
		}
		//else if(nodes.back().turn.compare("black")){
		else{
			return min;
		}
	}
	//else if (d == 0) {
	else{	
		std::cout << n.score() << std::endl;
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
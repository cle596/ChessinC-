#include <ctime>

#include "search.h"
#include "node.h"

int
Search::recurse(Node& n,int d,int max,int min)
{
	//std::cout << n.turn << std::endl;
	//std::cout << "recurse called" << std::endl;
	int score;
	std::vector<Node> nodes;
	std::vector<std::string> moves = n.gen_moves();
	//std::cout << "moves gend: " << moves.size() << std::endl;
	if (d > 0) {
		//std::cout << moves.size() << std::endl;
		for (size_t x = 0; x < moves.size(); ++x) {
			//std::cout << moves.at(x) << std::endl;
			Node nn = Node(n);
			nn.update_board(moves.at(x));
			//std::cout << "move: " << x << std::endl;
			//nn.print();
			//nodes.push_back(nn);
			//nodes.back().print();
			score = this->recurse(nn, d - 1, max, min);
			if (score<max ||
				score>min) {
				//std::cout << "break score: " << score << std::endl;
				break;
			}
			else if (score > max &&
				n.turn.compare("white")==0) {
				max = score;
				//to be removed
				if (d == 2) {
					this->bmove.assign(moves.at(x));
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
		//else if(nodes.back().turn.compare("black")){
		else{
			return min;
		}
	}
	else if (d == 0) {
	//else{	
		//std::cout << "node visited" << std::endl;
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
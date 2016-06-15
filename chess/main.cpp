#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <ctime>

#include "node.h"
#include "game.h"
#include "search.h"

int main() {

	Game g = Game();
	g.init();

	Search s = Search();

	while (true) {
		g.root.print();
		g.root.gen_moves();
		for (size_t x = 0; x < g.root.moves.size(); ++x) {
			std::cout << g.root.moves.at(x) << std::endl;
		}
		if (g.root.turn.compare("white")==0) {
			g.take_input("");
			g.process_input();
		}
		else {
			//s.tcurse(g.root, 3);
			//std::cout << s.bmove << std::endl;
			g.take_input("");
			g.process_input();
		}
	}

 	return 0;
}
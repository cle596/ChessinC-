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
	s.depth = 3;

	while (true) {
		g.root.print();
		std::cout << g.root.score() << std::endl;
		if (g.root.turn.compare("white")==0) {
			g.take_input("");
			g.process_input();
		}
		else {
			s.tcurse(g.root);
			std::cout << s.bmove << std::endl;
			g.take_input("");
			g.process_input();
		}
	}

 	return 0;
}
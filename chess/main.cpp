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
		std::cout << g.root.castle[0] << g.root.castle[1] << g.root.castle[2] << g.root.castle[3] << std::endl;
		g.root.print();
		if (g.root.turn.compare("white")==0) {
			g.take_input("");
			g.process_input();
		}
		else {
			s.tcurse(g.root, 2);
			std::cout << s.bmove << std::endl;
			g.take_input("");
			g.process_input();
		}
	}

 	return 0;
}
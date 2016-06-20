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
	s.gen_keymap();

	while (true) {
		g.root.print();
		if (g.root.turn.compare("white")==0) {
			g.take_input("");
			g.process_input();
		}
		else {
			s.tcurse(g.root);
			g.take_input("");
			while (!g.process_input()) {
				g.take_input("");
			}
		}
	}

 	return 0;
}
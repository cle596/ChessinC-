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

using namespace std;

int main() {

	Game g = Game();
	g.init();

	Search s = Search();
	s.depth = 3;
	s.gen_keymap();

	while (true) {
		g.root.print();
		if (g.root.turn=="white") {
			g.take_input("");
			g.process_input();
		}
		else {
			s.bmove = "";
			s.tcurse(g.root);
			if (s.bmove != "") {
				cout << Game::pos_to_move(s.bmove) << endl;
			}
			g.root.moves.clear();
			g.take_input("");
			while (!g.process_input()) {
				g.take_input("");
			}
		}
	}

 	return 0;
}
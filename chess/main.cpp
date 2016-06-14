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
	s.tcurse(g.root, 2);
	std::cout << s.bmove << std::endl;

	while (true) {		
		std::cout << "score: " << g.root.score() << std::endl;
		std::cout << "en_passant: " << g.root.en_passant << std::endl;
		g.root.print();
		g.take_input("");
		g.process_input();
	}

 	return 0;
}
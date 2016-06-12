#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "chess.h"
#include "gen.h"
#include "node.h"
#include "game.h"

int main() {

	Game g = Game();
	g.init();

	while (true) {	
		g.root.print();
		g.take_input();
		g.process_input();
	}

 	return 0;
}
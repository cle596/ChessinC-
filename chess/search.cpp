#include <ctime>
#include <algorithm>
#include <map>
#include <bitset>

#include "search.h"
#include "node.h"
#include "value.h"

int
Search::ab(Node& n,int alpha,int beta,int d)
{
	int g, a, b;
	if (db.find(hash(n)) != db.end()) {
		Value v = db[hash(n)];
		//std::cout << v.a << " " << v.b << std::endl;
		if (v.a >= beta) return v.a;
		if (v.b <= alpha) return v.b;
		alpha = std::max(alpha, v.a);
		beta = std::min(beta, v.b);
	}
	if (d == 0) {
		g = n.score();
	}
	else if (n.turn == "white") {
		g = -inf; 
		a = alpha;
		n.gen_moves();
		int c = 0;
		while (c < int(n.moves.size()) && g < beta) {
			Node nn = Node(n);
			nn.update_board(n.moves.at(c)); nn.flips();
			g = std::max(g, ab(nn, a, beta, d - 1));
			a = std::max(a, g);
			c += 1;
		}
	}
	else {
		g = inf; 
		b = beta;
		n.gen_moves();
		int c = 0;
		while (c < int(n.moves.size()) && g > alpha) {
			Node nn = Node(n);
			nn.update_board(n.moves.at(c)); nn.flips();
			g = std::min(g, ab(nn, alpha, b, d - 1));
			//std::cout << "g: " << g << " alpha: " << alpha << std::endl;
			if (d == depth &&
				g < b) {
				bmove = n.moves.at(c);
				b = g;
			}
			else {
				b = std::min(b, g);
			}
			c += 1;
		}
	}
	if (g <= alpha) {
		n.b = g;
		if (db.find(hash(n)) == db.end()) {
			db[hash(n)] = Value(-100000, n.b);
		}
		else {
			db[hash(n)].b = n.b;
		}
	}
	if (g > alpha && g < beta) {
		n.a = g;
		n.b = g;
		if (db.find(hash(n)) == db.end()) {
			db[hash(n)] = Value(n.a, n.b);
		}
		else {
			db[hash(n)].a = n.a;
			db[hash(n)].b = n.b;
		}
	}
	if (g >= beta) {
		n.a = g;
		if (db.find(hash(n)) == db.end()) {
			db[hash(n)] = Value(n.a, 100000);
		}
		else {
			db[hash(n)].a = n.a;
		}
	}
	return g;
}

int Search::guess(Node& n,int g) {
	//int guess = 0;
	int inf = 100000;
	int upper = inf;
	int lower = -inf;
	int b = 0;
	while (lower < upper) {
		b = std::max(g, lower + 1);
		g = ab(n, b - 1, b,depth);
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
	depth = 1;
	int inf = 100000;
	int g = 0;
	history.clear();
	while (depth <= max) {
		clock_t t = clock();
		std::cout << "depth: " << depth << std::endl;
		//std::cout << "ab score: " << ab(n,-inf, inf,depth) << std::endl;
		g = guess(n,g);
		std::cout << "guess: " << g << std::endl;
		std::cout << "best move: " << Game::pos_to_move(bmove) << std::endl;
		/*
		std::cout << "history: " << std::endl;
		for (size_t x = 0; x < history.size(); ++x) {
			std::cout << Game::pos_to_move(history.at(x)) << std::endl;
		}
		*/
		std::cout << "time: " << (clock() - t) / 1000.0 << std::endl << std::endl;
		/*
		if (int(history.size()) >= depth) {
			history.at(depth-1) = bmove;
		}
		else {
			history.push_back(bmove);
		}
		*/
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

void 
Search::gen_keymap() {
	int z = 0;
	for (int x = 0; x < 120; ++x) {
		P_keymap[x] = x;
		N_keymap[x] = x + 120;
		B_keymap[x] = x + 120*2;
		R_keymap[x] = x + 120 * 3;
		Q_keymap[x] = x + 120 * 4;
		K_keymap[x] = x + 120 * 5;
		p_keymap[x] = x + 120 * 6;
		n_keymap[x] = x + 120 * 7;
		b_keymap[x] = x + 120 * 8;
		r_keymap[x] = x + 120 * 9;
		q_keymap[x] = x + 120 * 10;
		k_keymap[x] = x + 120 * 11;
		//z += 1;
	}
	//std::cout << std::bitset< 16 >(k_keymap[119]).to_string << std::endl;
}

std::string
Search::hash(Node& n) {
	int hash = 0;
	for (size_t x = 0; x < n.board.length(); ++x) {
		if (n.board.at(x) == 'P') {
			hash |= P_keymap[x];
		}
		else if (n.board.at(x) == 'p') {
			hash |= p_keymap[x];
		}
		else if (n.board.at(x) == 'N') {
			hash |= N_keymap[x];
		}
		else if (n.board.at(x) == 'n') {
			hash |= n_keymap[x];
		}
		else if (n.board.at(x) == 'B') {
			hash |= B_keymap[x];
		}
		else if (n.board.at(x) == 'b') {
			hash |= b_keymap[x];
		}
		else if (n.board.at(x) == 'R') {
			hash |= R_keymap[x];
		}
		else if (n.board.at(x) == 'r') {
			hash |= r_keymap[x];
		}
		else if (n.board.at(x) == 'Q') {
			hash |= Q_keymap[x];
		}
		else if (n.board.at(x) == 'q') {
			hash |= q_keymap[x];
		}
		else if (n.board.at(x) == 'K') {
			hash |= K_keymap[x];
		}
		else if (n.board.at(x) == 'k') {
			hash |= k_keymap[x];
		}
		std::cout << "piece: " << n.board.at(x) << " hash: " << hash << std::endl;
	}
	return std::bitset<16>(hash).to_string();
}
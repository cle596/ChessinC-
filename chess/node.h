#pragma once

#include <string>
#include <vector>

class Node {

public:

	std::string board =
		"         \n"
		"         \n"
		" rnbqkbnr\n"
		" pppppppp\n"
		" ........\n"
		" ........\n"
		" ........\n"
		" ........\n"
		" PPPPPPPP\n"
		" RNBQKBNR\n"
		"         \n"
		"         \n";
	std::string turn;
	bool castle[4]; //wk,wq,bk,bq
	int en_passant;

	int P, N, B, R, Q, K, k;
	const int pawn_pst[120] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0, 50, 50, 50, 50, 50, 50, 50, 50,  0,
		0, 10, 10, 20, 30, 30, 20, 10, 10,  0,
		0,  5,  5, 10, 25, 25, 10,  5,  5,  0,
		0,  0,  0,  0, 20, 20,  0,  0,  0,  0,
		0,  5, -5,-10,  0,  0,-10, -5,  5,  0,
		0,  5, 10, 10,-20,-20, 10, 10,  5,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	};
	const int knight_pst[120] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,-50,-40,-30,-30,-30,-30,-40,-50,  0,
		0,-40,-20,  0,  0,  0,  0,-20,-40,  0,
		0,-30,  0, 10, 15, 15, 10,  0,-30,  0,
		0,-30,  5, 15, 20, 20, 15,  5,-30,  0,
		0,-30,  0, 15, 20, 20, 15,  0,-30,  0,
		0,-30,  5, 10, 15, 15, 10,  5,-30,  0,
		0,-40,-20,  0,  5,  5,  0,-20,-40,  0,
		0,-50,-40,-30,-30,-30,-30,-40,-50,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	};
	const int bishop_pst[120] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,-20,-10,-10,-10,-10,-10,-10,-20,  0,
		0,-10,  0,  0,  0,  0,  0,  0,-10,  0,
		0,-10,  0,  5, 10, 10,  5,  0,-10,  0,
		0,-10,  5,  5, 10, 10,  5,  5,-10,  0,
		0,-10,  0, 10, 10, 10, 10,  0,-10,  0,
		0,-10, 10, 10, 10, 10, 10, 10,-10,  0,
		0,-10,  5,  0,  0,  0,  0,  5,-10,  0,
		0,-20,-10,-10,-10,-10,-10,-10,-20,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	};
	const int rook_pst[120] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  5, 10, 10, 10, 10, 10, 10,  5,  0,
		0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
		0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
		0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
		0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
		0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
		0,  0,  0,  0,  5,  5,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	};
	const int queen_pst[120] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,-20,-10,-10, -5, -5,-10,-10,-20,  0,
		0,-10,  0,  0,  0,  0,  0,  0,-10,  0,
		0,-10,  0,  5,  5,  5,  5,  0,-10,  0,
		0, -5,  0,  5,  5,  5,  5,  0, -5,  0,
		0,  0,  0,  5,  5,  5,  5,  0, -5,  0,
		0,-10,  5,  5,  5,  5,  5,  0,-10,  0,
		0,-10,  0,  5,  0,  0,  0,  0,-10,  0,
		0,-20,-10,-10, -5, -5,-10,-10,-20,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	};
	const int king_pst[120] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
		0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
		0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
		0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
		0,-20,-30,-30,-40,-40,-30,-30,-20,  0,
		0,-10,-20,-20,-20,-20,-20,-20,-10,  0,
		0, 20, 20,  0,  0,  0,  0, 20, 20,  0,
		0, 20, 30, 10,  0,  0, 10, 30, 20,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	};

	std::vector<std::string> moves;

	void print();
	void pawn(int);
	void knight(int);
	void bishop(int);
	void rook(int);
	void queen(int);
	void king(int);
	std::vector<std::string> gen_moves();

	int score();

};
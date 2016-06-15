#pragma once

#include <string>
#include <vector>

class Node {

public:

	static const int up = -10;
	static const int dn = 10;
	static const int lt = -1;
	static const int rt = 1;

	static const int Nmoves[];
	static const int Bmoves[];
	static const int Rmoves[];
	static const int Kmoves[];

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
	std::string castle_input[4];
	int en_passant;

	static const int P = 100;
	static const int N = 320;
	static const int B = 330;
	static const int R = 500;
	static const int Q = 900;
	static const int K = 20000;

	static const int pawn_pst[120];
	static const int knight_pst[120];
	static const int bishop_pst[120];
	static const int rook_pst[120];
	static const int queen_pst[120];
	static const int king_pst[120];

	int npawn_pst[120];
	int nknight_pst[120];
	int nbishop_pst[120];
	int nrook_pst[120];
	int nqueen_pst[120];
	int nking_pst[120];

	char foe[6] = { 'p','n','b','r','q','k' };
	int dub[8] = { 81,82,83,84,85,86,87,88 };
	int bdub[8] = {31,32,33,34,35,36,37,38};
	int wdub[8] = { 81,82,83,84,85,86,87,88 };

	std::vector<std::string> moves;

	Node();
	Node(const Node& n);

	void update_board(std::string);

	void print();
	void pawn(int);
	void knight(int);
	void bishop(int);
	void rook(int);
	void queen(int);
	void king(int);
	std::vector<std::string> gen_moves();

	int* rotate_pst(const int*,int*);
	int score();
	void flip_foe();
	void flip_turn();
	void flip_dub();

	void castle_reset();
};


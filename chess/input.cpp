#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

std::string 
add_space_to_board(std::string board) {
	std::string formatted_board;
	for (size_t x = 0; x < board.length(); ++x) {
		formatted_board += board.at(x);
		if (board.at(x) != '\n') {
			formatted_board.append(" ");
		}
	}
	return formatted_board;
}

std::string 
move_to_pos(std::string move) {
	std::string pos;
	std::map<char, int> cols;
	std::map<char, int> rows;
	for (int x = 0; x < 8; ++x) {
		cols[97 + x] = 1 + x;
	}
	for (int x = 0; x < 8; ++x) {
		rows[49 + x] = 90 - 10 * x;
	}
	for (int x = 0; x < 3; x += 2) {
		pos.append(std::to_string(cols[move.at(x)] + rows[move.at(x + 1)]));
	}
	return pos;
}

std::string 
pos_to_move(std::string pos) {
	std::string move;
	std::map<int, char> cols;
	std::map<int, char> rows;
	for (int x = 0; x < 8; ++x) {
		cols[ 1 + x ] = 97 + x;
	}
	for (int x = 0; x < 8; ++x) {
		rows[9 - x] = 49 + x;
	}
	int posi1 = std::stoi(pos.substr(0, 2), nullptr);
	int posi2 = std::stoi(pos.substr(2, 2), nullptr);
	move += cols.at(posi1 - (posi1 / 10) * 10);
	move += rows.at(posi1 / 10);
	move += cols.at(posi2 - (posi2 / 10) * 10);
	move += rows.at(posi2 / 10);
	return move;
}

std::vector<std::string>
translate_moves(std::vector<std::string> moves) {
	std::vector<std::string> translated_moves;
	for (size_t x = 0; x < moves.size(); ++x) {
		translated_moves.push_back(pos_to_move(moves.at(x)));
	}
	return translated_moves;
}

std::string 
new_board(std::string oboard,std::string pos) {
	int from = std::stoi(pos.substr(0, 2), nullptr);
	int to = std::stoi(pos.substr(2, 2), nullptr);
	oboard.replace(to, 1, std::string(1,oboard.at(from)));
	oboard.replace(from, 1, ".");
	return oboard;
}
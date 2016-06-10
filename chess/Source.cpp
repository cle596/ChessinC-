#include <iostream>
#include <string>
#include <map>
#include <vector>

std::string add_space_to_board(std::string board) {
	std::string formatted_board;
	for (int x = 0; x < board.length(); ++x) {
		formatted_board += board.at(x);
		if (board.at(x) != '\n') {
			formatted_board.append(" ");
		}
	}
	return formatted_board;
}

std::string make_board_unicode(std::string board) {
	std::map<char, char> conversions;
	char alphabet[] = {
		'K', 'Q', 'R', 'B', 'N', 'P',
		'k', 'q', 'r', 'b', 'n', 'p'
	};
	char unicode[] = {
		'\u2654','\u2655','\u2656','\u2657','\u2658','\u2659',
		'\u266A','\u266B','\u266C','\u266D','\u266E','\u266F'
	};
	for (int x = 0; x < 12; ++x) {
		conversions[alphabet[x]] = unicode[x];
	}
	/*
	for (int x = 0; x < board.length(); ++x) {
		if (board.at(x) == )
	}
	*/
	return "shit";//weff
}

int main() {
	std::cout << "time to play chess cocksucka!\n";
	std::string input;
	std::string board =
		"           \n"
		"           \n"
		"  rnbqkbnr \n"
		"  pppppppp \n"
		"  ........ \n"
		"  ........ \n"
		"  ........ \n"
		"  ........ \n"
		"  PPPPPPPP \n"
		"  RNBQKBNR \n"
		"           \n"
		"           \n";
	std::cout << add_space_to_board(board) << std::endl;
	return 0;
}
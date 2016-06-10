#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::string add_space_to_board(std::string board) {
	std::string formatted_board;
	for (size_t x = 0; x < board.length(); ++x) {
		formatted_board += board.at(x);
		if (board.at(x) != '\n') {
			formatted_board.append(" ");
		}
	}
	return formatted_board;
}

std::string make_board_unicode(std::string board) {
	std::string unicode_board;
	std::map<char, std::string> conversions;
	char alphabet[] = {
		'K', 'Q', 'R', 'B', 'N', 'P',
		'k', 'q', 'r', 'b', 'n', 'p'
	};
	std::string unicode[] = {
		u8"\u2654",u8"\u2655",u8"\u2656",u8"\u2657",u8"\u2658",u8"\u2659",
		u8"\u266A",u8"\u266B",u8"\u266C",u8"\u266D",u8"\u266E",u8"\u266F"
	};
	for (int x = 0; x < 12; ++x) {
		conversions[alphabet[x]] = unicode[x];
	}
	for (size_t x = 0; x < board.length(); ++x) {
		if (std::find(std::begin(alphabet), std::end(alphabet), board.at(x)) != std::end(alphabet)) {
			unicode_board.append(conversions.at(board.at(x)));
		}
		else {
			unicode_board += board.at(x);
		}
	}
	return unicode_board;
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
	std::cout << u8"\u2654" << std::endl;
	std::cout << make_board_unicode(add_space_to_board(board)) << std::endl;
	return 0;
}
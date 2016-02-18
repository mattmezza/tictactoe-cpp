#include <iostream>
#include <cstdio>
#include <string>

void reset_field(int **field);
void print_field(int **field);
void print_points(int p1, int p2);
int check_field(int **field);
bool check_move(int player, std::string move, int **field);
void apply_move(int player, std::string move, int **field);
int ctoi(int c) {
	return c - '0';
}
char *itoa(long i, char* s, int dummy_radix) {
    sprintf(s, "%ld", i);
    return s;
}
void cls() {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
	int **field;
	field = new int *[3];
	for (int i = 0; i < 3; i++) {
		field[i] = new int[3];
	}
	int p1=0,p2=0;
	
	std::string new_ = "y";
	while(new_ == "Y"||new_=="y") {
		reset_field(field);
		int turn = 1;
		while(check_field(field)==0) {
			std::string move = "";
			print_points(p1,p2);
			print_field(field);
			std::cout << "\nPlayer " << (turn==1?"1":"2") << ", you move:\n";
			std::cin >> move;
			while(!check_move(turn, move, field)) {
				std::cin >> move;
			}
			apply_move(turn, move, field);
			turn==1 ? turn=2 : turn=1;
		}
		int res = check_field(field);
		std::string msg;
		if(res==1) {
			p1++;
			msg = "Player 1 won... Play again? [y/n]\n";
		} else if (res == 2) {
			p2++;
			msg = "Player 2 won... Play again? [y/n]\n";
		} else {
			msg = "Draw... Play again? [y/n]\n";
		}
		print_points(p1,p2);
		print_field(field);
		std::cout << msg;
		std::cin >> new_;
	}
	cls();
	std::cout << (p1==p2?"Nobody":(p1>p2?"Player 1":"Player 2")) << " won this game ;-)\n\nThank you for playing!\n\nType bye to exit...";
	std::string here = "bye";
	std::cin >> here;
}

void reset_field(int **field) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			field[i][j] = 0;
		}
	}
}

int check_field(int **f) {
	// check rows
	for (int i = 0; i < 3; i++) {
		if(f[i][0]==f[i][1] && f[i][1]==f[i][2] && f[i][1]!=0)
			return f[i][0];
	}
	// check cols
	for (int i = 0; i < 3; i++) {
		if(f[0][i]==f[1][i] && f[1][i]==f[2][i] && f[1][i]!=0)
			return f[0][i];
	}
	// check diag
	if(f[0][0]==f[1][1] && f[1][1]==f[2][2] && f[1][1]!= 0)
		return f[0][0];
	if(f[0][2]==f[1][1] && f[1][1]==f[2][0] && f[1][1]!= 0)
		return f[1][1];
	// check for draw
	int empty = 0;
	for (int i = 0; i < 3; i++) { 
		for (int j = 0; j < 3; j++) {
			if(f[i][j]==0)
				empty++;
		}
	}
	if(empty==0)
		return 3;
	return 0;
}

void print_points(int p1, int p2) {
	cls();
	std::string to_print = "Player 1   Player 2\n    ";
	char buffer[3];
	itoa(p1, buffer, 10);
	to_print += buffer;
	to_print += "          ";
	itoa(p2, buffer, 10);
	to_print += buffer;
	std::cout << to_print << "\n";
}

void print_field(int **field) {
	std::string to_print = "\n  0 1 2\n";
	for (int i = 0; i < 3; i++) {
		char buffer[3];
		itoa(i, buffer, 10);
		to_print += buffer;
		to_print += " ";
		for (int j = 0; j < 3; j++) {
			if(field[i][j]==1) {
				to_print += "X";
			} else if (field[i][j]==2) {
				to_print += "O";
			} else {
				to_print += " ";
			}
			if(j<2)
				to_print += "|";
			else
				to_print += "\n";
		}
		if(i<2)
			to_print += "  -----\n";
		else
			to_print += "\n";
	}
	std::cout << to_print;
}

bool check_move(int p, std::string move, int **f) {
	if(move.size()!=2) {
		std::cout << "Your move "<<move<<" is not correct, please re-enter your move.\n";
		return false;
	}
	if(ctoi(move.at(0))>2) {
		std::cout << "Your move "<<move<<" is not correct, please re-enter your move.\n";
		return false;
	}
	if(ctoi(move.at(1))>2) {
		std::cout << "Your move "<<move<<" is not correct, please re-enter your move.\n";
		return false;
	}
	int i = ctoi(move.at(0));
	int j = ctoi(move.at(1));
	if(f[i][j]!=0) {
		std::cout << "Cell at "<<move<<" is not available, please play a different move.\n";
		return false;
	}
	std::cout << "Your move is "<<move<<"\n";
	return true;
}
void apply_move(int p, std::string move, int** f) {
	int i = ctoi(move.at(0));
	int j = ctoi(move.at(1));
	f[i][j] = p;
}

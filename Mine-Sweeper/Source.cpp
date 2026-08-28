#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include "helper.h"

using namespace std;
#define l printf("\n")

int main(){
	srand(time(NULL));
	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<vector<char>> shown(1, vector<char>(1));
	vector<vector<char>> hidden(1, vector<char>(1));
	int rows, columns, mines,goal;
	int x;
	int y;
	int gamestate = 0;
	char repeat = 'Y';
	char input;

	while (repeat == 'Y' || repeat == 'y') {
		gamestate = 0;

		cout << "------------------------------"; l;
		cout << "Choose your prefered game size"; l;
		cout << "------------------------------"; l;
		cout << "1-Easy(9x9 10 mines)"; l;
		cout << "2-Medium(16x16 40 mines)"; l;
		cout << "3-Hard(16x30 90 mines)"; l;
		cout << "4-Extreme(24x30 160 mines)"; l;
		cout << "5-Custom"; l;
		cin >> rows;
		switch (rows) {
		case 1:
			rows = 9;
			columns = 9;
			mines = 10;
		break;

		case 2:
			rows = 16;
			columns = 16;
			mines = 40;
		break;

		case 3:
			rows = 16;
			columns = 30;
			mines = 90;
		break;

		case 4:
			rows = 24;
			columns = 30;
			mines = 160;
		break;

		
		case 5:
			cin >> rows;
			cin >> columns;
			cin >> mines;
		break;

		default:
			cout << "Please choose a valid option!!";
			continue;
		}

		resizeboard(shown, rows, columns);
		resizeboard(hidden, rows, columns);
		reset(shown, hidden, mines);
		setup(hidden);
		goal = (rows * columns) - mines;
		x = columns / 2;
		y = rows / 2;
		

		while (gamestate == 0) {
			system("cls");
			printboard(shown, colour, &x, &y);
			cout << goal << " Plots left,";
			cout << " Move with wasd, and when your selected plot is highlighted, use q to flag or e to dig" << endl;
			input = _getch();
			
			switch (input) {

			case'q':
				if (shown[y][x] != 'T') {
					shown[y][x] = 'T';
				}
				else {
					shown[y][x] = '#';
				}
				break;

			case'e':
				if (hidden[y][x] != '*') {
					if (shown[y][x] == '#') {
						reveal(shown, hidden, x, y, &goal);
					}
				}
				else {
					gamestate = -1;
				}
				break;

			case'w':
				if (y == 0) {
					continue;
				}
				y--;
				break;

			case'a':
				if (x == 0) {
					continue;
				}
				x--;
				break;

			case's':
				if (y == rows-1) {
					continue;
				}
				y++;
				break;

			case'd':
				if (x == columns-1) {
					continue;
				}
				x++;
				break;
			}
			
			if (goal == 0) {
				gamestate = 1;
			}
			
		}

		system("cls");
		result(shown, hidden, colour, gamestate, mines);
		cout << "Play again? Y/N";
		cin >> repeat;
		system("cls");
	}


	return 0;
}
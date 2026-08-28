#pragma once
#include <vector>

using namespace std;

void resizeboard(vector<vector<char>>& v, int rows, int columns);

void reset(vector<vector<char>>& shown, vector<vector<char>>& hidden, int mines);

void setup(vector<vector<char>>& hidden);

void printboard(vector<vector<char>>& shown, HANDLE colour, int* x, int* y);

void reveal(vector<vector<char>>& shown, vector<vector<char>>& hidden, int x, int y, int* goal);

void result(vector<vector<char>>& shown, vector<vector<char>>& hidden, HANDLE colour, int gamestate, int mines);
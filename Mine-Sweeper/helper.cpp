#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <random>
#include <algorithm>

using namespace std;

void resizeboard(vector<vector<char>>& v,int rows,int columns){
    
    v.resize(rows);

    
    for (int i = 0; i < rows; ++i) {
        v[i].resize(columns, 0);
    }
}

void reset(vector<vector<char>>& shown, vector<vector<char>>& hidden,int mines) {
    for (int i = 0; i < shown.size(); i++) {
        for (int j = 0; j < shown[i].size(); j++) {
            shown[i][j] = '#';
        }
    }

    for (int i = 0; i < hidden.size(); i++) {
        for (int j = 0; j < hidden[i].size(); j++) {
            hidden[i][j] = '0';
        }
    }

    vector<pair<int, int>> coords;

    for (int i = 0; i < hidden.size(); ++i) {
        for (int j = 0; j < hidden[0].size(); ++j) {
            coords.emplace_back(i, j);
        }
    }

    // Shuffle them
    default_random_engine rng(static_cast<unsigned>(time(nullptr)));
    shuffle(coords.begin(), coords.end(), rng);

    for (int i = 0; i < mines;i++) {  
        hidden[coords[i].first][coords[i].second] = '*';
    }
    
}

void setup(vector<vector<char>>& hidden){
    for (int i = 0; i < hidden.size(); i++) {
        for (int j = 0; j < hidden[i].size(); j++) {

            if (hidden[i][j] == '*') {
                for (int y = i - 1; y <= i + 1; y++) {
                    for (int x = j - 1; x <= j + 1; x++) {

                        
                        if (y < 0 || y >= hidden.size()) { 
                            continue;
                        }
                        if (x < 0 || x >= hidden[y].size()) { 
                            continue;
                        }

                        if (hidden[y][x] != '*') {
                            hidden[y][x] += 1;
                        }
                    }
                }
            }

        }
    }
}

void printboard(vector<vector<char>>& shown, HANDLE colour, int* x, int* y) {
    for (int i = 0; i < shown.size(); i++) {
        for (int j = 0; j < shown[i].size(); j++) {

            if (*x == j && *y == i) {
                SetConsoleTextAttribute(colour, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                cout << shown[i][j] << " ";
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                continue;
            }

            switch(shown[i][j]) {
            case'#':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;

            case'0':
                SetConsoleTextAttribute(colour,0);
                break;

            case'1':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE);
                break;

            case'2':
                SetConsoleTextAttribute(colour, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;

            case'3':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;

            case'4':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE | FOREGROUND_RED);
                break;

            case'5':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN);
                break;

            case'6':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE | FOREGROUND_GREEN);
                break;

            case'7':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;

            case'8':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
            }

            cout << shown[i][j] << " ";
            SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf("\n");
    }
}

void reveal(vector<vector<char>>& shown, vector<vector<char>>& hidden, int x, int y,int* goal) {

    if (shown[y][x] != '#') {
        return;
    }

    shown[y][x] = hidden[y][x];
    (*goal)--;

    if (hidden[y][x] == '0') {
        for
            (int i = y - 1; i <= y + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (i < 0 || j < 0 || i >= shown.size() || j >= shown[i].size()) {
                    continue;
                }
                reveal(shown, hidden, j, i, goal);
            }
        }
    }

}

void result(vector<vector<char>>& shown, vector<vector<char>>& hidden, HANDLE colour, int gamestate, int mines) {
    int falseflags = 0;
    int minesleft = mines;
    for (int i = 0; i < shown.size(); i++) {
        for (int j = 0; j < shown[i].size(); j++) {


            if (hidden[i][j] == '*' && shown[i][j] == 'T') {
                minesleft--;
            }

            if (gamestate == -1 && hidden[i][j] == '*' && shown[i][j] != 'T') {
                SetConsoleTextAttribute(colour, FOREGROUND_RED);
                cout << hidden[i][j] << " ";
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                continue;
            }

            if (gamestate == -1 && shown[i][j] == 'T') {
                if (hidden[i][j] != '*') {
                    SetConsoleTextAttribute(colour, FOREGROUND_RED);
                    cout << "F ";
                    falseflags++;
                    SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else {
                    cout << "T ";
                }
                continue;
            }
           
            switch (shown[i][j]) {
            case'#':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;

            case'0':
                SetConsoleTextAttribute(colour, 0);
                break;

            case'1':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE);
                break;

            case'2':
                SetConsoleTextAttribute(colour, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;

            case'3':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;

            case'4':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE | FOREGROUND_RED);
                break;

            case'5':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN);
                break;

            case'6':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE | FOREGROUND_GREEN);
                break;

            case'7':
                SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;

            case'8':
                SetConsoleTextAttribute(colour, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
            }

            cout << shown[i][j] << " ";
            SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf("\n");
    }
    if (gamestate == 1) {
        SetConsoleTextAttribute(colour, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "All mines cleared! You Win! :)" << endl;
    }
    else {
        SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You Lose! Mines left: " << minesleft << ", False flags " << falseflags << endl;
    }
    SetConsoleTextAttribute(colour, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


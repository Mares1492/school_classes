#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h> // For _getch() on Windows (for Linux, you can use ncurses library)

using namespace std;

const int MATRIX_WIDTH = 10;
const int MATRIX_HEIGHT = 20;

vector<string> gameBoard(MATRIX_HEIGHT, string(MATRIX_WIDTH, ' '));
vector<vector<int>> tetromino;
int tetrominoX, tetrominoY;
char tetrominoChar = '*';

void drawBoard() {
    system("cls"); // Clear the console screen (for Windows)
    // system("clear"); // Use this for Linux
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < MATRIX_WIDTH; j++) {
            cout << gameBoard[i][j];
        }
        cout << "|\n";
    }
    cout << "+----------+\n";
}

bool isValidMove() {
    for (int i = 0; i < tetromino.size(); i++) {
        for (int j = 0; j < tetromino[i].size(); j++) {
            int x = tetrominoX + j;
            int y = tetrominoY + i;
            if (tetromino[i][j] && (x < 0 || x >= MATRIX_WIDTH || y >= MATRIX_HEIGHT || gameBoard[y][x] != ' ')) {
                return false;
            }
        }
    }
    return true;
}

void placeTetromino() {
    for (int i = 0; i < tetromino.size(); i++) {
        for (int j = 0; j < tetromino[i].size(); j++) {
            if (tetromino[i][j]) {
                int x = tetrominoX + j;
                int y = tetrominoY + i;
                gameBoard[y][x] = tetrominoChar;
            }
        }
    }
}

void clearLines() {
    for (int i = MATRIX_HEIGHT - 1; i >= 0; ) {
        if (gameBoard[i].find(' ') == string::npos) {
            gameBoard.erase(gameBoard.begin() + i);
            gameBoard.insert(gameBoard.begin(), string(MATRIX_WIDTH, ' '));
        } else {
            i--;
        }
    }
}

int main() {
    srand(time(0));
    tetromino = {{1, 1, 1, 1}}; // I-piece

    while (true) {
        tetrominoX = MATRIX_WIDTH / 2 - tetromino[0].size() / 2;
        tetrominoY = 0;

        if (!isValidMove()) {
            break; // Game over
        }

        while (true) {
            drawBoard();
            if (_kbhit()) { // Check if a key is pressed
                char key = _getch();
                if (key == 'a') { // Move left
                    tetrominoX--;
                    if (!isValidMove()) {
                        tetrominoX++;
                    }
                } else if (key == 'd') { // Move right
                    tetrominoX++;
                    if (!isValidMove()) {
                        tetrominoX--;
                    }
                } else if (key == 's') { // Move down
                    tetrominoY++;
                    if (!isValidMove()) {
                        tetrominoY--;
                        placeTetromino();
                        clearLines();
                        break;
                    }
                } else if (key == 'q') { // Quit the game
                    return 0;
                }
            }

            tetrominoY++;
            if (!isValidMove()) {
                tetrominoY--;
                placeTetromino();
                clearLines();
                break;
            }
        }
    }

    cout << "Game Over!" << endl;
    return 0;
}

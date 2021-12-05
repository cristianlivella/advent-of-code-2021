#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAXN 500
#define BOARD_SIZE 5

struct Cell {
    bool drawn;
    int value;
};

class Board {
    public:
        bool hasAlreadyWin = false;
        Cell cells[BOARD_SIZE][BOARD_SIZE];

        void setCellValue(int value, int x, int y) {
            this->cells[x][y].value = value;
        }

        bool markDrawn(int value) {
            bool found = false;

            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (this->cells[i][j].value == value) {
                        this->cells[i][j].drawn = true;
                        found = true;
                    }
                }
            }

            return found;
        }

        bool checkWin() {
            this->hasAlreadyWin = this->partialHasWin(false) || this->partialHasWin(true);
            return this->hasAlreadyWin;
        }

        int getNotDrawnSum() {
            int sum = 0;

            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (!this->cells[i][j].drawn) {
                        sum += this->cells[i][j].value;
                    }
                }
            }

            return sum;
        }

    private:
        bool partialHasWin(bool withRow) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (((this->cells[i][j].drawn && withRow) || (this->cells[j][i].drawn && !withRow)) && j == (BOARD_SIZE - 1)) {
                        return true;
                    } else if ((!this->cells[i][j].drawn && withRow) || (!this->cells[j][i].drawn && !withRow)) {
                        break;
                    }
                }
            }
            return false;
        }
};

int main() {
    int drawnNumbers[MAXN], countDrawnNumbers = 0, countBoards = 0, firstBoardScore = -1, lastBoardScore, tmp;
    Board boards[MAXN];
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (input >> drawnNumbers[countDrawnNumbers]) {
        countDrawnNumbers++;

        if (input.peek() == ',')
            input.ignore();

        if (input.peek() == '\n') {
            break;
        }
    }

    while (!input.eof()) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (!(input >> tmp)) break;
                boards[countBoards].setCellValue(tmp, i, j);
            }
        }
        countBoards++;
    }

    countBoards--;

    for (int i = 0; i < countDrawnNumbers; i++) {
        for (int j = 0; j < countBoards; j++) {
            if (boards[j].markDrawn(drawnNumbers[i])) {
                if (!boards[j].hasAlreadyWin && boards[j].checkWin()) {
                    lastBoardScore = boards[j].getNotDrawnSum() * drawnNumbers[i];

                    if (firstBoardScore == -1) {
                        firstBoardScore = lastBoardScore;
                    }
                }
            }
        }
    }

    output << firstBoardScore << endl;
    output << lastBoardScore << endl;

    input.close();
    output.close();

    return 0;
}

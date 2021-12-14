#include <fstream>
#include <sstream>
using namespace std;

#define MAXN 2000

bool *initializeArray(bool value, int size);
bool **initializeMatrix(bool value, int sizeX, int sizeY);

int main() {
    int maxX = MAXN, maxY = MAXN, tmp1, tmp2;
    bool **matrix = initializeMatrix(false, MAXN, MAXN);
    char axe;
    string tmp;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        getline(input, tmp);

        if (tmp == "") {
            break;
        }

        istringstream tmpStream(tmp);

        tmpStream >> tmp1;
        tmpStream.ignore();
        tmpStream >> tmp2;
        matrix[tmp1][tmp2] = true;
    }

    int countDots = 0;
    bool firstFold = true;

    while (!input.eof()) {
        input.ignore(11);
        input.get(axe);
        input.ignore(1);

        if (!(input >> tmp1)) {
            break;
        }

        input.ignore();

        if (axe == 'x') {
            for (int i = 0; i < tmp1; i++) {
                for (int j = 0; j < MAXN; j++) {
                    matrix[i][j] = matrix[i][j] || matrix[tmp1 * 2 - i][j];
                    matrix[tmp1 * 2 - i][j] = false;
                }
            }
            maxY = tmp1;
        } else if (axe == 'y') {
            for (int i = 0; i < MAXN; i++) {
                for (int j = 0; j < tmp1; j++) {
                    matrix[i][j] = matrix[i][j] || matrix[i][tmp1 * 2 - j];
                    matrix[i][tmp1 * 2 - j] = false;
                }
            }
            maxX = tmp1;
        }

        if (firstFold) {
            for (int i = 0; i < maxX; i++) {
                for (int j = 0; j < maxY; j++) {
                    if (matrix[j][i]) {
                        countDots++;
                    }
                }
            }

            output << countDots << endl;
            firstFold = false;
        }
    }

    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {
            output << (matrix[j][i] ? '#' : ' ');
        }
        output << endl;
    }

    input.close();
    output.close();

    return 0;
}

bool *initializeArray(bool value, int size) {
    bool *array = (bool*) malloc(size * sizeof(bool));
    for (int i = 0; i < size; i++) {
        array[i] = value;
    }
    return array;
}

bool **initializeMatrix(bool value, int sizeX, int sizeY) {
    bool **matrix = (bool**) malloc(sizeX * sizeof(bool*));
    for (int i = 0; i < sizeX; i++) {
        matrix[i] = initializeArray(value, sizeY);
    }
    return matrix;
}

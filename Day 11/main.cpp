#include <fstream>
#include <stack>

using namespace std;

bool *initializeArray(bool value, int size);
bool **initializeMatrix(bool value, int sizeX, int sizeY);

int main() {
    int originalMatrix[12][12], matrix[12][12], step = 0, flashes = 0, stepFleshes, syncStep;
    bool **exploded, run, firstLoop, newExplosions;
    char tmp;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            input.get(tmp);
            originalMatrix[i][j] = (int) tmp - '0';
        }
        input.ignore();
    }

    for (int part = 0; part < 2; part++) {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                matrix[i][j] = originalMatrix[i][j];
            }
        }

        step = 0;
        run = true;

        while (run) {
            step++;

            exploded = initializeMatrix(false, 12, 12);
            stepFleshes = 0;
            firstLoop = true;
            newExplosions = true;

            while (newExplosions) {
                newExplosions = false;
                for (int i = 1; i < 11; i++) {
                    for (int j = 1; j < 11; j++) {
                        if (firstLoop) {
                            matrix[i][j]++;
                        }

                        if (matrix[i][j] > 9 && exploded[i][j] == false) {
                            if (part == 0) {
                                flashes++;
                            }

                            exploded[i][j] = true;
                            stepFleshes++;
                            newExplosions = true;

                            for (int x = -1; x < 2; x++) {
                                for (int y = -1; y < 2; y++) {
                                    if (x == 0 && y == 0) continue;
                                    matrix[i+x][j+y]++;
                                }
                            }
                        }
                    }
                }
                firstLoop = false;
            }

            for (int i = 1; i < 11; i++) {
                for (int j = 1; j < 11; j++) {
                    if (matrix[i][j] > 9) {
                        matrix[i][j] = 0;
                    }
                }
            }

            if ((step == 100 && part == 0) || stepFleshes == 100) {
                run = false;
            }

            if (part == 1 && stepFleshes == 100) {
                syncStep = step;
            }
        }
    }

    output << flashes << endl;
    output << syncStep << endl;

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

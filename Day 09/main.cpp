#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define SIZE_X 100
#define SIZE_Y 100

int compare (const void * a, const void * b);

int main() {
    int matrix[SIZE_X][SIZE_X] = {};
    int lowers[SIZE_X][SIZE_Y] = {};
    int sumRisk = 0;
    char tmp;

    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    for (int i = 0; i < SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            input.get(tmp);
            matrix[i][j] = tmp - '0';
        }
        input.ignore();
    }

    for (int i = 0; i <SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            bool isMinor = true;
            if (i > 0 && matrix[i-1][j] <= matrix[i][j]) {
                isMinor = false;
            } else if (i < (SIZE_X-1) && matrix[i+1][j] <= matrix[i][j]) {
                isMinor = false;
            } else if (j > 0 && matrix[i][j-1] <= matrix[i][j]) {
                isMinor = false;
            } else if (j < (SIZE_Y-1) && matrix[i][j+1] <= matrix[i][j]) {
                isMinor = false;
            }
            if (isMinor) {
                sumRisk += matrix[i][j] + 1;
                lowers[i][j] = 1;
            }
        }
    }

    int basinIndex = 1;
    int basinSizes[SIZE_X * SIZE_Y] = {};

    for (int i = 0; i <SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            if (lowers[i] && matrix[i][j] != 9) {
                lowers[i][j] = ++basinIndex;
            }
        }
    }

    bool madeChanges = true;
    while (madeChanges) {
        madeChanges = false;
        for (int i = 0; i < SIZE_X; i++) {
            for (int j = 0; j < SIZE_Y; j++) {
                if (lowers[i][j] < 1) {
                    continue;
                }
                if (i > 0 && (lowers[i-1][j] > 1) && lowers[i][j] < lowers[i-1][j]) {
                    lowers[i][j] = lowers[i-1][j];
                    madeChanges = true;
                }
                if (i < (SIZE_X-1) && (lowers[i+1][j] > 1) && lowers[i][j] < lowers[i+1][j]) {
                    lowers[i][j] = lowers[i+1][j];
                    madeChanges = true;
                }
                if (j > 0 && (lowers[i][j-1] > 1) && lowers[i][j] < lowers[i][j-1]) {
                    lowers[i][j] = lowers[i][j-1];
                    madeChanges = true;
                }
                if (j < (SIZE_Y-1) && (lowers[i][j+1] > 1) && lowers[i][j] < lowers[i][j+1]) {
                    lowers[i][j] = lowers[i][j+1];
                    madeChanges = true;
                }
            }
        }
    }

    for (int i = 0; i < SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            basinSizes[lowers[i][j]]++;
        }
    }

    basinSizes[0] = 0;
    basinSizes[1] = 0;

    qsort(basinSizes, basinIndex, sizeof(int), compare);

    int multSize = 1;
    for (int i = 0; i < 3; i++) {
        multSize *= basinSizes[i];
    }

    output << sumRisk << endl;
    output << multSize << endl;

    input.close();
    output.close();

    return 0;
}

int compare (const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}

#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAXN 4000

int sumRange(int n) {
    return (n * (n+1)) / 2;
}

int main() {
    int crabPositions[MAXN], maxPosition = -1, crabCount = 0, sum, minimumSum;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        input >> crabPositions[crabCount];
        if (crabPositions[crabCount] > maxPosition) {
            maxPosition = crabPositions[crabCount];
        }
        crabCount++;
        input.ignore();
    }
    crabCount--;


    for (int part = 0; part < 2; part++) {
        minimumSum = -1;
        for (int target = 0; target < maxPosition; target++) {
            sum = 0;

            for (int i = 0; i < crabCount; i++) {
                if (part == 0) {
                    sum += abs(target - crabPositions[i]);
                } else {
                    sum += sumRange(abs(target - crabPositions[i]));
                }
            }

            if (sum < minimumSum || minimumSum == -1) {
                minimumSum = sum;
            }
        }
        output << minimumSum << endl;
    }

    input.close();
    output.close();

    return 0;
}

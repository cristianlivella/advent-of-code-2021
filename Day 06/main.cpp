#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAXN 1000

int main() {
    long long timerFishes[MAXN], tmp, newFishes, sum;
    ifstream input;
    ofstream output;

    for (int i = 0; i < 9; i++) {
        timerFishes[i] = 0;
    }

    input.open("input.txt");
    output.open("output.txt");

    while (input >> tmp) {
        timerFishes[tmp]++;
        input.ignore();
    }

    for (int day = 1; day <= 256; day++) {
        newFishes = timerFishes[0];
        for (int i = 0; i < 8; i++) {
            timerFishes[i] = timerFishes[i + 1];
        }
        timerFishes[6] += newFishes;
        timerFishes[8] = newFishes;

        if (day == 80 || day == 256) {
            sum = 0;
            for (int i = 0; i < 9; i++) {
                sum += timerFishes[i];
            }
            output << sum << endl;
        }
    }

    input.close();
    output.close();

    return 0;
}

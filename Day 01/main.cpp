#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int i = 0;
    int depthIncreased = 0, depthWindowIncreased = 0;
    int prevWindowSum = 0, windowSum = 0;
    int depths[2000];

    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (input >> depths[i]) {
        if (i > 0 && depths[i] > depths[i - 1]) {
            depthIncreased++;
        }

        if (i > 2) {
            prevWindowSum = windowSum;
            windowSum = windowSum + depths[i] - depths[i - 3];

            if (windowSum > prevWindowSum) {
                depthWindowIncreased++;
            }
        } else {
            windowSum += depths[i];
        }

        i++;
    }

    output << depthIncreased << endl << depthWindowIncreased;

    input.close();
    output.close();

    return 0;
}

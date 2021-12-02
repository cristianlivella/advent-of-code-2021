#include <iostream>
#include <fstream>

using namespace std;

int main() {
    long value, depth1 = 0, depth2 = 0, horizontalPos = 0, aim = 0;
    string command;

    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (input >> command >> value) {
        if (command == "forward") {
            horizontalPos += value;
            depth2 += (aim * value);
        } else if (command == "down") {
            depth1 += value;
            aim += value;
        } else if (command == "up") {
            depth1 -= value;
            aim -= value;
        }
    }

    output << (depth1 * horizontalPos) << endl;
    output << (depth2 * horizontalPos) << endl;

    input.close();
    output.close();

    return 0;
}

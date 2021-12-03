#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAXN 2000

string binaryNot(string binaryNumber);
int binaryToDecimal(string binaryNumber);
char mostCommonDigitInPosition(string *rows, int countRows, int position);
string *filterByMostLeastCommonDigit(string *rows, int countRows, bool mostCommon, int position);

int main() {
    int countRows = 0;
    string rows[MAXN], deltaRate = "", epsilonRate = "", oxigenRating, co2ScrubberRating;

    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (input >> rows[countRows]) {
        countRows++;
    }

    // part 1
    for (int i = 0; i < rows[0].length(); i++) {
        deltaRate += mostCommonDigitInPosition(rows, countRows, i);
    }

    epsilonRate = binaryNot(deltaRate);
    output << binaryToDecimal(deltaRate) * binaryToDecimal(epsilonRate) << endl;

    // part 2
    oxigenRating = filterByMostLeastCommonDigit(rows, countRows, true, 0)[0];
    co2ScrubberRating = filterByMostLeastCommonDigit(rows, countRows, false, 0)[0];

    output << binaryToDecimal(oxigenRating) * binaryToDecimal(co2ScrubberRating) << endl;

    input.close();
    output.close();

    return 0;
}


string binaryNot(string binaryNumber) {
    string notNumber = "";

    for (int i = 0; i < binaryNumber.length(); i++) {
        if (binaryNumber[i] == '0') {
            notNumber += '1';
        } else {
            notNumber += '0';
        }
    }

    return notNumber;
}

int binaryToDecimal(string binaryNumber) {
    int number = 0;

    for (int i = 0; i < binaryNumber.length(); i++) {
        if (binaryNumber[i] == '1') {
            number += pow(2, binaryNumber.length() - i - 1);
        }
    }

    return number;
}

char mostCommonDigitInPosition(string *rows, int countRows, int position) {
    int countZero = 0;

    for (int i = 0; i < countRows; i++) {
        if (rows[i][position] == '0') {
            countZero++;
        }
    }

    if (countZero > (countRows - countZero)) {
        return '0';
    } else {
        return '1';
    }
}

string *filterByMostLeastCommonDigit(string *rows, int countRows, bool mostCommon, int position) {
    int countNewRows = 0;
    string *newRows = (string*) malloc(MAXN * sizeof(string));

    char mostCommonDigit = mostCommonDigitInPosition(rows, countRows, position);

    for (int i = 0; i < countRows; i++) {
        if ((rows[i][position] == mostCommonDigit) == mostCommon) {
            newRows[countNewRows++] = rows[i];
        }
    }

    if (countNewRows == 1) {
        return newRows;
    } else {
        return filterByMostLeastCommonDigit(newRows, countNewRows, mostCommon, position + 1);
    }
}

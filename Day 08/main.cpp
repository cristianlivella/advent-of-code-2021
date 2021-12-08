#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

char SEGMENTS[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

string NUMBERS[10] = {
    "abcefg",
    "cf",
    "acdeg",
    "acdfg",
    "bcdf",
    "abdfg",
    "abdefg",
    "acf",
    "abcdefg",
    "abcdfg"
};

int getDigitIndex(char digit);
int getNumberBySegments(string segments);
int *getNumbersWithXSegments(int segments);
bool *initializeArray(bool value, int size);
bool **initializeMatrix(bool value, int sizeX, int sizeY);

int main() {
    int countSimpleDigits = 0, sumNumbers = 0;
    string tmp;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        bool **validSegmentsMatch = initializeMatrix(true, 7, 7);

        for (int pattern = 0; pattern < 10; pattern++) {
            input >> tmp;

            int *numbers = getNumbersWithXSegments(tmp.length());
            bool *commonDigits = initializeArray(true, 7);
            bool *commonDigitsCustomSchema = initializeArray(false, 7);

            int numberIndex = 0;

            while (numbers[numberIndex] != -1) {
                bool *singleNumberDigits = initializeArray(false, 7);
                string numberSegments = NUMBERS[numbers[numberIndex]];

                for (int i = 0; i < numberSegments.length(); i++) {
                    singleNumberDigits[getDigitIndex(numberSegments[i])] = true;
                }

                for (int i = 0; i < 7; i++) {
                    commonDigits[i] = commonDigits[i] && singleNumberDigits[i];
                }

                numberIndex++;
            }

            for (int i = 0; i < tmp.length(); i++) {
                commonDigitsCustomSchema[getDigitIndex(tmp[i])] = true;
            }

            for (int i = 0; i < 7; i++) {
                if (commonDigits[i]) {
                    for (int j = 0; j < 7; j++) {
                        validSegmentsMatch[i][j] = validSegmentsMatch[i][j] && commonDigitsCustomSchema[j];
                    }
                }
            }
        }

        bool needCheck = true;
        while (needCheck) {
            needCheck = false;
            for (int i = 0; i < 7; i++) {
                int found = -1;
                for (int j = 0; j < 7; j++) {
                    if (validSegmentsMatch[i][j]) {
                        if (found == -1) {
                            found = j;
                        } else if (found >= 0) {
                            found = -2;
                        }
                    }
                }
                if (found >= 0) {
                    for (int j = 0; j < 7; j++) {
                        if (i == j) {
                            continue;
                        } else if (validSegmentsMatch[j][found]) {
                            needCheck = true;
                            validSegmentsMatch[j][found] = false;
                        }
                    }
                }
            }
        }

        input.ignore(3);

        int realNumber = 0;

        for (int digitIdx = 0; digitIdx < 4; digitIdx++) {
            input >> tmp;

            bool *segments = initializeArray(false, 7);
            string segmentsString = "";

            for (int i = 0; i < tmp.length(); i++) {
                int index = getDigitIndex(tmp[i]);
                for (int j = 0; j < 7; j++) {
                    if (validSegmentsMatch[j][index]) {
                        segments[j] = true;
                    }
                }
            }

            for (int i = 0; i < 7; i++) {
                if (segments[i]) {
                    segmentsString += SEGMENTS[i];
                }
            }

            int digit = getNumberBySegments(segmentsString);
            realNumber += pow(10, 3 - digitIdx) * digit;

            if (digit == 1 || digit == 4 || digit == 7 || digit == 8) {
                countSimpleDigits++;
            }
        }

        sumNumbers += realNumber;

        while (input.peek() == '\n') input.ignore();
    }

    output << countSimpleDigits << endl;
    output << sumNumbers << endl;

    input.close();
    output.close();

    return 0;
}

int getDigitIndex(char digit) {
    for (int i = 0; i < 7; i++) {
        if (SEGMENTS[i] == digit) {
            return i;
        }
    }
    return -1;
}

int getNumberBySegments(string segments) {
    for (int i = 0; i < 10; i++) {
        if (NUMBERS[i] == segments) {
            return i;
        }
    }
    return -1;
}

int *getNumbersWithXSegments(int segments) {
    int *numbers = (int*) malloc(10 * sizeof(int)), countNumbers = 0;

    for (int i = 0; i < 10; i++) {
        if (NUMBERS[i].length() == segments) {
            numbers[countNumbers++] = i;
        }
    }

    numbers[countNumbers] = -1;

    return numbers;
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

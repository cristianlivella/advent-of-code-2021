#include <fstream>

using namespace std;

#define MAXN 50

string NAMES[MAXN];
int ADJ[MAXN][MAXN];
int countCaves = 0;

int getNodeIndex(string name);
void addNode(string name);
void addAdj(string nodeA, string nodeB);
void addAdjImpl(int indexA, int indexB);
int *cloneIntArray(int *array);
bool isUpperCase(string s);
bool isStartOrEnd(int index);
int countPathStartingFrom(int index, int *caveVisits, bool canRepeatSmallCave);
int countPathStartingFrom(string node, int *caveVisits, bool canRepeatSmallCave);

int main() {
    int caveVisits[MAXN];
    bool readingString2 = false;
    string string1, string2;
    char tmp;
    ifstream input;
    ofstream output;

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            ADJ[i][j] = -1;
        }
        caveVisits[i] = 0;
    }

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        input.get(tmp);
        if (tmp == '-') {
            readingString2 = true;
        } else if (tmp == '\n') {
            addAdj(string1, string2);
            string1 = "";
            string2 = "";
            readingString2 = false;
        } else if (!readingString2) {
            string1 += tmp;
        } else {
            string2 += tmp;
        }
    }

    output << countPathStartingFrom("start", caveVisits, false) << endl;
    output << countPathStartingFrom("start", caveVisits, true) << endl;

    input.close();
    output.close();

    return 0;
}

int getNodeIndex(string name) {
    for (int i = 0; i < countCaves; i++) {
        if (NAMES[i] == name) {
            return i;
        }
    }
    addNode(name);
    return getNodeIndex(name);
}

void addNode(string name) {
    NAMES[countCaves++] = name;
}

void addAdj(string nodeA, string nodeB) {
    int indexA = getNodeIndex(nodeA);
    int indexB = getNodeIndex(nodeB);

    addAdjImpl(indexA, indexB);
    addAdjImpl(indexB, indexA);
}

void addAdjImpl(int indexA, int indexB) {
    for (int i = 0; i < MAXN; i++) {
        if (ADJ[indexA][i] == -1) {
            ADJ[indexA][i] = indexB;
            break;
        }
    }
}

int *cloneIntArray(int *array) {
    int *newArray = (int *) malloc(MAXN * sizeof(int));
    for (int i = 0; i < MAXN; i++) {
        newArray[i] = array[i];
    }
    return newArray;
}

bool isUpperCase(string s) {
    return s[0] >= 'A' && s[0] <= 'Z';
}

bool isStartOrEnd(int index) {
    return NAMES[index] == "start" || NAMES[index] == "end";
}

int countPathStartingFrom(int index, int *caveVisits, bool canRepeatSmallCave) {
    int count = 0;
    int *newCaveVisits = cloneIntArray(caveVisits);

    if (NAMES[index] == "end") {
        return 1;
    }

    newCaveVisits[index]++;

    for (int i = 0; i < MAXN; i++) {
        if (ADJ[index][i] == -1) {
            break;
        }

        bool newCanRepeatSmallCave = true;

        if (isUpperCase(NAMES[ADJ[index][i]]) || (caveVisits[ADJ[index][i]] < ((canRepeatSmallCave && !isStartOrEnd(ADJ[index][i])) ? 2 : 1))) {
            if (newCaveVisits[ADJ[index][i]] > 0 && !isUpperCase(NAMES[ADJ[index][i]])) {
                newCanRepeatSmallCave = false;
            }

            count += countPathStartingFrom(ADJ[index][i], newCaveVisits, canRepeatSmallCave && newCanRepeatSmallCave);
        }
    }

    return count;
}

int countPathStartingFrom(string node, int *caveVisits, bool canRepeatSmallCave) {
    int index = getNodeIndex(node);
    return countPathStartingFrom(index, caveVisits, canRepeatSmallCave);
}

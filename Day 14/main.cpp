#include <fstream>

using namespace std;

#define MAXN 200

int countRules = 0;

string RULES_PAIRS[MAXN];
char RULES_INSERTIONS[MAXN];

long COUNT_TOUPLES[MAXN] = {};
long COUNT_TOUPLES_PARTIAL[MAXN] = {};
long COUNT_ELEMENTS[26] = {};

int getRuleIndex(string pair);
void addRule(string pair);
string computatePolymer(string pair);
int compare (const void * a, const void * b);

int main() {
    string polymer, tmp1, tmp2;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    input >> polymer;

    input.ignore();

    while (!input.eof()) {
        input >> tmp1;
        input.ignore(4);
        input >> tmp2;
        RULES_INSERTIONS[getRuleIndex(tmp1)] = tmp2[0];
    }

    int len = polymer.length();

    for (int part = 0; part < 2; part++) {
        for (int i = 0; i < MAXN; i++) {
            COUNT_TOUPLES[i] = 0;
            COUNT_TOUPLES_PARTIAL[i] = 0;
        }

        for (int i = 0; i < 26; i++) {
            COUNT_ELEMENTS[i] = 0;
        }

        COUNT_ELEMENTS[(char) polymer[0] - 'A'] = 1;

        for (int i = 0; i < (len - 1); i++) {
            string chunk = "";
            chunk += polymer[i];
            chunk += polymer[i+1];
            COUNT_TOUPLES[getRuleIndex(chunk)]++;
        }

        for (int step = 0; step < (part == 0 ? 10 : 40); step++) {
            for (int i = 0; i < countRules; i++) {
                string newPolymer = computatePolymer(RULES_PAIRS[i]);

                string pair1 = "", pair2 = "";
                pair1 += newPolymer[0];
                pair1 += newPolymer[1];
                pair2 += newPolymer[1];
                pair2 += newPolymer[2];

                COUNT_TOUPLES_PARTIAL[getRuleIndex(pair1)] += COUNT_TOUPLES[i];
                COUNT_TOUPLES_PARTIAL[getRuleIndex(pair2)] += COUNT_TOUPLES[i];
            }

            for (int i = 0; i < MAXN; i++) {
                COUNT_TOUPLES[i] = COUNT_TOUPLES_PARTIAL[i];
                COUNT_TOUPLES_PARTIAL[i] = 0;
            }
        }

        for (int i = 0; i < countRules; i++) {
            COUNT_ELEMENTS[(int) RULES_PAIRS[i][1] - 'A'] += COUNT_TOUPLES[i];
        }

        qsort(COUNT_ELEMENTS, 26, sizeof(long), compare);

        long leastCommonOccurrences = 0;

        for (int i = 0; i < 26; i++) {
            if (COUNT_ELEMENTS[i] > 0) {
                leastCommonOccurrences = COUNT_ELEMENTS[i];
            }
        }

        output << COUNT_ELEMENTS[0] - leastCommonOccurrences << endl;
    }

    input.close();
    output.close();

    return 0;
}

int getRuleIndex(string pair) {
    for (int i = 0; i < countRules; i++) {
        if (RULES_PAIRS[i] == pair) {
            return i;
        }
    }
    addRule(pair);
    return getRuleIndex(pair);
}

void addRule(string pair) {
    RULES_PAIRS[countRules++] = pair;
}

string computatePolymer(string pair) {
    string polymer = "";
    polymer += pair[0];
    polymer += RULES_INSERTIONS[getRuleIndex(pair)];
    polymer += pair[1];
    return polymer;
}

int compare (const void * a, const void * b) {
    long x = *(long*) a;
    long y = *(long*) b;

    if (x > y) {
        return -1;
    } else if (x < y) {
        return 1;
    } else {
        return 0;
    }
}

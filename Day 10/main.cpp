#include <fstream>
#include <stack>

using namespace std;

#define MAXN 1000
#define CHARS_COUNT 4

char OPENING_CHARS[CHARS_COUNT] = {'(', '[', '{', '<'};
char CLOSING_CHARS[CHARS_COUNT] = {')', ']', '}', '>'};
int SYNTAX_SCORES[CHARS_COUNT] = {3, 57, 1197, 25137};
int AUTOCOMPLETE_SCORES[CHARS_COUNT] = {1, 2, 3, 4};

bool isOpeningChar(char c);
bool isClosingChar(char c);
bool isCharInArray(char c, char *array, int size);
int getCharArrayIndex(char c, char *array, int size);
bool isChunkCorrect(char opening, char closing);
void deleteAllStackItems(stack<char> &s);
char topAndPop(stack<char> &s);
int compare (const void * a, const void * b);

int main() {
    int scoreIndex = 0;
    long syntaxScore = 0, partialScore, autocompleteScores[MAXN];
    char tmp;
    stack<char> characters;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        input.get(tmp);

        if (tmp == '\n') {
            partialScore = 0;

            while (!characters.empty()) {
                partialScore *= 5;
                partialScore += AUTOCOMPLETE_SCORES[getCharArrayIndex(topAndPop(characters), OPENING_CHARS, CHARS_COUNT)];
            }

            if (partialScore > 0) {
                autocompleteScores[scoreIndex++] = partialScore;
            }

            continue;
        }

        if (isOpeningChar(tmp)) {
            characters.push(tmp);
        } else if (characters.empty() || !isChunkCorrect(topAndPop(characters), tmp)) {
            syntaxScore += SYNTAX_SCORES[getCharArrayIndex(tmp, CLOSING_CHARS, CHARS_COUNT)];

            deleteAllStackItems(characters);
            while (input.peek() != '\n') input.ignore();
        }
    }

    qsort(autocompleteScores, scoreIndex, sizeof(long), compare);

    output << syntaxScore << endl;
    output << autocompleteScores[scoreIndex / 2] << endl;

    input.close();
    output.close();

    return 0;
}

bool isOpeningChar(char c) {
    return isCharInArray(c, OPENING_CHARS, CHARS_COUNT);
}

bool isClosingChar(char c) {
    return isCharInArray(c, CLOSING_CHARS, CHARS_COUNT);
}

bool isCharInArray(char c, char *array, int size) {
    return getCharArrayIndex(c, array, size) != -1;
}

int getCharArrayIndex(char c, char *array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == c) {
            return i;
        }
    }
    return -1;
}

bool isChunkCorrect(char opening, char closing) {
    if (!isOpeningChar(opening) || !isClosingChar(closing)) {
        return false;
    }

    int index = getCharArrayIndex(opening, OPENING_CHARS, CHARS_COUNT);

    return CLOSING_CHARS[index] == closing;
}

void deleteAllStackItems(stack<char> &s) {
    while (!s.empty()) {
        s.pop();
    }
}

char topAndPop(stack<char> &s) {
    char c = '\0';
    if (!s.empty()) {
        c = s.top();
        s.pop();
    }
    return c;
}

int compare (const void * a, const void * b) {
    long x = *(long*) a;
    long y = *(long*) b;

    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

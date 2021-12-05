#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAXN 1000

struct Point {
    int x, y;
};

class Vent {
    public:
        Point start, end, iterator;
        bool iteratorInitialized = false;

        bool isVerticalOrHorizontal() {
            return isVertical() || isHorizontal();
        }

        bool hasNext() {
            if (!iteratorInitialized) {
                return true;
            } else if (iterator.x == end.x && iterator.y == end.y) {
                return false;
            } else {
                return true;
            }
        }

        Point getNext() {
            if (!iteratorInitialized) {
                initIterator();
            } else if (isVertical()) {
                incrementIteratorY();
            } else if (isHorizontal()) {
                incrementIteratorX();
            } else {
                incrementIteratorX();
                int m = (end.y - start.y) / (end.x - start.x);
                int q = start.y - m * start.x;
                iterator.y = m * iterator.x + q;
            }
            return iterator;
        }

        void resetIterator() {
            iteratorInitialized = false;
        }

    private:
        bool isVertical() {
            return start.x == end.x;
        }

        bool isHorizontal() {
            return start.y == end.y;
        }

        void initIterator() {
            iteratorInitialized = true;
            iterator.x = start.x;
            iterator.y = start.y;
        }

        void incrementIteratorX() {
            iterator.x += 1 * (end.x > iterator.x ? 1 : -1);
        }

        void incrementIteratorY() {
            iterator.y += 1 * (end.y > iterator.y ? 1 : -1);
        }

};

int main() {
    Vent vents[MAXN];
    int countVents = 0, countOverlaps, grid[MAXN][MAXN];
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        input >> vents[countVents].start.x;
        input.ignore();
        input >> vents[countVents].start.y;
        input.ignore(4);
        input >> vents[countVents].end.x;
        input.ignore();
        input >> vents[countVents].end.y;
        countVents++;
    }
    countVents--;

    for (int part = 0; part < 2; part++) {
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                grid[i][j] = 0;
            }
        }

        for (int i = 0; i < countVents; i++) {
            vents[i].resetIterator();
            if (vents[i].isVerticalOrHorizontal() || part == 1) {
                while (vents[i].hasNext()) {
                    Point next = vents[i].getNext();
                    grid[next.x][next.y]++;
                }
            }
        }

        countOverlaps = 0;

        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                if (grid[i][j] > 1) {
                    countOverlaps++;
                }
            }
        }

        output << countOverlaps << endl;
    }

    input.close();
    output.close();

    return 0;
}

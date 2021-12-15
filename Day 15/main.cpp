#include <fstream>
#include <climits>

using namespace std;

#define MAX_MATRIX 500
#define MAX_NODES 250000

struct Node {
    int a, b;
    short distance;
};

int getNodeId(int i, int j, int maxX);
void addConnection(Node **adjMatrix, int a, int b, int distance);
void dijkstra(Node **adjMatrix, int *&distances, int countNodes, int firstNode);
int *initializeArrayInt(int value, int size);
int **initializeMatrixInt(int value, int sizeX, int sizeY);
bool *initializeArrayBool(bool value, int size);
bool **initializeMatrixBool(bool value, int sizeX, int sizeY);
Node *initializeArrayNode(int size);
Node **initializeMatrixNode(int sizeX, int sizeY);

int main() {
    int **matrix = initializeMatrixInt(0, MAX_MATRIX, MAX_MATRIX);
    char tmp;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    int i = 0, j = 0, maxX = 0, maxY = 0;
    while (!input.eof()) {
        if (input.peek() == '\n') {
            input.ignore();
            i++;
            j = 0;

            if (input.peek() == '\n') {
                break;
            }

            continue;
        }

        input.get(tmp);
        matrix[i][j] = (int) tmp - '0';

        if (i > maxX) {
            maxX = i;
        }

        if (j > maxY) {
            maxY = j;
        }

        j++;
    }

    maxX++;
    maxY++;

    for (int time = 1; time < 5; time++) {
        for (int i = 0; i < maxX * 5; i++) {
            for (int j = 0; j < maxY; j++) {
                if (time == 1 && i < maxX * 4) {
                    matrix[i + maxX * time][j] = matrix[i + maxX * (time - 1)][j] + 1;
                    if (matrix[i + maxX * time][j] > 9) {
                        matrix[i + maxX * time][j] = 1;
                    }
                }
                matrix[i][j + maxY * time] = matrix[i][j + maxY * (time - 1)] + 1;
                if (matrix[i][j + maxY * time] > 9) {
                    matrix[i][j + maxY * time] = 1;
                }
            }
        }
    }

    for (int part = 0; part < 2; part++) {
        int *distances = initializeArrayInt(0, MAX_NODES);
        Node **adjMatrix = initializeMatrixNode(MAX_NODES, 5);

        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        int compX = i + k;
                        int compY = j + l;

                        if ((k == 0 || l == 0) && (k != 0 || l != 0) && compX >= 0 && compX < maxX && compY >= 0 && compY < maxY) {
                            addConnection(adjMatrix, getNodeId(i, j, maxX), getNodeId(compX, compY, maxX), matrix[compX][compY]);
                        }
                    }
                }
            }
        }

        int lastNodeId = getNodeId(maxX - 1, maxY - 1, maxX);
        dijkstra((Node**)adjMatrix, distances, lastNodeId - 1, 0);
        output << distances[lastNodeId] << endl;

        maxX *= 5;
        maxY *= 5;
    }


    input.close();
    output.close();

    return 0;
}

int getNodeId(int i, int j, int maxX) {
    return  i * maxX + j;
}

void addConnection(Node **adjMatrix, int a, int b, int distance) {
    int index = 0;

    while (adjMatrix[a][index].a != -1) {
        index++;
    }

    adjMatrix[a][index].a = a;
    adjMatrix[a][index].b = b;
    adjMatrix[a][index].distance = distance;
    adjMatrix[a][index + 1].a = -1;
}

void dijkstra(Node **adjMatrix, int *&distances, int countNodes, int firstNode) {
    int countVisits = 0;
    distances = initializeArrayInt(INT_MAX, MAX_NODES);
    bool *visitated = initializeArrayBool(false, MAX_NODES);

    for (int i=0; i < MAX_NODES; i++) {
        distances[i] = INT_MAX;
        visitated[i] = false;
    }

    distances[firstNode] = 0;
    while (countVisits < countNodes) {
        int id = -1;
        for (int i=0; i < countNodes; i++) {
            if ((id == -1 || distances[i] < distances[id]) && !visitated[i]) {
                id = i;
            }
        }

        visitated[id] = true;
        countVisits++;

        int indexAdj = 0;

        while (adjMatrix[id][indexAdj].a != -1) {
            if (distances[id] + adjMatrix[id][indexAdj].distance < distances[adjMatrix[id][indexAdj].b]) {
                distances[adjMatrix[id][indexAdj].b] = distances[id] + adjMatrix[id][indexAdj].distance;
            }

            indexAdj++;
        }
    }
}

int *initializeArrayInt(int value, int size) {
    int *array = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = value;
    }
    return array;
}

int **initializeMatrixInt(int value, int sizeX, int sizeY) {
    int **matrix = (int**) malloc(sizeX * sizeof(int*));
    for (int i = 0; i < sizeX; i++) {
        matrix[i] = initializeArrayInt(value, sizeY);
    }
    return matrix;
}

bool *initializeArrayBool(bool value, int size) {
    bool *array = (bool*) malloc(size * sizeof(bool));
    for (int i = 0; i < size; i++) {
        array[i] = value;
    }
    return array;
}

bool **initializeMatrixBool(bool value, int sizeX, int sizeY) {
    bool **matrix = (bool**) malloc(sizeX * sizeof(bool*));
    for (int i = 0; i < sizeX; i++) {
        matrix[i] = initializeArrayBool(value, sizeY);
    }
    return matrix;
}

Node *initializeArrayNode(int size) {
    Node *array = (Node*) malloc(size * sizeof(Node));
    for (int i = 0; i < size; i++) {
        array[i].a = -1;
    }
    return array;
}

Node **initializeMatrixNode(int sizeX, int sizeY) {
    Node **matrix = (Node**) malloc(sizeX * sizeof(Node*));
    for (int i = 0; i < sizeX; i++) {
        matrix[i] = initializeArrayNode(sizeY);
    }
    return matrix;
}

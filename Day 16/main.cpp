#include <fstream>
#include <climits>
#include <iostream>
#include <math.h>

using namespace std;

#define MAXN 10000

struct PacketReturnData {
    int lastBitIndex;
    int sumVersion;
    long result;
};

char *hexToBinary(char hex);
long binaryRangeToDecimal(char *stream, int start, int end, bool skipMultipleFive);
PacketReturnData readPacket(char *stream, int start, int length);

int main() {
    int streamLength = 0;
    char stream[MAXN], *binaryNumber;
    char tmp;
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        if (input.peek() == '\n') break;

        input.get(tmp);
        binaryNumber = hexToBinary(tmp);

        for (int i = 0; i < 4; i++) {
            stream[streamLength++] = binaryNumber[i];
        }
    }

    PacketReturnData packetData = readPacket(stream, 0, streamLength);

    output << packetData.sumVersion << endl;
    output << packetData.result << endl;

    input.close();
    output.close();

    return 0;
}

char *hexToBinary(char hex) {
    char *binary = (char*) malloc(4 * sizeof(char));
    int decimal = 0;

    if (hex >= '0' && hex <= '9') {
        decimal = hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        decimal = 10 + hex - 'A';
    }

    for (int i = 0; i < 4; i++) {
        binary[i] = (decimal & (int) pow(2, 3 - i)) ? '1' : '0';
    }

    return binary;
}

long binaryRangeToDecimal(char *stream, int start, int end, bool skipMultipleFive) {
    long number = 0;

    for (int i = start; i <= end; i++) {
        if (stream[i] == '1' && (!skipMultipleFive || (end - i + 1) % 5 != 0)) {
            number += pow(2, end - i - (skipMultipleFive ? ((end - i + 1) / 5) : 0));
        }
    }

    return number;
}

PacketReturnData readPacket(char *stream, int start, int length) {
    int version = binaryRangeToDecimal(stream, start + 0, start + 2, false);
    int typeId = binaryRangeToDecimal(stream, start + 3, start + 5, false);
    int headerLength = 0;

    if (typeId == 4) {
        headerLength = start + 5;

        int pos = headerLength + 1;

        while (stream[pos] == '1') {
            pos += 5;
        }

        return PacketReturnData{
            .lastBitIndex = pos + 4,
            .sumVersion = version,
            .result = binaryRangeToDecimal(stream, headerLength + 1, pos + 4, true)
        };
    } else {
        int lengthTypeId = binaryRangeToDecimal(stream, start + 6, start + 6, false);
        int packetsLength = 0;

        if (lengthTypeId == 0) {
            packetsLength = binaryRangeToDecimal(stream, start + 7, start + 7 + 14, false);
            headerLength = start + 5 + 1 + 15;
        } else {
            packetsLength = binaryRangeToDecimal(stream, start + 7, start + 7 + 10, false);
            headerLength = start + 5 + 1 + 11;
        }

        PacketReturnData subpackets[1000];
        int packetIndex = 0;
        int pos = headerLength + 1;
        int sumVersion = version;

        while ((lengthTypeId == 0 && (headerLength + packetsLength) > pos) || (lengthTypeId == 1 && packetIndex < packetsLength)) {
            subpackets[packetIndex] = readPacket(stream, pos, length);
            pos = subpackets[packetIndex].lastBitIndex + 1;
            sumVersion += subpackets[packetIndex].sumVersion;
            packetIndex++;
        }

        pos = lengthTypeId == 0 ? headerLength + packetsLength : pos - 1;

        long result = 0;

        if (typeId == 0) {
            result = 0;
            
            for (int i = 0; i < packetIndex; i++) {
                result += subpackets[i].result;
            }
        } else if (typeId == 1) {
            result = 1;

            for (int i = 0; i < packetIndex; i++) {
                result *= subpackets[i].result;
            }
        } else if (typeId == 2 || typeId == 3) {
            result = typeId == 2 ? LONG_MAX : 0;

            for (int i = 0; i < packetIndex; i++) {
                if ((typeId == 2 && subpackets[i].result < result) || (typeId == 3 && subpackets[i].result > result)) {
                    result = subpackets[i].result;
                }
            }
        } else if (typeId > 4) {
            bool compareResult = false;

            if (typeId == 5) {
                compareResult = subpackets[0].result > subpackets[1].result;
            } else if (typeId == 6) {
                compareResult = subpackets[0].result < subpackets[1].result;
            } else if (typeId == 7) {
                compareResult = subpackets[0].result == subpackets[1].result;
            }

            result = compareResult ? 1 : 0;
        }

        return PacketReturnData{
            .lastBitIndex = pos,
            .sumVersion = sumVersion,
            .result = result,
        };
    }
}

#include "EightPuzzle.h"

const int puzzleSize = 3;

Node EightPuzzle::shiftBlankLeft(Node puzzleNode) { // find the blank in the puzzle and swap it with the number on the left
    int zeroRow;
    int zeroColumn;

    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (puzzleNode.state[i][j] == 0) {
                zeroRow = i;
                zeroColumn = j;
            }
        }
    }

    if (zeroColumn > 0) { // make sure the shift left is valid
        swap(puzzleNode.state[zeroRow][zeroColumn], puzzleNode.state[zeroRow][zeroColumn - 1]);
    }

    return puzzleNode;
}

Node EightPuzzle::shiftBlankRight(Node puzzleNode) { // find the blank in the puzzle and swap it with the number on the right
    int zeroRow;
    int zeroColumn;

    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (puzzleNode.state[i][j] == 0) {
                zeroRow = i;
                zeroColumn = j;
            }
        }
    }

    if (zeroColumn < (puzzleSize - 1)) { // make sure the shift right is valid
        swap(puzzleNode.state[zeroRow][zeroColumn], puzzleNode.state[zeroRow][zeroColumn + 1]);
    }

    return puzzleNode;
}

Node EightPuzzle::shiftBlankUp(Node puzzleNode) { // find the blank in the puzzle and swap it with the number above
    int zeroRow;
    int zeroColumn;

    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (puzzleNode.state[i][j] == 0) {
                zeroRow = i;
                zeroColumn = j;
            }
        }
    }

    if (zeroRow > 0) { // make sure the shift up is valid
        swap(puzzleNode.state[zeroRow][zeroColumn], puzzleNode.state[zeroRow - 1][zeroColumn]);
    }

    return puzzleNode;
}

Node EightPuzzle::shiftBlankDown(Node puzzleNode) { // find the blank in the puzzle and swap it with the number below
    int zeroRow;
    int zeroColumn;

    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (puzzleNode.state[i][j] == 0) {
                zeroRow = i;
                zeroColumn = j;
            }
        }
    }

    if (zeroRow < (puzzleSize - 1)) { // make sure the shift down is valid
        swap(puzzleNode.state[zeroRow][zeroColumn], puzzleNode.state[zeroRow + 1][zeroColumn]);
    }

    return puzzleNode;
}
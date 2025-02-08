#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    static const int puzzleSize = 3;

    int state[puzzleSize][puzzleSize];

    int gCost;
    int hCost;

    Node(int inputState[puzzleSize][puzzleSize], int g, int h) : gCost(g), hCost(h) {
        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                state[i][j] = inputState[i][j];
            }
        }
    }

    int fCost() const {
        return gCost + hCost;
    }

    bool operator>(const Node &other) const { // for priority queue
        return fCost() > other.fCost();
    }

    void printState() { // prints the state of the puzzle
        cout << "-----" << endl;
        
        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                cout << state[i][j] << " ";
            }
            cout << endl;
        }
        
        cout << "-----" << endl;
    }

    bool operator<(const Node &other) const {
        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                if (state[i][j] != other.state[i][j]) {
                    return state[i][j] < other.state[i][j];
                }
            }
        }
        return false;
    }
  
private:
};

struct CompareNode { // lets the set in main store unique states of the puzzle
    bool operator()(const Node &a, const Node &b) const { // use < operator in Node class
        return a < b;
    }
};

class EightPuzzle {
public:
    Node shiftBlankLeft(Node puzzleNode);

    Node shiftBlankRight(Node puzzleNode);

    Node shiftBlankUp(Node puzzleNode);

    Node shiftBlankDown(Node puzzleNode);
  
private:
};

#endif
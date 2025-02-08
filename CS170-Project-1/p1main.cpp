#include <iostream>
#include <string>
#include <queue>
#include <set>

#include "EightPuzzle.h"

using namespace std;

const int puzzleSize = 3;

Node generalSearch(int initialState[puzzleSize][puzzleSize], int algorithmChoice, int goalState[puzzleSize][puzzleSize]);

bool isGoalState(int currState[puzzleSize][puzzleSize], int goalState[puzzleSize][puzzleSize]);

vector<Node> expand(const Node &currNode);

int misplacedTile(int currState[puzzleSize][puzzleSize], int goalState[puzzleSize][puzzleSize]);

int manhattanDistance(int currState[puzzleSize][puzzleSize], int goalState[puzzleSize][puzzleSize]);

int main() {
    // get input from the user
    int userInitialState[puzzleSize][puzzleSize] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
    };

    int trivial[puzzleSize][puzzleSize] = { // solved (goal state)
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
    };

    int veryEasy[puzzleSize][puzzleSize] = { // difficulty 2
    {1, 2, 3},
    {4, 5, 6},
    {7, 0, 8}
    };

    int easy[puzzleSize][puzzleSize] = { // difficulty 3
    {1, 2, 0},
    {4, 5, 3},
    {7, 8, 6}
    };

    int doable[puzzleSize][puzzleSize] = { // difficulty 4
    {0, 1, 2},
    {4, 5, 3},
    {7, 8, 6}
    };

    int ohBoy[puzzleSize][puzzleSize] = { // difficulty 5
    {8, 7, 1},
    {6, 0, 2},
    {5, 4, 3}
    };

    cout << "Welcome to my CS170 8 slide puzzle solver. Type '1' to use a default puzzle, or '2' to create your own." << endl;
    int userChoice = 0;
    cin >> userChoice;

    if (userChoice == 1) { // have user select a premade puzzle
        cout << "You wish to use a default puzzle. Please enter a desired difficulty on a scale from 1 to 5." << endl;
        cin >> userChoice;

        if (userChoice == 1) { // trivial puzzle
            for (int i = 0; i < puzzleSize; ++i) {
                for (int j = 0; j < puzzleSize; ++j) {
                    userInitialState[i][j] = trivial[i][j];
                }
            }
        }
        if (userChoice == 2) { // veryEasy puzzle
            for (int i = 0; i < puzzleSize; ++i) {
                for (int j = 0; j < puzzleSize; ++j) {
                    userInitialState[i][j] = veryEasy[i][j];
                }
            }
        }
        if (userChoice == 3) { // easy puzzle
            for (int i = 0; i < puzzleSize; ++i) {
                for (int j = 0; j < puzzleSize; ++j) {
                    userInitialState[i][j] = easy[i][j];
                }
            }
        }
        if (userChoice == 4) { // doable puzzle
            for (int i = 0; i < puzzleSize; ++i) {
                for (int j = 0; j < puzzleSize; ++j) {
                    userInitialState[i][j] = doable[i][j];
                }
            }
        }
        if (userChoice == 5) { // ohBoy puzzle
            for (int i = 0; i < puzzleSize; ++i) {
                for (int j = 0; j < puzzleSize; ++j) {
                    userInitialState[i][j] = ohBoy[i][j];
                }
            }
        }
    }
    else if (userChoice == 2) { // have user enter their own puzzle
        cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8 puzzles." << endl;
        cout << "Type the number, then enter after each number." << endl;

        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                cin >> userInitialState[i][j];
            }
        }

        // cout << "The puzzle you entered was: " << endl;
    }

    cout << "The puzzle you chose is: " << endl;
    Node userPuzzle(userInitialState, 0, 0);
    userPuzzle.printState();

    cout << "Select the search algorithm you would like to use: (1) Uniform Cost Search, (2) A* with the Misplaced Tile Heuristic, (3) A* with the Manhattan Distance Heuristic." << endl;
    cin >> userChoice;

    Node solutionNode(userInitialState, 0, 0);

    // call the search function passing in different arguments depending on the input
    if (userChoice == 1) {
        cout << "Here's the Uniform Cost Search algorithm on your puzzle:" << endl;
        solutionNode = generalSearch(userInitialState, userChoice, trivial);
    }
    else if (userChoice == 2) {
        cout << "Here's the A* algorithm with the Misplaced Tile Heuristic on your puzzle:" << endl;
        solutionNode = generalSearch(userInitialState, userChoice, trivial);
    }
    else if (userChoice == 3) {
        cout << "Here's the A* algorithm with the Manhattan Distance Heuristic on your puzzle:" << endl;
        solutionNode = generalSearch(userInitialState, userChoice, trivial);
    }

    solutionNode.printState();

    // remember Uniform Search is the same as A* but with h(n) hard coded to 0

    return 0;
}

Node generalSearch(int initialState[puzzleSize][puzzleSize], int algorithmChoice, int goalState[puzzleSize][puzzleSize]) { // calls Uniform and A*
    priority_queue<Node, vector<Node>, greater<Node>> nodes; // make a priority queue of nodes
    set<Node> visited; // keep track of the visited states of the puzzle
    
    int hCost = 0; // hardcoded value of h(n) for Unifrom Cost Search
    int numNodesExpanded = 0;
    int maxQueueSize = 0;
    
    // cout << "ALGORITHM CHOICE: " << algorithmChoice << endl; // TESTING

    if (algorithmChoice == 2) {
        hCost = misplacedTile(initialState, goalState);
    }
    else if (algorithmChoice == 3) {
        hCost = manhattanDistance(initialState, goalState);
    }
    
    // nodes.push(Node(initialState, 0, hCost)); // nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    Node initialNode(initialState, 0, hCost);
    nodes.push(initialNode);
    visited.insert(initialNode);

    while (!nodes.empty()) // loop do
    {
        maxQueueSize = max(maxQueueSize, (int)nodes.size());

        Node topNode = nodes.top(); // node = REMOVE-FRONT(nodes)
        nodes.pop();

        ++numNodesExpanded;

        // cout << "ALGORITHM CHOICE: " << algorithmChoice << endl; // TESTING

        cout << "The best state to expand with g(n) = " << topNode.gCost << " and h(n) = " << topNode.hCost << " is: " << endl;
        topNode.printState();

        if (isGoalState(topNode.state, goalState)) { // if problem.GOAL-TEST(node.STATE) succeeds then return node
            // output statistics
            cout << "Goal state!" << endl;
            cout << "Number of nodes expanded: " << numNodesExpanded << endl;
            cout << "Solution depth was: " << topNode.gCost << endl;
            cout << "Max queue size: " << maxQueueSize << endl;
            return topNode;
        }

        vector<Node> expandedNodes = expand(topNode); // nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
        for (Node &child : expandedNodes) { // push all expanded nodes to the queue
            if (visited.find(child) == visited.end()) { // check if state is new
                int newGCost = topNode.gCost + 1;
                int newHCost = 0;

                if (algorithmChoice == 2) {
                    newHCost = misplacedTile(child.state, goalState);
                }
                else if (algorithmChoice == 3) {
                    newHCost = manhattanDistance(child.state, goalState);
                }

                // nodes.push(Node(child.state, newGCost, newHCost));
                Node newNode(child.state, newGCost, newHCost);
                nodes.push(newNode);
                visited.insert(newNode); // mark node as visited
            }
        }
    }

    throw runtime_error("No solution found"); // if EMPTY(nodes) return failure
    
}

bool isGoalState(int currState[puzzleSize][puzzleSize], int goalState[puzzleSize][puzzleSize]) {
    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (currState[i][j] != goalState[i][j]) {
                return false;
            }
        }
    }

    return true; // the 2d arrays are equal
}

vector<Node> expand(const Node &currNode) { // generate new states of the puzzle
    vector<Node> children;
    EightPuzzle puzzle;

    // call every shift operator on the passed in node
    children.push_back(puzzle.shiftBlankDown(currNode));
    children.push_back(puzzle.shiftBlankLeft(currNode));
    children.push_back(puzzle.shiftBlankRight(currNode));
    children.push_back(puzzle.shiftBlankUp(currNode));

    return children;
}

int misplacedTile(int currState[puzzleSize][puzzleSize], int goalState[puzzleSize][puzzleSize]) {
    int numMisplacedTiles = 0;

    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (currState[i][j] != goalState[i][j]) { // found a misplaced tile
                ++numMisplacedTiles;
            }
        }
    }

    // cout << "MISPLACED TILES: " << numMisplacedTiles << endl; // TESTING

    if (numMisplacedTiles <= 0) { // puzzle matches the goal state
        return numMisplacedTiles;
    }
    else {
        return numMisplacedTiles - 1; // - 1 to account for the blank tile
    }
}

int manhattanDistance(int currState[puzzleSize][puzzleSize], int goalState[puzzleSize][puzzleSize]) {
    int totalDistance = 0;

    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (currState[i][j] != 0) { // for every tile in the puzzle that's not the blank
                int targetRow = 0;
                int targetColumn = 0;

                for (int x = 0; x < puzzleSize; ++x) {
                    for (int y = 0; y < puzzleSize; ++y) {
                        if (currState[i][j] == goalState[x][y]) { // find where the tile is supposed to be
                            targetRow = x;
                            targetColumn = y;
                        }
                    }
                }

                totalDistance += abs(i - targetRow) + abs(j - targetColumn); // calculate the manhattan distance
            }
        }
    }

    // cout << "TOTAL DISTANCE: " << totalDistance << endl; // TESTING

    return totalDistance;
}
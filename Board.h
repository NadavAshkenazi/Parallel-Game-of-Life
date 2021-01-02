#ifndef OS_HW3_BOARD_H
#define OS_HW3_BOARD_H

#endif //OS_HW3_BOARD_H
#include "vector"
#include "string"

using namespace std;

class Board{
    unsigned int weight;
    unsigned int height;
    vector<vector<int>> matrix;

public:
    Board(const string& filename);
    ~Board();
    bool isAlive(int i, int j);
    int getSpecies(int i, int j);
    int setSpecies(int i, int j, int species);
    int getHeight();
    int getWeight();
    int calcNewSpecies(int i, int j);
    int dominantSpeciesInNeighborhood(int i, int j);
    int getAliveCellsInNeighborhood(int i, int j);
    friend ostream& operator<<(ostream& os, const Board& board);
};
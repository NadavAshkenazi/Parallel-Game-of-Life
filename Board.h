#ifndef OS_HW3_BOARD_H
#define OS_HW3_BOARD_H

#include "vector"
#include "string"

using namespace std;

class neighborhoodBorders{
public:
    int left;
    int right;
    int down;
    int up;
};

class Board{
    unsigned int width;
    unsigned int height;
    vector<vector<int>*>* matrix;
    neighborhoodBorders _getNeighborhoodBorders(int i, int j);
    bool isNeighbor(int cellI, int cellJ, int iForCheck, int jForCheck);
public:
    Board(const string& filename);
    ~Board();
    bool isAlive(int i, int j);
    int getSpecies(int i, int j);
    void setSpecies(int i, int j, int species);
    int getHeight();
    int getWidth();
    int getAliveCellsInNeighborhood(int i, int j); //excludes [i,j]
    int calcNewSpecies(int i, int j); //includes [i,j]
    int dominantSpeciesInNeighborhood(int i, int j); //returns 0 if all dead
};

#endif //OS_HW3_BOARD_H

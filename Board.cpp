#include "Board.h"
#include "utils.hpp"
#include "map"

using namespace utils;

# define NEIGHBORHOOD_DIST 1

Board::Board(const string& filename){
    vector<string> temp = read_lines(filename);
    this->height = temp.size();
    vector<vector<string>> tempBoard;
    vector<string>::iterator it;
    for(it = temp.begin(); it != temp.end(); ++it){
        tempBoard.push_back(split(*it, ' '));
    }
    this->width = tempBoard[0].size();
    vector<vector<string>>::iterator it2;
    this->matrix = new vector<vector<int>*>;
    for(it2 = tempBoard.begin(); it2 != tempBoard.end(); ++it2){
        vector<int>* tempVec = new vector<int>;
        for(it = it2->begin(); it != it2->end(); ++it){
            tempVec->push_back(stoi(*it));
        }
        this->matrix->push_back(tempVec);
    }
}

Board::~Board(){
    vector<vector<int>*>::iterator it;
    for(int i = 0; i < height; i++) {
        vector<int>* tempVec = matrix->back();
        matrix->pop_back();
        delete tempVec;
    }
    delete matrix;
}

int Board::getSpecies(int i, int j){
    return (*(*this->matrix)[i])[j];
}

bool Board::isAlive(int i, int j){
    if (getSpecies(i,j) > 0 )
        return true;
    return false;
}

void Board::setSpecies(int i, int j, int species){
    (*(*this->matrix)[i])[j] = species;
}

int Board::getHeight(){
    return this->height;
}

int Board::getWidth(){
    return this->width;
}

// TODO: maybe change Neighborhood to star (not square)
/**
 * checks if a given cell is a neighbor of another
 * will work only when checking within neighborhoods borders
 * @param cellI - i of the cell defining the neighborhood
 * @param cellJ - j of the cell defining the neighborhood
 * @param iForCheck
 * @param jForCheck
 * @return True if neighbors, false otherwise
 */
bool Board::isNeighbor(int cellI, int cellJ, int iForCheck, int jForCheck){
    if (cellI == iForCheck || cellJ == jForCheck)
        return true;
    if (abs(cellI - iForCheck) == abs(cellJ - jForCheck))
        return true;
    return false;
}


neighborhoodBorders Board::_getNeighborhoodBorders(int i, int j){
    neighborhoodBorders n = neighborhoodBorders();
    n.left = (j - NEIGHBORHOOD_DIST) >= 0 ? (j-NEIGHBORHOOD_DIST) : 0;
    n.right = (j + NEIGHBORHOOD_DIST) < width ? (j+NEIGHBORHOOD_DIST) : width-1;
    n.up = (i-NEIGHBORHOOD_DIST) >= 0 ? (i-NEIGHBORHOOD_DIST) : 0;
    n.down = (i+NEIGHBORHOOD_DIST) < height ? (i+NEIGHBORHOOD_DIST) : height-1;
    return n;
}

int Board::getAliveCellsInNeighborhood(int i, int j){
    neighborhoodBorders n = _getNeighborhoodBorders(i, j);
    int aliveInNeighborhood = 0;
    for (int k = n.up; k <= n.down; k++){
        for (int m = n.left; m <= n.right; m++){
            if (isNeighbor(i,j,k,m))
                aliveInNeighborhood += isAlive(k,m);
        }
    }
    if (isAlive(i,j)){
        aliveInNeighborhood--;
    }
    return aliveInNeighborhood;
}

int Board::calcNewSpecies(int i, int j){
    double aliveInNeighborhood = isAlive(i,j) ? getAliveCellsInNeighborhood(i,j) + 1 : getAliveCellsInNeighborhood(i,j);
    double speciesSum = 0;
    neighborhoodBorders n = _getNeighborhoodBorders(i, j);
    for (int k = n.up; k <= n.down; k++){
        for (int m = n.left; m <= n.right; m++){
            if (isNeighbor(i,j,k,m))
                speciesSum += getSpecies(k,m);
        }
    }
    double newSpecies = speciesSum/aliveInNeighborhood;
//    cout << "no round: " << newSpecies << " round: " << std::round(newSpecies) << endl;
    return std::round(newSpecies);

}

int Board::dominantSpeciesInNeighborhood(int i, int j){
    neighborhoodBorders n = _getNeighborhoodBorders(i, j);
    std::map<int,int> species = std::map<int,int>();
    for (int k = n.up; k <= n.down; k++){
        for (int m = n.left; m <= n.right; m++){
            if (isNeighbor(i,j,k,m) && isAlive(k,m)) {
                if (species.find(getSpecies(k, m)) != species.end()) {
                    species[getSpecies(k, m)]++;
                } else {
                    species[getSpecies(k, m)] = 1;
                }
            }
        }
    }
    int dominantSpecies = 0;
    int maxElements = 0;

    std::map<int,int>::iterator it;
    for(it = species.begin(); it != species.end(); ++it){
        if (maxElements * dominantSpecies < it->first*it->second){
            dominantSpecies = it->first;
            maxElements = it->second;
        }
        else if (maxElements == it->second){
            dominantSpecies = min(it->first, dominantSpecies);
            maxElements = species[dominantSpecies];
        }
    }
//    cout << "dominant species: " << dominantSpecies << endl; //todo:: delete
    return dominantSpecies;
}

void Board::clear(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            setSpecies(i,j,DEAD);
        }
    }
}

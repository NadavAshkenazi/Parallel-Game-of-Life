#include "Board.h"
#include "utils.hpp"
#include "map"

using namespace utils;

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

neighborhood Board::_getNeighborhood(int i, int j){
    neighborhood n = neighborhood();
    n.left = (j-8) >= 0 ? (j-8) : 0;
    n.right = (j+8) < width ? (j+8) : width-1;
    n.up = (i-8) >= 0 ? (i-8) : 0;
    n.down = (i+8) < height ? (i+8) : height-1;
    return n;
}
int Board::getAliveCellsInNeighborhood(int i, int j){
    neighborhood n = _getNeighborhood(i,j);
    int aliveInNeighborhood = 0;
    for (int k = n.up; k <= n.down; k++){
        for (int m = n.left; m <= n.right; m++){
            aliveInNeighborhood += isAlive(k,m);
        }
    }
    if (isAlive(i,j)){
        aliveInNeighborhood--;
    }
    return aliveInNeighborhood;
}

int Board::calcNewSpecies(int i, int j){
    int aliveInNeighborhood = isAlive(i,j) ? getAliveCellsInNeighborhood(i,j) + 1 : getAliveCellsInNeighborhood(i,j);
    int speciesSum = 0;
    neighborhood n = _getNeighborhood(i,j);
    for (int k = n.down; k <= n.up; k++){
        for (int m = n.left; m <= n.right; m++){
            speciesSum += getSpecies(k,m);
        }
    }
    double newSpecies = speciesSum/aliveInNeighborhood;
    return std::round(newSpecies);
}

int Board::dominantSpeciesInNeighborhood(int i, int j){
    neighborhood n = _getNeighborhood(i,j);
    std::map<int,int> species = std::map<int,int>();
    for (int k = n.down; k <= n.up; k++){
        for (int m = n.left; m <= n.right; m++){
           if (species.find(getSpecies(i,j)) != species.end()){
               species[getSpecies(i,j)]++;
           }
           else{
               species[getSpecies(i,j)] = 1;
           }
        }
    }
    int dominantSpecies = 0;
    int maxElements = 0;

    std::map<int,int>::iterator it;
    for(it = species.begin(); it != species.end(); ++it){
        if (maxElements < it->second){
            dominantSpecies = it->first;
            maxElements = it->second;
        }
        else if (maxElements == it->second){
            dominantSpecies = min(it->first, dominantSpecies);
            maxElements = species[dominantSpecies];
        }
    }
    return dominantSpecies;
}

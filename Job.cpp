#include "Job.h"
#include <unistd.h>
#include <sys/syscall.h>

Job::Job(Board* currentBoard, Board* nextBoard, int rowStart, int rowEnd) : _currentBoard(currentBoard), _nextBoard(nextBoard),
                                                                            _rowStart(rowStart), _rowEnd(rowEnd) {}

AliveJob::AliveJob(Board* currentBoard, Board* nextBoard, int rowStart, int rowEnd) : Job(currentBoard, nextBoard, rowStart, rowEnd) {}
void AliveJob::execute(Thread* thread) {
    /*
    int aliveNeigborsNum;
    for (int i = _rowStart; i <= _rowEnd; i++) { // go over this job lines
        for (int j = 0; j < _currentBoard->getWidth(); j++) { // go over one line
            aliveNeigborsNum = _currentBoard->getAliveCellsInNeighborhood(i, j);
            if (_currentBoard->isAlive(i, j)) { // alive cell
                if (aliveNeigborsNum == 2 || aliveNeigborsNum == 3) {
                    _nextBoard->setSpecies(i, j, _currentBoard->getSpecies(i, j));
                } else {
                    _nextBoard->setSpecies(i, j, DEAD);
                }
            } else { // dead cell
                if (aliveNeigborsNum == 3) {
                    _nextBoard->setSpecies(i, j, _currentBoard->dominantSpeciesInNeighborhood(i, j));
                } else {
                    _nextBoard->setSpecies(i, j, DEAD);
                }
            }
        }
    } */
    //sleep(5);
    std::cout << "working on Job Alive, my pid:  " << syscall(SYS_gettid) << endl;
    return;
}

SpeciesJob::SpeciesJob(Board* currentBoard, Board* nextBoard, int rowStart, int rowEnd) : Job(currentBoard, nextBoard, rowStart, rowEnd) {}
void SpeciesJob::execute(Thread* thread) {
    /*
    for (int i = _rowStart; i <= _rowEnd; i++) { // go over this job lines
        for (int j = 0; j < _currentBoard->getWidth(); j++) { // go over one line
            if (_currentBoard->isAlive(i, j)){
                _nextBoard->setSpecies(i, j, _currentBoard->calcNewSpecies(i,j));
            }
        }
    } */

    std::cout << "working on Job Species, my pid:  " << syscall(SYS_gettid) << endl;
    //sleep(5);
    return;
}

KillThreadJob::KillThreadJob(): Job(NULL, NULL, NULL, NULL) {}
void KillThreadJob::execute(Thread* thread) {
    thread->exit();
}

/*
ostream& operator<<(ostream& os, const Job& job){
    os << job._rowStart << job._rowEnd << endl;
    return os;
} */
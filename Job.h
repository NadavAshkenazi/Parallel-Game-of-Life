#ifndef OS_HW3_JOB_H
#define OS_HW3_JOB_H

#include "Board.h"
#define DEAD 0

class Job {
    public:
        Job (Board*, Board*, int, int);
        virtual ~Job() {};
        virtual void execute() = 0;

        Board* _currentBoard;
        Board* _nextBoard;
        int _rowStart;
        int _rowEnd;
};

class AliveJob : public Job {
public:
    AliveJob (Board*, Board*, int, int);
    void execute();
};

class SpeciesJob : public Job {
public:
    SpeciesJob (Board*, Board*, int, int);
    void execute();
};

class KillThreadJob : public Job {
public:
    KillThreadJob ();
    void execute(); // exit(0)
};

#endif //OS_HW3_JOB_H

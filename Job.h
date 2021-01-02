#ifndef OS_HW3_JOB_H
#define OS_HW3_JOB_H

#include "Board.h"

class Job {
    public:
        Job (Board*, Board*, int, int);
        virtual ~Job() {};
        virtual void execute() = 0;

        Board* _currentBoard;
        Board* _next_Board;
        int _rowStart;
        int _rowEnd;
};

class AliveJob : public Job {
    AliveJob (Board*, Board*, int, int);
    void execute();
};

class SpeciesJob : public Job {
    SpeciesJob (Board*, Board*, int, int);
    void execute();
};

class KillThreadJob : public Job {
    KillThreadJob (Board*, Board*, int, int);
    void execute(); // exit(0)
};



#endif //OS_HW3_JOB_H

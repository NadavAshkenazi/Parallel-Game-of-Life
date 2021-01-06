#ifndef OS_HW3_JOB_H
#define OS_HW3_JOB_H

#include "Board.h"
#include "Headers.hpp"
#include "Thread.hpp"

class Job {
    public:
        Job (Board*, Board*, int, int);
        virtual ~Job() {};
        virtual void execute(Thread* thread) = 0;
        friend ostream& operator<<(ostream& os, const Job& job); // for debug

        Board* _currentBoard;
        Board* _nextBoard;
        int _rowStart;
        int _rowEnd;

        string jobLind; // for debug
};

class AliveJob : public Job {
public:
    AliveJob (Board*, Board*, int, int);
    void execute(Thread* thread);
};

class SpeciesJob : public Job {
public:
    SpeciesJob (Board*, Board*, int, int);
    void execute(Thread* thread);
};

class KillThreadJob : public Job {
public:
    KillThreadJob ();
    void execute(Thread* thread); // exit(0)
};


#endif //OS_HW3_JOB_H

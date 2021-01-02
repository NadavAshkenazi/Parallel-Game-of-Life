#include <iostream>
#include "Job.h"
#include "Board.h"
#include "Game.hpp"

static inline game_params parse_input_args(int argc, char **argv) {

    if (argc != 6) // ./gameoflife filename.txt 100 20 Y Y
        cout<< "Wrong number of arguments - expected 5" << endl;

    game_params g;
    g.filename = argv[1];
    g.n_gen = strtoul(argv[2], NULL, 10);
    g.n_thread = strtoul(argv[3], NULL, 10);

    string inter = string(argv[4]);
    string print = string(argv[5]);
    g.interactive_on = (inter == "y" || inter == "Y") ? true : false;
    g.print_on = (print == "y" || print == "Y") ? true : false;

    if (g.n_gen <= 0 || g.n_thread <= 0)
        cout << "Invalid number of generations/number of threads (Required: integer >0)" << endl;
    return g;
}


int main(int argc, char **argv) {

    game_params params = parse_input_args(argc, argv);
    string filename = params.filename;
    Board* startBoard = new Board(filename);
    Board* nextBoard = new Board(filename);

    AliveJob* job1 = new AliveJob(startBoard, nextBoard, 0 ,startBoard->getHeight() -1);
    job1->execute();


    return 0;
}


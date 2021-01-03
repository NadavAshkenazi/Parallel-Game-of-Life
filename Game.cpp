#include "Game.hpp"


static const char *colors[7] = {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};
/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
void Game::run() {

	_init_game(); // Starts the threads and all other variables you need
	//print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i) {
		//auto gen_start = std::chrono::system_clock::now();
		_step(phase1); // Iterates a single generation
        //_step(phase2);
		//auto gen_end = std::chrono::system_clock::now();
		//m_gen_hist.push_back((double)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		//print_board(nullptr);
	} // generation loop
	//print_board("Final Board");
	//_destroy_game();
}

void Game::_init_game() {
	// Create game fields - Consider using utils:read_file, utils::split // no need- we create them in the game constructor
	//calcTiles();
	/* TODO: delete. debug tiles calc
	for (auto i = tilesStratRow.begin() ; i!= tilesStratRow.end() ; i++){
        cout << *i << endl;
    } */
	// Create & Start threads
	for (int i=0 ; i< m_thread_num; i++){
        m_threadpool.push_back(new ThreadGame(i, &jobQueue, &waitForThreads));
        m_threadpool[i]->start();
	}
	// Testing of your implementation will presume all threads are started here
}

void Game::_step(Phase phase) {
	// Push jobs to queue - Phase1
	/*
    for (auto i = tilesStratRow.begin() ; i != tilesStratRow.end() ; i++){
        int rowEnd = i+1 != tilesStratRow.end() ? *(i+1)-1 : currentBoard->getHeight()-1;
        //cout << "start= " << *i << " end= " << rowEnd<< endl; // TODO: delete
        if (phase== phase1)
            jobQueue.push(new AliveJob(currentBoard, nextBoard, *i, rowEnd));
        if (phase== phase2)
            jobQueue.push(new SpeciesJob(currentBoard, nextBoard, *i, rowEnd));
    }*/
    for (int i=0 ; i< m_thread_num; i++) { // TODO: delete, debug
        jobQueue.push(new AliveJob(currentBoard, nextBoard, 0, 0));
    }
    // Wait for the workers to finish calculating
    for (int i=0 ; i< m_thread_num; i++) {
        waitForThreads.down();
    }
    cout << "All threads are finished " << endl; // TODO: delete, debug
	// Swap pointers between current and next field
//    Board* temp = currentBoard;
//	currentBoard = nextBoard;
//    nextBoard = temp;
	// NOTE: Threads must not be started here - doing so will lead to a heavy penalty in your grade 
}

void Game::_destroy_game(){
	// Destroys board and frees all threads and resources
    delete currentBoard;
    delete nextBoard;
	// Not implemented in the Game's destructor for testing purposes.
	// All threads must be joined here
    for (int i=0 ; i< m_thread_num; i++){ // to make the threads finish
            jobQueue.push(new KillThreadJob());
    }
	for (uint i = 0; i < m_thread_num; ++i) { // kill the threads
        m_threadpool[i]->join();
    }
    cout << "All threads are joined " << endl; // TODO: delete, debug
}

/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
inline void Game::print_board(const char* header) {

	if(print_on){ 

		// Clear the screen, to create a running animation 
		if(interactive_on)
			system("clear");

		// Print small header if needed
		if (header != nullptr)
			cout << "<------------" << header << "------------>" << endl;
		
		// TODO: Print the board 

		// Display for GEN_SLEEP_USEC micro-seconds on screen 
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);
	}

}


/* Function sketch to use for printing the board. You will need to decide its placement and how exactly 
	to bring in the field's parameters. 

		cout << u8"╔" << string(u8"═") * field_width << u8"╗" << endl;
		for (uint i = 0; i < field_height ++i) {
			cout << u8"║";
			for (uint j = 0; j < field_width; ++j) {
                if (field[i][j] > 0)
                    cout << colors[field[i][j] % 7] << u8"█" << RESET;
                else
                    cout << u8"░";
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * field_width << u8"╝" << endl;
*/

Game::ThreadGame::ThreadGame(uint thread_id, PCQueue<Job*>* jobQueue, Semaphore* waitForThreads) : Thread(thread_id), jobQueue(jobQueue)
                                                                                                   ,waitForThreads(waitForThreads) {}
void Game::ThreadGame::thread_workload() {
    while (1){
        Job* job = jobQueue->pop();
        //auto gen_start = std::chrono::system_clock::now();
        job->execute(this);
        //auto gen_end = std::chrono::system_clock::now();
        //m_tile_hist.push_back((double)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
        delete job;
        waitForThreads->up();
    }
//    pop job from queue
//    start timer
//    execute job
//    stop timer
//    append duration to shared tile history vector

}

Game::Game(game_params params){
    m_gen_num = params.n_gen;
    interactive_on = params.interactive_on;
    print_on = params.print_on;
    currentBoard = new Board(params.filename);
    nextBoard = new Board(params.filename);
    m_thread_num = params.n_thread > currentBoard->getHeight() ? currentBoard->getHeight() : params.n_thread;
}
Game::~Game() {
    delete currentBoard;
    delete nextBoard;
}
void Game::calcTiles() {
    int tileSize = currentBoard->getHeight() / m_thread_num;
    int startRow = 0;
    for (int i=0 ; i< m_thread_num; i++){
        tilesStratRow.push_back(startRow);
        startRow += tileSize;
    }
}

const vector<double> Game::gen_hist() const {}
const vector<double> Game::tile_hist() const {}
uint Game::thread_num() const {
    return m_thread_num;
}
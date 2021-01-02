cmake_minimum_required(VERSION 3.5.1)
project(os_hw3)

set(CMAKE_CXX_STANDARD 11)

# real executable
add_executable(os_hw3 main.cpp Semaphore.cpp Semaphore.hpp PCQueue.hpp utils.cpp Game.cpp Game.hpp utils.hpp Headers.hpp Job.cpp Job.h Board.h Board.cpp)  #test.cpp

# testing executables
# test Board
#add_executable(os_hw3 Board_Job_test.cpp utils.cpp Board.cpp Headers.hpp Job.cpp Job.h Board.h )
# test Smaphore and PCQ
#add_executable(os_hw3 Semaphore_PCQ_test.cpp utils.cpp Semaphore.cpp Semaphore.hpp PCQueue.hpp Headers.hpp)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(os_hw3 PRIVATE Threads::Threads)


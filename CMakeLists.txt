cmake_minimum_required(VERSION 3.5.1)
project(os_hw3)

set(CMAKE_CXX_STANDARD 11)
add_executable(os_hw3 Semaphore.cpp Semaphore.hpp PCQueue.hpp main.cpp utils.cpp Game.cpp Game.hpp utils.hpp Headers.hpp)  #test.cpp
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(os_hw3 PRIVATE Threads::Threads)


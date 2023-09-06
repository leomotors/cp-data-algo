mkdir -p bin
g++ grader/$1.cpp -o bin/$1 -std=c++17 -Wall -Wextra -D_GLIBCXX_DEBUG -DDEBUG
./bin/$1

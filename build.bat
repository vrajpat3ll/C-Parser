set CFLAGS=-Wall -Wextra

g++ %CFLAGS% "src/parser.cpp" -o build/run 
cls
"./build/run"
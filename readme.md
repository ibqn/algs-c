# Josephus problem

    gcc -O3 src/josephus-problem.c  -o josephus -Wall -pedantic -std=c11
    ./josephus 41 3

## Buld using cmake

    cmake -H. -Bbuild

This will create a `build` directory and generate there all the required files.

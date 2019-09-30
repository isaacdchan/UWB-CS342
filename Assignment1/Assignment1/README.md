# library

Library class that supports adding and removing books.

## Included Files

- `CMakeLists.txt`: For complex projects, `cmake CMakeLists.txt` will
  generate a `Makefile`. We can then use `make` to compile the
  project. Optional for a small project like this, but included as an
  example.

- `library.cpp`: Definitions for library functions

- `library.h`: Header file for library

- `main.cpp`: Runs all tests

- `output.txt`: Output from `./simple.compile.sh > output.txt 2>&1`
showing how the program is compiled and run

- `simplecompile.sh`: Unix bash script file to compile, run 
and then delete the executable. Can be used to create an output.txt file


## Compile and Run

```
./simplecompile.sh
```

or

```
g++ -std=c++14 -Wall -Wextra *.cpp -o ass1
./ass1
```

## Misc

This file is part of a repository located at
https://github.com/pisan342/ass1-starter

# TimeSpan

Goals: Understanding operator overloading

Design and implement TimeSpan class which represents a duration in hours,
minutes and seconds.
```$xslt
Displayed       Meaning
2:12:07         2 hours, 12 minutes, 7 seconds
-0:10:43        Minus 10 minutes and 43 seconds
```

The seconds and minutes have to be between 0 and 59.
The hours can be 0 to any number.
When TimeSpan is printed, the minutes and seconds (fixed 4/4) 
should always have 2 digits. 
The constructor for TimeSpan can take 0, 1, 2, or 3 parameters.
In addition to integer value, the constructor should also be able to handle double values and convert them as accurately as possible

```$xslt
TimeSpan(1.5, -10, 93)	same as 1:21:33
TimeSpan(1.5)		    same as 1:30:00
``` 

## Included Files

- `CMakeLists.txt`: For complex projects, `cmake CMakeLists.txt` will
  generate a `Makefile`. We can then use `make` to compile the
  project. Optional for a small project like this, but included as an
  example.

- `timespan.cpp`: Definitions for timespan functions

- `timespan.h`: Header file for timespan

- `main.cpp`: Runs all tests

- `output.txt`: Output from `./simple.compile.sh > output.txt 2>&1`
showing how the program is compiled and run.

- `simplecompile.sh`: Unix bash script file to compile, run 
and then delete the executable. Can be used to create an output.txt file


## Compile and Run

```
./simplecompile.sh
```

or

```
clang++ -std=c++14 -Wall -Wextra *.cpp -o ass2
./ass1
```


### Style Explanation
These options are defined in `.clang-tidy` file.

Perform all check except the following:

-fuchsia-* do not need specific checks for "fuchsia" a modular, capability-based operating system
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-readability-braces-around-statements: allow compact code without `{`
- readability-braces-around-statements: allow compact code without `{`
This option is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using 9.0.0
- hicpp-no-array-decay need to use assert
- modernize-use-trailing-return-type: not ready yet for `auto func() -> int` format
- hicpp-braces-around-statements: allow compact code without `{` (this option
- cppcoreguidelines-pro-bounds-pointer-arithmetic,
- llvm-header-guard: not using full directory name
- google-global-names-in-headers: for simplicity allow `using namespace std;`
- cppcoreguidelines-special-member-functions: not defining move operator
- hicpp-special-member-functions: not defining move operator
- cppcoreguidelines-owning-memory: not using gsl

## Misc

date

echo "*** compiling with g++ to create an executable called myprogram"
g++ --version
g++ -std=c++14 -Wall -Wextra -Wno-sign-compare *.cpp -g -o myprogram

echo "*** running clang-tidy using options from .clang-tidy"
clang-tidy --version
clang-tidy *.cpp -- -std=c++14

echo "*** running myprogram"
./myprogram

# valgrind will detect memory leaks
echo "*** running with valgrind"
valgrind ./myprogram BankTransIn.txt

echo "*** cleaning up, deleting myprogram"
rm myprogram

date
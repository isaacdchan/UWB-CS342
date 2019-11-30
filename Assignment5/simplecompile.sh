date

echo "*** compiling with clang++ to create an executable called myprogram"
clang++ --version
clang++ -std=c++14 -Wall -Wextra -Wno-sign-compare *.cpp -g -o myprogram

echo "*** running clang-tidy using options from .clang-tidy"
clang-tidy --version
clang-tidy *.cpp -- -std=c++14

echo "*** running myprogram"
./myprogram BankTransIn.txt

# valgrind will detect memory leaks
# echo "*** running with valgrind"
# valgrind ./myprogram BankTransIn.txtr

echo "*** cleaning up, deleting myprogram"
rm myprogram

date

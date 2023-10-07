#include <iostream>
#include <getopt.h>
#include "Error/Error.cpp"
#include "Arguments/Arguments.cpp"

int main(int argc, char *argv[]) {
    Arguments arg;
    arg.parse(argc, argv);

    std::cout << arg.r << "\n";
    std::cout << arg.x << "\n";
    std::cout << arg._6 << "\n";
    std::cout << arg.s << "\n";
    std::cout << arg.p << "\n";
    std::cout << arg.address << "\n";

    return 0;
}

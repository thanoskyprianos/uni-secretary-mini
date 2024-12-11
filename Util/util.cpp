#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef UTIL
#define UTIL
#include "util.h"
#endif

using std::cout;
using std::cin;

using std::istream;
using std::numeric_limits;
using std::streamsize;

void util::clear_buf(istream &str) {
    str.ignore(numeric_limits<streamsize>::max(), '\n');
}

void util::clear_screen() {
    printf("\033[1;1H\033[2J");
}

void util::clear_lines(unsigned int c) {
    cout << "\033[" << c << "A\033[2K";
}

void util::wait_for_enter() {
    cout << "Press enter to continue...";
    while(getchar() != '\n');
}
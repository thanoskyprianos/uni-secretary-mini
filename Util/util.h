#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef LIMITS
#define LIMITS
#include <limits>
#endif

using std::istream;

using std::string;

using std::numeric_limits;
using std::streamsize;

namespace util {
    
    const string CYAN = "\033[0;96m";
    const string RED = "\033[0;91m";
    const string GREEN = "\033[0;92m";
    const string RESET = "\033[0m";

    template <typename T>
    void cinWithClear(istream &str, T &dest) {
        str >> dest;
        str.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void clear_buf(istream &str);
    void clear_screen();
    void clear_lines(unsigned int c = 1);
    void wait_for_enter();

}
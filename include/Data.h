#ifndef DATA_H
#define DATA_H

#include <chrono>

using std::chrono::system_clock;

class Data
{
    public:
        size_t size;
        system_clock::duration d1, d2, d3, d4, d5;
};

#endif // DATA_H

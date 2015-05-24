#include "Auxilary.h"

#include <iostream>
#include <chrono>
#include <ctime>

using std::cout;
using std::endl;
using std::ifstream;
using std::chrono::system_clock;


vector<size_t> readFromFile()
{
    size_t size;
    vector<size_t> params;
    ifstream input("params.txt");

    if(input)//if successfully opened
    {
        while(input >> size)//while not EOF
        {
            params.push_back(size);
        }
    }
    else
    {
        cout << "Failed to open a file" << endl;
    }

    return params;
}

void addTimeStamp(ofstream& output)
{
    for(size_t i = 0; i != 50; ++i) output << "-"; output << endl;

    time_t t = system_clock::to_time_t(system_clock::now());
    output << ctime(&t);

    for(size_t i = 0; i != 50; ++i) output << "-"; output << endl;
}


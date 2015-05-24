#ifndef AUXILARY_H
#define AUXILARY_H

#include <vector>
#include <fstream>

using std::vector;
using std::ofstream;


vector<size_t> readFromFile();

void addTimeStamp(ofstream& output);

#endif // AUXILARY_H

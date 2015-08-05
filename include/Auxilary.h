#ifndef AUXILARY_H
#define AUXILARY_H

#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using std::vector;
using std::ofstream;
using std::string;
using std::chrono::system_clock;


vector<size_t> readFromFile();

void addDelimiter(ofstream& output, size_t count = 50, char delim = '-');
void addCpuInfo(ofstream& output);
void addTimeStamp(ofstream& output);
void addHeader(ofstream& output);

void displayMessage(const string& message, const size_t& data);
void displayMessage(const string& message, const system_clock::duration& data, bool newLine = false);

#endif // AUXILARY_H

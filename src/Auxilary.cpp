#include "Auxilary.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <locale>
#include <iomanip>

#include "CpuInfo.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::locale;
using std::time_put;
using std::use_facet;
using std::setw;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;


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

void addDelimiter(ofstream& output, size_t count, char delim)
{
    for(size_t i = 0; i != count; ++i) output << delim; output << endl;
}

void addCpuInfo(ofstream& output)
{
    CpuInfo cpu;

    output << "CPU Vendor: " << cpu.getVendorID() << endl;
    output << "CPU Name  : " << cpu.getBrandString() << endl;
}

void addTimeStamp(ofstream& output)
{
    time_t t = system_clock::to_time_t(system_clock::now()); //interval
    tm* tmObject = localtime(&t); //parse interval into a date/time struct

    locale global; //copy of the current global locale
    const time_put<char>& tp = use_facet<time_put<char>>(global); //reference to the facet time_put<> in global

    string format = "%d.%m.%y %H:%M:%S\n"; //output format
    tp.put(output, output, ' ', tmObject, format.c_str(), format.c_str() + format.size() );//write to an output stream
}

void addHeader(ofstream& output)
{
    addDelimiter(output);
    addTimeStamp(output);
    addDelimiter(output);
    addCpuInfo(output);
    addDelimiter(output);
}

void displayMessage(const string& message, const size_t& data)
{
    cout << message << setw(7) << data << endl;
}

void displayMessage(const string& message, const system_clock::duration& data, bool newLine)
{
    cout << message << setw(7) << duration_cast<milliseconds>(data).count() << " ms" << endl;

    if(newLine) cout << endl;
}

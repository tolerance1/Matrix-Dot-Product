#include "Table.h"

#include <iomanip>
#include <fstream>
#include <iostream>

#include "Message.h"
#include "Auxilary.h"

using namespace std;
using namespace std::chrono;

Table::Table()
{
    row1 << left << setw(16) << message1;
    row2 << left << setw(16) << message2;
    row3 << left << setw(16) << message3;
    row4 << left << setw(16) << message4;
    row5 << left << setw(16) << message5;
    row6 << left << setw(16) << message6;
}

void Table::addData(const Data& data)
{
    row1 << setw(7) << data.size;
    row2 << setw(7) << duration_cast<milliseconds>(data.d1).count();
    row3 << setw(7) << duration_cast<milliseconds>(data.d2).count();
    row4 << setw(7) << duration_cast<milliseconds>(data.d3).count();
    row5 << setw(7) << duration_cast<milliseconds>(data.d4).count();
    row6 << setw(7) << duration_cast<milliseconds>(data.d5).count();

}

void Table::writeTable()
{
    ofstream output("results.txt", ios_base::app);

    if(output)//if successfully opened
    {
        addTimeStamp(output);

        output << row1.str() << endl;
        output << row2.str() << endl;
        output << row3.str() << endl;
        output << row4.str() << endl;
        output << row5.str() << endl;
        output << row6.str() << endl << endl;
    }
    else
    {
        cout << "Failed to write to a file" << endl;
    }
}

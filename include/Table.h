#ifndef TABLE_H
#define TABLE_H

#include <sstream>

#include "Data.h"

class Table
{
    public:
        Table();

        void addData(const Data& data);
        void writeTable();

    private:
        std::ostringstream row1, row2, row3, row4, row5, row6;
};

#endif // TABLE_H

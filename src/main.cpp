#include <vector>
#include <chrono>
#include <utility>

#include "Data.h"
#include "Table.h"
#include "Matrix.h"
#include "Message.h"
#include "Auxilary.h"

using std::vector;
using std::pair;
using std::chrono::system_clock;


int main()
{
    Table table;
    vector<size_t> params (readFromFile());

    for(auto iter = params.cbegin(); iter != params.cend(); ++iter)
    {
        Data data;
        data.size = *iter;
        displayMessage(message1, data.size);

        Matrix M1, M2, RES, tM2, tRES;
        resizeMatrix(M1, data.size);
        tRES = tM2 = RES = M2 = M1;

        system_clock::time_point t1 = system_clock::now();
        initMatrix(M1, data.size);
        data.d1 = system_clock::now() - t1;
        displayMessage(message2, data.d1);

        t1 = system_clock::now();
        initMatrix(M2, data.size);
        data.d2 = system_clock::now() - t1;
        displayMessage(message3, data.d2);

        t1 = system_clock::now();
        matrixDot(M1, M2, RES, data.size);
        data.d3 = system_clock::now() - t1;
        displayMessage(message4, data.d3);

        tM2 = M2;
        t1 = system_clock::now();
        transposeMatrix(tM2, data.size);
        data.d4 = system_clock::now() - t1;
        displayMessage(message5, data.d4);

        t1 = system_clock::now();
        tranposedMatrixDot(M1, tM2, tRES, data.size);
        data.d5 = system_clock::now() - t1;
        displayMessage(message6, data.d5, true);

        table.addData(data);

        if(data.size <= 10)
        {
            typedef pair<string, Matrix&> Pair;
            vector<Pair> pairs {{"M1", M1},
                                {"M2", M2},
                                {"RES", RES},
                                {"tM2", tM2},
                                {"tRES", tRES}};

            for(size_t i = 0; i < pairs.size(); ++i)
                writeMatrix(pairs[i].first, pairs[i].second, data.size);
        }
    }

    table.writeTable();


    return 0;
}

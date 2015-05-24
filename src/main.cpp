#include <iostream>
#include <vector>
#include <chrono>
#include <utility>

#include "Data.h"
#include "Table.h"
#include "Matrix.h"
#include "Message.h"
#include "Auxilary.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::chrono::time_point;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;


int main()
{
    Table table;
    vector<size_t> params (readFromFile());

    for(auto iter = params.cbegin(); iter != params.cend(); ++iter)
    {
        Data data;
        data.size = *iter;
        cout << message1 << data.size << endl;

        Matrix M1, M2, RES, tM2, tRES;
        resizeMatrix(M1, data.size);
        tRES = tM2 = RES = M2 = M1;

        auto t1 = system_clock::now();
        initMatrix(M1, data.size);
        data.d1 = system_clock::now() - t1;
        cout << message2 << duration_cast<milliseconds>(data.d1).count() << "ms" << endl;

        t1 = system_clock::now();
        initMatrix(M2, data.size);
        data.d2 = system_clock::now() - t1;
        cout << message3 << duration_cast<milliseconds>(data.d2).count() << "ms" << endl;

        t1 = system_clock::now();
        matrixDot(M1, M2, RES, data.size);
        data.d3 = system_clock::now() - t1;
        cout << message4 << duration_cast<milliseconds>(data.d3).count() << "ms" << endl;

        tM2 = M2;
        t1 = system_clock::now();
        transposeMatrix(tM2, data.size);
        data.d4 = system_clock::now() - t1;
        cout << message5 << duration_cast<milliseconds>(data.d4).count() << "ms" << endl;

        t1 = system_clock::now();
        tranposedMatrixDot(M1, tM2, tRES, data.size);
        data.d5 = system_clock::now() - t1;
        cout << message6 << duration_cast<milliseconds>(data.d5).count() << "ms" << endl << endl;

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

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

typedef vector<double> Matrix;

class Data
{
    public:
        size_t size;
        system_clock::duration d1, d2, d3, d4, d5;
};

void resizeMatrix(Matrix& matrix, size_t size)
{
    matrix.resize(size * size);
}

void initMatrix(Matrix& matrix, size_t size)
{
    static default_random_engine e; //generates unsigned random integers (default seed)
    static uniform_real_distribution<double> u(0, 1);//uniformly distributed from 0 to 1 exclusive

    for(size_t i = 0; i < size; ++i)//for every row
    {
        for(size_t j = 0; j < size; ++j)//for every column
        {
            matrix[i * size + j] = u(e);
        }
    }
}

void outputMatrix(ostream& output, string& name, Matrix& matrix, size_t size)
{
    output << name << endl;

    for(size_t i = 0; i < size; ++i)//for every row
    {
        for(size_t j = 0; j < size; ++j)//for every column
        {
            output << left << setw(7) << setprecision(3) << matrix[i * size + j];
        }
        output << endl;
    }
    output << endl;
}

void matrixDot(Matrix& matrix1, Matrix& matrix2,
               Matrix& resultMatrix, size_t size)
{
    for(size_t i = 0; i < size; ++i)//for every row in resultMatrix
    {
        for(size_t j = 0; j < size; ++j)//for every column in resultMatrix
        {
            //dot M1 and M2 elements
            for(size_t k = 0; k < size; ++k)//'k' - number of elements in a M1 row/M2 column
            {
                resultMatrix[i * size + j] += matrix1[i * size + k] * matrix2[k * size + j];
            }
        }
    }
}

void tranposedMatrixDot(Matrix& matrix1, Matrix& matrix2,
                        Matrix& resultMatrix, size_t size)
{
    for(size_t i = 0; i < size; ++i)//for every row in resultMatrix
    {
        for(size_t j = 0; j < size; ++j)//for every column in resultMatrix
        {
            //dot M1 and M2 elements
            for(size_t k = 0; k < size; ++k)//'k' - number of elements in a M1 row/M2 row
            {
                resultMatrix[i * size + j] += matrix1[i * size + k] * matrix2[j * size + k];
            }
        }
    }
}

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

void writeMatrix(string& name, Matrix& matrix, size_t size)
{
    ofstream output("results.txt", ios_base::app);

    if(output)//if successfully opened
    {
        outputMatrix(output, name, matrix, size);
    }
    else
    {
        cout << "Failed to write to a file" << endl;
    }
}

void writeData(Data& data)
{
    ofstream output("results.txt", ios_base::app);

    if(output)//if successfully opened
    {
        output << "Matrix size: "<< data.size << endl;
        output << "Matrix1 init time: "<< duration_cast<milliseconds>(data.d1).count() << "ms" << endl;
        output << "Matrix2 init time: "<< duration_cast<milliseconds>(data.d2).count() << "ms" << endl;
        output << "Matrix multiplication time: "<< duration_cast<milliseconds>(data.d3).count() << "ms" << endl;
        output << "Matrix2 transposition time: "<< duration_cast<milliseconds>(data.d4).count() << "ms" << endl;
        output << "Transposed matrix multiplication time: "<< duration_cast<milliseconds>(data.d5).count() << "ms" << endl << endl;
    }
    else
    {
        cout << "Failed to write to a file" << endl;
    }
}

void transposeMatrix(Matrix& matrix, size_t size)
{
    for(size_t i = 0; i < size; ++i)//for every row
    {
        for(size_t j = i + 1; j < size; ++j)//for every column
        {
            double temp = matrix[i * size + j];
            matrix[i * size + j] = matrix[j * size + i];
            matrix[j * size + i] = temp;
        }
    }
}


int main()
{
    vector<size_t> params (readFromFile());

    for(auto iter = params.cbegin(); iter != params.cend(); ++iter)
    {
        Data data;
        data.size = *iter;
        cout << "Matrix size: "<< data.size << endl;

        Matrix M1, M2, RES, tM2, tRES;
        resizeMatrix(M1, data.size);
        tRES = tM2 = RES = M2 = M1;

        typedef pair<string, Matrix&> Pair;
        vector<Pair> pairs {{"M1", M1},
                            {"M2", M2},
                            {"RES", RES},
                            {"tM2", tM2},
                            {"tRES", tRES}};

        auto t1 = system_clock::now();
        initMatrix(M1, data.size);
        data.d1 = system_clock::now() - t1;
        cout << "Matrix1 init time: "<< duration_cast<milliseconds>(data.d1).count() << "ms" << endl;

        t1 = system_clock::now();
        initMatrix(M2, data.size);
        data.d2 = system_clock::now() - t1;
        cout << "Matrix2 init time: "<< duration_cast<milliseconds>(data.d2).count() << "ms" << endl;

        t1 = system_clock::now();
        matrixDot(M1, M2, RES, data.size);
        data.d3 = system_clock::now() - t1;
        cout << "Matrix multiplication time: "<< duration_cast<milliseconds>(data.d3).count() << "ms" << endl;

        tM2 = M2;
        t1 = system_clock::now();
        transposeMatrix(tM2, data.size);
        data.d4 = system_clock::now() - t1;
        cout << "Matrix2 transposition time: "<< duration_cast<milliseconds>(data.d4).count() << "ms" << endl;

        t1 = system_clock::now();
        tranposedMatrixDot(M1, tM2, tRES, data.size);
        data.d5 = system_clock::now() - t1;
        cout << "Transposed matrix multiplication time: "<< duration_cast<milliseconds>(data.d5).count() << "ms" << endl << endl;

        writeData(data);

        if(data.size <= 10)
        {
            for(size_t i = 0; i < pairs.size(); ++i)
                outputMatrix(cout, pairs[i].first, pairs[i].second, data.size);

            for(size_t i = 0; i < pairs.size(); ++i)
                writeMatrix(pairs[i].first, pairs[i].second, data.size);
        }
    }


    return 0;
}

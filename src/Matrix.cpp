#include "Matrix.h"

#include <random>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Auxilary.h"

using namespace std;


void resizeMatrix(Matrix& matrix, const size_t size)
{
    matrix.resize(size * size);
}

void initMatrix(Matrix& matrix, const size_t size)
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

void matrixDot(const Matrix& matrix1, const Matrix& matrix2,
               Matrix& resultMatrix, const size_t size)
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

void tranposedMatrixDot(const Matrix& matrix1, const Matrix& matrix2,
                        Matrix& resultMatrix, const size_t size)
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

void transposeMatrix(Matrix& matrix, const size_t size)
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

void outputMatrix(ostream& output, const string& name, const Matrix& matrix, const size_t size)
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

void writeMatrix(const string& name, const Matrix& matrix, const size_t size)
{
    ofstream output("matrices.txt", ios_base::app);

    if(output)//if successfully opened
    {
        static bool stampAdded = false;

        if(! stampAdded)
        {
            addTimeStamp(output);
            stampAdded = true;
        }

        outputMatrix(output, name, matrix, size);
    }
    else
    {
        cout << "Failed to write to a file" << endl;
    }
}

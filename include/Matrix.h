#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;


typedef vector<double> Matrix;


void resizeMatrix(Matrix& matrix, const size_t size);

void initMatrix(Matrix& matrix, const size_t size);

void matrixDot(const Matrix& matrix1, const Matrix& matrix2,
               Matrix& resultMatrix, const size_t size);

void tranposedMatrixDot(const Matrix& matrix1, const Matrix& matrix2,
                        Matrix& resultMatrix, const size_t size);

void transposeMatrix(Matrix& matrix, const size_t size);

void outputMatrix(ostream& output, const string& name, const Matrix& matrix, const size_t size);

void writeMatrix(const string& name, const Matrix& matrix, const size_t size);

#endif // MATRIX_H

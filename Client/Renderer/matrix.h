#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

using namespace std;
class Matrix
{
public:
    vector<vector<double> > points;
    Matrix();
    Matrix operator * (Matrix rhs);
};

#endif // MATRIX_H

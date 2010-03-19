#include "matrix.h"

Matrix::Matrix()
{
}

Matrix Matrix::operator *(Matrix rhs)
{
    Matrix result;

    for (size_t i = 0; i < points.size(); i++)//rows
    {
        result.points.push_back(vector<double>());
        for (size_t j = 0; j < 3; j++)//cols
        {
            double temp = 0.0;
            for (size_t k = 0; k < 3; k++){
                double x = points[i][k], y = rhs.points[k][j];
                temp += x * y;
            }
            result.points[i].push_back(temp);
        }
    }
    return result;
}

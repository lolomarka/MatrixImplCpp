#include <iostream>
using namespace std;

template <typename T>
class Matrix
{
private:
    T** data;
    size_t rowsCount;
    size_t colsCount;
public:
    
    
    size_t GetRows();
    size_t GetColumns();

    Matrix();
    Matrix(size_t rows, size_t cols);
    ~Matrix();
};

template <typename T>
inline size_t Matrix<T>::GetRows()
{
    return rowsCount;
}

template <typename T>
inline size_t Matrix<T>::GetColumns()
{
    return colsCount;
}

template <typename T>
inline Matrix<T>::Matrix()
{
    rowsCount = colsCount = 0;
    data = nullptr;
}

template <typename T>
inline Matrix<T>::Matrix(size_t rows, size_t cols) : rowsCount(rows), colsCount(cols)
{
    data = new T*[rowsCount];
    for (size_t i = 0; i < rowsCount; i++)
    {
        data[i] = new T[colsCount];
        for (size_t j = 0; j < colsCount; j++)
        {
            data[i][j] = T();
        }
    }
}

template <typename T>
inline Matrix<T>::~Matrix()
{
    for (size_t i = 0; i < rowsCount; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}



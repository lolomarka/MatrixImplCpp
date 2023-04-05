#include <iostream>
#include <math.h>
using namespace std;

template <typename T>
class Matrix
{
private:
    T* data;
    size_t rowsCount;
    size_t colsCount;
    void Print(T* d, size_t r, size_t c);
public:
    class iterator {
        public:
            iterator(T* ptr) : m_ptr(ptr) {}
            iterator operator++() { m_ptr++; return *this; }
            T& operator*() {return *m_ptr; }
            bool operator != (const iterator& other) const{ return m_ptr != other.m_ptr; }
        
        private:
            T* m_ptr;
    };

    T& operator()(size_t row, size_t col);

    void Print();
    
    size_t GetRowsCount();
    size_t GetColumnsCount();

    void Resize(size_t rows, size_t cols);

    Matrix();
    Matrix(size_t rows, size_t cols);
    ~Matrix();

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + rowsCount * colsCount); }
};

template <typename T>
inline void Matrix<T>::Print(T *d, size_t r, size_t c)
{
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
        {
            cout << d[i*r + j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

template <typename T>
inline T &Matrix<T>::operator()(size_t row, size_t col)
{
    if (row >= rowsCount)
        std::__throw_invalid_argument("Rows");
    if (col >= colsCount)
        std::__throw_invalid_argument("Cols");
    return data[row * rowsCount + col];
}

template <typename T>
inline void Matrix<T>::Print()
{
    Print(data, rowsCount, colsCount);
}

template <typename T>
inline size_t Matrix<T>::GetRowsCount()
{
    return rowsCount;
}

template <typename T>
inline size_t Matrix<T>::GetColumnsCount()
{
    return colsCount;
}

template <typename T>
inline void Matrix<T>::Resize(size_t rows, size_t cols)
{
    if (rows == rowsCount && cols == colsCount)
        return;
    T* newData = new T [rows*cols];
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if(i < rowsCount && j < colsCount)
            {
                newData[i*rows + j] = operator()(i,j);
            }
            else
            {
                newData[i*rows + j] = T();
            }
        }
    }
    delete[] data;
    data = newData;
    rowsCount = rows;
    colsCount = cols;
}

template <typename T>
inline Matrix<T>::Matrix()
{
    rowsCount = colsCount = 0;
    data = new T[0];
}

template <typename T>
inline Matrix<T>::Matrix(size_t rows, size_t cols) : rowsCount(rows), colsCount(cols)
{
    size_t len = rowsCount * colsCount;
    data = new T[len];
    for (size_t i = 0; i < len; i++)
    {
        auto value = T();
        data[i] = value;
    }
}

template <typename T>
inline Matrix<T>::~Matrix()
{
    delete[] data;
}



#include <iostream>
using namespace std;

template <typename T>
class Matrix
{
private:
    T* data;
    size_t rowsCount;
    size_t colsCount;
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
    
    size_t GetRows();
    size_t GetColumns();

    Matrix();
    Matrix(size_t rows, size_t cols);
    ~Matrix();

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + rowsCount * colsCount); }
};

template <typename T>
inline T& Matrix<T>::operator()(size_t row, size_t col)
{
    if (row >= rowsCount)
        std::__throw_invalid_argument("Rows");
    if (col >= colsCount)
        std::__throw_invalid_argument("Cols");
    return data[row * col + col];
}

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
    data = new T[0];
}

template <typename T>
inline Matrix<T>::Matrix(size_t rows, size_t cols) : rowsCount(rows), colsCount(cols)
{
    size_t len = rowsCount * colsCount;
    data = new T[len];
    for (size_t i = 0; i < len; i++)
    {
        data[i] = T();
    }
}

template <typename T>
inline Matrix<T>::~Matrix()
{
    delete[] data;
}



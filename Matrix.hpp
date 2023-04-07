#include <iostream>
#include <string.h>
using namespace std;

template <typename T>
class Matrix
{
private:
    T *data;
    size_t rowsCount;
    size_t colsCount;
    void Print(T *d, size_t r, size_t c);

public:
    class iterator
    {
    public:
        iterator(T *ptr) : m_ptr(ptr) {}
        iterator operator++()
        {
            m_ptr++;
            return *this;
        }
        T &operator*() { return *m_ptr; }
        bool operator!=(const iterator &other) const { return m_ptr != other.m_ptr; }

    private:
        T *m_ptr;
    };

    T &operator()(size_t row, size_t col);

    void Print();

    void Swap(Matrix<T> &other);

    size_t InsertRow(size_t index, T *elements, size_t elementsLength);
    size_t RemoveRow(size_t index);
    size_t InsertColumn(size_t index, T *elements, size_t elementsLength);
    size_t RemoveColumn(size_t index);

    size_t GetRowsCount() const;
    size_t GetColumnsCount() const;

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
            auto element = d[i * c + j];
            cout << element << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

template <typename T>
inline T &Matrix<T>::operator()(size_t row, size_t col)
{
    if (row < 0 || row >= rowsCount)
        std::__throw_invalid_argument("Rows");
    if (col < 0 || col >= colsCount)
        std::__throw_invalid_argument("Cols");
    return data[row * colsCount + col];
}

template <typename T>
inline void Matrix<T>::Print()
{
    Print(data, rowsCount, colsCount);
}

template <typename T>
inline void Matrix<T>::Swap(Matrix<T> &other)
{
    swap(colsCount, other.colsCount);
    swap(rowsCount, other.rowsCount);
    swap(data, other.data);
}

template <typename T>
inline size_t Matrix<T>::InsertRow(size_t index, T *elements, size_t elementsLength)
{
    if (elementsLength != colsCount)
        std::__throw_length_error("Length of row not similar with matrix width.");
    if (index < 0 || index > rowsCount)
        std::__throw_invalid_argument("Index out of range.");

    size_t insertStartIndex = index * colsCount;
    size_t insertEndIndex = insertStartIndex + colsCount;
    size_t newLen = (rowsCount + 1) * colsCount;
    T *tmpData = new T[newLen];

    for (size_t i = 0; i < insertStartIndex; i++)
    {
        tmpData[i] = data[i];
    }

    for (size_t i = insertStartIndex; i < insertEndIndex; i++)
    {
        tmpData[i] = elements[i - insertStartIndex];
    }

    for (size_t i = insertEndIndex; i < newLen; i++)
    {
        tmpData[i] = data[insertStartIndex - insertEndIndex + i];
    }

    delete[] data;
    data = tmpData;
    rowsCount++;

    return rowsCount;
}

template <typename T>
inline size_t Matrix<T>::RemoveRow(size_t index)
{
    if (index < 0 || index > rowsCount)
        std::__throw_invalid_argument("Index out of range.");
    size_t oldLen = rowsCount * colsCount;
    size_t newLen = (rowsCount - 1) * colsCount;
    T *tmpData = new T[newLen];
    size_t removeStartIndex = index * colsCount;
    size_t removeEndIndex = removeStartIndex + colsCount;

    for (size_t i = 0; i < removeStartIndex; i++)
    {
        tmpData[i] = data[i];
    }

    for (size_t i = removeEndIndex; i < oldLen; i++)
    {
        tmpData[removeStartIndex - removeEndIndex + i] = data[i];
    }

    delete[] data;
    data = tmpData;
    rowsCount--;

    return rowsCount;
}

template <typename T>
inline size_t Matrix<T>::InsertColumn(size_t index, T *elements, size_t elementsLength)
{
    if (elementsLength != rowsCount)
        std::__throw_length_error("Length of column not similar with matrix width.");
    if (index < 0 || index > rowsCount)
        std::__throw_invalid_argument("Index out of range.");
    size_t newColsCount = colsCount + 1;
    size_t newLen = rowsCount * (newColsCount);

    T *tmpData = new T[newLen];

    for (size_t i = 0; i < rowsCount; i++)
    {
        for (size_t j = 0; j < index; j++)
        {
            tmpData[i * newColsCount + j] = data[i * colsCount + j];
        }
        auto value = elements[i];
        tmpData[i * newColsCount + index] = value;
        for (size_t j = index; j < colsCount; j++)
        {
            tmpData[i * newColsCount + j + 1] = data[i * colsCount + j];
        }
    }

    delete[] data;
    data = tmpData;
    colsCount = newColsCount;

    return colsCount;
}

template <typename T>
inline size_t Matrix<T>::RemoveColumn(size_t index)
{
    if (index < 0 || index > rowsCount)
        std::__throw_invalid_argument("Index out of range.");
    size_t newColsCount = colsCount - 1;
    size_t oldLen = rowsCount * colsCount;
    size_t newLen = rowsCount * newColsCount;
    T *tmpData = new T[newLen];

    for (size_t i = 0; i < rowsCount; i++)
    {
        for (size_t j = 0; j < index; j++)
        {
            tmpData[i * newColsCount + j] = data[i * colsCount + j];
        }
        for (size_t j = index + 1; j < colsCount; j++)
        {
            tmpData[i * newColsCount + j - 1] = data[i * colsCount + j];
        }
    }

    delete[] data;
    data = tmpData;
    colsCount = newColsCount;

    return colsCount;
}

template <typename T>
inline size_t Matrix<T>::GetRowsCount() const
{
    return rowsCount;
}

template <typename T>
inline size_t Matrix<T>::GetColumnsCount() const
{
    return colsCount;
}

template <typename T>
inline void Matrix<T>::Resize(size_t rows, size_t cols)
{
    if (rows == rowsCount && cols == colsCount)
        return;
    T *newData = new T[rows * cols];
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (i < rowsCount && j < colsCount)
            {
                newData[i * cols + j] = operator()(i, j);
            }
            else
            {
                newData[i * cols + j] = T();
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

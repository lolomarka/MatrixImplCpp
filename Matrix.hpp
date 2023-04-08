#include <iostream>
#include <string.h>
#include <cstring>
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
        bool operator==(const iterator &other) const { return m_ptr == other.m_ptr; }

    private:
        T *m_ptr;
    };

    T &operator()(size_t row, size_t col);
    T &operator=(const Matrix &other);

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
    Matrix(const Matrix &other);
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
    using std::invalid_argument;
    if (row < 0 || row >= rowsCount)
        throw invalid_argument("Rows");
    if (col < 0 || col >= colsCount)
        throw invalid_argument("Cols");
    return data[row * colsCount + col];
}

template <typename T>
inline T &Matrix<T>::operator=(const Matrix &other)
{
    using std::memcpy;
    if (this != &other)
    {
        delete[] data;
        rowsCount = other.rowsCount;
        colsCount = other.colsCount;
        data = new T[rowsCount * colsCount];
        memcpy(data, other.data, rowsCount * colsCount * sizeof(T));
    }
    return *this;
}

template <typename T>
inline void Matrix<T>::Print()
{
    Print(data, rowsCount, colsCount);
}

template <typename T>
inline void Matrix<T>::Swap(Matrix<T> &other)
{
    using std::swap;
    swap(colsCount, other.colsCount);
    swap(rowsCount, other.rowsCount);
    swap(data, other.data);
}

template <typename T>
inline size_t Matrix<T>::InsertRow(size_t index, T *elements, size_t elementsLength)
{
    using std::invalid_argument;
    using std::length_error;
    if (elementsLength != colsCount)
        throw length_error("Length of row not similar with matrix width.");
    if (index < 0 || index > rowsCount)
        throw invalid_argument("Index out of range.");

    size_t insertStartIndex = index * colsCount;
    size_t insertEndIndex = insertStartIndex + colsCount;
    size_t newLen = (rowsCount + 1) * colsCount;

    T *tmpData;

    if (newLen == 0)
        tmpData = nullptr;
    else
    {
        tmpData = new T[newLen];

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
    }

    delete[] data;
    data = tmpData;
    rowsCount++;

    return rowsCount;
}

template <typename T>
inline size_t Matrix<T>::RemoveRow(size_t index)
{
    using std::invalid_argument;
    if (index < 0 || index > rowsCount)
        throw invalid_argument("Index out of range.");
    size_t oldLen = rowsCount * colsCount;
    size_t newLen = (rowsCount - 1) * colsCount;
    T *tmpData;
    if (newLen == 0)
    {
        tmpData = nullptr;
    }
    else
    {
        tmpData = new T[newLen];
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
    }

    delete[] data;
    data = tmpData;
    rowsCount--;

    return rowsCount;
}

template <typename T>
inline size_t Matrix<T>::InsertColumn(size_t index, T *elements, size_t elementsLength)
{
    using std::invalid_argument;
    using std::length_error;

    if (elementsLength != rowsCount)
        throw length_error("Length of column not similar with matrix width.");
    if (index < 0 || index > rowsCount)
        throw invalid_argument("Index out of range.");
    size_t newColsCount = colsCount + 1;
    size_t newLen = rowsCount * (newColsCount);

    T *tmpData;
    if (newLen == 0)
    {
        tmpData = nullptr;
    }
    else
    {
        tmpData = new T[newLen];
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
    }

    delete[] data;
    data = tmpData;
    colsCount = newColsCount;

    return colsCount;
}

template <typename T>
inline size_t Matrix<T>::RemoveColumn(size_t index)
{
    using std::invalid_argument;
    if (index < 0 || index > rowsCount)
        throw invalid_argument("Index out of range.");
    size_t newColsCount = colsCount - 1;
    size_t oldLen = rowsCount * colsCount;
    size_t newLen = rowsCount * newColsCount;
    T *tmpData;
    if (newLen == 0)
        tmpData = nullptr;
    else
    {
        tmpData = new T[newLen];
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
    size_t len = rows * cols;
    T *newData;
    if (len == 0)
        newData = nullptr;
    else
    {
        newData = new T[len];

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
    data = nullptr;
}

template <typename T>
inline Matrix<T>::Matrix(size_t rows, size_t cols) : rowsCount(rows), colsCount(cols)
{
    size_t len = rowsCount * colsCount;
    if (len == 0)
        data = nullptr;
    else
    {
        data = new T[len];

        for (size_t i = 0; i < len; i++)
        {
            auto value = T();
            data[i] = value;
        }
    }
}

template <typename T>
inline Matrix<T>::Matrix(const Matrix &other)
{
    rowsCount = other.rowsCount;
    colsCount = other.colsCount;
    size_t len = rowsCount * colsCount;
    if (len == 0)
        data = nullptr;
    else
    {
        data = new T[len];
        memcpy(data, other.data, len * sizeof(T));
    }
}

template <typename T>
inline Matrix<T>::~Matrix()
{
    delete[] data;
}

// nullptr в конструкторе и проверка.
// 2 метода, которые защитят от Double free и write after remove memory (оператор присвоения и конструктор копирования)?

// 5.3.4/7 : When the value of the expression in a noptr-new-declarator is zero, the allocation function is called to allocate an array with no elements.
// If the value of that expression is less than zero or such that the size of the allocated object would exceed the implementation-defined limit,
// or if the new-initializer is a braced-init-list for which the number of initializer-clauses exceeds the number of elements to initialize, no storage
// is obtained and the new-expression terminates by throwing an exception of a type that would match a handler (15.3) of type std::bad_array_new_length (18.6.2.2).

// 3.7.4.1/2
// Even if the size of the space requested is zero, the request can fail.
// If the request succeeds, the value returned shall be a non-null pointer value (4.10) p0 different from any previously returned value p1,
// unless that value p1 was subsequently passed to an operator delete.
// The effect of dereferencing a pointer returned as a request for zero size is undefined.

// Сноска к 3.7.4.1/2
// The intent is to have operator new() implementable by calling std::malloc() or std::calloc(),
// so the rules are sub-stantially the same. C++ differs from C in requiring a zero request to return a non-null pointer.
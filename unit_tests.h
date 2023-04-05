#include <cassert>
#include "Matrix.hpp"

void TestMatrixConstructor() 
{
    auto assertMatrix = Matrix<int>();
    auto test = Matrix<int>(0,0);

    assert(assertMatrix.GetColumnsCount() == test.GetColumnsCount() && assertMatrix.GetRowsCount() == test.GetRowsCount());
}

void TestMatrixOperatorWrongGetter()
{
    auto assertMatrix = Matrix<int>();

    try
    {
        assertMatrix(1,1);
        assert(false);
    }
    catch(const std::invalid_argument& e)
    {
        assert(true);
    }
}

void TestMatrixOperatorRightGetter()
{
    auto assertMatrix = Matrix<int>(10,10);

    assert(assertMatrix(1,1) == int());
}

void TestMatrixOperatorSetter()
{
    auto assertMatrix = Matrix<int>(5,5);
    assertMatrix(3,2) = 10;

    assert(assertMatrix(3,2) == 10);
}

void TestIterator()
{
    bool correct = true;
    
    auto assertMatrix = Matrix<int>(10,10);
    
    for (auto it = assertMatrix.begin(); it != assertMatrix.end(); ++it)
    {
        correct &= *it == int();
    }
    
    assert(correct);
}

void TestResizeGrow()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t newRows = 5;
    size_t newCols = 5;
    int assertValue = 666;

    auto testMatrix = Matrix<int>(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            testMatrix(i,j) = assertValue;
        }
    }

    testMatrix.Resize(newRows, newCols);

    bool correct = true;
    for (size_t i = 0; i < newRows; i++)
    {
        for (size_t j = 0; j < newCols; j++)
        {
            if(i < rows && j < cols)
            {
                correct = correct && (assertValue == testMatrix(i,j));
            }
            else
            {
                correct = correct && (testMatrix(i,j) == int());
            }
        }
    }

    assert(correct);
}

void TestResizeReduce()
{
    size_t rows = 5;
    size_t cols = 5;
    size_t newRows = 3;
    size_t newCols = 3;
    int assertValue = 666;

    auto testMatrix = Matrix<int>(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            testMatrix(i,j) = assertValue;
        }
    }

    testMatrix.Resize(newRows, newCols);

    bool correct = true;
    for (size_t i = 0; i < newRows; i++)
    {
        for (size_t j = 0; j < newCols; j++)
        {
            if(i < rows && j < cols)
            {
                correct = correct && (assertValue == testMatrix(i,j));
            }
            else
            {
                correct = correct && (testMatrix(i,j) == int());
            }
        }
    }

    assert(correct);
}

void TestResizeMixed()
{
    size_t rows = 1;
    size_t cols = 10;
    size_t newRows = 5;
    size_t newCols = 5;
    int assertValue = 666;

    auto testMatrix = Matrix<int>(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            testMatrix(i,j) = assertValue;
        }
    }

    testMatrix.Resize(newRows, newCols);

    bool correct = true;
    for (size_t i = 0; i < newRows; i++)
    {
        for (size_t j = 0; j < newCols; j++)
        {
            if(i < rows && j < cols)
            {
                correct = correct && (assertValue == testMatrix(i,j));
            }
            else
            {
                correct = correct && (testMatrix(i,j) == int());
            }
        }
    }

    assert(correct);
}

void TestInsertRowStart()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t insertIndex = 0;
    size_t insertRowLength = 3;
    int assertValue = 666;

    auto testMatrix = Matrix<int>(rows,cols);

    int* row = new int[insertRowLength];

    for (size_t i = 0; i < insertRowLength; i++)
    {
        row[i] = assertValue;
    }
    
    auto newRowsCount = testMatrix.InsertRow(insertIndex, row, insertRowLength);
    assert(newRowsCount == (rows + 1));
    delete[] row;
    for (size_t i = 0; i < cols; i++)
    {
        assert(testMatrix(insertIndex,i) == assertValue);
    }
}

void TestInsertRowMiddle()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t insertIndex = 1;
    size_t insertRowLength = 3;
    int assertValue = 666;

    auto testMatrix = Matrix<int>(rows,cols);

    int* row = new int[insertRowLength];

    for (size_t i = 0; i < insertRowLength; i++)
    {
        row[i] = assertValue;
    }
    
    auto newRowsCount = testMatrix.InsertRow(insertIndex, row, insertRowLength);
    assert(newRowsCount == (rows + 1));
    delete[] row;
    for (size_t i = 0; i < cols; i++)
    {
        assert(testMatrix(insertIndex,i) == assertValue);
    }
}

void TestInsertRowEnd()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t insertIndex = 3;
    size_t insertRowLength = 3;
    int assertValue = 666;

    auto testMatrix = Matrix<int>(rows,cols);

    int* row = new int[insertRowLength];

    for (size_t i = 0; i < insertRowLength; i++)
    {
        row[i] = assertValue;
    }
    
    auto newRowsCount = testMatrix.InsertRow(insertIndex, row, insertRowLength);
    assert(newRowsCount == (rows + 1));
    delete[] row;
    for (size_t i = 0; i < cols; i++)
    {
        assert(testMatrix(insertIndex,i) == assertValue);
    }
}

void TestInsertRowWrongIndex()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t insertIndex = 6;
    size_t insertRowLength = 3;
    int assertValue = 666;


    auto testMatrix = Matrix<int>(rows,cols);

    int* row = new int[insertRowLength];

    for (size_t i = 0; i < insertRowLength; i++)
    {
        row[i] = assertValue;
    }
    
    try
    {
        testMatrix.InsertRow(insertIndex, row, insertRowLength);
        assert(false);
    }
    catch(const std::invalid_argument& e)
    {
        assert(true);
    }
    
    delete[] row;
}

void TestInsertRowWrongRowSize()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t insertIndex = 0;
    size_t insertRowLength = 5;
    int assertValue = 666;


    auto testMatrix = Matrix<int>(rows,cols);

    int* row = new int[insertRowLength];

    for (size_t i = 0; i < insertRowLength; i++)
    {
        row[i] = assertValue;
    }
    
    try
    {
        testMatrix.InsertRow(insertIndex, row, insertRowLength);
        assert(false);
    }
    catch(const std::length_error& e)
    {
        assert(true);
    }
    
    delete[] row;
}

void TestRemoveRowStart()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t removeIndex = 0;
    int assertValue = 666;


    auto testMatrix = Matrix<int>(rows,cols);
    
    auto newRowsCount = testMatrix.RemoveRow(removeIndex);
    assert(newRowsCount == (rows - 1));
}

void TestRemoveRowMiddle()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t removeIndex = 1;
    int assertValue = 666;


    auto testMatrix = Matrix<int>(rows,cols);
    
    auto newRowsCount = testMatrix.RemoveRow(removeIndex);
    assert(newRowsCount == (rows - 1));
}

void TestRemoveRowEnd()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t removeIndex = 2;
    int assertValue = 666;


    auto testMatrix = Matrix<int>(rows,cols);
    
    auto newRowsCount = testMatrix.RemoveRow(removeIndex);
    assert(newRowsCount == (rows - 1));
}

void TestRemoveRowOutOfRange()
{
    size_t rows = 3;
    size_t cols = 3;
    size_t removeIndex = -1;
    int assertValue = 666;


    auto testMatrix = Matrix<int>(rows,cols);
    try
    {
        testMatrix.RemoveRow(removeIndex);
        assert(false);
    }
    catch(const std::invalid_argument& e)
    {
        assert(true);
    }
}




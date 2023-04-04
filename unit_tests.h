#include <cassert>
#include "Matrix.hpp"

void TestMatrixConstructor() 
{
    auto assertMatrix = Matrix<int>();
    auto test = Matrix<int>(0,0);

    assert(assertMatrix.GetColumns() == test.GetColumns() && assertMatrix.GetRows() == test.GetRows());
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
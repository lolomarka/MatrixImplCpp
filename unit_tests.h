#include <cassert>
#include "Matrix.hpp"

void TestMatrixConstructor() 
{
    auto assertMatrix = Matrix<int>();
    auto test = Matrix<int>(0,0);

    assert(assertMatrix.GetColumns() == test.GetColumns() && assertMatrix.GetRows() == test.GetRows());
}
#include <iostream>

#include "Async2DMatrix.hpp"
#include "Async3DMatrix.hpp"
#include "Piece.hpp"
#include "MatrixManip.hpp"

using namespace Gungi;


int main(int argc, char** argv)
{
    Heap2DMatrix       <char>          h2(5, 5, 'a');
    Heap3DMatrix       <char>          h3(5, 5, 'a');
    Stack2DMatrix      <char, 5, 5>    s2('a');
    Stack3DMatrix      <char, 5, 5, 5> s3('a');
    AsyncHeap2DMatrix  <char>          ah2(5, 5, 'a');
    AsyncHeap3DMatrix  <char>          ah3(5, 5, 5, 'a');
    AsyncStack2DMatrix <char, 5, 5>    as2('a');
    AsyncStack3DMatrix <char, 5, 5, 5> as3('a');
    

    std::cout << "Move: " << sizeof (Move) << std::endl
        << "XY_Indices: " << sizeof (XY_Indices) << std::endl
        << "XYZ_Indices: " << sizeof (XYZ_Indices) << std::endl;

    return 0;
}

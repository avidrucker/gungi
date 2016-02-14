#include <iostream>

#include "Matrix.hpp"
#include "MatrixManip.hpp"
#include "Protocol.hpp"
#include "Gungi.hpp"

using namespace Gungi;

int main(int argc, char** argv)
{
    Matrix2<char> h2 {5, 5, 'a'};
    Matrix3<char> h3 {5, 5, 5, 'a'};
    std::cout << h2(1,2) << std::endl;
    std::cout << h3(1,2,2);
    return 0;
}

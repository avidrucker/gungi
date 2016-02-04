#pragma once

#include <cstring>

namespace Gungi
{
    enum class Piece : unsigned char 
    { None, One, Two, Three, Four, Five, Six, Seven, Eight };
    
   
    /**
     * Inspect this struct for padding using sizeof
     */
    struct Move
    {
        Move(const char* x, const char* y, const char* z)
        {
            strcpy(X,x);
            strcpy(Y,y);
            strcpy(Z,z);
        }

        char[2] X;
        char[2] Y;
        char[2] Z;
    };


}

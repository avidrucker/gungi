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

        char X[2];
        char Y[2];
        char Z[2];
    };
}

#include <iostream>
#include <utility>
#include <vector>

template <class T, size_t N>
class UnsafeFixedStack
{
    public:
        UnsafeFixedStack()
        : _top  (-1)
        {}
        
        const T& top() const
        {
            return _arr[_top];                
        }
        
        void pop()
        {
            --_top;    
            return;
        }
        
        void push(const T& val)
        {
            ++_top;
            _arr[_top] = val;
            return;
        }
        
        bool empty() const
        {
            return _top == -1;    
        }
        
    private:
        T _arr[N];        
        int _top;
};


template <class T, size_t Rows, size_t Cols>
class Board
{
    public:
        Board(const T& initValues = T())
        {
            for (size_t i = 0; i < Rows * Cols; ++i)
                _board[i] = initValues;
        }
        
        const T& getState(const size_t& row, const size_t& col) const
        {
            return _board[Cols * row + col];    
        }
        
        void setState(const size_t& row, const size_t& col, const T& state)
        {
            _board[Cols * row + col] = state;    
        }
        
        void swapState(const size_t& row1, const size_t& col1, const size_t& row2, const size_t& col2)
        {
            T tmp = getState(row1,col1);
            setState(row1,col1, getState(row2, col2));
            setState(row2,col2, tmp);
        }
    private:
        T _board[Rows * Cols];
        
};

template <class T, size_t Length, size_t Width, size_t Height>
class 3DBoard
{
    public:
        3DBoard(const T& initValue = T ())
        {
            for (size_t i = 0; i < Length * Width * Height; ++i)
                _board[i] = initValues;
        }

        const T& getState(const size_t& x, const size_t& y, const size_t z) const
        {
            return _board[x + y * Width + z * Width * Height];
        }

        const T& operator () (const size_t& x, const size_t& y, const size_t& z) const
        {
            return getState(x,y,z);
        }
        
        void setState(const size_t& x, const size_t& y, const size_t& z, const T& state)
        {
            _board[x + y * Width + z * Width * Height] = state;
        }
        
        void setState(const size_t& x, const size_t& y, const size_t& z, T&& state)
        {
            _board[x + y * Width + z * Width * Height] = std::move(state);
        }

        void swapState(const size_t& x1, const size_t& y1, const size_t& z1,
                const size_t& x2, const size_t& y2, const size_t& z2)
        {
            T tmp = getState(x1, y1, z1);
            setState(x1, y1, z1, getState(x2, y2, z2));
            setState(x2, y2, z2 ,tmp);
        }

    private:
        T _board[Length * Width * Height];
};


enum class : unsigned char Piece
{
    None = 0, Commander = 1, Captain = 2, Samurai = 3, Ninja = 4, Catapult = 5, 
    Fortress = 6, Hidden_Dragon = 7, Prodigy = 8, Archer = 9, Soldier = 10;
};

/*
 * Gungi board size is 9 * 9, with each point being able to stack up to three pieces. 
 * Thus an array of 9 * 9 * 3 will be needed to hold the pieces.
 * The total space needed will be roughly 9 * 9 * 3 * sizeof (Piece Type)
 */


int main()
{
    Board < UnsafeFixedStack <Piece, 3>, 9, 9 > board; //Empty stacks represent no pieces on the board
    return 0;
}

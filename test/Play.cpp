#include <iostream>
#include <ctime>

#include <Engine.hpp>

/**
 * Notes:
 * Using Clang && GCC on 32-Bit:
 * sizeof (Piece) = 4
 * sizeof (size_t) = 4
 * sizeof (Point3) = 12
 * sizeof (IndexedPiece) = 16
 *
 * On 64-Bit:
 * sizeof (Piece) = TBD
 * sizeof (size_t) = TBD
 * sizeof (Point3) = TBD
 * sizeof (IndexedPiece) = TBD
 */


using std::cout;
using std::cin;
using std::endl;
using namespace Gungi;

char getHeadChar(const Head& head);
char getTailChar(const Tail& tail);
void print(const IndexedPiece& piece);
void displayBoard(const Board& board);

int main()
{
    srand(time(0));

    Game game;
    game.start();
    /*
        cout << sizeof (Piece) << endl
        << sizeof (size_t) << endl
        << sizeof (Point3) << endl
        << sizeof (IndexedPiece) << endl;
    */
    for (auto i = 0u; i < 23; ++i)
    {
        size_t x;
        size_t y;
        size_t z; 
        SmallPoint3 pt { UNBOUNDED, UNBOUNDED, UNBOUNDED };

        x = rand() % 9;
        y = 0;;
        z = rand() % 3;
        pt = SmallPoint3(x,z,y);
        game.placeOnBoard(i, pt);
    
        x = rand() % 9;
        y = 0;
        z = rand() % 3 + 6;
        pt = SmallPoint3(x,z,y);
        game.placeOnBoard(i, pt);
    }
    const Board* board = &game.gameBoard();
    displayBoard(*board);
    return 0;
}

char getHeadChar(const Head& head)
{
        switch (head)
        {
            case Head::Commander:
                return 'C';
            case Head::Captain:
                return 'c';
            case Head::Samurai:
                return 'S';
            case Head::Ninja:
                return 'N';
            case Head::Catapult:
                return 'a';
            case Head::Fortress:
                return 'F';
            case Head::HiddenDragon:
                return 'D';
            case Head::Prodigy:
                return 'P';
            case Head::Archer:
                return 'A';
            case Head::Soldier:
                return 's';
            default:
                return ' ';
        }
}

char getTailChar(const Tail& tail)
{
        switch (tail)
        {
            case Tail::DragonKing:
                return 'K';
            case Tail::Lance:
                return 'L';
            case Tail::Phoenix:
                return 'p';
            case Tail::Jounin:
                return 'J';
            case Tail::Arrow:
                return 'R';
            case Tail::Pike:
                return 'i';
            case Tail::Gold:
                return 'G';
            case Tail::Pistol:
                return 'I';
            case Tail::Silver:
                return 'V';
            case Tail::Bronze:
                return 'B';
            default:
                return ' ';
        }
}

void print(const IndexedPiece& piece)
{
    if (piece.isNull())
        cout << ' ';
    else
    {
        if (piece.onHead())
            cout << getHeadChar(piece.getHead());
        else
            cout << getTailChar(piece.getTail());
    }
}

void displayBoard(const Board& board)
{
    for (auto i = 0u; i < board.getWidth(); ++i)
    { 
        cout << '|';
        for (auto j = 0u; j < board.getHeight(); ++j)
        {
            for (auto k = 0u; k < board.getDepth(); ++k)
            {
                auto p = board(i,k,j);
                print(*p);
            }
            cout << '|';
        }

        cout << endl << ' ';

        for (auto j = 0u; j < board.getHeight(); ++j)
        {
            for (auto k = 0u; k < board.getDepth(); ++k)
                cout << '-';

            cout << ' ';
        }

        cout << endl;
    }
}

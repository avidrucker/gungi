#include <iostream>

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
void placePieces(Game& game);
void displayBoard(const Board& board);

int main()
{
    /*
        cout << sizeof (Piece) << endl
        << sizeof (size_t) << endl
        << sizeof (Point3) << endl
        << sizeof (IndexedPiece) << endl;
    */

    Game game;
    game.start(); // Set Phase to Placement
    placePieces(game);
    game.start(); // Set Phase to Running

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

void placePieces(Game& game)
{
    std::cout << game.drop(0,  SmallPoint3(0, 5, 2)) << std::endl; // Commander
    std::cout << game.drop(0,  SmallPoint3(0, 5, 2)) << std::endl; // Commander
    std::cout << game.drop(1,  SmallPoint3(1, 5, 2)) << std::endl; // Captain 
    std::cout << game.drop(1,  SmallPoint3(1, 5, 2)) << std::endl; // Captain 
    std::cout << game.drop(2,  SmallPoint3(0, 4, 2)) << std::endl; // Captain 
    std::cout << game.drop(2,  SmallPoint3(0, 4, 2)) << std::endl; // Captain 
    std::cout << game.drop(3,  SmallPoint3(1, 1, 0)) << std::endl; // Samurai
    std::cout << game.drop(3,  SmallPoint3(1, 1, 0)) << std::endl; // Samurai 
    std::cout << game.drop(4,  SmallPoint3(2, 0, 0)) << std::endl; // Samurai 
    std::cout << game.drop(4,  SmallPoint3(2, 0, 0)) << std::endl; // Samurai 
    std::cout << game.drop(5,  SmallPoint3(2, 6, 0)) << std::endl; // Ninja 
    std::cout << game.drop(5,  SmallPoint3(2, 8, 0)) << std::endl; // Ninja 
    std::cout << game.drop(6,  SmallPoint3(3, 9, 0)) << std::endl; // Ninja 
    std::cout << game.drop(6,  SmallPoint3(3, 9, 0)) << std::endl; // Ninja 
    std::cout << game.drop(7,  SmallPoint3(3, 5, 0)) << std::endl; // Ninja 
    std::cout << game.drop(7,  SmallPoint3(9, 1, 3)) << std::endl; // Ninja 
    std::cout << game.drop(8,  SmallPoint3(4, 0, 0)) << std::endl; // Catapult 
    std::cout << game.drop(8,  SmallPoint3(4, 0, 0)) << std::endl; // Catapult 
    std::cout << game.drop(9,  SmallPoint3(4, 1, 0)) << std::endl; // Fortress 
    std::cout << game.drop(9,  SmallPoint3(4, 1, 0)) << std::endl; // Fortress 
    std::cout << game.drop(10, SmallPoint3(5, 0, 0)) << std::endl; // Hidden Dragon 
    std::cout << game.drop(10, SmallPoint3(5, 0, 0)) << std::endl; // Hidden Dragon 
    std::cout << game.drop(11, SmallPoint3(5, 1, 0)) << std::endl; // Prodigy 
    std::cout << game.drop(11, SmallPoint3(5, 1, 0)) << std::endl; // Prodigy 
    std::cout << game.drop(12, SmallPoint3(6, 0, 0)) << std::endl; // Archer
    std::cout << game.drop(12, SmallPoint3(6, 0, 0)) << std::endl; // Archer
    std::cout << game.drop(13, SmallPoint3(6, 1, 0)) << std::endl; // Archer
    std::cout << game.drop(13, SmallPoint3(6, 1, 0)) << std::endl; // Archer
    std::cout << game.drop(14, SmallPoint3(0, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(14, SmallPoint3(0, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(15, SmallPoint3(1, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(15, SmallPoint3(1, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(16, SmallPoint3(2, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(16, SmallPoint3(2, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(17, SmallPoint3(3, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(17, SmallPoint3(3, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(18, SmallPoint3(4, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(18, SmallPoint3(4, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(19, SmallPoint3(5, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(19, SmallPoint3(5, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(20, SmallPoint3(6, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(20, SmallPoint3(6, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(21, SmallPoint3(8, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(21, SmallPoint3(8, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(22, SmallPoint3(8, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(22, SmallPoint3(8, 2, 0)) << std::endl; // Soldier 
}
/*
void placePieces(Game& game)
{
    std::cout << game.drop(0,  SmallPoint3(0, 0, 0)) << std::endl; // Commander
    std::cout << game.drop(0,  SmallPoint3(0, 0, 0)) << std::endl; // Commander
    std::cout << game.drop(1,  SmallPoint3(1, 0, 0)) << std::endl; // Captain 
    std::cout << game.drop(1,  SmallPoint3(1, 0, 0)) << std::endl; // Captain 
    std::cout << game.drop(2,  SmallPoint3(0, 1, 0)) << std::endl; // Captain 
    std::cout << game.drop(2,  SmallPoint3(0, 1, 0)) << std::endl; // Captain 
    std::cout << game.drop(3,  SmallPoint3(1, 1, 0)) << std::endl; // Samurai
    std::cout << game.drop(3,  SmallPoint3(1, 1, 0)) << std::endl; // Samurai 
    std::cout << game.drop(4,  SmallPoint3(2, 0, 0)) << std::endl; // Samurai 
    std::cout << game.drop(4,  SmallPoint3(2, 0, 0)) << std::endl; // Samurai 
    std::cout << game.drop(5,  SmallPoint3(2, 1, 0)) << std::endl; // Ninja 
    std::cout << game.drop(5,  SmallPoint3(2, 1, 0)) << std::endl; // Ninja 
    std::cout << game.drop(6,  SmallPoint3(3, 0, 0)) << std::endl; // Ninja 
    std::cout << game.drop(6,  SmallPoint3(3, 0, 0)) << std::endl; // Ninja 
    std::cout << game.drop(7,  SmallPoint3(3, 1, 0)) << std::endl; // Ninja 
    std::cout << game.drop(7,  SmallPoint3(3, 1, 0)) << std::endl; // Ninja 
    std::cout << game.drop(8,  SmallPoint3(4, 0, 0)) << std::endl; // Catapult 
    std::cout << game.drop(8,  SmallPoint3(4, 0, 0)) << std::endl; // Catapult 
    std::cout << game.drop(9,  SmallPoint3(4, 1, 0)) << std::endl; // Fortress 
    std::cout << game.drop(9,  SmallPoint3(4, 1, 0)) << std::endl; // Fortress 
    std::cout << game.drop(10, SmallPoint3(5, 0, 0)) << std::endl; // Hidden Dragon 
    std::cout << game.drop(10, SmallPoint3(5, 0, 0)) << std::endl; // Hidden Dragon 
    std::cout << game.drop(11, SmallPoint3(5, 1, 0)) << std::endl; // Prodigy 
    std::cout << game.drop(11, SmallPoint3(5, 1, 0)) << std::endl; // Prodigy 
    std::cout << game.drop(12, SmallPoint3(6, 0, 0)) << std::endl; // Archer
    std::cout << game.drop(12, SmallPoint3(6, 0, 0)) << std::endl; // Archer
    std::cout << game.drop(13, SmallPoint3(6, 1, 0)) << std::endl; // Archer
    std::cout << game.drop(13, SmallPoint3(6, 1, 0)) << std::endl; // Archer
    std::cout << game.drop(14, SmallPoint3(0, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(14, SmallPoint3(0, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(15, SmallPoint3(1, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(15, SmallPoint3(1, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(16, SmallPoint3(2, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(16, SmallPoint3(2, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(17, SmallPoint3(3, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(17, SmallPoint3(3, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(18, SmallPoint3(4, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(18, SmallPoint3(4, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(19, SmallPoint3(5, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(19, SmallPoint3(5, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(20, SmallPoint3(6, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(20, SmallPoint3(6, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(21, SmallPoint3(7, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(21, SmallPoint3(7, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(22, SmallPoint3(8, 2, 0)) << std::endl; // Soldier 
    std::cout << game.drop(22, SmallPoint3(8, 2, 0)) << std::endl; // Soldier 
}
*/
void displayBoard(const Board& board)
{
    /*
    for (uint8_t ht = 0; ht < board.getHeight(); ++ht)
    {
        for (uint8_t wd = 0; wd < board.getWidth(); ++wd)
        {
            for (uint8_t dp = 8; dp < board.getDepth(); --dp)
            {
                auto p = board(wd, dp, ht);
                print(*p);
            }
            std::cout << "|";
        }
    }
    */
}

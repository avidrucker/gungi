#include <iostream>

#include <Engine.hpp>

/**
 * Notes:
 * Using Clang && GCC on 32-Bit:
 * sizeof (Piece) = ?
 * sizeof (uint8_t) = ?
 * sizeof (SmallPoint3) = ?
 * sizeof (IndexedPiece) = ?
 *
 * On 64-Bit:
 * sizeof (Piece) = TBD
 * sizeof (uint8_t) = TBD
 * sizeof (SmallPoint3) = TBD
 * sizeof (IndexedPiece) = TBD
 */

using std::cout;
using std::cin;
using std::endl;
using namespace Gungi;

char getHeadChar(const Head& head);
char getTailChar(const Tail& tail);
void print(const Piece& piece);
void placePieces(Game& game);
void displayBoard(const Board& board);
void displayPlayerSet(const Player& player);
void displayPieces(const Game& game);

void displayState(const Game& game)
{
    const Board* board = game.gameBoard();
   // const Player* one = game.playerOne();
   // const Player* two = game.playerTwo();
    displayBoard(*board);
   // cout << "Player One: " << endl;
   // displayPlayerSet(*one);
   // cout << "Player Two: " << endl;
   // displayPlayerSet(*two);
//    displayPieces(game);
}

int main()
{
    /*
        cout << sizeof (Piece) << endl
        << sizeof (uint8_t) << endl
        << sizeof (SmallPoint3) << endl
        << sizeof (IndexedPiece) << endl;
    */

    Game game;
    game.start(); // Set Phase to Placement
    placePieces(game);
    game.start(); // Set Phase to Running
    displayState(game);
    /*
    for (SizeType i = 0; i < 23; ++i)
    {
        game.move(i, Move(1, Direction::N));
        displayState(game);
        game.move(i, Move(1, Direction::N));
        displayState(game);
    }
    */
    game.move(10, Move(3, Direction::N));
    displayState(game);
    game.move(10, Move(3, Direction::N));
    displayState(game);
    
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

void print(const Piece& piece)
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
    game.drop(0,  SmallPoint3(0, 0, 0)); // Commander
    game.drop(0,  SmallPoint3(0, 0, 0)); // Commander
    game.drop(1,  SmallPoint3(1, 0, 0)); // Captain 
    game.drop(1,  SmallPoint3(1, 0, 0)); // Captain 
    game.drop(2,  SmallPoint3(0, 1, 0)); // Captain 
    game.drop(2,  SmallPoint3(0, 1, 0)); // Captain 
    game.drop(3,  SmallPoint3(1, 1, 0)); // Samurai
    game.drop(3,  SmallPoint3(1, 1, 0)); // Samurai 
    game.drop(4,  SmallPoint3(2, 0, 0)); // Samurai 
    game.drop(4,  SmallPoint3(2, 0, 0)); // Samurai 
    game.drop(5,  SmallPoint3(2, 1, 0)); // Ninja 
    game.drop(5,  SmallPoint3(2, 1, 0)); // Ninja 
    game.drop(6,  SmallPoint3(3, 0, 0)); // Ninja 
    game.drop(6,  SmallPoint3(3, 0, 0)); // Ninja 
    game.drop(7,  SmallPoint3(3, 1, 0)); // Ninja 
    game.drop(7,  SmallPoint3(3, 1, 0)); // Ninja 
    game.drop(8,  SmallPoint3(4, 0, 0)); // Catapult 
    game.drop(8,  SmallPoint3(4, 0, 0)); // Catapult 
    game.drop(9,  SmallPoint3(4, 1, 0)); // Fortress 
    game.drop(9,  SmallPoint3(4, 1, 0)); // Fortress 
    game.drop(10, SmallPoint3(5, 0, 0)); // Hidden Dragon 
    game.drop(10, SmallPoint3(5, 0, 0)); // Hidden Dragon 
    game.drop(11, SmallPoint3(5, 1, 0)); // Prodigy 
    game.drop(11, SmallPoint3(5, 1, 0)); // Prodigy 
    game.drop(12, SmallPoint3(6, 0, 0)); // Archer
    game.drop(12, SmallPoint3(6, 0, 0)); // Archer
    game.drop(13, SmallPoint3(6, 1, 0)); // Archer
    game.drop(13, SmallPoint3(6, 1, 0)); // Archer
    game.drop(14, SmallPoint3(0, 2, 0)); // Soldier 
    game.drop(14, SmallPoint3(0, 2, 0)); // Soldier 
    game.drop(15, SmallPoint3(1, 2, 0)); // Soldier 
    game.drop(15, SmallPoint3(1, 2, 0)); // Soldier 
    game.drop(16, SmallPoint3(2, 2, 0)); // Soldier 
    game.drop(16, SmallPoint3(2, 2, 0)); // Soldier 
    game.drop(17, SmallPoint3(3, 2, 0)); // Soldier 
    game.drop(17, SmallPoint3(3, 2, 0)); // Soldier 
    game.drop(18, SmallPoint3(4, 2, 0)); // Soldier 
    game.drop(18, SmallPoint3(4, 2, 0)); // Soldier 
    game.drop(19, SmallPoint3(5, 2, 0)); // Soldier 
    game.drop(19, SmallPoint3(5, 2, 0)); // Soldier 
    game.drop(20, SmallPoint3(6, 2, 0)); // Soldier 
    game.drop(20, SmallPoint3(6, 2, 0)); // Soldier 
    game.drop(21, SmallPoint3(7, 2, 0)); // Soldier 
    game.drop(21, SmallPoint3(7, 2, 0)); // Soldier 
    game.drop(22, SmallPoint3(8, 2, 0)); // Soldier 
    game.drop(22, SmallPoint3(8, 2, 0)); // Soldier 
}

void displayBoard(const Board& board)
{
    for (int j = 8; j != -1; --j)
    {
        for (SizeType k = 0; k < board.getHeight(); ++k)
        {
            for (SizeType i = 0; i < board.getWidth(); ++i)
            {
                cout << '|';
                auto p = board(i,j,k);
                print (*p);
            }
            cout << "|  ";
        }
        cout << endl;
    }
    cout << endl;
}

void displayPlayerSet(const Player& player)
{
    auto pieceSet = player.getFullSet();
    
    for (SizeType i = 0; i < pieceSet.Set.size(); ++i)
    {
        cout << "Index: " << (size_t) i << " --> Piece: ";
        const auto piece = pieceSet.pieceAt(i);
        if (piece.onHead()) 
            cout << getHeadString(piece) << " --> ";
        else 
            cout << getTailString(piece) << " --> ";
        cout << " Point3: " << pieceSet.pointAt(i) << "  |  ";
        if (i != 0 && i % 2 == 0) cout << endl;
    }
    cout << endl;
}

void displayPieces(const Game& game)
{
    auto pieceSet = game.currentPlayer().getFullSet();
    
    for (SizeType i = 0; i < pieceSet.Set.size(); ++i)
    {
        cout << "Index: " << (size_t) i << " --> Piece: ";
        const auto piece = pieceSet.pieceAt(i);
        if (piece.onHead()) 
            cout << getHeadString(piece) << " --> ";
        else 
            cout << getTailString(piece) << " --> ";
        cout << " Point3: " << pieceSet.pointAt(i) << "  |  ";
        if (i % 2 != 0) cout << endl;
    }
    cout << endl << endl;
}

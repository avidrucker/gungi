#pragma once

namespace Gungi
{
    constexpr uint8_t BOARD_SIZE = 9;
    constexpr uint8_t NUM_FRONT_PIECES = 10;
    constexpr uint8_t NUM_BACK_PIECES = 10; 

    /**
     * Heads
     */

    enum class Head : uint8_t
    { None, Commander, Captain, Samurai, Ninja,  Catapult, 
        Fortress, HiddenDragon , Prodigy, Archer, Soldier };

    constexpr uint8_t CAPTAIN_RANK = 12;
    constexpr uint8_t SAMURAI_RANK = 10;
    constexpr uint8_t NINJA_RANK = 8;
    constexpr uint8_t HIDDEN_DRAGON_RANK = 8;
    constexpr uint8_t CATAPULT_RANK = 6;
    constexpr uint8_t FORTRESS_RANK = 6;
    constexpr uint8_t PRODIGY_RANK = 4;
    constexpr uint8_t ARCHER_RANK = 4;
    constexpr uint8_t SOLDIER_RANK = 2;
    constexpr uint8_t NO_HEAD = 0;
    
    /**
     * Tails
     */

    enum class Tail : uint8_t
    { None, Pistol, Pike, Jounin, Lance, DragonKing,
        Phoenix, Arrow, Gold, Silver, Bronze };

    constexpr uint8_t DRAGON_KING_RANK = 12;
    constexpr uint8_t LANCE_RANK = 10;
    constexpr uint8_t PHOENIX_RANK = 10;
    constexpr uint8_t JOUNIN_RANK = 8;
    constexpr uint8_t ARROW_RANK = 6;
    constexpr uint8_t PIKE_RANK = 6;
    constexpr uint8_t GOLD_RANK = 6;
    constexpr uint8_t PISTOL_RANK = 4;
    constexpr uint8_t SILVER_RANK = 4;
    constexpr uint8_t BRONZE_RANK = 2;
    constexpr uint8_t NO_TAIL = 0;
    
    struct Piece
    {
        Piece()
        : head      (Head::None)
        , tail      (Tail::None) 
        , nullPiece (true)
        {}

        Piece(const Head& h, const Tail& t = Tail::None)
        : head      (h)
        , tail      (t)
        , nullPiece (false)
        {}

        Head head;
        Tail tail;
        bool nullPiece;
    };
    

    uint8_t getHeadValue(const Piece& piece)
    j
        switch (piece.head)
        {
            case Head::Captain:
                return CAPTAIN_RANK;
            case Head::Samurai:
                return SAMURAI_RANK;
            case Head::Ninja:
                return NINJA_RANK;
            case Head::Catapult:
                return CATAPULT_RANK;
            case Head::Fortress:
                return FORTRESS_RANK;
            case Head::HiddenDragon:
                return HIDDEN_DRAGON_RANK;
            case Head::Prodigy:
                return PRODIGY_RANK;
            case Head::Archer:
                return ARCHER_RANK;
            case Head::Soldier:
                return SOLDIER_RANK;
            default:
                return NO_HEAD;
        }
    }

    uint8_t getTailValue(const Piece& piece)
    {
        switch (piece.tail)
        {
            case Tail::DragonKing:
                return DRAGON_KING_RANK;
            case Tail::Lance:
                return LANCE_RANK;
            case Tail::Phoenix:
                return PHOENIX_RANK;
            case Tail::Jounin:
                return JOUNIN_RANK;
            case Tail::Arrow:
                return ARROW_RANK;
            case Tail::Pike:
                return PIKE_RANK;
            case Tail::Gold:
                return GOLD_RANK;
            case Tail::Pistol:
                return PISTOL_RANK;
            case Tail::Silver:
                return SILVER_RANK;
            case Tail::Bronze:
                return BRONZE_RANK;
            default:
                return NO_TAIL;

        }
    }
}

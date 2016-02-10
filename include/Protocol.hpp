#pragma once

#include <memory>
#include <set>

namespace Gungi
{
    constexpr uint8_t BOARD_SIZE = 9;
    constexpr uint8_t NUM_FRONT_PIECES = 10;
    constexpr uint8_t NUM_BACK_PIECES = 10; 

    using MoveSet = std::set<Move>;

    constexpr uint8_t INFINITE_RANGE = ~0;

    namespace DIRECTIONS
    {
        constexpr uint8_t COUNT = 8;
        constexpr uint8_t NW = 0;
        constexpr uint8_t N = 1;
        constexpr uint8_t NE = 2;
        constexpr uint8_t E = 3;
        constexpr uint8_t SE = 4;
        constexpr uint8_t S = 5;
        constexpr uint8_t SW 6;
        constexpr uint8_t W = 7;
    }

    enum class Direction : uint8_t 
    { NW, N, NE, E, SE, S, SW, W };

    /**
     * Check this
     */
    class Move
    {
        using MovePtr = std::shared_ptr<Move>;

        public:
            Move(const uint8_t& steps, const Direction& direction, MovePtr next = nullptr)
            : _steps     (steps)
            , _direction (direction)
            , _next      (next)
            {}

            const uint8_t& getSteps() const
            {
                return _steps;
            }

            const Direction& getDirection() const
            {
                return _direction;
            }
            
            MovePtr getNext() const
            {
                return _next;
            }
        
        private:
            const uint8_t _steps;
            const Direction _direction;
            MovePtr _next;
    };

    enum class Tier : uint8_t 
    { One, Two, Three };

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
        Head head;
        Tail tail;
        
        bool nullPiece;

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
    };
    
    uint8_t getHeadValue(const Piece& piece)
    {
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

    
    void genCommanderMoveSet(MoveSet& moveset)
    {
        moveset.emplace(1, Direction::NW);
        moveset.emplace(1, Direction::N);
        moveset.emplace(1, Direction::NE);
        moveset.emplace(1, Direction::E);
        moveset.emplace(1, Direction::SE);
        moveset.emplace(1, Direction::S);
        moveset.emplace(1, Direction::SW);
        moveset.emplace(1, Direction::W);
    }

    void genCaptainMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::S);
            moveset.emplace(1, Direction::SW);
        }
        else
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NW);
        }
    }

    void genSamuraiMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {
            move[DIRECTIONS::NW] = 1;
            move[DIRECTIONS::N]  = 1;
            move[DIRECTIONS::NE] = 1;
            move[DIRECTIONS::E] = 1;
            move[DIRECTIONS::W] = 1;
        }
        else
        {
            move[DIRECTIONS::NW] = 1;
            move[DIRECTIONS::N]  = 2;
            move[DIRECTIONS::NE] = 1;
            move[DIRECTIONS::E] = 1;
            move[DIRECTIONS::S] = 2;
            move[DIRECTIONS::W] = 1;
        }

        moveset.insert(move);
    }

    void genNinjaMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {
            move[DIRECTIONS::] = 1;     
        }
        else
        {

        }

        moveset.insert(move);
    }

    void genCatapultMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genFortressMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genHiddenDragonMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genProdigyMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genArcherMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genSoldierMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genDragonKingMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genLanceMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genPhoenixMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genJouninMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genPikeMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genGoldMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genPistolMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genSilverMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    void genBronzeMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };

        if (tier == Tier::One)
        {

        }
        else if (tier == Tier::Two)
        {

        }
        else
        {

        }

        moveset.insert(move);
    }

    MoveSet genHeadMoveSet(const Piece& piece, const Tier& tier)
    {
        MoveSet moveset;
        
        switch (piece.head)
        {
            case Head::Commader:
                genCommanderMoveSet(moveset);
                break;
            case Head::Captain:
                genCaptainMoveSet(moveset, tier);
                break;
            case Head::Samurai:
                genSamuraiMoveSet(moveset, tier);
                break;
            case Head::Ninja:
                genNinjaMoveSet(moveset, tier);
                break;
            case Head::Catapult:
                genCatapultMoveSet(moveset, tier);
                break;
            case Head::Fortress:
                genFortressMoveSet(moveset, tier);
                break;
            case Head::HiddenDragon:
                genHiddenDragonMoveSet(moveset, tier);
                break;
            case Head::Prodigy:
                genProdigyMoveSet(moveset, tier);
                break;
            case Head::Archer:
                genArcherMoveSet(moveset, tier);
                break;
            case Head::Soldier:
                genSoldierMoveSet(moveset, tier);
                break;
            default:
        }

        return moveset;
    }

    MoveSet genTailMoveSet(const Piece& piece, const Tier& tier)
    {
        MoveSet moveset;
        
        switch (piece.tail)
        {
            case Tail::DragonKing:
                genDragonKingMoveSet(moveset, tier);
                break;
            case Tail::Lance:
                genLanceMoveSet(moveset, tier);
                break;
            case Tail::Phoenix:
                genPhoenixMoveSet(moveset, tier);
                break;
            case Tail::Jounin:
                genJouninMoveSet(moveset, tier);
                break;
            case Tail::Arrow:
                genArrowMoveSet(moveset, tier);
                break;
            case Tail::Pike:
                genPikeMoveSet(moveset, tier);
                break;
            case Tail::Gold:
                genGoldMoveSet(moveset, tier);
                break;
            case Tail::Pistol:
                genPistolMoveSet(moveset, tier);
                break;
            case Tail::Silver:
                genSilverMoveSet(moveset, tier);
                break;
            case Tail::Bronze:
                genBronzeMoveSet(moveset, tier);
                break;
            default:
        }

        return moveset;
    }

}

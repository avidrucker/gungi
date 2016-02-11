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
        public:
            Move(const uint8_t& steps, const Direction& direction)
            : _steps     (steps)
            , _direction (direction)
            , _next      (nullptr)
            {}

            Move(const uint8_t& steps, const Direction& direction, 
                    const uint8_t& nextSteps, const uint8_t& nextDirection)
            : _steps     (steps)
            , _direction (direction)
            , _next      (new Move(nextSteps, nextDirection))
            {}

            ~Move()
            {
                if (_next != nullptr)
                    delete _next;
            }

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

    class Piece
    {
        public:
            Piece()
            : _head      (Head::None)
            , _tail      (Tail::None) 
            , _nullPiece (true)
            , _onHead    (true) 
            {}

            Piece(const Head& head, const Tail& tail = Tail::None)
            : _head      (head)
            , _tail      (tail)
            , _nullPiece (false)
              _onHead    (true)
            {}

            void setSide(const bool& onHead)
            {
                _onHead = onHead;
            }

            const Head& getHead() const
            {
                return _head;
            }

            const Tail& getTail() const
            {
                return _tail;
            }

            bool isNull() const
            {
                return _nullPiece;
            }

            bool onHead() const
            {
                return _onHead;
            }

        private:
            const Head _head;
            const Tail _tail;
            const bool _nullPiece;
            bool _onHead;

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
            moveset.emplace(2, Direction::NW);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(2, Direction::NE);
            moveset.emplace(2, Direction::E);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
            moveset.emplace(2, Direction::W);
        }
    }

    void genSamuraiMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::E);
            moveset.emplace(1, Direction::W);
        }
        else
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(2, Direction::N);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::E);
            moveset.emplace(2, Direction::S);
            moveset.emplace(1, Direction::W);
        }
    }

    void genNinjaMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier != Tier::One)
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NE);
        }
        moveset.emplace(1, Direction::NW, 1, Direction::N);
        moveset.emplace(1, Direction::NE, 1, Direction::N);
    }

    /**
     * Mobile expanders
     */
    void genCatapultMoveSet(MoveSet& moveset, const Tier& tier)
    {}

    /**
     * Mobile expanders
     */
    void genFortressMoveSet(MoveSet& moveset, const Tier& tier)
    {}

    void genHiddenDragonMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(INFINITE_RANGE, Direction::N);
            moveset.emplace(INFINITE_RANGE, Direction::E);
            moveset.emplace(INFINITE_RANGE, Direction::S);
            moveset.emplace(INFINITE_RANGE, Direction::W);
        }
        else
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
        }
    }

    void genProdigyMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };
 
        if (tier == Tier::One)
        {
            moveset.emplace(INFINITE_RANGE, Direction::NW);
            moveset.emplace(INFINITE_RANGE, Direction::NE);
            moveset.emplace(INFINITE_RANGE, Direction::SE);
            moveset.emplace(INFINITE_RANGE, Direction::SW);
        }
        else
        {
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::E);
            moveset.emplace(1, Direction::S);
            moveset.emplace(1, Direction::W);
        }
    }

    void genArcherMoveSet(MoveSet& moveset, const Tier& tier)
    {
        Move move { DIRECTIONS::COUNT, 0 };
 
        if (tier == Tier::One)
        {
            moveset.emplace(2, Direction::N);
            moveset.emplace(2, Direction::E);
            moveset.emplace(2, Direction::W);
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace(2, Direction::NW);
            moveset.emplace(1, Direction::N);
            moveset.emplace(2, Direction::NE);
            moveset.emplace(1, Direction::S);
        }
        else
        {
            moveset.emplace(2, Direction::NW);
            moveset.emplace(2, Direction::NE);
            moveset.emplace(2, Direction::NE);
            moveset.emplace(2, Direction::E);
            moveset.emplace(2, Direction::S);
            moveset.emplace(2, Direction::W);
        }
    }

    void genSoldierMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(1,Direction::N); 
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace(1,Direction::N); 
            moveset.emplace(2,Direction::E); 
            moveset.emplace(2,Direction::W); 
        }
        else
        {
            moveset.emplace(1,Direction::NW); 
            moveset.emplace(1,Direction::NE); 
            moveset.emplace(2,Direction::E); 
            moveset.emplace(2,Direction::W); 
        }
    }

    void genDragonKingMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(INFINITE_RANGE, Direction::N);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(INFINITE_RANGE, Direction::E);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(INFINITE_RANGE, Direction::S);
            moveset.emplace(1, Direction::SW);
            moveset.emplace(INFINITE_RANGE, Direction::W);
        }
        else
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
        }
    }

    void genLanceMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(INFINITE_RANGE, Direction::N);
        }
        else
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
        }
    }

    void genPhoenixMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(INFINITE_RANGE, Direction::NW);
            moveset.emplace(1, Direction::N);
            moveset.emplace(INFINITE_RANGE, Direction::NE);
            moveset.emplace(1, Direction::E);
            moveset.emplace(INFINITE_RANGE, Direction::SE);
            moveset.emplace(1, Direction::S);
            moveset.emplace(INFINITE_RANGE, Direction::SW);
            moveset.emplace(1, Direction::W);
        }
        else
        {
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::E);
            moveset.emplace(1, Direction::S);
            moveset.emplace(1, Direction::W);
        }
    }

    void genJouninMoveSet(MoveSet& moveset, const Tier& tier)
    {
        moveset.emplace(1,Direction::NW, 1, Direction::N);
        moveset.emplace(1,Direction::NE, 1, Direction::N);
        moveset.emplace(1,Direction::S);

        if (tier == Tier::Two || tier == Tier::Three)
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NE);

            if (tier == Tier::Three)
            {
                moveset.emplace(2, Direction::SE);
                moveset.emplace(2, Direction::SE);
                moveset.emplace(2, Direction::SW);
                moveset.emplace(2, Direction::SW);
            }
        }
    }

    void genPikeMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(2, Direction::N);
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::E);
            moveset.emplace(1, Direction::S);
            moveset.emplace(1, Direction::W);
        }
        else
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
        }
    }

    void genArrowMoveSet(MoveSet& moveset, const Tier& tier)
    {
        moveset.emplace(1,Direction::N);
        moveset.emplace(1,Direction::S);
        if (tier == Tier::One)
        {
            moveset.emplace(1,Direction::SE);
            moveset.emplace(1,Direction::SW);
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace(2,Direction::SE);
            moveset.emplace(2,Direction::SW);
        }
        else
        {
            moveset.emplace(1,Direction::SE);
            moveset.emplace(1,Direction::SW);
            moveset.emplace(2,Direction::SE);
            moveset.emplace(2,Direction::SW);
        }
    }

    void genGoldMoveSet(MoveSet& moveset)
    {
        moveset.emplace(1,Direction::NW);
        moveset.emplace(1,Direction::N);
        moveset.emplace(1,Direction::NE);
        moveset.emplace(1,Direction::E);
        moveset.emplace(1,Direction::S);
        moveset.emplace(1,Direction::W);
    }

    void genPistolMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
            moveset.emplace(1, Direction::NW);
        }
        else
        {
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::E);
            moveset.emplace(1, Direction::S);
            moveset.emplace(1, Direction::W);
        }
    }

    void genSilverMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace(1, Direction::N);
            moveset.emplace(1, Direction::E);
            moveset.emplace(1, Direction::S);
            moveset.emplace(1, Direction::W);
        }
        else
        {
            moveset.emplace(1, Direction::NW);
            moveset.emplace(1, Direction::NE);
            moveset.emplace(1, Direction::SE);
            moveset.emplace(1, Direction::SW);
        }
    }

    void genBronzeMoveSet(MoveSet& moveset)
    {
        moveset.emplace(1, Direction::E);
        moveset.emplace(1, Direction::W);
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
                genBronzeMoveSet(moveset);
                break;
            default:
        }

        return moveset;
    }

}

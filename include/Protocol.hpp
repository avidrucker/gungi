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

    enum class Direction : uint8_t 
    { NW, N, NE, E, SE, S, SW, W };

    class Move
    {
        public:
            Move(const uint8_t& steps, const Direction& direction);
            Move(const uint8_t& steps, const Direction& direction, 
                    const uint8_t& nextSteps, const uint8_t& nextDirection);
            ~Move();
            const uint8_t& getSteps() const;
            const Direction& getDirection() const;
            MovePtr getNext() const;
        
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
            Piece();
            Piece(const Head& head, const Tail& tail = Tail::None);
            void setSide(const bool& onHead);
            const Head& getHead() const;
            const Tail& getTail() const;
            bool isNull() const;
            bool onHead() const;

        private:
            const Head _head;
            const Tail _tail;
            const bool _nullPiece;
            bool _onHead;

    };
    
    uint8_t getHeadValue(const Piece& piece);
    uint8_t getTailValue(const Piece& piece);

    void genCommanderMoveSet    (MoveSet& moveset);
    void genCaptainMoveSet      (MoveSet& moveset, const Tier& tier);
    void genSamuraiMoveSet      (MoveSet& moveset, const Tier& tier);
    void genNinjaMoveSet        (MoveSet& moveset, const Tier& tier);
    void genCatapultMoveSet     (MoveSet& moveset, const Tier& tier);
    void genFortressMoveSet     (MoveSet& moveset, const Tier& tier);
    void genHiddenDragonMoveSet (MoveSet& moveset, const Tier& tier);
    void genProdigyMoveSet      (MoveSet& moveset, const Tier& tier);
    void genArcherMoveSet       (MoveSet& moveset, const Tier& tier);
    void genSoldierMoveSet      (MoveSet& moveset, const Tier& tier);
    void genDragonKingMoveSet   (MoveSet& moveset, const Tier& tier);
    void genLanceMoveSet        (MoveSet& moveset, const Tier& tier);
    void genPhoenixMoveSet      (MoveSet& moveset, const Tier& tier);
    void genJouninMoveSet       (MoveSet& moveset, const Tier& tier);
    void genPikeMoveSet         (MoveSet& moveset, const Tier& tier);
    void genArrowMoveSet        (MoveSet& moveset, const Tier& tier);
    void genGoldMoveSet         (MoveSet& moveset);
    void genPistolMoveSet       (MoveSet& moveset, const Tier& tier);
    void genSilverMoveSet       (MoveSet& moveset, const Tier& tier);
    void genBronzeMoveSet       (MoveSet& moveset);

    MoveSet genHeadMoveSet(const Piece& piece, const Tier& tier);
    MoveSet genTailMoveSet(const Piece& piece, const Tier& tier);

}

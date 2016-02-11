/*
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 * 
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 * 
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 * 
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include "Protocol.hpp"

namespace Gungi
{

    // move.Class
    //
    Move::Move(const uint8_t& steps, const Direction& direction)
    : _steps     (steps)
    , _direction (direction)
    , _next      (nullptr)
    {}

    Move::Move(const uint8_t& steps, const Direction& direction, 
        const uint8_t& nextSteps, const Direction& nextDirection)
    : _steps     (steps)
    , _direction (direction)
    , _next      (new Move(nextSteps, nextDirection))
    {}

    Move::~Move()
    {
        if (_next != nullptr)
            delete _next;
    }

    const uint8_t& Move::getSteps() const
    {
        return _steps;
    }

    const Direction& Move::getDirection() const
    {
        return _direction;
    }

    Move* Move::getNext() const
    {
        return _next;
    }

    // Piece class
    //
    Piece::Piece()
    : _head      (Head::None)
    , _tail      (Tail::None) 
    , _nullPiece (true)
    , _onHead    (true) 
    {}

    Piece::Piece(const Head& head, const Tail& tail)
    : _head      (head)
    , _tail      (tail)
    , _nullPiece (false)
    , _onHead    (true)
    {}

    void Piece::setSide(const bool& onHead)
    {
        _onHead = onHead;
    }

    const Head& Piece::getHead() const
    {
        return _head;
    }

    const Tail& Piece::getTail() const
    {
        return _tail;
    }

    bool Piece::isNull() const
    {
        return _nullPiece;
    }

    bool Piece::onHead() const
    {
        return _onHead;
    }

    //Free functions
    uint8_t getHeadValue(const Piece& piece)
    {
        switch (piece.getHead())
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
        switch (piece.getTail())
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
        moveset.emplace_back(1, Direction::NW);
        moveset.emplace_back(1, Direction::N);
        moveset.emplace_back(1, Direction::NE);
        moveset.emplace_back(1, Direction::E);
        moveset.emplace_back(1, Direction::SE);
        moveset.emplace_back(1, Direction::S);
        moveset.emplace_back(1, Direction::SW);
        moveset.emplace_back(1, Direction::W);
    }

    void genCaptainMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(1, Direction::SW);
        }
        else
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(2, Direction::NW);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(2, Direction::NE);
            moveset.emplace_back(2, Direction::E);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
            moveset.emplace_back(2, Direction::W);
        }
    }

    void genSamuraiMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(1, Direction::W);
        }
        else
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(2, Direction::N);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(2, Direction::S);
            moveset.emplace_back(1, Direction::W);
        }
    }

    void genNinjaMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier != Tier::One)
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::NE);
        }
        moveset.emplace_back(1, Direction::NW, 1, Direction::N);
        moveset.emplace_back(1, Direction::NE, 1, Direction::N);
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
            moveset.emplace_back(INFINITE_RANGE, Direction::N);
            moveset.emplace_back(INFINITE_RANGE, Direction::E);
            moveset.emplace_back(INFINITE_RANGE, Direction::S);
            moveset.emplace_back(INFINITE_RANGE, Direction::W);
        }
        else
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
        }
    }

    void genProdigyMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(INFINITE_RANGE, Direction::NW);
            moveset.emplace_back(INFINITE_RANGE, Direction::NE);
            moveset.emplace_back(INFINITE_RANGE, Direction::SE);
            moveset.emplace_back(INFINITE_RANGE, Direction::SW);
        }
        else
        {
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(1, Direction::W);
        }
    }

    void genArcherMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(2, Direction::N);
            moveset.emplace_back(2, Direction::E);
            moveset.emplace_back(2, Direction::W);
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace_back(2, Direction::NW);
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(2, Direction::NE);
            moveset.emplace_back(1, Direction::S);
        }
        else
        {
            moveset.emplace_back(2, Direction::NW);
            moveset.emplace_back(2, Direction::NE);
            moveset.emplace_back(2, Direction::NE);
            moveset.emplace_back(2, Direction::E);
            moveset.emplace_back(2, Direction::S);
            moveset.emplace_back(2, Direction::W);
        }
    }

    void genSoldierMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(1,Direction::N); 
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace_back(1,Direction::N); 
            moveset.emplace_back(2,Direction::E); 
            moveset.emplace_back(2,Direction::W); 
        }
        else
        {
            moveset.emplace_back(1,Direction::NW); 
            moveset.emplace_back(1,Direction::NE); 
            moveset.emplace_back(2,Direction::E); 
            moveset.emplace_back(2,Direction::W); 
        }
    }

    void genDragonKingMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(INFINITE_RANGE, Direction::N);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(INFINITE_RANGE, Direction::E);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(INFINITE_RANGE, Direction::S);
            moveset.emplace_back(1, Direction::SW);
            moveset.emplace_back(INFINITE_RANGE, Direction::W);
        }
        else
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
        }
    }

    void genLanceMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(INFINITE_RANGE, Direction::N);
        }
        else
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
        }
    }

    void genPhoenixMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(INFINITE_RANGE, Direction::NW);
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(INFINITE_RANGE, Direction::NE);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(INFINITE_RANGE, Direction::SE);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(INFINITE_RANGE, Direction::SW);
            moveset.emplace_back(1, Direction::W);
        }
        else
        {
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(1, Direction::W);
        }
    }

    void genJouninMoveSet(MoveSet& moveset, const Tier& tier)
    {
        moveset.emplace_back(1,Direction::NW, 1, Direction::N);
        moveset.emplace_back(1,Direction::NE, 1, Direction::N);
        moveset.emplace_back(1,Direction::S);

        if (tier == Tier::Two || tier == Tier::Three)
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::NE);

            if (tier == Tier::Three)
            {
                moveset.emplace_back(2, Direction::SE);
                moveset.emplace_back(2, Direction::SE);
                moveset.emplace_back(2, Direction::SW);
                moveset.emplace_back(2, Direction::SW);
            }
        }
    }

    void genPikeMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(2, Direction::N);
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(1, Direction::W);
        }
        else
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
        }
    }

    void genArrowMoveSet(MoveSet& moveset, const Tier& tier)
    {
        moveset.emplace_back(1,Direction::N);
        moveset.emplace_back(1,Direction::S);
        if (tier == Tier::One)
        {
            moveset.emplace_back(1,Direction::SE);
            moveset.emplace_back(1,Direction::SW);
        }
        else if (tier == Tier::Two)
        {
            moveset.emplace_back(2,Direction::SE);
            moveset.emplace_back(2,Direction::SW);
        }
        else
        {
            moveset.emplace_back(1,Direction::SE);
            moveset.emplace_back(1,Direction::SW);
            moveset.emplace_back(2,Direction::SE);
            moveset.emplace_back(2,Direction::SW);
        }
    }

    void genGoldMoveSet(MoveSet& moveset)
    {
        moveset.emplace_back(1,Direction::NW);
        moveset.emplace_back(1,Direction::N);
        moveset.emplace_back(1,Direction::NE);
        moveset.emplace_back(1,Direction::E);
        moveset.emplace_back(1,Direction::S);
        moveset.emplace_back(1,Direction::W);
    }

    void genPistolMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
            moveset.emplace_back(1, Direction::NW);
        }
        else
        {
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(1, Direction::W);
        }
    }

    void genSilverMoveSet(MoveSet& moveset, const Tier& tier)
    {
        if (tier == Tier::One)
        {
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(1, Direction::W);
        }
        else
        {
            moveset.emplace_back(1, Direction::NW);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(1, Direction::SW);
        }
    }

    void genBronzeMoveSet(MoveSet& moveset)
    {
        moveset.emplace_back(1, Direction::E);
        moveset.emplace_back(1, Direction::W);
    }

    MoveSet genHeadMoveSet(const Piece& piece, const Tier& tier)
    {
        MoveSet moveset;
        
        switch (piece.getHead())
        {
            case Head::Commander:
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
                return moveset;
        }

        return moveset;
    }

    MoveSet genTailMoveSet(const Piece& piece, const Tier& tier)
    {
        MoveSet moveset;
        
        switch (piece.getTail())
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
                genGoldMoveSet(moveset);
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
                return moveset;
        }

        return moveset;
    }

    template <class PieceMatrix, class Indices>
    bool isOccupied(const PieceMatrix& matrix, const Indices& idx)
    {
        return !matrix[idx].isNull();
    }

    template <class PieceMatrix>
    bool hasAnEmptyTier(const PieceMatrix& matrix, XYZ_Indices idx)
    {
        bool emptyTier = false;
        for (auto i = 0u; !emptyTier && i < BOARD_TIERS; ++i)
        {
            idx.z = i;
            if (matrix[idx].isNull())
                emptyTier = true; 
        }
        return emptyTier;
    }

    size_t OverflowSub(const size_t& lhs, const size_t& rhs, const size_t& overflow)
    {
        if (lhs < rhs)
            return overflow;
        else
            return lhs - rhs;
    }

    size_t OverflowAdd(const size_t& lhs, const size_t& rhs, 
            const size_t& constraint, const size_t& overflow)
    {
        size_t res = lhs + rhs;
        return res < constraint ? res : overflow;
    }

    /**
     * Assuming (0,0) is top left
     */
    template <class TwoDimMatrix, class Indices>
    Indices genIndexOf2DMove(const TwoDimMatrix& matrix, 
            Indices idx, const Move& move)
    {
        switch (move.getDirection())
        {
            case Direction::NW:
                idx.x = OverflowSub(idx.x, move.getSteps(), INDEX_OVERFLOW);
                idx.y = OverflowSub(idx.y, move.getSteps(), INDEX_OVERFLOW);
                break;
            case Direction::N:
                idx.y = OverflowSub(idx.y, move.getSteps(), INDEX_OVERFLOW);
                break;
            case Direction::NE:
                idx.x = OverflowAdd(idx.x, move.getSteps(), matrix.getWidth(), INDEX_OVERFLOW);
                idx.y = OverflowSub(idx.y, move.getSteps(), INDEX_OVERFLOW);
                break;
            case Direction::E:
                idx.x = OverflowAdd(idx.x, move.getSteps(), matrix.getWidth(), INDEX_OVERFLOW);
                break;
            case Direction::SE:
                idx.x = OverflowAdd(idx.x, move.getSteps(), matrix.getWidth(), INDEX_OVERFLOW);
                idx.y = OverflowAdd(idx.y, move.getSteps(), matrix.getLength(), INDEX_OVERFLOW);
                break;
            case Direction::S:
                idx.y = OverflowAdd(idx.y, move.getSteps(), matrix.getLength(), INDEX_OVERFLOW);
                break;
            case Direction::SW:
                idx.x = OverflowSub(idx.x, move.getSteps(), INDEX_OVERFLOW);
                idx.y = OverflowAdd(idx.y, move.getSteps(), matrix.getLength(), INDEX_OVERFLOW);
                break;
            case Direction::W:
                idx.x = OverflowSub(idx.x, move.getSteps(), INDEX_OVERFLOW);
                break;
        }
        return idx;
    }

    template <class TwoDimMatrix>
    bool inBound(const TwoDimMatrix& matrix, const XY_Indices& idx)
    {
        return idx.x < matrix.getWidth() && idx.y < matrix.getHeight();
    }

    template <class ThreeDimMatrix>
    XYZ_Indices genIndexOf3DMove(const ThreeDimMatrix& matrix, 
            XYZ_Indices idx, const Move& move)
    {
        auto twoDimIDX = genIndexOf2DMove(matrix, toXY(idx), move);
        return toXYZ(twoDimIDX, idx.z);    
    }

    template <class ThreeDimMatrix>
    bool inBound(const ThreeDimMatrix& matrix, const XYZ_Indices& idx)
    {
        return inBound(matrix, toXY(idx)) && idx.y < matrix.getHeight();
    }

    template <class Matrix, class Indices>
    auto genPossibleMoves(const Matrix& matrix, const Indices& idx, const MoveSet& moveset)
    {
        Heap3DMatrix<bool> allowedmove { BOARD_SIZE, BOARD_SIZE, BOARD_TIERS, false };
        for (auto itr = moveset.cbegin(); itr != moveset.cend(); ++itr)
        {
            auto moveIdx = genIndexOf3DMove(matrix, idx, *itr);
            if (inBound(matrix, moveIdx) && hasAnEmptyTier(matrix, moveIdx))
                allowedmove[moveIdx] = true;
        }

        return allowedmove;
    }
}

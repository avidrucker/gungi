/*
 * Copyright 2016 Fermin, Yaneury <fermin.yaneury@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Protocol.hpp"

namespace Gungi
{
    // Move Class

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

    IndexedPiece::IndexedPiece()
    : Piece ()
    , _idx  ()
    {}

    IndexedPiece::IndexedPiece(const Head& head, const Tail& tail, const Point3& idx)
    : Piece (head, tail)
    , _idx  (idx)
    {}

    void IndexedPiece::setIndex(const Point3& idx)
    {
        _idx = idx;
    }

    const Point3& IndexedPiece::getIndex() const
    {
        return _idx;
    }

    bool operator < (const IndexedPiece& lhs, const IndexedPiece& rhs)
    {
        return lhs._idx < rhs._idx;
    }

    StdPieceSet::StdPieceSet()
    {
       _pieceSet[0]  = IndexedPiece(Head::Commander);
       _pieceSet[1]  = IndexedPiece(Head::Captain, Tail::Pistol);
       _pieceSet[2]  = IndexedPiece(Head::Captain, Tail::Pistol);
       _pieceSet[3]  = IndexedPiece(Head::Samurai, Tail::Pike);
       _pieceSet[4]  = IndexedPiece(Head::Samurai, Tail::Pike);
       _pieceSet[5]  = IndexedPiece(Head::Ninja, Tail::Jounin);
       _pieceSet[6]  = IndexedPiece(Head::Ninja, Tail::Jounin);
       _pieceSet[7]  = IndexedPiece(Head::Ninja, Tail::Jounin);
       _pieceSet[8]  = IndexedPiece(Head::Catapult, Tail::Lance);
       _pieceSet[9]  = IndexedPiece(Head::Fortress, Tail::Lance);
       _pieceSet[10] = IndexedPiece(Head::HiddenDragon, Tail::DragonKing);
       _pieceSet[11] = IndexedPiece(Head::Prodigy, Tail::Phoenix);
       _pieceSet[12] = IndexedPiece(Head::Archer, Tail::Arrow);
       _pieceSet[13] = IndexedPiece(Head::Archer, Tail::Arrow);
       _pieceSet[14] = IndexedPiece(Head::Soldier, Tail::Gold);
       _pieceSet[15] = IndexedPiece(Head::Soldier, Tail::Silver);
       _pieceSet[16] = IndexedPiece(Head::Soldier, Tail::Bronze);
       _pieceSet[17] = IndexedPiece(Head::Soldier, Tail::Bronze);
       _pieceSet[18] = IndexedPiece(Head::Soldier, Tail::Bronze);
       _pieceSet[19] = IndexedPiece(Head::Soldier, Tail::Bronze);
       _pieceSet[20] = IndexedPiece(Head::Soldier, Tail::Bronze);
       _pieceSet[21] = IndexedPiece(Head::Soldier, Tail::Bronze);
       _pieceSet[22] = IndexedPiece(Head::Soldier, Tail::Bronze);
    }

    IndexedPiece& StdPieceSet::operator [] (size_t i)
    {
        return _pieceSet[i];
    }

    const IndexedPiece& StdPieceSet::operator [] (size_t i) const
    {
        return _pieceSet[i];
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
    bool hasAnEmptyTier(const PieceMatrix& matrix, Point3 idx)
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
                idx.x = OverflowSub(idx.x, move.getSteps(), UNBOUND);
                idx.y = OverflowSub(idx.y, move.getSteps(), UNBOUND);
                break;
            case Direction::N:
                idx.y = OverflowSub(idx.y, move.getSteps(), UNBOUND);
                break;
            case Direction::NE:
                idx.x = OverflowAdd(idx.x, move.getSteps(), matrix.getWidth(), UNBOUND);
                idx.y = OverflowSub(idx.y, move.getSteps(), UNBOUND);
                break;
            case Direction::E:
                idx.x = OverflowAdd(idx.x, move.getSteps(), matrix.getWidth(), UNBOUND);
                break;
            case Direction::SE:
                idx.x = OverflowAdd(idx.x, move.getSteps(), matrix.getWidth(), UNBOUND);
                idx.y = OverflowAdd(idx.y, move.getSteps(), matrix.getLength(), UNBOUND);
                break;
            case Direction::S:
                idx.y = OverflowAdd(idx.y, move.getSteps(), matrix.getLength(), UNBOUND);
                break;
            case Direction::SW:
                idx.x = OverflowSub(idx.x, move.getSteps(), UNBOUND);
                idx.y = OverflowAdd(idx.y, move.getSteps(), matrix.getLength(), UNBOUND);
                break;
            case Direction::W:
                idx.x = OverflowSub(idx.x, move.getSteps(), UNBOUND);
                break;
        }
        return idx;
    }

    template <class TwoDimMatrix>
    bool inBound(const TwoDimMatrix& matrix, const Point& idx)
    {
        return idx.x < matrix.getWidth() && idx.y < matrix.getHeight();
    }

    template <class ThreeDimMatrix>
    Point3 genIndexOf3DMove(const ThreeDimMatrix& matrix, 
            Point3 idx, const Move& move)
    {
        auto twoDimIDX = genIndexOf2DMove(matrix, toXY(idx), move);
        return toXYZ(twoDimIDX, idx.z);    
    }

    template <class ThreeDimMatrix>
    bool inBound(const ThreeDimMatrix& matrix, const Point3& idx)
    {
        return inBound(matrix, toXY(idx)) && idx.y < matrix.getHeight();
    }

    template <class Matrix, class Indices>
    auto genPossibleMoves(const Matrix& matrix, const Indices& idx, const MoveSet& moveset)
    {
        ThreeDimMatrix<bool> allowedMoves { BOARD_SIZE, BOARD_SIZE, BOARD_TIERS, false };

        for (auto itr = moveset.cbegin(); itr != moveset.cend(); ++itr)
        {
            auto moveIdx = genIndexOf3DMove(matrix, idx, *itr);
            if (inBound(matrix, moveIdx) && hasAnEmptyTier(matrix, moveIdx))
                allowedMoves[moveIdx] = true;
        }

        return allowedMoves;
    }
}

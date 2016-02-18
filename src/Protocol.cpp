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

#include <Protocol.hpp>

namespace Gungi
{
    bool isUnbounded(const SmallPoint2& pt)
    {
        return pt.x == UNBOUNDED && pt.y == UNBOUNDED;
    }

    bool isUnbounded(const SmallPoint3& pt)
    {
        return pt.x == UNBOUNDED && pt.z == UNBOUNDED
            && pt.y == UNBOUNDED;
    }

    Move::Move(const MagnitudeType& magnitude, const Direction& direction)
    : _magnitude (magnitude)
    , _direction (direction)
    , _next      (nullptr)
    {}

    Move::Move(const MagnitudeType& magnitude, const Direction& direction, 
        const MagnitudeType& nextMagnitude, const Direction& nextDirection)
    : _magnitude (magnitude)
    , _direction (direction)
    , _next      (new Move(nextMagnitude, nextDirection))
    {}

    Move::~Move()
    {
        if (_next != nullptr)
            delete _next;
    }

    const Move::MagnitudeType& Move::getMagnitude() const
    {
        return _magnitude;
    }

    const Direction& Move::getDirection() const
    {
        return _direction;
    }

    Move* Move::getNext() const
    {
        return _next;
    }

    Tier& operator ++(Tier& tier)
    {
        switch (tier)
        {
            case Tier::One:
                tier = Tier::Two;
                return tier;
            case Tier::Two:
                tier = Tier::Three;
                return tier;
            case Tier::Three:
                tier = Tier::One;
                return tier;
        }
    }

    Tier& operator --(Tier& tier)
    {
        switch (tier)
        {
            case Tier::One:
                tier = Tier::Three;
                return tier;
            case Tier::Two:
                tier = Tier::One;
                return tier;
            case Tier::Three:
                tier = Tier::Two;
                return tier;
        }
    }

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
    {
        if (head == Head::None)
            _nullPiece = true;
    }

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
    , _idx  (UBD_PT3)
    {}

    IndexedPiece::IndexedPiece(const Head& head, const Tail& tail, const SmallPoint3& idx)
    : Piece (head, tail)
    , _idx  (idx)
    {}

    void IndexedPiece::setIndex(const SmallPoint3& idx)
    {
        _idx = idx;
    }

    const SmallPoint3& IndexedPiece::getIndex() const
    {
        return _idx;
    }

    bool IndexedPiece::isUnbounded() const
    {
        return _idx == UBD_PT3;
    }

    bool operator < (const IndexedPiece& lhs, const IndexedPiece& rhs)
    {
        return lhs._idx < rhs._idx;
    }

    bool operator == (const IndexedPiece& lhs, const IndexedPiece& rhs)
    {
        return (lhs._idx == rhs._idx) && (lhs._head == rhs._head) && (lhs._tail == rhs._tail);
    }

    void initPieceSet(PieceSet& pieceSet)
    {
       pieceSet.push_back(IndexedPiece(Head::Commander));
       pieceSet.push_back(IndexedPiece(Head::Captain, Tail::Pistol));
       pieceSet.push_back(IndexedPiece(Head::Captain, Tail::Pistol));
       pieceSet.push_back(IndexedPiece(Head::Samurai, Tail::Pike));
       pieceSet.push_back(IndexedPiece(Head::Samurai, Tail::Pike));
       pieceSet.push_back(IndexedPiece(Head::Ninja, Tail::Jounin));
       pieceSet.push_back(IndexedPiece(Head::Ninja, Tail::Jounin));
       pieceSet.push_back(IndexedPiece(Head::Ninja, Tail::Jounin));
       pieceSet.push_back(IndexedPiece(Head::Catapult, Tail::Lance));
       pieceSet.push_back(IndexedPiece(Head::Fortress, Tail::Lance));
       pieceSet.push_back(IndexedPiece(Head::HiddenDragon, Tail::DragonKing));
       pieceSet.push_back(IndexedPiece(Head::Prodigy, Tail::Phoenix));
       pieceSet.push_back(IndexedPiece(Head::Archer, Tail::Arrow));
       pieceSet.push_back(IndexedPiece(Head::Archer, Tail::Arrow));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Gold));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Silver));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Bronze));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Bronze));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Bronze));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Bronze));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Bronze));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Bronze));
       pieceSet.push_back(IndexedPiece(Head::Soldier, Tail::Bronze));
    }
    
    RankSize getHeadValue(const Piece& piece)
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

    RankSize getTailValue(const Piece& piece)
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
            moveset.emplace_back(UNBOUNDED, Direction::N);
            moveset.emplace_back(UNBOUNDED, Direction::E);
            moveset.emplace_back(UNBOUNDED, Direction::S);
            moveset.emplace_back(UNBOUNDED, Direction::W);
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
            moveset.emplace_back(UNBOUNDED, Direction::NW);
            moveset.emplace_back(UNBOUNDED, Direction::NE);
            moveset.emplace_back(UNBOUNDED, Direction::SE);
            moveset.emplace_back(UNBOUNDED, Direction::SW);
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
            moveset.emplace_back(UNBOUNDED, Direction::N);
            moveset.emplace_back(1, Direction::NE);
            moveset.emplace_back(UNBOUNDED, Direction::E);
            moveset.emplace_back(1, Direction::SE);
            moveset.emplace_back(UNBOUNDED, Direction::S);
            moveset.emplace_back(1, Direction::SW);
            moveset.emplace_back(UNBOUNDED, Direction::W);
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
            moveset.emplace_back(UNBOUNDED, Direction::N);
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
            moveset.emplace_back(UNBOUNDED, Direction::NW);
            moveset.emplace_back(1, Direction::N);
            moveset.emplace_back(UNBOUNDED, Direction::NE);
            moveset.emplace_back(1, Direction::E);
            moveset.emplace_back(UNBOUNDED, Direction::SE);
            moveset.emplace_back(1, Direction::S);
            moveset.emplace_back(UNBOUNDED, Direction::SW);
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

    bool isNullAt(const Board& board, const SmallPoint3& pt)
    {
        return board[pt] == &NULL_PIECE;
    }

    void nullifyAt(Board& board, const SmallPoint3& pt)
    {
        board[pt] = &NULL_PIECE;
    }
    
    uint8_t availableTierAt(const Board& board, const SmallPoint2& pt)
    {
        for (uint8_t i = 0; i < BOARD_HEIGHT; ++i)
            if (isNullAt(board, SmallPoint3(pt.x, pt.y, i)))
                return i;
        return NO_TIERS_FREE;
    }

    uint8_t availableTierAt(const Board& board, SmallPoint3 pt)
    {
        for (uint8_t i = 0; i < BOARD_HEIGHT; ++i)
        {
            pt.y = i;
            if (isNullAt(board, pt))
                    return i;
        }
        return NO_TIERS_FREE;
    }
    
    bool hasOpenTierAt(const Board& board, const SmallPoint2& pt)
    {
        if (availableTierAt(board, pt) == NO_TIERS_FREE)
            return false;
        return true;
    }

    bool hasOpenTierAt(const Board& board, const SmallPoint3& pt)
    {
        if (availableTierAt(board, pt) == NO_TIERS_FREE)
            return false;
        return true;
    }

    void placeAt(Board& board, const IndexedPiece* piece)
    {
        board[piece->getIndex()] = piece;
    }
}

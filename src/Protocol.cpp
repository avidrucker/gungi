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

    void Piece::flip()
    {
        _onHead = !_onHead;
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

    bool isUnbounded(const SmallPoint2& pt)
    {
        return pt.x == UNBOUNDED && pt.y == UNBOUNDED;
    }

    bool isUnbounded(const SmallPoint3& pt)
    {
        return pt.x == UNBOUNDED && pt.z == UNBOUNDED
            && pt.y == UNBOUNDED;
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

    Phase& operator ++ (Phase& phase)
    {
        switch (phase)
        {
            case Phase::Standby:
                phase = Phase::Placement;
                return phase;
            case Phase::Placement:
                phase = Phase::Running;
                return phase;
            case Phase::Running:
                phase = Phase::Placement;
                return phase;
        }
    }

    Phase& operator -- (Phase& phase)
    {
        switch (phase)
        {
            case Phase::Standby:
                phase = Phase::Running;
                return phase;
            case Phase::Placement:
                phase = Phase::Standby;
                return phase;
            case Phase::Running:
                phase = Phase::Placement;
                return phase;
        }
    }

    void initPieceSet(PieceSet& pieceSet)
    {
       pieceSet.push_back(std::make_tuple(Piece(Head::Commander), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Captain, Tail::Pistol), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Captain, Tail::Pistol), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Samurai, Tail::Pike), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Samurai, Tail::Pike), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Ninja, Tail::Jounin), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Ninja, Tail::Jounin), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Ninja, Tail::Jounin), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Catapult, Tail::Lance), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Fortress, Tail::Lance), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::HiddenDragon, Tail::DragonKing), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Prodigy, Tail::Phoenix), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Archer, Tail::Arrow), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Archer, Tail::Arrow), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Gold), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Silver), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Bronze), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Bronze), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Bronze), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Bronze), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Bronze), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Bronze), UBD_PT3));
       pieceSet.push_back(std::make_tuple(Piece(Head::Soldier, Tail::Bronze), UBD_PT3));
    }
    
    SizeType getHeadValue(const Piece& piece)
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

    SizeType getTailValue(const Piece& piece)
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

    SmallPoint2 asPositive2(const SmallPoint2& pt2)
    {
        return SmallPoint2((BOARD_WIDTH - pt2.x - 1),
                (BOARD_DEPTH - pt2.y - 1));
    }

    SmallPoint2 asNegative2(const SmallPoint2& pt2)
    {
        return SmallPoint2((pt2.x + 1 - BOARD_WIDTH),
                (pt2.y + 1 - BOARD_DEPTH));
    }

    SmallPoint2 asPositive2(const SmallPoint3& pt3)
    {
        return SmallPoint2((BOARD_WIDTH - pt3.x - 1),
                (BOARD_DEPTH - pt3.z - 1));
    }

    SmallPoint2 asNegative2(const SmallPoint3& pt3)
    {
        return SmallPoint2((pt3.x + 1 - BOARD_WIDTH),
                (pt3.z + 1 - BOARD_DEPTH));
    }

    SmallPoint3 asPositive3(const SmallPoint2& pt2)
    {
        return SmallPoint3((BOARD_WIDTH - pt2.x - 1),
                (BOARD_DEPTH - pt2.y - 1), 0);
    }

    SmallPoint3 asNegative3(const SmallPoint2& pt2)
    {
        return SmallPoint3((pt2.x + 1 - BOARD_WIDTH),
                (pt2.y + 1 - BOARD_DEPTH), 0);
    }

    SmallPoint3 asPositive3(const SmallPoint3& pt3)
    {
        return SmallPoint3((BOARD_WIDTH - pt3.x - 1),
                (BOARD_DEPTH - pt3.z - 1), pt3.y);
    }

    SmallPoint3 asNegative3(const SmallPoint3& pt3)
    {
        return SmallPoint3((pt3.x  + 1 - BOARD_WIDTH),
                (pt3.z + 1 - BOARD_DEPTH), pt3.y);
    }

    SizeType availableTierAt(const Board& board, const SmallPoint2& pt2)
    {
        for (SizeType i = 0; i < BOARD_HEIGHT; ++i)
            if (isNullAt(board, SmallPoint3(pt2.x, pt2.y, i)))
                return i;
        return NO_TIERS_FREE;
    }

    bool isNullAt(const Board& board, const SmallPoint3& pt3, Orientation o)
    {
		if (o == ORIENTATION_POS)
			return board[pt3]->isNull();
		return board[asPositive3(pt3)]->isNull();
    }

    void nullifyAt(Board& board, const SmallPoint3& pt3, Orientation o)
    {
        if (o == ORIENTATION_POS)
            board[pt3] = &NULL_PIECE;
        board[asPositive3(pt3)] = &NULL_PIECE;
    }
    
    SizeType availableTierAt(const Board& board, const SmallPoint2& pt2, Orientation o)
    {
		for (SizeType i = 0; i < BOARD_HEIGHT; ++i)
		{
			if (isNullAt(board, SmallPoint3(pt2.x, pt2.y, i), o))
				return i;
		}
			return NO_TIERS_FREE;
    }

    SizeType availableTierAt(const Board& board, const SmallPoint3& pt3, Orientation o)
    {
        return availableTierAt(board, SmallPoint2(pt3.x, pt3.z), o);
    }

    bool hasOpenTierAt(const Board& board, const SmallPoint2& pt2, Orientation o)
    {
        if (availableTierAt(board, pt2, o) == NO_TIERS_FREE)
            return false;
        return true;
    }

    bool hasOpenTierAt(const Board& board, const SmallPoint3& pt3, Orientation o)
    {
        if (availableTierAt(board, pt3, o) == NO_TIERS_FREE)
            return false;
        return true;
    }

    void placeAt(Board& board, const Piece& piece, SmallPoint3 pt3)
    {
        pt3.y = availableTierAt(board, pt3);
        board[pt3] = &piece;
    }

    SmallPoint2 genIndex2(SmallPoint2 pt2, const Move& move, Orientation o)
    {
        if (o == ORIENTATION_POS)
        {
            switch (move.getDirection())
            {
                case Direction::NW:
                    pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                    pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::N:
                    pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::NE:
                    pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                    pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::E:
                    pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                    break;
                case Direction::SE:
                    pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                    pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                    break;
                case Direction::S:
                    pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                    break;
                case Direction::SW:
                    pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                    pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                    break;
                case Direction::W:
                    pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                    break;
            }
        }
        else
        {
            switch (move.getDirection())
            {
                case Direction::NW:
                    pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                    pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                    break;
                case Direction::N:
                    pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                    break;
                case Direction::NE:
                    pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                    pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::E:
                    pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::SE:
                    pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                    pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::S:
                    pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::SW:
                    pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                    pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                    break;
                case Direction::W:
                    pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                    break;
            }
        }
        return pt2;
    }

    SmallPoint2 genIndex2(const SmallPoint3& pt3, const Move& move, Orientation o)
    {
        return genIndex2(SmallPoint2(pt3.x, pt3.z), move, o);
    }

    BoardState genBoardState(const Board& board, const Indices3& indices, StateFilter filter)
    {
        BoardState state { BOARD_WIDTH, BOARD_DEPTH, BOARD_HEIGHT, false };
        for (auto idx = indices.cbegin(); idx != indices.cend(); ++idx)
            if (filter(*idx, *(board[*idx])))
                    state[*idx] = true;
        return std::move(state);
    }

    bool validPlacementDrop(const Board& board, const Piece& piece, SmallPoint3 pt3,
            Orientation o)
    {
        // Better short-circuit Mr. Compiler
        if ((o == ORIENTATION_POS) && pt3.z >= VALID_PLCMT_DEPTH)
            return false;
        
        if (o == ORIENTATION_NEG)
        {
            pt3 = asPositive3(pt3);
            if (not(pt3.z >= (BOARD_DEPTH - VALID_PLCMT_DEPTH)))
                return false;
        }

        if (availableTierAt(board, pt3) == NO_TIERS_FREE)
            return false;

        if (piece.onHead() && piece.getHead() == Head::Soldier)
        {
            if (o == ORIENTATION_POS)
            {
                for (SizeType i = 0u; i < VALID_PLCMT_DEPTH; ++i)
                {
                    for (SizeType j = 0u; j < BOARD_HEIGHT; ++j)
                    {
                        pt3.z = i;
                        pt3.y = j;
                        if (isNullAt(board, pt3))
                            break;

                        if (board[pt3]->getHead() == Head::Soldier)
                            return false;
                    }
                }
            }
            else
            {
                for (SizeType i = BOARD_DEPTH - VALID_PLCMT_DEPTH; 
                        i < BOARD_DEPTH; ++i)
                {
                    for (SizeType j = 0u; j < BOARD_HEIGHT; ++j)
                    {
                        SmallPoint3 tmp = { pt3.x, i, j };
                        if (board[tmp]->getHead() == Head::Soldier)
                            return false;
                    }
                }
            }
        }

        if (piece.onHead() && (piece.getHead() == Head::Catapult || piece.getHead() == Head::Catapult)
                && availableTierAt(board, pt3) != 0)
            return false;

        return true;
    }

    bool validRunningDrop(const Board& board, const Piece& piece, const SmallPoint3& pt3,
            Orientation o)
    {
        return true;
    }
}

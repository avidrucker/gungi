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

/**
 * Notes:
 * 1. Move to Index function doesn't check for chained moves (Recursion ?)
 */

namespace Gungi
{
    #if (DEBUG)
        std::ostream& operator << (std::ostream& out, const SmallPoint2& pt2)
        {
            out << "(" << (size_t) pt2.x << ", " << (size_t) pt2.y << ")"; 
            return out;
        }

        std::ostream& operator << (std::ostream& out, const SmallPoint3& pt3)
        {
            out << "(" << (size_t) pt3.x << ", " << (size_t) pt3.z << ", " << (size_t) pt3.y
                << ")";
            return out;
        }
    #endif

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

    const Move::MagnitudeType& Move::getMagnitude() const
    {
        return _magnitude;
    }

    const Direction& Move::getDirection() const
    {
        return _direction;
    }

    const Move* Move::getNext() const
    {
        return _next.get();
    }

    bool operator == (const Move& lhs, const Move& rhs)
    {
        if (lhs.getMagnitude() == UNBOUNDED || rhs.getMagnitude() == UNBOUNDED)
            return lhs.getDirection() == rhs.getDirection() && lhs.getNext() == rhs.getNext();

        return ((lhs.getMagnitude() == rhs.getMagnitude())
            && (lhs.getDirection() == rhs.getDirection())
            && (lhs.getNext() == rhs.getNext()));
    }

    Piece::Piece()
    : _head      (Head::None)
    , _tail      (Tail::None) 
    , _nullPiece (true)
    , _onHead    (true)
    , _headColor (Color::None)
    , _tailColor (Color::None)
    {}

    Piece::Piece(const Head& head, const Tail& tail, const Color& headColor,
            const Color& tailColor)
    : _head      (head)
    , _tail      (tail)
    , _nullPiece (false)
    , _onHead    (true)
    , _headColor (headColor)
    , _tailColor (tailColor)
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

    const Color& Piece::getHeadColor() const
    {
        return _headColor;
    }

    const Tail& Piece::getTail() const
    {
        return _tail;
    }

    const Color& Piece::getTailColor() const
    {
        return _tailColor;
    }

    const Color& Piece::getActiveColor() const
    {
        return _onHead ? _headColor : _tailColor;
    }

    bool Piece::isNull() const
    {
        return _nullPiece;
    }

    bool Piece::onHead() const
    {
        return _onHead;
    }

    bool Piece::dropStackable() const
    {
        return _head == Head::Catapult || _head == Head::Fortress ||
            _head == Head::Ninja || _tail == Tail::Jounin || _nullPiece;
    }

    bool Piece::canJump() const
    {
        return (_onHead && (_head == Head::Ninja || _head == Head::Archer)) ||
            (!_onHead && _tail == Tail::Jounin);
    }

    // This constructor is not good for the eyes o.O
    PieceSet::PieceSet(Color headColors, Color tailColors)
    {
       Set.push_back(std::make_tuple( 
                   Piece(Head::Commander, Tail::None, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Captain, Tail::Pistol, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Captain, Tail::Pistol, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Samurai, Tail::Pike, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Samurai, Tail::Pike, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Ninja, Tail::Jounin, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Ninja, Tail::Jounin, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Ninja, Tail::Jounin, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Catapult, Tail::Lance, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Fortress, Tail::Lance, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::HiddenDragon, Tail::DragonKing, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Prodigy, Tail::Phoenix, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Archer, Tail::Arrow, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Archer, Tail::Arrow, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Gold, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Silver, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Bronze, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Bronze, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Bronze, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Bronze, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Bronze, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Bronze, headColors, tailColors), UBD_PT3));
       Set.push_back(std::make_tuple(
                   Piece(Head::Soldier, Tail::Bronze, headColors, tailColors), UBD_PT3));
    }

    void PieceSet::remove(const SizeType& i)
    {
        if (i < Set.size())
            Set.erase(Set.begin() + i);
    }

    void PieceSet::append(const IndexedPiece& piece)
    {
        Set.push_back(piece); 
    }

    void PieceSet::append(IndexedPiece&& piece)
    {
        Set.push_back(std::move(piece));
    }

    void PieceSet::append(const Piece& piece, const SmallPoint3& pt3)
    {
        Set.emplace_back(piece, pt3);
    }

    Piece& PieceSet::pieceAt(const SizeType& i)
    {
        return std::get<Piece>(Set[i]);
    }

    SmallPoint3& PieceSet::pointAt(const SizeType& i)
    {
        return std::get<SmallPoint3>(Set[i]);
    }

    const Piece& PieceSet::pieceAt(const SizeType& i) const
    {
        return std::get<Piece>(Set[i]);
    }

    const SmallPoint3& PieceSet::pointAt(const SizeType& i) const
    {
        return std::get<SmallPoint3>(Set[i]);
    }

    bool isUnbounded(const SmallPoint2& pt)
    {
        return pt.x == UNBOUNDED || pt.y == UNBOUNDED;
    }

    bool isUnbounded(const SmallPoint3& pt)
    {
        return pt.x == UNBOUNDED || pt.z == UNBOUNDED
            || pt.y == UNBOUNDED;
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
            default:
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
            default:
                return tier;
        }
    }

    Tier asTier(const SizeType& i)
    {
        if (i == 0)
            return Tier::One;
        else if (i == 1)
            return Tier::Two;
        else if (i == 2)
            return Tier::Three;
        else
            return Tier::None;
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

    std::string getHeadString(const Piece& piece)
    {
        switch (piece.getHead())
        {
            case Head::Commander:
                return "Commander";
            case Head::Captain:
                return "Captain";
            case Head::Samurai:
                return "Samurai";
            case Head::Ninja:
                return "Ninja";
            case Head::Catapult:
                return "Catapult";
            case Head::Fortress:
                return "Fortress";
            case Head::HiddenDragon:
                return "Hidden Dragon";
            case Head::Prodigy:
                return "Prodigy";
            case Head::Archer:
                return "Archer";
            case Head::Soldier:
                return "Soldier";
            default:
                return "None";
        }
    }

    std::string getTailString(const Piece& piece)
    {
        switch (piece.getTail())
        {
            case Tail::DragonKing:
                return "Dragon King";
            case Tail::Lance:
                return "Lance";
            case Tail::Phoenix:
                return "Phoenix";
            case Tail::Jounin:
                return "Jounin";
            case Tail::Arrow:
                return "Arrow";
            case Tail::Pike:
                return "Pike";
            case Tail::Gold:
                return "Gold";
            case Tail::Pistol:
                return "Pistol";
            case Tail::Silver:
                return "Silver";
            case Tail::Bronze:
                return "Bronze";
            default:
                return "None";
        }
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

    Indices2 genFortressRangeSet(const Board& board, const SmallPoint2& origin, Orientation o)
    {
        Indices2  ranges;
        bool overflowing = false;
        SizeType i = 0;
        while (not(overflowing))
        {
            auto tmp = origin;
            tmp.y = OverflowAdd(tmp.y, i, BOARD_WIDTH, UNBOUNDED);
            if (isUnbounded(tmp))
                overflowing = true;
            else
            {
                ++i;
                ranges.push_back(tmp);
            }
        }
        if (o == ORIENTATION_NEG)
            std::for_each(ranges.begin(), ranges.end(), 
                    [] (const SmallPoint2& pt2) { return asPositive2(pt2); });
        return ranges;
    }
    
    Indices2 genCatapultRangeSet(const Board& board, const SmallPoint3& origin, Orientation o)
    {
        Indices2 ranges;
        if (origin.z < 3)
        {
            for (SizeType i = 0; i < 8; ++i)
                ranges.emplace_back(SmallPoint2(origin));
                //Type can't be deduced
                ranges[0].x = OverflowAdd<SizeType>(origin.x, 1, BOARD_WIDTH, UNBOUNDED); 
                ranges[1].x = OverflowAdd<SizeType>(origin.x, 2, BOARD_WIDTH, UNBOUNDED); 
                ranges[2].x = OverflowSub<SizeType>(origin.x, 1, UNBOUNDED); 
                ranges[3].x = OverflowSub<SizeType>(origin.x, 2, UNBOUNDED); 

                if (origin.z == 0) // The overflow stuff isn't really needed here, 
                    // I'll remove them later
                {
                    ranges[4].x = OverflowSub<SizeType>(origin.x, 1, UNBOUNDED);
                    ranges[4].y = OverflowAdd<SizeType>(origin.z, 1, BOARD_DEPTH, UNBOUNDED); 
                    ranges[5].y = OverflowAdd<SizeType>(origin.z, 1, BOARD_DEPTH, UNBOUNDED); 
                    ranges[6].y = OverflowAdd<SizeType>(origin.z, 2, BOARD_DEPTH, UNBOUNDED); 
                    ranges[7].x = OverflowAdd<SizeType>(origin.x, 1, BOARD_WIDTH, UNBOUNDED);
                    ranges[7].y = OverflowAdd<SizeType>(origin.z, 1, BOARD_DEPTH, UNBOUNDED); 
                }
                else if (origin.z == 1)
                {
                    ranges.emplace_back(SmallPoint2(origin));
                    ranges.emplace_back(SmallPoint2(origin));
                    ranges[4].x = OverflowSub<SizeType>(origin.x, 1, UNBOUNDED);
                    ranges[4].y = OverflowAdd<SizeType>(origin.z, 1, BOARD_DEPTH, UNBOUNDED); 
                    ranges[5].y = OverflowAdd<SizeType>(origin.z, 1, BOARD_DEPTH, UNBOUNDED); 
                    ranges[6].x = OverflowAdd<SizeType>(origin.x, 1, BOARD_WIDTH, UNBOUNDED);
                    ranges[6].y = OverflowAdd<SizeType>(origin.z, 1, BOARD_DEPTH, UNBOUNDED);
                    ranges[7].x = OverflowAdd<SizeType>(origin.x, 1, BOARD_WIDTH, UNBOUNDED);
                    ranges[7].y = OverflowSub<SizeType>(origin.z, 1, UNBOUNDED);
                    ranges[8].y = OverflowSub<SizeType>(origin.z, 1, UNBOUNDED);
                    ranges[9].x = OverflowSub<SizeType>(origin.x, 1, UNBOUNDED);
                    ranges[9].y = OverflowSub<SizeType>(origin.z, 1, UNBOUNDED);
                }
                else if (origin.z == 2)
                {
                    ranges[4].x = OverflowAdd<SizeType>(origin.x, 1, BOARD_WIDTH, UNBOUNDED);
                    ranges[4].y = OverflowSub<SizeType>(origin.z, 1, UNBOUNDED);
                    ranges[5].y = OverflowSub<SizeType>(origin.z, 1, UNBOUNDED);
                    ranges[6].y = OverflowSub<SizeType>(origin.z, 2, UNBOUNDED);
                    ranges[7].x = OverflowSub<SizeType>(origin.x, 1, UNBOUNDED);
                    ranges[7].y = OverflowSub<SizeType>(origin.z, 1, UNBOUNDED);
                }

            if (o == ORIENTATION_NEG)
                std::for_each(ranges.begin(), ranges.end(), 
                        [] (const SmallPoint2& pt2) { return asPositive2(pt2); });

            std::remove_if(ranges.begin(), ranges.end(), 
                    [] (const SmallPoint2& pt2) { return isUnbounded(pt2); });
        }
        return std::move(ranges);
    }

    SmallPoint2 asPositive2(const SmallPoint2& pt2)
    {
        #if (DEBUG)
            cerr << "In SmallPoint2 asPositive2(SmallPoint2)" << endl;
            cerr << "Point is: " << pt2 << endl;
        #endif

        if (isUnbounded(pt2))
            return pt2;
        return SmallPoint2((BOARD_WIDTH - pt2.x - 1),
                (BOARD_DEPTH - pt2.y - 1));
    }

    SmallPoint2 asNegative2(const SmallPoint2& pt2)
    {
        if (isUnbounded(pt2))
            return pt2;
        return SmallPoint2((pt2.x + 1 - BOARD_WIDTH),
                (pt2.y + 1 - BOARD_DEPTH));
    }

    SmallPoint2 asPositive2(const SmallPoint3& pt3)
    {
        if (isUnbounded(pt3))
            return SmallPoint2(pt3);
        return SmallPoint2((BOARD_WIDTH - pt3.x - 1),
                (BOARD_DEPTH - pt3.z - 1));
    }

    SmallPoint2 asNegative2(const SmallPoint3& pt3)
    {
        if (isUnbounded(pt3))
            return SmallPoint2(pt3);
        return SmallPoint2((pt3.x + 1 - BOARD_WIDTH),
                (pt3.z + 1 - BOARD_DEPTH));
    }

    SmallPoint3 asPositive3(const SmallPoint2& pt2)
    {
        if (isUnbounded(pt2))
            return SmallPoint3(pt2);
        return SmallPoint3((BOARD_WIDTH - pt2.x - 1),
                (BOARD_DEPTH - pt2.y - 1), 0);
    }

    SmallPoint3 asNegative3(const SmallPoint2& pt2)
    {
        if (isUnbounded(pt2))
            return SmallPoint3(pt2);
        return SmallPoint3((pt2.x + 1 - BOARD_WIDTH),
                (pt2.y + 1 - BOARD_DEPTH), 0);
    }

    SmallPoint3 asPositive3(const SmallPoint3& pt3)
    {
        if (isUnbounded(pt3))
            return pt3;
        return SmallPoint3((BOARD_WIDTH - pt3.x - 1),
                (BOARD_DEPTH - pt3.z - 1), pt3.y);
    }

    SmallPoint3 asNegative3(const SmallPoint3& pt3)
    {
        if (isUnbounded(pt3))
            return pt3;
        return SmallPoint3((pt3.x  + 1 - BOARD_WIDTH),
                (pt3.z + 1 - BOARD_DEPTH), pt3.y);
    }

    bool isNullAt(const Board& board, const SmallPoint3& pt3)
    {
        return board[pt3]->isNull();
    }

    void nullifyAt(Board& board, const SmallPoint3& pt3)
    {
        #if (DEBUG)
            cerr << "In nullifyAt() called for pt3: " << pt3 << endl;
        #endif

        if (isUnbounded(pt3))
            return;

        board[pt3] = &NULL_PIECE;
    }
    
    SizeType availableTierAt(const Board& board, const SmallPoint2& pt2)
    {
		for (SizeType i = 0; i < BOARD_HEIGHT; ++i)
		{
			if (isNullAt(board, SmallPoint3(pt2.x, pt2.y, i)))
				return i;
		}
			return NO_TIERS_FREE;
    }

    SizeType availableTierAt(const Board& board, const SmallPoint3& pt3)
    {
        return availableTierAt(board, SmallPoint2(pt3.x, pt3.z));
    }

    bool hasOpenTierAt(const Board& board, const SmallPoint2& pt2)
    {
        if (availableTierAt(board, pt2) == NO_TIERS_FREE)
            return false;
        return true;
    }

    bool hasOpenTierAt(const Board& board, const SmallPoint3& pt3)
    {
        if (availableTierAt(board, pt3) == NO_TIERS_FREE)
            return false;
        return true;
    }

    bool towerMeets(const Board& board, const SmallPoint2& pt2, TierFilter filter)
    {
        for (SizeType i = 0; i < BOARD_HEIGHT; ++i)
        {
            SmallPoint3 pt3 { pt2.x, pt2.y, i };
            if (!filter(i, *(board[pt3])))
                return false;
        }
        return true;
    }

    bool towerMeets(const Board& board, SmallPoint3 pt3, TierFilter filter)
    {
        for (SizeType i = 0; i < BOARD_HEIGHT; ++i)
        {
            pt3.y = i;
            if (!filter(i, *(board[pt3])))
                return false;
        }
        return true;
    }

    void placeAt(Board& board, const Piece* piece, const SmallPoint3& pt3)
    {
        board[pt3] = piece;
    }

    SmallPoint2 genIndex2Of(SmallPoint2 pt2, const Move& move)
    {
        #if (DEBUG)
            cerr << "In genIndex2Of() for pt2: " << pt2 << endl;
        #endif

    //    if (o == ORIENTATION_NEG)
     //       return genIndex2Of(asPositive2(pt2), move, ORIENTATION_POS);

        switch (move.getDirection())
        {
            case Direction::NW:
                pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                break;
            case Direction::N:
                pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                break;
            case Direction::NE:
                pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                break;
            case Direction::E:
                pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                break;
            case Direction::SE:
                pt2.x = OverflowAdd(pt2.x, move.getMagnitude(), BOARD_WIDTH, UNBOUNDED);
                pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                break;
            case Direction::S:
                pt2.y = OverflowSub(pt2.y, move.getMagnitude(), UNBOUNDED);
                break;
            case Direction::SW:
                pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                pt2.y = OverflowAdd(pt2.y, move.getMagnitude(), BOARD_DEPTH, UNBOUNDED);
                break;
            case Direction::W:
                pt2.x = OverflowSub(pt2.x, move.getMagnitude(), UNBOUNDED);
                break;
        }

        return pt2;
    }

    Indices3 filterIndices3(const Board& board, const Indices3& indices, StateFilter filter)
    {
        Indices3 state;
        for (auto i = indices.cbegin(); i != indices.cend(); ++i)
            if (filter(*i, *(board[*i])))
                state.push_back(*i);
        return state;
    }

    // This function is gon' be slow, tread with caution
    Indices3 genInfluenceSources(const Board& board, SmallPoint3 destination,
            Orientation o)
    {
        Indices3 sources;
        
        if (o == ORIENTATION_NEG)
            destination = asPositive3(destination);

        for (SizeType i = 0; i < BOARD_WIDTH; ++i)
        {
            for (SizeType j = 0; j < BOARD_DEPTH; ++j)
            {
                for (SizeType k = 0; k < BOARD_HEIGHT; ++k)
                {
                    auto piece = board(i, j, k);
                    MoveSet moveset;
                    if (not(piece->isNull()))
                    {
                        if (piece->onHead())
                            moveset = genHeadMoveSet(*piece, asTier(k));
                        else
                            moveset = genTailMoveSet(*piece, asTier(k));
                        
                        for (Move& move : moveset)
                        {
                            auto pt2 = genIndex2Of(SmallPoint2(i, j), move); // Doesn't check N-Based moves
                            if (o == ORIENTATION_NEG)
                                pt2 = asPositive2(pt2);

                            if (pt2 == SmallPoint2(destination))
                                sources.emplace_back(i, j, k); 
                        }
                    }
                }
            }
        }
        return sources;
    }

    bool validPlacementDrop(const Board& board, const Piece& piece, SmallPoint3 pt3,
            Orientation o)
    {
        #if (DEBUG)
            cerr << "In validPlacementDrop()" << endl;
        #endif

        // Better short-circuit Mr. Compiler
        if ((o == ORIENTATION_POS) && pt3.z >= VALID_PLCMT_DEPTH)
            return false;
        
        if (o == ORIENTATION_NEG)
        {
            pt3 = asPositive3(pt3);
            if (not(pt3.z >= (BOARD_DEPTH - VALID_PLCMT_DEPTH)))
                return false;
        }

        #if (DEBUG)
            cerr << "In validPlacementDrop(), depth is valid." << endl;
        #endif

        if (availableTierAt(board, pt3) == NO_TIERS_FREE)
            return false;

        #if (DEBUG)
            cerr << "In validPlacementDrop(), there is at least one open tier." << endl;
        #endif

        if (piece.onHead() && piece.getHead() == Head::Soldier)
        {
            #if (DEBUG)
                cerr << "In validPlacementDrop(), piece is a soldier." << endl;
            #endif

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

            #if (DEBUG)
                cerr << "In validPlacementDrop(), piece (soldier) can be dropped." << endl;
            #endif
        }

        if (piece.onHead() && (piece.getHead() == Head::Catapult || piece.getHead() == Head::Catapult)
                && availableTierAt(board, pt3) != 0)
            return false;

        #if (DEBUG)
            cerr << "In validPlacementDrop(), piece (any) can be dropped." << endl;
        #endif

        return true;
    }

    bool validRunningDrop(const Board& board, const Piece& piece, SmallPoint3 pt3,
            Orientation o)
    {
        if (o == ORIENTATION_NEG)
            pt3 = asPositive3(pt3);

        // Catapult and Fortress must be at first tier.
        if (piece.onHead() && (piece.getHead() == Head::Catapult || 
                    piece.getHead() == Head::Catapult) && availableTierAt(board, pt3) != 0) 
            return false;

        pt3.y = availableTierAt(board, pt3);
        if (pt3.y == NO_TIERS_FREE)
            return false;

        const Piece& topPiece = *(board[pt3]); 
        return topPiece.dropStackable();
    }


    bool validRunningShift(const Board& board, const SmallPoint3& origin, const Move& move, 
            Orientation o)
    {
        auto index = genIndex2Of(origin, move);
        if (isUnbounded(index))
            return false;

        return hasOpenTierAt(board, index);
    }

    bool validRunningShift(const Board& board, const Piece& piece, const SmallPoint3& pt3,
            const Move& move, Orientation o)
    {
        bool movablePiece = not(piece.onHead() && 
                (piece.getHead() == Head::Fortress || piece.getHead() == Head::Catapult));

        if (piece.onHead() && piece.getHead() == Head::Commander)
        {
            auto pt2 = genIndex2Of(SmallPoint2(pt3.x, pt3.z), move);
            auto destIndex = SmallPoint3(pt2.x, pt2.y, pt3.y);
            auto influencePoints = genInfluenceSources(board, destIndex);
            movablePiece = influencePoints.empty();
        }

        return validRunningShift(board, pt3, move, o) && movablePiece;
    }

    bool flatPathHas(const Board& board, SmallPoint2 pt2, const Move& move, 
            PieceFilter filter)
    {
        bool inBound = not(isUnbounded(pt2));
        for (SizeType i = 0; inBound && i <= move.getMagnitude(); ++i)
        {
            pt2 = genIndex2Of(pt2, Move(i, move.getDirection()));
            if (filter(*(board(pt2.x, pt2.y, 0))))
                return true;
        }
        return false; 
    }
}

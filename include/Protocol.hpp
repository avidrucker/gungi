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

#pragma once

#include <cstdint>
#include <vector>

#include <Matrix.hpp>

namespace Gungi
{
    class Move;
    class IndexedPiece;

    constexpr uint8_t BOARD_WIDTH        = 9;
    constexpr uint8_t BOARD_DEPTH        = 9;
    constexpr uint8_t BOARD_HEIGHT       = 3;
    constexpr uint8_t FRONT_PCS_CT       = 10;
    constexpr uint8_t BACK_PCS_CT        = 10;
    constexpr uint8_t UNBOUNDED          = ~0;
    constexpr uint8_t NO_TIERS_FREE      = ~0;
    constexpr uint8_t VALID_PLCMT_DEPTH  = 3;
    constexpr uint8_t STD_PIECE_CT       = 23;
    constexpr uint8_t CAPTAIN_RANK       = 12;
    constexpr uint8_t SAMURAI_RANK       = 10;
    constexpr uint8_t NINJA_RANK         = 8;
    constexpr uint8_t HIDDEN_DRAGON_RANK = 8;
    constexpr uint8_t CATAPULT_RANK      = 6;
    constexpr uint8_t FORTRESS_RANK      = 6;
    constexpr uint8_t PRODIGY_RANK       = 4;
    constexpr uint8_t ARCHER_RANK        = 4;
    constexpr uint8_t SOLDIER_RANK       = 2;
    constexpr uint8_t NO_HEAD            = 0;
    constexpr uint8_t DRAGON_KING_RANK   = 12;
    constexpr uint8_t LANCE_RANK         = 10;
    constexpr uint8_t PHOENIX_RANK       = 10;
    constexpr uint8_t JOUNIN_RANK        = 8;
    constexpr uint8_t ARROW_RANK         = 6;
    constexpr uint8_t PIKE_RANK          = 6;
    constexpr uint8_t GOLD_RANK          = 6;
    constexpr uint8_t PISTOL_RANK        = 4;
    constexpr uint8_t SILVER_RANK        = 4;
    constexpr uint8_t BRONZE_RANK        = 2;
    constexpr uint8_t NO_TAIL            = 0;

    using RankSize    = uint8_t;
    using SmallPoint2 = Point2<uint8_t>;
    using SmallPoint3 = Point3<uint8_t>;
    using MoveSet     = std::vector<Move>;
    using PieceSet    = std::vector<IndexedPiece>;
    using Board       = Matrix3<const IndexedPiece*, uint8_t>;

    enum class Orientation : uint8_t
    { Positive, Negative };

    enum class Direction : uint8_t 
    { NW, N, NE, E, SE, S, SW, W };

    enum class Tier : uint8_t 
    { One, Two, Three };


    enum class Head : uint8_t
    { None, Commander, Captain, Samurai, Ninja,  Catapult, 
        Fortress, HiddenDragon , Prodigy, Archer, Soldier };

    enum class Tail : uint8_t
    { None, Pistol, Pike, Jounin, Lance, DragonKing,
        Phoenix, Arrow, Gold, Silver, Bronze };

    const SmallPoint2 UBD_PT2 { UNBOUNDED, UNBOUNDED };
    const SmallPoint3 UBD_PT3 { UNBOUNDED, UNBOUNDED, UNBOUNDED };

    class Move
    {
        using MagnitudeType = uint8_t;

        public:
            Move(const MagnitudeType& magnitude, const Direction& direction);
            Move(const MagnitudeType& magnitude, const Direction& direction, 
                    const MagnitudeType& nextMagnitude, const Direction& nextDirection);
            ~Move();
            const MagnitudeType& getMagnitude() const;
            const Direction& getDirection() const;
            Move* getNext() const;

        private:
            const MagnitudeType _magnitude;
            const Direction _direction;
            Move* _next;
    };
    
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

        protected:
            Head _head;
            Tail _tail;
            bool _nullPiece;
            bool _onHead;
    };
    
    class IndexedPiece : public Piece
    {
        public:
            IndexedPiece();
            IndexedPiece(const Head& head, const Tail& tail = Tail::None, 
                    const SmallPoint3& idx = UBD_PT3);
            void setIndex(const SmallPoint3& idx);
            const SmallPoint3& getIndex() const;
            bool isUnbounded() const;

            friend bool operator < (const IndexedPiece& lhs, const IndexedPiece& rhs);
            friend bool operator == (const IndexedPiece& lhs, const IndexedPiece& rhs);
            
        private:
            SmallPoint3 _idx;
    };

    const IndexedPiece NULL_PIECE { Head::None, Tail::None };

    Tier& operator ++(Tier& tier);
    Tier& operator --(Tier& tier);

    bool isUnbounded(const SmallPoint2& pt);
    bool isUnbounded(const SmallPoint3& pt);
    using BoardState = Matrix3<bool, uint8_t>;
    using Indices3 = std::vector<SmallPoint3>;
    using StateFilter = bool(*)(const IndexedPiece&);

    void initPieceSet(PieceSet& pieceSet);

    RankSize getHeadValue(const Piece& piece);
    RankSize getTailValue(const Piece& piece);

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

    template <class SizeType>
    SizeType OverflowSub(const SizeType& lhs, const SizeType& rhs, const SizeType& overflow)
    {
        if (lhs < rhs)
            return overflow;
        else
            return lhs - rhs;
    }

    template <class SizeType>
    SizeType OverflowAdd(const SizeType& lhs, const SizeType& rhs,
            const SizeType& constraint, const SizeType& overflow)
    {
        SizeType res = lhs + rhs;
        return res < constraint ? res : overflow;
    }

    // A bunch of overloads o.O
    SmallPoint2 asPositive2(const SmallPoint2& pt2);
    SmallPoint2 asNegative2(const SmallPoint2& pt2);
    SmallPoint2 asPositive2(const SmallPoint3& pt3);
    SmallPoint2 asNegative2(const SmallPoint3& pt3);
    SmallPoint3 asPositive3(const SmallPoint2& pt2);
    SmallPoint3 asNegative3(const SmallPoint2& pt2);
    SmallPoint3 asPositive3(const SmallPoint3& pt3);
    SmallPoint3 asNegative3(const SmallPoint3& pt3);

    bool isNullAt(const Board& board, const SmallPoint3& pt3);
    void nullifyAt(Board& board, const SmallPoint3& pt3);
    uint8_t availableTierAt(const Board& board, const SmallPoint2& pt2);
    uint8_t availableTierAt(const Board& board, const SmallPoint3& pt3);
    bool hasOpenTierAt(const Board& board, const SmallPoint2& pt2);
    bool hasOpenTierAt(const Board& board, const SmallPoint3& pt3);
    
    bool isNullAt(const Board& board, const SmallPoint3& pt3, const Orientation& o);
    void nullifyAt(Board& board, const SmallPoint3& pt3, const Orientation& o);
    uint8_t availableTierAt(const Board& board, const SmallPoint2& pt2, const Orientation& o);
    uint8_t availableTierAt(const Board& board, const SmallPoint3& pt3, const Orientation& o);
    bool hasOpenTierAt(const Board& board, const SmallPoint2& pt3, const Orientation& o);
    bool hasOpenTierAt(const Board& board, const SmallPoint3& pt3, const Orientation& o);

    void placeAt(Board& board, const IndexedPiece* piece);

    SmallPoint2 genIndex2(SmallPoint2 pt2, const Move& move, const Orientation& o);
    SmallPoint2 genIndex2(const SmallPoint3& pt3, const Move& move, const Orientation& o);
    
    BoardState genBoardState(const Board& board, const Indices3& indices, StateFilter filter);
}

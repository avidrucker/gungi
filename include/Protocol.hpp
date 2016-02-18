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
    constexpr uint8_t BOARD_WIDTH   = 9;
    constexpr uint8_t BOARD_DEPTH   = 9;
    constexpr uint8_t BOARD_HEIGHT  = 3;
    constexpr uint8_t FRONT_PCS_CT  = 10;
    constexpr uint8_t BACK_PCS_CT   = 10;
    constexpr uint8_t UNBOUNDED     = ~0;
    constexpr uint8_t NO_TIERS_FREE = ~0;

    using SmallPoint2 = Point2<uint8_t>;
    using SmallPoint3 = Point3<uint8_t>;

    const SmallPoint2 UBD_PT2 { UNBOUNDED, UNBOUNDED };
    const SmallPoint3 UBD_PT3 { UNBOUNDED, UNBOUNDED, UNBOUNDED };

    bool isUnbounded(const SmallPoint2& pt);
    bool isUnbounded(const SmallPoint3& pt);

    enum class Direction : uint8_t 
    { NW, N, NE, E, SE, S, SW, W };

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

    using MoveSet = std::vector<Move>;

    enum class Tier : uint8_t 
    { One, Two, Three };

    Tier& operator ++(Tier& tier);
    Tier& operator --(Tier& tier);

    using RankSize = uint8_t;

    /**
     * Heads
     */

    enum class Head : uint8_t
    { None, Commander, Captain, Samurai, Ninja,  Catapult, 
        Fortress, HiddenDragon , Prodigy, Archer, Soldier };

    constexpr RankSize CAPTAIN_RANK       = 12;
    constexpr RankSize SAMURAI_RANK       = 10;
    constexpr RankSize NINJA_RANK         = 8;
    constexpr RankSize HIDDEN_DRAGON_RANK = 8;
    constexpr RankSize CATAPULT_RANK      = 6;
    constexpr RankSize FORTRESS_RANK      = 6;
    constexpr RankSize PRODIGY_RANK       = 4;
    constexpr RankSize ARCHER_RANK        = 4;
    constexpr RankSize SOLDIER_RANK       = 2;
    constexpr RankSize NO_HEAD            = 0;
    
    /**
     * Tails
     */

    enum class Tail : uint8_t
    { None, Pistol, Pike, Jounin, Lance, DragonKing,
        Phoenix, Arrow, Gold, Silver, Bronze };

    constexpr RankSize DRAGON_KING_RANK = 12;
    constexpr RankSize LANCE_RANK       = 10;
    constexpr RankSize PHOENIX_RANK     = 10;
    constexpr RankSize JOUNIN_RANK      = 8;
    constexpr RankSize ARROW_RANK       = 6;
    constexpr RankSize PIKE_RANK        = 6;
    constexpr RankSize GOLD_RANK        = 6;
    constexpr RankSize PISTOL_RANK      = 4;
    constexpr RankSize SILVER_RANK      = 4;
    constexpr RankSize BRONZE_RANK      = 2;
    constexpr RankSize NO_TAIL          = 0;

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

    constexpr uint8_t STD_PIECE_CT = 23;

    using PieceSet = std::vector<IndexedPiece>;

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

    const IndexedPiece NULL_PIECE { Head::None, Tail::None };

    using Board = Matrix3<const IndexedPiece*, uint8_t>;

    bool isNullAt(const Board& board, const SmallPoint3& pt);
    void nullifyAt(Board& board, const SmallPoint3& pt);
    uint8_t availableTierAt(const Board& board, const SmallPoint2& pt);
    uint8_t availableTierAt(const Board& board, SmallPoint3 pt);
    bool hasOpenTierAt(const Board& board, const SmallPoint2& pt);
    bool hasOpenTierAt(const Board& board, const SmallPoint3& pt);
    void placeAt(Board& board, const IndexedPiece* piece);
}

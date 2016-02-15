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
#include <list>
#include <array>

#include "Matrix.hpp"

namespace Gungi
{
    constexpr uint8_t BOARD_SIZE = 9;
    constexpr uint8_t BOARD_TIERS = 3;
    constexpr uint8_t NUM_FRONT_PIECES = 10;
    constexpr uint8_t NUM_BACK_PIECES = 10; 

    constexpr uint8_t INFINITE_RANGE = ~0;

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

    using MoveSet = std::list<Move>;

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

        protected:
            Head _head;
            Tail _tail;
            bool _nullPiece;
            bool _onHead;
    };

    
    class IndexedPiece : public Piece
    {
        using IndexingType = Point3;

        public:
            IndexedPiece();
            IndexedPiece(const Head& head, const Tail& tail = Tail::None, const IndexingType& idx = IndexingType());
            void setIndex(const IndexingType& idx);
            const IndexingType& getIndex() const;
            friend bool operator < (const IndexedPiece& lhs, const IndexedPiece& rhs);
            friend bool operator == (const IndexedPiece& lhs, const IndexedPiece& rhs);
        private:
            IndexingType _idx;
    };

    constexpr size_t STD_PIECE_CT = 23;

    class StdPieceSet
    {
        using AccessType = size_t;

        public:

            using SetType = std::array<IndexedPiece,STD_PIECE_CT>;

            StdPieceSet();
            IndexedPiece& operator [] (const AccessType& i);
            const IndexedPiece& operator [] (const AccessType& i) const;

            void swap(const AccessType& a, const AccessType& b);
            const SetType& showSet() const;
        private:
            SetType _pieceSet;
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

    size_t OverflowSub(const size_t& lhs, const size_t& rhs, const size_t& overflow);
    size_t OverflowAdd(const size_t& lhs, const size_t& rhs, 
            const size_t& constraint, const size_t& overflow);

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

    /**
     * Assuming (0,0) is top left
     */
    template <class Matrix2, class Indices>
    Indices genIndexOf2DMove(const Matrix2& matrix, 
            Indices idx, const Move& move)
    {
        switch (move.getDirection())
        {
            case Direction::NW:
                idx.x = OverflowSub(idx.x, move.getMagnitude(), UNBOUND);
                idx.y = OverflowSub(idx.y, move.getMagnitude(), UNBOUND);
                break;
            case Direction::N:
                idx.y = OverflowSub(idx.y, move.getMagnitude(), UNBOUND);
                break;
            case Direction::NE:
                idx.x = OverflowAdd(idx.x, move.getMagnitude(), matrix.getWidth(), UNBOUND);
                idx.y = OverflowSub(idx.y, move.getMagnitude(), UNBOUND);
                break;
            case Direction::E:
                idx.x = OverflowAdd(idx.x, move.getMagnitude(), matrix.getWidth(), UNBOUND);
                break;
            case Direction::SE:
                idx.x = OverflowAdd(idx.x, move.getMagnitude(), matrix.getWidth(), UNBOUND);
                idx.y = OverflowAdd(idx.y, move.getMagnitude(), matrix.getLength(), UNBOUND);
                break;
            case Direction::S:
                idx.y = OverflowAdd(idx.y, move.getMagnitude(), matrix.getLength(), UNBOUND);
                break;
            case Direction::SW:
                idx.x = OverflowSub(idx.x, move.getMagnitude(), UNBOUND);
                idx.y = OverflowAdd(idx.y, move.getMagnitude(), matrix.getLength(), UNBOUND);
                break;
            case Direction::W:
                idx.x = OverflowSub(idx.x, move.getMagnitude(), UNBOUND);
                break;
        }
        return idx;
    }

    template <class Matrix2>
    bool inBound(const Matrix2& matrix, const Point& idx)
    {
        return idx.x < matrix.getWidth() && idx.y < matrix.getHeight();
    }

    template <class Matrix3>
    Point3 genIndexOf3DMove(const Matrix3& matrix, 
            Point3 idx, const Move& move)
    {
        auto twoDimIDX = genIndexOf2DMove(matrix, toXY(idx), move);
        return toXYZ(twoDimIDX, idx.z);
    }

    template <class Matrix3>
    bool inBound(const Matrix3& matrix, const Point3& idx)
    {
        return inBound(matrix, toXY(idx)) && idx.y < matrix.getHeight();
    }

    template <class Matrix, class Indices>
    auto genPossibleMoves(const Matrix& matrix, const Indices& idx, const MoveSet& moveset)
    {
        Matrix3<bool> allowedMoves { BOARD_SIZE, BOARD_SIZE, BOARD_TIERS, false };

        for (auto itr = moveset.cbegin(); itr != moveset.cend(); ++itr)
        {
            auto moveIdx = genIndexOf3DMove(matrix, idx, *itr);
            if (inBound(matrix, moveIdx) && hasAnEmptyTier(matrix, moveIdx))
                allowedMoves[moveIdx] = true;
        }

        return allowedMoves;
    }
}

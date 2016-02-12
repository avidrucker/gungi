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
        public:
            Move(const uint8_t& steps, const Direction& direction);
            Move(const uint8_t& steps, const Direction& direction, 
                    const uint8_t& nextSteps, const Direction& nextDirection);
            ~Move();
            const uint8_t& getSteps() const;
            const Direction& getDirection() const;
            Move* getNext() const;

        private:
            const uint8_t _steps;
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

    template <class PieceMatrix, class Indices>
    bool isOccupied(const PieceMatrix& matrix, const Indices& idx);

    template <class PieceMatrix>
    bool hasAnEmptyTier(const PieceMatrix& matrix, XYZ_Indices idx);

    size_t OverflowSub(const size_t& lhs, const size_t& rhs, const size_t& overflow);
    size_t OverflowAdd(const size_t& lhs, const size_t& rhs, 
            const size_t& constraint, const size_t& overflow);

    template <class TwoDimMatrix, class Indices>
    Indices genIndexOf2DMove(const TwoDimMatrix& matrix, 
            Indices idx, const Move& move);

    template <class TwoDimMatrix>
    bool inBound(const TwoDimMatrix& matrix, const XY_Indices& idx);

    template <class ThreeDimMatrix>
    XYZ_Indices genIndexOf3DMove(const ThreeDimMatrix& matrix, 
            XYZ_Indices idx, const Move& move);

    template <class ThreeDimMatrix>
    bool inBound(const ThreeDimMatrix& matrix, const XYZ_Indices& idx);

    template <class Matrix, class Indices>
    auto genPossibleMoves(const Matrix& matrix, const Indices& idx, const MoveSet& moveset);

}

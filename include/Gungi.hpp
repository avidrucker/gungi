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

#include "Matrix.hpp"
#include "MatrixManip.hpp"
#include "Protocol.hpp"
#include "Utility.hpp"

namespace Gungi
{
    class Board : public Matrix3<const IndexedPiece*>
    {
        using Super = Matrix3<const IndexedPiece*>;

        public:
            Board();
            static const IndexedPiece NOT_A_PIECE;
    };

    class Player
    {
        using AccessType = size_t;
        using SetType = StdPieceSet::SetType;

        public:
            enum class Color : uint8_t { Black, White };

            Player(Board& gameBoard, const Color& color);
            Player(Board* gameBoard, const Color& color);
            const IndexedPiece& operator [] (const AccessType& i) const;
            const Point3& indexFor(const AccessType& i) const;
            void placeOnBoard(const AccessType& i, const Point3& spot);
            void move(const AccessType& idx, const Move& move); 
            const Color& getColor() const;
            const SetType& getFullSet() const;
        private:
           StdPieceSet _pieces;
           Board* _gameBoard;
           Color _color;
           uint8_t _onHandCursor;
    };

    class Game
    {
        using AccessType = size_t;

        public:
            Game();
            void start();
            const Board& gameBoard() const;
            const Player& currentPlayer() const;
            void placeOnBoard(const AccessType& i, const Point3& spot);
            void move(const AccessType& idx, const Move& move);
        private:
            void _flipPlayer();
            bool _running;
            bool _onesTurn;
            Board _gameBoard;
            Player _one;
            Player _two;
            Player* _currentPlayer;
    };
}
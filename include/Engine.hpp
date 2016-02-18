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

#include <iostream> // For Debugging
#include <Matrix.hpp>
#include <Protocol.hpp>

namespace Gungi
{

    class Player
    {
        using AccessType = uint8_t;

        public:
            enum class Orientation : uint8_t
            { Positive, Negative };

            enum class Color : uint8_t { Black, White }; //Could grow

            Player(Board* gameBoard, const Color& color, const Orientation& o);
            bool drop(const AccessType& idx, const SmallPoint3& spot);
            bool place(const AccessType& idx, const Move& move);
            void transfer(const AccessType& idx, Player& player);
            void append(const IndexedPiece& pc);
            const IndexedPiece& operator [] (const AccessType& i) const;
            const SmallPoint3& indexFor(const AccessType& i) const;
            const Color& getColor() const;
            const PieceSet& getFullSet() const;
            const Orientation& getOrientation() const;
        private:
            void _makePositive(SmallPoint3& pt);
            bool _place(const AccessType& i, SmallPoint3 spot);

            PieceSet _pieces;
            Board* _gameBoard;
            Color _color;
            //uint8_t _onHandCursor;
            Orientation _orientation; 
    };

    enum class Phase : uint8_t
    { Standby, Placement, Running };
        
    Phase& operator ++ (Phase& phase);
    Phase& operator -- (Phase& phase);

    class Game
    {
        using AccessType = size_t;
    
        public:
            Game();
            void start();
            const Board& gameBoard() const;
            const Player* currentPlayer() const;
            bool placeOnBoard(const AccessType& i, const SmallPoint3& spot);
            void move(const AccessType& idx, const Move& move);

            static constexpr uint8_t VALID_PLACEMENT_DEPTH = 3;
        private:
            void _flipPlayer();
            bool _validPlacement(const AccessType& i, 
                    const SmallPoint3& spot, const Player::Orientation& o) const;
            bool _running() const;
            bool _onesTurn;

            Board _gameBoard;
            Player _one;
            Player _two;
            Phase _phase;
            Player* _currentPlayer;
    };
}

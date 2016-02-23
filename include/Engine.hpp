/*
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 * 
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 * 
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 * 
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

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
            enum class Color : uint8_t { Black, White }; //Could grow

            Player(Board* gameBoard, const Color& color, const Orientation& o);
            bool drop(const AccessType& idx, SmallPoint3 pt3);
            bool shift(const AccessType& idx, const Move& move);
            void transfer(const AccessType& idx, Player& player);
            void append(IndexedPiece pc);
            const IndexedPiece& operator [] (const AccessType& i) const;
            const SmallPoint3& indexFor(const AccessType& i) const;
            const Color& getColor() const;
            const PieceSet& getFullSet() const;
            const Orientation& getOrientation() const;
        private:
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
        using AccessType = uint8_t;
    
        public:
            Game();
            ~Game();
            void start();
            const Board& gameBoard() const;
            const Player* currentPlayer() const;
            bool drop(const AccessType& i, const SmallPoint3& spot);
            bool move(const AccessType& idx, const Move& move);
            const Phase& getPhase() const;
            bool validPlacementDrop(const AccessType& i, SmallPoint3 pt3,
                    const Orientation& o) const;
        private:
            void _flipPlayer();
            bool _running() const;
            bool _onesTurn;
            Board _gameBoard;
            Player _one;
            Player _two;
            Phase _phase;
            Player* _currentPlayer;
    };
}

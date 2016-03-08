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

#include <tuple>
#include <algorithm>

#include <Matrix.hpp>
#include <Protocol.hpp>

/**
 * The control of evaluating good/bad moves should under the control of the game engine. The
 * player should only be allowed to directly place a piece upon after the game engine has 
 * assured that it is a valid move.
 * Consider using Bitfields for IndexState, maybe even drop the tier. See what other options
 * will be useful., Commander in check, game over, etc.
 * Use an 8-bit bitfield for Commander's in-check positions. He has eight, eh?
 * Player remove method, can return a piece&& so that move-semantics can be applied during
 * transfer
 * Remove SmallPoint3 maneuvering where possible, the game should in two-dimensional manner.
 * Consider adding idle player *, since access to opponent is needed at times as well.
 */

namespace Gungi
{
    /**
     * This class holds a typical game player. It contains a set of pieces, a pointer to
     * a game board, a unique color, and the orientation in which it perceives the board.
     */
    class Player
    {
        public:
            
            Player(Board* gameBoard, const Color& color, const Color& oppColor, 
                    Orientation o);

            void drop(const SizeType& i, const SmallPoint3& pt3);

            void updatePoint(const SizeType& i, const SmallPoint3& pt3);
            
            void remove(const SizeType& i);

            void append(const Piece& pc);

            /**
             * This method accesses the player's piece set on a read-only basis.
             * @param i index of piece
             * @return a const reference to the piece at i
             */
            const IndexedPiece& operator [] (const SizeType& i) const;

            const Piece& pieceAt(const SizeType &i) const;

            /**
             * This method accesses the player's piece set for it's SmallPoint3 index.
             * @param i index of piece
             * @return the point of the piece
             */
            const SmallPoint3& pointAt(const SizeType& i) const;

            const Color& colorAt(const SizeType& i) const;

            /**
             * This method returns the color of the player.
             * @return the color of the player
             */
            const Color& getColor() const;

            const Color& getOppColor() const;

            /**
             * This method returns the piece set of the player.
             * @return the piece set of the player.
             */
            const PieceSet& getFullSet() const;

            /**
             * This method returns the orientation of the player.
             * @return the orientation of the player
             */
            Orientation getOrientation() const;

            /**
             * This method returns the number of pieces that the player has on the board.
             * @return the number of pieces that the player has on board
             */
            const SizeType& onBoard() const;
            
            /**
             * This method returns the number of pieces that the player has on his/her hand.
             * @return the number of pieces that the player has on his/her hand.
             */
            const SizeType& onHand() const;

            /**
             * This method returns the total number of pieces of the player.
             * @return the total number pieces of the player.
             */
            const SizeType& numPieces() const;

            SizeType getIndexAt(const SmallPoint3& pt3) const;

        private:
            void _nullifyIndex(const SizeType& i);

            PieceSet _pieces; /**< Player's piece set. */
            Board* _gameBoard; /**< Pointer to the game board. */
            const Color _color; /**< The color of the player. */
            const Color _oppColor; 
            const Orientation _orientation; /**< The orientation of the player. */
            SizeType _onBoard; /**< Amount of player's pieces on board. */
            SizeType _onHand; /**< Amount of player's pieces on hand. */
            SizeType _numPieces; /**< Amount of player's pieces total. */
    };

    /**
     * This class encapsulates the logic of a running a Gungi game. It will instantiate
     * the players and game board. It is the main interface in which to run the game from.
     */
    class Game
    {
        public:

            /**
             * This constructor will instantiate a game object. It will initialize an empty board
             * , two players and the phase as standby.
             */
            Game();

            /**
             * This destructor will set the current player pointer to nullptr.
             */
            ~Game();

            /**
             * This will increment the phase from standby to placement, or from placement
             * to start. If phase is running nothing happens. 
             * The method will also set current player * to player one.
             */
            void start();

            /**
             * This method will return the game board of the game.
             * @return a const reference to the game board
             */

            IndexState drop(const SizeType& i, SmallPoint3 pt3);

            IndexState move(const SizeType& i, const Move& move);
    
            IndexState assessDrop(bool playerOne, const SizeType& i, SmallPoint3 pt3) const;
            IndexState assessMove(bool playerOne, const SizeType& i, const Move& move) const;

            const Board* gameBoard() const;

            const Player* playerOne() const;

            const Player* playerTwo() const;

            const Player* currentPlayer() const;
            /**
             * This method will return the current phase of the game.
             * @return a const reference to the current phase of the game.
             */
            const Phase& getPhase() const;

        private:

            /**
             * This method will set the current player pointer to the other player.
             * @see _currentPlayer
             */
            void _flipPlayer(); 

            /**
             * This method returns true if the phase of the game is running.
             * @return true if game phase is equal to Phase::Running
             * @see Phase
             */
            bool _running() const;

            void _takeAndTransfer(const SizeType& i, const SmallPoint3& pt3);

            bool _onesTurn; /**< Flag indicating player one's turn. */
            Board _gameBoard; /**< The game board. */
            Player _one; /**< Player one. */
            Player _two; /**< Player two. */
            Phase _phase; /** Phase of the game. */
            Player* _currentPlayer; /**< Pointer to current player. */
    };
}

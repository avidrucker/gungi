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

#include <Matrix.hpp>
#include <Protocol.hpp>

/**
 * Notes:
 * 1. Consider making color and orientation constant for player.
 * 2. Consider placing a piece on the parameter of validPlacementDrop instead
 *      of current player's index.
 * 3. Pieces with pieces out of bounds still get nullified, and placed. DONE
 * 4. Check for dropping same piece twice. DONE
 * 5. Consider moving the validators to Protocol since it's part of the ruleset
 * 6. Add ability to check if all of a player's pieces have been placed on board. DONE
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
            enum class Color : SizeType { Black, White }; //Could grow
            
            /**
             * This constructor will instantiate a player that points to game board.
             * It will generate the standard piece set as dictated by the game's protocol.
             * @param gameBoard a pointer to the main gameboard
             * @param color the color to set the player to
             * @param o the orientation in which the player will perceive the board
             */
            Player(Board* gameBoard, const Color& color, Orientation o);

            /**
             * This method will drop, or place, a piece on the board from the player's hand.
             * @param idx the index of the piece of interest
             * @param pt3 the point on the board to place the piece on
             * @return true if piece has been placed, false if couldn't.
             */
            bool drop(const SizeType& idx, SmallPoint3 pt3);

            /**
             * This method will shift a piece on the board to index generated from the move.
             * @param idx the index of the piece of interest
             * @param move the move being applied to the move
             * @return true if piece has been shifted, false if couldn't.
             */
            bool shift(const SizeType& idx, const Move& move);
            
            /**
             * This method will transfer a piece on the board to another player. 
             * @param idx the index of the piece of interest
             * @param player reference of the player to give the piece to
             */
            void transfer(const SizeType& idx, Player& player);

            /**
             * This method will append a piece to the player's piece set.
             * @param pc the piece to append
             */
            void append(IndexedPiece pc);

            /**
             * This method accesses the player's piece set on a read-only basis.
             * @param i index of piece
             * @return a const reference to the piece at i
             */
            const IndexedPiece& operator [] (const SizeType& i) const;

            const Piece& pieceFor(const SizeType &i) const;

            /**
             * This method accesses the player's piece set for it's SmallPoint3 index.
             * @param i index of piece
             * @return the point of the piece
             */
            const SmallPoint3& pointFor(const SizeType& i) const;

            /**
             * This method returns the color of the player.
             * @return the color of the player
             */
            const Color& getColor() const;

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

        private:
            void _setIndex(const SizeType& i, const SmallPoint3& pt3);
            void _nullifyIndex(const SizeType& i);
            Piece& _pieceFor(const SizeType& i);
            SmallPoint3& _pointFor(const SizeType& i);

            PieceSet _pieces; /**< Player's piece set. */
            Board* _gameBoard; /**< Pointer to the game board. */
            Color _color; /**< The color of the player. */
            Orientation _orientation; /**< The orientation of the player. */
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
            const Board& gameBoard() const;

            /**
             * This method will return const pointer to the current player.
             * @return a const pointer to the current player.
             */
            const Player* currentPlayer() const;

            /**
             * This method will drop('place') piece at the given index at the pt3 indicated. 
             * @param i the index of the current player's piece in his/her piece set
             * @param pt3 the desired pt3 to place the piece in
             * @return true if piece was successfully placed, false if not
             */
            bool drop(const SizeType& i, const SmallPoint3& pt3);

            /**
             * This method will apply a move to the piece at the given index.
             * @param i the index of the current player's piece in his/her piece set
             * @param move the move to apply to the piece
             * @return true if piece was successfully moved, false if not
             */
            bool move(const SizeType& idx, const Move& move);

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

            bool _onesTurn; /**< Flag indicating player one's turn. */
            Board _gameBoard; /**< The game board. */
            Player _one; /**< Player one. */
            Player _two; /**< Player two. */
            Phase _phase; /** Phase of the game. */
            Player* _currentPlayer; /**< Pointer to current player. */
    };
}

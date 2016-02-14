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

#include "Gungi.hpp"

namespace Gungi
{
    const IndexedPiece Board::NOT_A_PIECE { Head::None, Tail::None };

    Board::Board()
    : Super (BOARD_SIZE, BOARD_SIZE, BOARD_TIERS)
    {
        for (decltype (getSize()) i = 0; i < getSize(); ++i)
            _matrix[i] = &Board::NOT_A_PIECE;
    }

    Player::Player(Board& gameBoard, const Color& color)
    : _pieces       ()
    , _gameBoard    (&gameBoard)
    , _color        (color)
    , _onHandCursor (STD_PIECE_CT)
    {}

    Player::Player(Board* gameBoard, const Color& color)
    : _pieces       ()
    , _gameBoard    (gameBoard)
    , _color        (color)
    , _onHandCursor (STD_PIECE_CT)
    {}

    void Player::placeOnBoard(const AccessType& i, const Point3& spot)
    {
        if ((*_gameBoard)[spot] == &Board::NOT_A_PIECE)
        {
            (*_gameBoard)[spot] = &_pieces[i];
            --_onHandCursor;
            _pieces.swap(i, _onHandCursor);          
        }
    }

    const IndexedPiece& Player::operator [] (const AccessType& i) const
    {
        return _pieces[i];
    }

    const Point3& Player::indexFor(const AccessType& i) const
    {
        return _pieces[i].getIndex();
    }

    void Player::move(const AccessType& idx, const Move& move)
    {
        auto currentSpot = indexFor(idx);
        auto newSpot = genIndexOf3DMove(*_gameBoard, indexFor(idx), move);
        (*_gameBoard)[currentSpot] = &Board::NOT_A_PIECE;
        (*_gameBoard)[newSpot] = &_pieces[idx]; 
    }

    const Player::Color& Player::getColor() const
    {
        return _color;
    }
}

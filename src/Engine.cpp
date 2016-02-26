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

#include <Engine.hpp>

namespace Gungi
{
    Player::Player(Board* gameBoard, const Color& color, Orientation o)
    : _gameBoard    (gameBoard)
    , _color        (color)
    , _orientation  (o)
    , _onBoard      (0)
    , _onHand       (STD_PIECE_CT)
    , _numPieces    (STD_PIECE_CT)
    {
       initPieceSet(_pieces);
    }

    bool Player::drop(const SizeType& i, SmallPoint3 pt3)
    {
        if (not(isUnbounded(pointFor(i))))
            return false;

        if (not(validPlacementDrop(*_gameBoard, pieceFor(i), pt3, _orientation)))
            return false;
         
        if (_orientation == ORIENTATION_NEG)
            pt3 = asPositive3(pt3);
        
        pt3.y = availableTierAt(*_gameBoard, pt3, _orientation);
        std::get<SmallPoint3>(_pieces[i]) = pt3;
        placeAt(*_gameBoard, pieceFor(i), pt3);
        return true;
    }

    bool Player::shift(const SizeType& i, const Move& move)
    {
        auto pt2 = genIndex2(pointFor(i), move, _orientation);
        if (isUnbounded(pt2))
            return false;

        if (not(isUnbounded(pointFor(i))))
            nullifyAt(*_gameBoard, pointFor(i), _orientation); 

        auto pt3 = SmallPoint3(pt2);
        pt3.y = availableTierAt(*_gameBoard, pt3, _orientation);

        if (pt3.y == NO_TIERS_FREE)
            return false;
        
        _setIndex(i, pt3);
        placeAt(*_gameBoard, pieceFor(i), pointFor(i));
        return true;
    }

    void Player::transfer(const SizeType& i, Player& player)
    {
        nullifyAt(*_gameBoard, pointFor(i), _orientation);
        _nullifyIndex(i);
        player.append(_pieces[i]);
        _pieces.erase(_pieces.cbegin() + i);
    }

    void Player::append(IndexedPiece pc)
    {
        std::get<Piece> (pc).flip();
        _pieces.push_back(pc);
    }

    const IndexedPiece& Player::operator [] (const SizeType& i) const
    {
        return _pieces[i];
    }

    const Piece& Player::pieceFor(const SizeType &i) const
    {
        return std::get<Piece>(_pieces[i]);
    }

    const SmallPoint3& Player::pointFor(const SizeType& i) const
    {
        return std::get<SmallPoint3>(_pieces[i]);
    }

    const Player::Color& Player::getColor() const
    {
        return _color;
    }

    const PieceSet& Player::getFullSet() const
    {
        return _pieces;
    }

    Orientation Player::getOrientation() const
    {
        return _orientation;
    }

    const SizeType& Player::onBoard() const
    {
        return _onBoard;
    }
    const SizeType& Player::onHand() const
    {
        return _onHand;
    }

    const SizeType& Player::numPieces() const
    {
        return _numPieces;
    }

    void Player::_setIndex(const SizeType& i, const SmallPoint3& pt3)
    {
        std::get<SmallPoint3> (_pieces[i]) = pt3;
    }

    void Player::_nullifyIndex(const SizeType& i)
    {
        std::get<SmallPoint3> (_pieces[i]) = UBD_PT3;
    }

    Piece& Player::_pieceFor(const SizeType& i)
    {
        return std::get<Piece> (_pieces[i]);
    }

    SmallPoint3& Player::_pointFor(const SizeType& i)
    {
        return std::get<SmallPoint3> (_pieces[i]);
    }

    Game::Game()
    : _onesTurn      (true)
    , _gameBoard     (BOARD_WIDTH, BOARD_DEPTH, BOARD_HEIGHT, &NULL_PIECE)
    , _one           (&_gameBoard, Player::Color::Black, ORIENTATION_POS)
    , _two           (&_gameBoard, Player::Color::White, ORIENTATION_NEG)
    , _phase         (Phase::Standby)
    , _currentPlayer (nullptr)
    {}

    Game::~Game()
    {
        _currentPlayer = nullptr;
    }

    void Game::start()
    {
        if (_phase != Phase::Running)
        {
            _currentPlayer = &_one;
            ++_phase;
        }
    }

    const Board& Game::gameBoard() const
    {
        return _gameBoard;
    }

    const Player* Game::currentPlayer() const
    {
        return _currentPlayer; 
    }

    bool Game::drop(const SizeType& i, const SmallPoint3& pt)
    {
        if (_phase == Phase::Standby)
            return false;

        bool result = _currentPlayer->drop(i, pt);
        if (result)
            _flipPlayer();
        return result;
    }

    bool Game::move(const SizeType& idx, const Move& move)
    {
        if (!_running())
            return false;

        if (!_currentPlayer->shift(idx,move))
            return false;

        _flipPlayer();
        return true;
    }

    const Phase& Game::getPhase() const
    {
        return _phase;
    }

    void Game::_flipPlayer()
    {
        _currentPlayer = _onesTurn ? &_two : &_one;
        _onesTurn = !_onesTurn;
    }

    bool Game::_running() const
    {
        return _phase == Phase::Running;
    }
}

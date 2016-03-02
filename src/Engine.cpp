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

/*
 * Notes:
 * 1. Player transfer shouldn't exist. Game should handle that. Implemente remove, and append.
 * 2. Figure out how to take..
 */

namespace Gungi
{
    Player::Player(Board* gameBoard, const Color& color, const Color& oppColor, Orientation o)
    : _pieces       (color, oppColor)
    , _gameBoard    (gameBoard)
    , _color        (color)
    , _oppColor     (oppColor)
    , _orientation  (o)
    , _onBoard      (0)
    , _onHand       (STD_PIECE_CT)
    , _numPieces    (STD_PIECE_CT)
    {}

    bool Player::drop(const SizeType& i, SmallPoint3 pt3)
    {
        if (not(isUnbounded(pointAt(i))))
            return false;

        if (not(validPlacementDrop(*_gameBoard, pieceAt(i), pt3, _orientation)))
            return false;
         
        if (_orientation == ORIENTATION_NEG)
            pt3 = asPositive3(pt3);

        pt3.y = availableTierAt(*_gameBoard, pt3);

        _pieces.pointAt(i) = pt3;
        placeAt(*_gameBoard, pieceAt(i), pt3);
        return true;
    }

    bool Player::shift(const SizeType& i, const Move& move)
    {
        #if (DEBUG)
            cout << "Player.shift() --> _orientation: " << _orientation << endl;
            cout << "Player.shift() --> Point at i: " << pointAt(i) << endl;
        #endif
        
        auto pt2 = genIndex2Of(pointAt(i), move, _orientation);

        if (_orientation == ORIENTATION_NEG)
            pt2 = asPositive2(pt2);

        auto pieceMoveSet = pieceAt(i).onHead() ? genHeadMoveSet(pieceAt(i), 
                asTier(pointAt(i).y)) : genTailMoveSet(pieceAt(i), asTier(pointAt(i).y));

        auto itr = std::find_if(pieceMoveSet.begin(), pieceMoveSet.end(), [&move] (const Move& rhs)
                { return move == rhs; });

        if (itr == pieceMoveSet.end())
        {
            #if (DEBUG)
                cout << "Player.shift() --> Move not in piece's moveset." << endl;
            #endif
            return false;

        }

        #if (DEBUG)
            cout << "Player.shift() --> Move in piece's moveset." << endl;
            cout << "Player.shift() --> pt2: " << pt2 << endl;
        #endif

        if (isUnbounded(pt2))
            return false;

        auto pt3 = SmallPoint3(pt2);
        pt3.y = availableTierAt(*_gameBoard, pt3);

        if (pt3.y == NO_TIERS_FREE)
        {
            auto pieceColor = (*((*_gameBoard)[pt3])).getActiveColor();
            if (pieceColor == _color)
                return false;
                         
        }

        if (not(isUnbounded(pointAt(i))))
            nullifyAt(*_gameBoard, pointAt(i));
       
        #if (DEBUG)
            cout << "Player.shift() --> pt3: " << pt3 << endl;
        #endif

        _pieces.pointAt(i) = pt3;
        placeAt(*_gameBoard, pieceAt(i), pointAt(i));
        return true;
    }

    void Player::transfer(const SizeType& i, Player& player)
    {
        nullifyAt(*_gameBoard, pointAt(i), _orientation);
        _nullifyIndex(i);
        player.append(_pieces.remove(i));
    }

    void Player::append(IndexedPiece pc)
    {
        _pieces.append(pc);
    }

    const IndexedPiece& Player::operator [] (const SizeType& i) const
    {
        return _pieces.Set[i];
    }

    const Piece& Player::pieceAt(const SizeType &i) const
    {
        return _pieces.pieceAt(i);
    }

    const SmallPoint3& Player::pointAt(const SizeType& i) const
    {
        return _pieces.pointAt(i);
    }

    const Color& Player::colorAt(const SizeType& i) const
    {
        return _pieces.pieceAt(i).getActiveColor();
    }

    const Color& Player::getColor() const
    {
        return _color;
    }

    const Color& Player::getOppColor() const
    {
        return _oppColor;
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

    void Player::_nullifyIndex(const SizeType& i)
    {
        _pieces.pointAt(i) = UBD_PT3;
    }

    Game::Game()
    : _onesTurn      (true)
    , _gameBoard     (BOARD_WIDTH, BOARD_DEPTH, BOARD_HEIGHT, &NULL_PIECE)
    , _one           (&_gameBoard, Color::Black, Color::White, ORIENTATION_POS)
    , _two           (&_gameBoard, Color::White, Color::Black, ORIENTATION_NEG)
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

    const Board* Game::gameBoard() const
    {
        return &_gameBoard;
    }

    const Player* Game::playerOne() const
    {
        return &_one;
    }

    const Player* Game::playerTwo() const
    {
        return &_two;
    }

    const Player& Game::currentPlayer() const
    {
        return *_currentPlayer; 
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

    bool Game::move(const SizeType& i, const Move& move)
    {
        if (!_running())
            return false;

        if (!_currentPlayer->shift(i,move))
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

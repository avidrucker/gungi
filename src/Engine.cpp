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

#include <Engine.hpp>

namespace Gungi
{
    Player::Player(Board* gameBoard, const Color& color, const Orientation& o)
    : _gameBoard    (gameBoard)
    , _color        (color)
//    , _onHandCursor (STD_PIECE_CT)
    , _orientation  (o)
    {
       initPieceSet(_pieces);
    }

    bool Player::drop(const AccessType& i, SmallPoint3 pt3)
    {
        if (!_pieces[i].isUnbounded())
            nullifyAt(*_gameBoard, _pieces[i].getIndex(), getOrientation()); 

        pt3.y = availableTierAt(*_gameBoard, pt3, getOrientation());
        if (pt3.y == NO_TIERS_FREE)
            return false;

        _pieces[i].setIndex(pt3);
        placeAt(*_gameBoard, &_pieces[i]);
        return true;
    }

    bool Player::shift(const AccessType& i, const Move& move)
    {
        auto pt2 = genIndex2(_pieces[i].getIndex(), move, getOrientation());
        if (isUnbounded(pt2))
            return false;

        if (!_pieces[i].isUnbounded())
            nullifyAt(*_gameBoard, _pieces[i].getIndex(), getOrientation()); 

        auto pt3 = pt2;
        pt3.y = availableTierAt(*_gameBoard, pt3, getOrientation());

        if (pt3.y == NO_TIERS_FREE)
            return false;
        
        _pieces[i].setIndex(pt3);
        placeAt(*_gameBoard, &_pieces[i]);
        return true;
    }

    void Player::transfer(const AccessType& idx, Player& player)
    {
        nullifyAt(*_gameBoard, _pieces[idx].getIndex(), getOrientation());
        player.append(_pieces[idx]);
        _pieces.erase(_pieces.cbegin() + idx);
    }

    void Player::append(IndexedPiece pc)
    {
        pc.setIndex(SmallPoint3(UNBOUNDED, UNBOUNDED, UNBOUNDED));
        _pieces.push_back(pc);
    }

    const IndexedPiece& Player::operator [] (const AccessType& i) const
    {
        return _pieces[i];
    }

    const SmallPoint3& Player::indexFor(const AccessType& i) const
    {
        return _pieces[i].getIndex();
    }

    const Player::Color& Player::getColor() const
    {
        return _color;
    }

    const PieceSet& Player::getFullSet() const
    {
        return _pieces;
    }

    const Orientation& Player::getOrientation() const
    {
        return _orientation;
    }

    Phase& operator ++ (Phase& phase)
    {
        switch (phase)
        {
            case Phase::Standby:
                phase = Phase::Placement;
                return phase;
            case Phase::Placement:
                phase = Phase::Running;
                return phase;
            case Phase::Running:
                phase = Phase::Placement;
                return phase;
        }
    }

    Phase& operator -- (Phase& phase)
    {
        switch (phase)
        {
            case Phase::Standby:
                phase = Phase::Running;
                return phase;
            case Phase::Placement:
                phase = Phase::Standby;
                return phase;
            case Phase::Running:
                phase = Phase::Placement;
                return phase;
        }
    }

    Game::Game()
    : _onesTurn      (true)
    , _gameBoard     (BOARD_WIDTH, BOARD_DEPTH, BOARD_HEIGHT, &NULL_PIECE)
    , _one           (&_gameBoard, Player::Color::Black, Orientation::Positive)
    , _two           (&_gameBoard, Player::Color::White, Orientation::Negative)
    , _phase         (Phase::Standby)
    , _currentPlayer (nullptr)
    {}

    Game::~Game()
    {
        _currentPlayer = nullptr;
    }

    void Game::start()
    {
        if (_phase == Phase::Standby)
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

    bool Game::drop(const AccessType& i, const SmallPoint3& pt)
    {
        if (_phase == Phase::Standby)
            return false;

        if (validPlacementDrop(i, pt, _currentPlayer->getOrientation()))
        {
            _currentPlayer->drop(i, pt);
            _flipPlayer();
            return true;
        }

        return false;
    }

    bool Game::move(const AccessType& idx, const Move& move)
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

    bool Game::validPlacementDrop(const AccessType& i, SmallPoint3 pt3,
            const Orientation& o) const
    {
        auto pieceSet = _currentPlayer->getFullSet();
        auto piece = pieceSet[i];

        if (_currentPlayer->getOrientation() == Orientation::Positive)
        {
            if (pt3.z >= VALID_PLCMT_DEPTH)
                return false;

            if (piece.getHead() == Head::Soldier)
            {
                for (uint8_t i = 0u; i < VALID_PLCMT_DEPTH; ++i)
                {
                    for (uint8_t j = 0u; j < BOARD_HEIGHT; ++j)
                    {
                        pt3.z = i;
                        pt3.y = j;
                        if (isNullAt(_gameBoard, pt3))
                            break;

                        if (_gameBoard[pt3]->getHead() == Head::Soldier)
                            return false;
                    }
                }
            }
        }
        else
        {
            if (!(pt3.z >= (BOARD_DEPTH - VALID_PLCMT_DEPTH)
                    && pt3.z < BOARD_DEPTH))
                return false; 

            if (piece.getHead() == Head::Soldier)
            {
                for (auto i = (BOARD_DEPTH - VALID_PLCMT_DEPTH); 
                        i < BOARD_DEPTH; ++i)
                {
                    for (auto j = 0u; j < BOARD_HEIGHT; ++j)
                    {
                        SmallPoint3 tmp = { pt3.x, i, j };
                        if (_gameBoard[tmp]->getHead() == Head::Soldier)
                            return false;
                    }
                }
            }
        }
        return true;
    }

    bool Game::_running() const
    {
        return _phase == Phase::Running;
    }
}

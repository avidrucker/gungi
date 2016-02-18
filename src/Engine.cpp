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

    bool Player::drop(const AccessType& idx, const SmallPoint3& spot)
    {
        return _place(idx, spot);
    }

    bool Player::place(const AccessType& idx, const Move& move)
    {
        return true;
    }

    void Player::transfer(const AccessType& idx, Player& player)
    {
        nullifyAt(*_gameBoard, _pieces[idx].getIndex());
        player.append(_pieces[idx]);
        _pieces.erase(_pieces.cbegin() + idx);
    }

    void Player::append(const IndexedPiece& pc)
    {
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

    const Player::Orientation& Player::getOrientation() const
    {
        return _orientation;
    }

    void Player::_makePositive(SmallPoint3& pt)
    {
        pt.x = BOARD_WIDTH - pt.x;
        pt.z = BOARD_DEPTH - pt.z;
    }

    bool Player::_place(const AccessType& i, SmallPoint3 pt)
    {
        if (_orientation == Orientation::Negative)
            _makePositive(pt);

        if (!_pieces[i].isUnbounded())
            nullifyAt(*_gameBoard, _pieces[i].getIndex()); 

        auto tmp = _pieces[i].getIndex();
        tmp.y = availableTierAt(*_gameBoard, pt); 
        _pieces[i].setIndex(tmp);
        if (_pieces[i].getIndex().y == NO_TIERS_FREE)
            return false;
        
        placeAt(*_gameBoard, &_pieces[i]);
        return true;
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
    , _one           (&_gameBoard, Player::Color::Black, Player::Orientation::Positive)
    , _two           (&_gameBoard, Player::Color::White, Player::Orientation::Negative)
    , _phase         (Phase::Standby)
    , _currentPlayer (nullptr)
    {}

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

    bool Game::placeOnBoard(const AccessType& i, const SmallPoint3& pt)
    {
        if (_phase == Phase::Standby)
            return false;

        //auto pt = Board::convertIndex(_currentPlayer->getOrientation(), spot);

        if (_validPlacement(i, pt, _currentPlayer->getOrientation()))
        {
            _currentPlayer->drop(i, pt);
            _flipPlayer();
            return true;
        }

        return false;
    }

    void Game::move(const AccessType& idx, const Move& move)
    {
        if (_running())
        {
            _currentPlayer->place(idx,move);
            _flipPlayer();
        }
    }

    void Game::_flipPlayer()
    {
        _currentPlayer = _onesTurn ? &_two : &_one;
        _onesTurn = !_onesTurn;
    }

    bool Game::_validPlacement(const AccessType& i, const SmallPoint3& spot, 
            const Player::Orientation& o) const
    {
        if (_phase == Phase::Placement)
        {
            std::cout << spot.x << ',' << spot.z << ',' << spot.y << std::endl;
            auto PieceSet = _currentPlayer->getFullSet();
            auto Piece = PieceSet[i];

            if (o == Player::Orientation::Positive)
            {
                if (spot.z >= VALID_PLACEMENT_DEPTH)
                    return false;

                // Could be optimized worst-case @ O(n)
                if (Piece.getHead() == Head::Soldier)
                {
                    for (auto i = 0u; i < VALID_PLACEMENT_DEPTH; ++i)
                    {
                        for (auto j = 0u; j < BOARD_HEIGHT; ++j)
                        {
                            SmallPoint3 tmp = { spot.x, i, j };
                            if (_gameBoard[tmp]->getHead() == Head::Soldier)
                                return false;
                        }
                    }
                }
            }
            else
            {
                if (!(spot.z >= (BOARD_DEPTH - VALID_PLACEMENT_DEPTH)
                        && spot.z < BOARD_DEPTH))
                    return false; 

                if (Piece.getHead() == Head::Soldier)
                {
                    for (auto i = (BOARD_DEPTH - VALID_PLACEMENT_DEPTH); 
                            i < BOARD_DEPTH; ++i)
                    {
                        for (auto j = 0u; j < BOARD_HEIGHT; ++j)
                        {
                            SmallPoint3 tmp = { spot.x, i, j };
                            if (_gameBoard[tmp]->getHead() == Head::Soldier)
                                return false;
                        }
                    }
                }
            }

            //if (_gameBoard.hasAnEmptyTier(spot))
             //   return true;

            return false;
        }
        else
        {
            return true;
        }
    }

    bool Game::_running() const
    {
        return _phase == Phase::Running;
    }
}

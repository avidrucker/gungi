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

#include <Gungi.hpp>

namespace Gungi
{
    const IndexedPiece Board::NOT_A_PIECE { Head::None, Tail::None };

    Board::Board()
    : Super (BOARD_SIZE, BOARD_SIZE, BOARD_TIERS)
    {
        for (decltype (getSize()) i = 0; i < getSize(); ++i)
            _matrix[i] = &Board::NOT_A_PIECE;
    }

    bool Board::hasAnEmptyTier(Point3 idx) const
    {
        bool emptyTier = false;
        for (auto i = 0u; !emptyTier && i < BOARD_TIERS; ++i)
        {
            idx.z = i;
            auto j = coorToIndex(idx, getWidth(), getDepth());
            if (_matrix[j]->isNull())
                emptyTier = true; 
        }
        return emptyTier;
    }

    Point3 Board::convertIndex(const Orientation& o, const Point3& idx)
    {
        if (o == Orientation::Positive) // I know, what's the point of having the function
            return idx;
        
        auto pt = idx;
        pt.x = BOARD_SIZE - idx.x;
        pt.z = BOARD_SIZE - idx.z;
        return pt;
    }

    Player::Player(Board& gameBoard, const Color& color, const Orientation& o)
    : _pieces       ()
    , _gameBoard    (&gameBoard)
    , _color        (color)
    , _onHandCursor (STD_PIECE_CT)
    , _orientation  (o)
    {}

    Player::Player(Board* gameBoard, const Color& color, const Orientation& o)
    : _pieces       ()
    , _gameBoard    (gameBoard)
    , _color        (color)
    , _onHandCursor (STD_PIECE_CT)
    , _orientation  (o)
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

    const Player::SetType& Player::getFullSet() const
    {
        return _pieces.showSet();
    }

    const Player::Orientation& Player::getOrientation() const
    {
        return _orientation;
    }

    Game::Game()
    : _onesTurn      (true)
    , _gameBoard     (Board())
    , _one           (&_gameBoard, Player::Color::Black, Board::Orientation::Positive)
    , _two           (&_gameBoard, Player::Color::White, Board::Orientation::Negative)
    , _phase         (Phase::Standby)
    {}

    void Game::start()
    {
        if (_phase == Phase::Standby)
        {
            _currentPlayer = &_one;
            _progressPhase();
        }
    }

    const Board& Game::gameBoard() const
    {
        return _gameBoard;
    }

    const Player& Game::currentPlayer() const
    {
        return *_currentPlayer; 
    }

    bool Game::placeOnBoard(const AccessType& i, const Point3& spot)
    {
        if (_phase == Phase::Standby)
            return false;

        auto pt = Board::convertIndex(_currentPlayer->getOrientation(), spot);

        if (_validPlacement(i, pt, _currentPlayer->getOrientation()))
        {
            _currentPlayer->placeOnBoard(i, pt);
            _flipPlayer();
            return true;
        }

        return false;
    }

    void Game::move(const AccessType& idx, const Move& move)
    {
        if (_running())
        {
            _currentPlayer->move(idx,move);
            _flipPlayer();
        }
    }

    void Game::_flipPlayer()
    {
        _currentPlayer = _onesTurn ? &_two : &_one;
        _onesTurn = !_onesTurn;
    }

    void Game::_progressPhase()
    {
        switch (_phase)
        {
            case Phase::Standby:
                _phase = Phase::Placement;
                break;
            case Phase::Placement:
                _phase = Phase::Running;
                break;
            case Phase::Running:
                _phase = Phase::Standby;
                break;
        }
    }

    bool Game::_validPlacement(const AccessType& i, const Point3& spot, 
            const Board::Orientation& o) const
    {
        if (_phase == Phase::Placement)
        {
            std::cout << spot.x << ',' << spot.z << ',' << spot.y << std::endl;
            auto PieceSet = _currentPlayer->getFullSet();
            auto Piece = PieceSet[i];

            if (o == Board::Orientation::Positive)
            {
                if (spot.z >= VALID_PLACEMENT_DEPTH)
                    return false;

                // Could be optimized worst-case @ O(n)
                if (Piece.getHead() == Head::Soldier)
                {
                    for (auto i = 0u; i < VALID_PLACEMENT_DEPTH; ++i)
                    {
                        for (auto j = 0u; j < BOARD_TIERS; ++j)
                        {
                            Point3 tmp = { spot.x, i, j };
                            if (_gameBoard[tmp]->getHead() == Head::Soldier)
                                return false;
                        }
                    }
                }
            }
            else
            {

                if (!(spot.z >= (BOARD_SIZE - VALID_PLACEMENT_DEPTH)
                        && spot.z < BOARD_SIZE))
                    return false; 

                if (Piece.getHead() == Head::Soldier)
                {
                    for (auto i = (BOARD_SIZE - VALID_PLACEMENT_DEPTH); 
                            i < BOARD_SIZE; ++i)
                    {
                        for (auto j = 0u; j < BOARD_TIERS; ++j)
                        {
                            Point3 tmp = { spot.x, i, j };
                            if (_gameBoard[tmp]->getHead() == Head::Soldier)
                                return false;
                        }
                    }
                }
            }

            if (_gameBoard.hasAnEmptyTier(spot))
                return true;

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

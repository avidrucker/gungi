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
    , _orientation  (o)
    {
       initPieceSet(_pieces);
    }

    bool Player::drop(const AccessType& i, SmallPoint3 pt3)
    {
        std::cout << "P Inside drop function" << std::endl;

        if (!_pieces[i].isUnbounded())
            nullifyAt(*_gameBoard, _pieces[i].getIndex(), getOrientation()); 
         
        std::cout << "P Index has been nullified." << std::endl;

        auto tmp = availableTierAt(*_gameBoard, pt3, getOrientation());
		std::cout << "P Free tiers count: " << (size_t) tmp << std::endl;
		if (tmp == NO_TIERS_FREE)
            return false;

        std::cout << "P Tier avaialable at: " << tmp << std::endl;

        if (getOrientation() == Orientation::Negative)
            pt3 = asPositive3(pt3);

        std::cout << "P Converted pt3 to postive if needed." << std::endl;
        
        pt3.y = tmp;
        _pieces[i].setIndex(pt3);
        placeAt(*_gameBoard, &_pieces[i]);
        std::cout << "P Piece placed." << std::endl;
        auto p = _pieces[i].getIndex();
        std::cout << "P Piece Index: (" << (size_t) p.x << ", " << (size_t) p.z 
            << ", " << (size_t) p.y << ")" << std::endl;
        std::cout << "P Is null there: " << isNullAt(*_gameBoard, p) << std::endl;
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

    bool Game::drop(const AccessType& i, const SmallPoint3& pt)
    {
        if (_phase == Phase::Standby)
            return false;

		std::cout << "G Phase is not standby." << std::endl;
		std::cout << "Pt is (" << (size_t) pt.x << ", " << (size_t) pt.z << ", " << (size_t) pt.y 
			<< ")." << std::endl;
        if (validPlacementDrop(i, pt, _currentPlayer->getOrientation()))
        {
			std::cout << "G Placement was valid." << std::endl;
            _currentPlayer->drop(i, pt);
            _flipPlayer();
            return true;
        }

		std::cout << "G Place was invalid." << std::endl;

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

		std::cout << "V Inside validPlacementDrop" << std::endl;

        if (_currentPlayer->getOrientation() == Orientation::Positive)
        {
			std::cout << "V Player Orientation is positive." << std::endl;
            if (pt3.z >= VALID_PLCMT_DEPTH)
                return false;
            
			std::cout << "V Pc's Z: " << (size_t) pt3.z << " is >= " << (size_t) VALID_PLCMT_DEPTH << std::endl;
            if (piece.getHead() == Head::Soldier)
            {
				std::cout << "V Piece is a soldier." << std::endl;
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
				std::cout << "Soldier can be placed here." << std::endl;
            }
        }
        else
        {
			std::cout << "V Player Orientation is negative." << std::endl;
			pt3 = asPositive3(pt3);
			std::cout << "V Pt is now (" << (size_t) pt3.x << ", " << (size_t) pt3.z << ", " << 
				(size_t) pt3.y << ")" << std::endl;
			if (!(pt3.z >= (BOARD_DEPTH - VALID_PLCMT_DEPTH)))
                return false; 

			std::cout << "V Pc's Z: " << (size_t) pt3.z << " is >= " << (size_t) (BOARD_DEPTH - VALID_PLCMT_DEPTH) << 
				" && " << " < " << (size_t) BOARD_DEPTH << std::endl;

            if (piece.getHead() == Head::Soldier)
            {
				std::cout << "V Piece is a soldier." << std::endl;
                for (uint8_t i = (BOARD_DEPTH - VALID_PLCMT_DEPTH); 
                        i < BOARD_DEPTH; ++i)
                {
                    for (uint8_t j = 0u; j < BOARD_HEIGHT; ++j)
                    {
                        SmallPoint3 tmp = { pt3.x, i, j };
                        if (_gameBoard[tmp]->getHead() == Head::Soldier)
                            return false;
                    }
                }
						std::cout << "Soldier can be placed here." << std::endl;
            }
        }
        return true;
    }

    bool Game::_running() const
    {
        return _phase == Phase::Running;
    }
}

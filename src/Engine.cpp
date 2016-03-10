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
    : _pieces         (color, oppColor)
    , _gameBoard      (gameBoard)
    , _color          (color)
    , _oppColor       (oppColor)
    , _orientation    (o)
    , _onBoard        (0)
    , _onHand         (STD_PIECE_CT)
    , _numPieces      (STD_PIECE_CT)
    {}

    void Player::drop(const SizeType& i, const SmallPoint3& pt3)
    {
        _pieces.pointAt(i) = pt3;
        placeAt(*_gameBoard, &_pieces.pieceAt(i), pt3);
        --_onHand;
        ++_onBoard;
    }

    void Player::updatePoint(const SizeType& i, const SmallPoint3& pt3)
    {
        _pieces.pointAt(i) = pt3;
    }

    void Player::remove(const SizeType& i)
    {
        _pieces.remove(i);
        --_onBoard;
    }

    void Player::append(const Piece& pc)
    {
        _pieces.append(pc, UBD_PT3);
        ++_onHand;
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

    SizeType Player::getIndexAt(const SmallPoint3& pt3) const
    {
        for (SizeType i = 0; i < _pieces.Set.size(); ++i)
            if (_pieces.pointAt(i) == pt3)
                return i;

        return UNBOUNDED;
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

    IndexState Game::drop(const SizeType& i, SmallPoint3 pt3)
    {
        #if (DEBUG)
            cerr << "In Game::drop()"<< endl;
        #endif

        auto state = assessDrop(_onesTurn, i, pt3);
        if (!(state.validState))
            return state;
        
        #if (DEBUG)
            cerr << "In Game::drop(), drop is valid." << endl;
        #endif

        Player* player = _onesTurn ? &_one : &_two;
        if (!(player->getOrientation()))
            pt3 = asPositive3(pt3);

        pt3.y = availableTierAt(_gameBoard, pt3);

        #if (DEBUG)
            cerr << "In Game::drop(), pt3: " << pt3 << endl;
        #endif

        player->updatePoint(i, pt3);
        placeAt(_gameBoard, &player->pieceAt(i), pt3);
        _flipPlayer();
        return state;
    }


    IndexState Game::move(const SizeType& i, const Move& move)
    {
        #if (DEBUG)
            cerr <<  "In Game::move()" << endl;
        #endif

        auto state = assessMove(_onesTurn, i, move);

        if (!(state.validState))
            return state;

        #if (DEBUG)
            cerr << "In Game::move(), move is valid." << endl;
        #endif

        Player* player = _onesTurn ? &_one : &_two;
        auto tmp = player->getOrientation() ? genIndex2Of(player->pointAt(i), move) :
            genIndex2Of(asPositive3(player->pointAt(i)), move);
        auto pt3 = SmallPoint3(tmp);
        
        if (player->getOrientation() == ORIENTATION_NEG)
            pt3 = asPositive3(pt3);
        
        pt3.y = availableTierAt(_gameBoard, pt3);

        if (state.onOpponent)
        {
            #if (DEBUG)
                cerr << "In Game::move(), on opponent." << endl;
            #endif
            --pt3.y;
            _takeAndTransfer(i, pt3);
        }

        #if (DEBUG)
            cerr << "In Game::move(), destination pt3: " << pt3 << endl;
        #endif

        nullifyAt(_gameBoard, player->pointAt(i));
        player->updatePoint(i, pt3); 
        placeAt(_gameBoard, &player->pieceAt(i), pt3);
        _flipPlayer();

        return state;
    }
            
    IndexState Game::assessDrop(bool playerOne, const SizeType& i, SmallPoint3 pt3) const
    {
        #if (DEBUG)
            cerr << "In Game::assessDrop()" << endl;
        #endif

        const Player* player = playerOne ? &_one : &_two;
        auto piece = player->pieceAt(i);
        auto point = player->pointAt(i);
        auto positiveOrientation = player->getOrientation();

        if (_phase == Phase::Standby || !(isUnbounded(point)) || 
                !(validPlacementDrop(_gameBoard, piece, pt3, positiveOrientation)))
            return IndexState(false, false, Tier::None);

        #if (DEBUG)
            cerr << "In Game::assessDrop(), _phase is valid, point is unbounded, and drop is valid." 
                << endl;
        #endif

        if (!(positiveOrientation))
            pt3 = asPositive3(pt3);

        pt3.y = availableTierAt(_gameBoard, pt3);
        

        #if (DEBUG)
            cerr << "In Game::assessDrop(), evaluation pt3: " << pt3 << endl;
        #endif

        bool onOpponent = pt3.y == 0 ? false : 
            player->getOppColor() == _gameBoard(pt3.x, pt3.z, pt3.y - 1)->getActiveColor();
    
        return IndexState(true, onOpponent, asTier(pt3.y));
    }

    IndexState Game::assessMove(bool playerOne, const SizeType& i, const Move& move) const
    {
        #if (DEBUG)
            cerr << "In Game::assessMove()" << endl;
        #endif

        const Player* player = playerOne ? &_one : &_two; //Already have a player* pointer?
        auto piece = player->pieceAt(i);
        auto point = player->pointAt(i);
        auto positiveOrientation = player->getOrientation();

        if (isUnbounded(point))
            return IndexState(false, false, Tier::None);

        if (point.y != 2)
        {
            auto pieceAbove = SmallPoint3(point.x, point.z, point.y + 1);
            if (!(isNullAt(_gameBoard, pieceAbove)))
                return IndexState(false, false, Tier::None);

            #if (DEBUG)
                cerr << "In Game::assessMove(), point: " << point << endl;
                cerr << "In Game::assessMove(), pieceAbove: " << pieceAbove << endl;
            #endif
        }

        auto pt2 = positiveOrientation ? genIndex2Of(point, move) : 
            genIndex2Of(asPositive2(point), move);

        if (isUnbounded(pt2))
            return IndexState(false, false, Tier::None);

        #if (DEBUG)
            cerr << "In Game::assessMove(), pt2 is bounded." << endl;
            cerr << "In Game::assessMove(), evaluation pt2: " << pt2 << endl;
        #endif

        auto pieceMoveSet = piece.onHead() ? genHeadMoveSet(piece, asTier(point.y)) : 
            genTailMoveSet(piece, asTier(point.y));

        auto itr = std::find_if(pieceMoveSet.begin(), pieceMoveSet.end(), [&move] (const Move& rhs)
                { return move == rhs; });

        if (itr == pieceMoveSet.end())
            return IndexState(false, false, Tier::None);

        #if (DEBUG)
            cerr <<  "In Game::assessMove(), move is in piece's moveset." << endl;
        #endif

        if (!(piece.canJump()) && flatPathHas(_gameBoard, pt2, move, [] (const Piece& piece)
                    { return !(piece.isNull());}))
            return IndexState(false, false, Tier::None);

        auto pt3 = player->getOrientation() == ORIENTATION_POS ? SmallPoint3(pt2) : 
            asPositive3(pt2);
        pt3.y = availableTierAt(_gameBoard, pt3);

        IndexState state { true, true, Tier::None };
        if (pt3.y == 0)
            state.onOpponent = false;
        else
        {
            SizeType indexBelow = pt3.y == NO_TIERS_FREE ? 2 : pt3.y - 1;
            state.onOpponent = player->getColor() != 
                _gameBoard(pt3.x, pt3.z, indexBelow)->getActiveColor();

            #if (DEBUG)
                std::string oppcolor = player->getColor() == Color::Black ? "Black" : "White";
                std::string actColor = _gameBoard(pt3.x, pt3.z, indexBelow)->getActiveColor() ==
                    Color::Black ? "Black" : "White";
                    
                cerr << "In Game::assessMove(), player's color: " << oppcolor << endl;
                cerr << "In Game::assessMove(), piece active's color: " << actColor << endl;
            #endif
        }

        return state;
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

    const Player* Game::currentPlayer() const
    {
        return _currentPlayer; 
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

    void Game::_takeAndTransfer(const SizeType& i, const SmallPoint3& oppPt3)
    {
        #if (DEBUG)
            cerr << "In Game::_takeAndTransfer()" << endl;
            cerr << "In Game::_takeAndTransfer(), i: " << (size_t) i << endl;
            cerr << "In Game::_takeAndTransfer(), oppPt3: " << oppPt3 << endl;
        #endif

        Player* opponent = _onesTurn ? &_two : &_one;
        auto pieceIndex = opponent->getIndexAt(oppPt3);
        if (pieceIndex == UNBOUNDED)
            return;
       
        //Returning Piece&& and using move-semantics can shrink these 3 lines to 1
        auto piece = opponent->pieceAt(pieceIndex);
        opponent->remove(pieceIndex);
        _currentPlayer->append(piece); 
    }
}

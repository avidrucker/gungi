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

#include <cstdint>
#include <vector>
#include <tuple>

#include <Matrix.hpp>

/**
 * Notes: 
 * 1. Consider making IndexedPiece a std::tuple< Piece, SmallPoint3>;
 *      Having an IndexedPiece container seems like poor design to me.
 * 2. Consider making a Piece Head,Tail as const.
 * 3. Consider removing setSide from Piece in favor of a flip() function.
 * 4. Consider storing pieces on a 32-bit int where bits correspnof to piece.
 * 5. Make orientation bools, enums are a waste, da fuq is this
 */

namespace Gungi
{
    class Move;
    
    constexpr uint8_t BOARD_WIDTH        = 9; /**< Standard Gungi board width (Cols). */
    constexpr uint8_t BOARD_DEPTH        = 9; /** Standard Gungi board depth (Rows). */
    constexpr uint8_t BOARD_HEIGHT       = 3; /**< Standard amount of tiers in Gungi board.*/
    constexpr uint8_t FRONT_PCS_CT       = 10; /**< Count of front side pieces. */
    constexpr uint8_t BACK_PCS_CT        = 10; /**< Count of back side pieces. */
    constexpr uint8_t UNBOUNDED          = ~0; /**< Indicates unbounded point. */
    constexpr uint8_t NO_TIERS_FREE      = ~0; /**< Indicates lack of available tiers. */
    constexpr uint8_t VALID_PLCMT_DEPTH  = 3; /**< Allowed rows to drop pieces during placement.*/
    constexpr uint8_t STD_PIECE_CT       = 23; /**< Standard initial piece count per player. */
    constexpr uint8_t CAPTAIN_RANK       = 12; /**< Rank value of captain. */
    constexpr uint8_t SAMURAI_RANK       = 10; /**< Rank value of samurai. */
    constexpr uint8_t NINJA_RANK         = 8; /**< Rank value of ninja. */
    constexpr uint8_t HIDDEN_DRAGON_RANK = 8; /**< Rank value of hidden dragon. */
    constexpr uint8_t CATAPULT_RANK      = 6; /**< Rank value of catapult. */
    constexpr uint8_t FORTRESS_RANK      = 6; /**< Rank value of fortress. */
    constexpr uint8_t PRODIGY_RANK       = 4; /**< Rank value of prodigy. */
    constexpr uint8_t ARCHER_RANK        = 4; /**< Rank value of archer. */
    constexpr uint8_t SOLDIER_RANK       = 2; /**< Rank value of soldier. */
    constexpr uint8_t NO_HEAD            = 0; /**< Indicates piece wihout head (null piece). */
    constexpr uint8_t DRAGON_KING_RANK   = 12; /**< Rank value of dragon king. */
    constexpr uint8_t LANCE_RANK         = 10; /**< Rank value of lance. */
    constexpr uint8_t PHOENIX_RANK       = 10; /**< Rank value of phoenix. */
    constexpr uint8_t JOUNIN_RANK        = 8; /**< Rank value of jounin. */
    constexpr uint8_t ARROW_RANK         = 6; /**< Rank value of arrow. */
    constexpr uint8_t PIKE_RANK          = 6; /**< Rank value of pike. */
    constexpr uint8_t GOLD_RANK          = 6; /**< Rank value of gold. */
    constexpr uint8_t PISTOL_RANK        = 4; /**< Rank value of pistol. */
    constexpr uint8_t SILVER_RANK        = 4; /**< Rank value of silver. */
    constexpr uint8_t BRONZE_RANK        = 2; /**< Rank value of bronze. */
    constexpr uint8_t NO_TAIL            = 0; /**< Indicates piece wihout tail.*/

    using RankSize     = uint8_t;
    using SmallPoint2  = Point2<uint8_t>;
    using SmallPoint3  = Point3<uint8_t>;
    using MoveSet      = std::vector<Move>;
    using IndexedPiece = std::tuple<Piece, SmallPoint3>;
    using PieceSet     = std::vector<IndexedPiece>;
    using Board        = Matrix3<const Piece*, uint8_t>;

    /**
     * Enum that stores possible board orientations. Positive indicates
     * that the board is being accessed with x(0),z(0) being at the immediate left
     * of the computer screen. Negative indicates that board is being accessed with 
     * x,z being at the far right of the computer screen.
     */
    enum class Orientation : uint8_t
    { Positive, Negative, None };

    /**
     * Enum that stores the directions of a move using the conventional NW (north west),
     * N (north), etc. , directions.
     */
    enum class Direction : uint8_t 
    { NW, N, NE, E, SE, S, SW, W };

    /**
     * Enum that stores the current tier of a value.
     */
    enum class Tier : uint8_t 
    { One, Two, Three };


    /**
     * Enum that stores the head side character of a piece.
     */
    enum class Head : uint8_t
    { None, Commander, Captain, Samurai, Ninja,  Catapult, 
        Fortress, HiddenDragon , Prodigy, Archer, Soldier };

    /**
     * Enum that stores the tail side character of a piece.
     */
    enum class Tail : uint8_t
    { None, Pistol, Pike, Jounin, Lance, DragonKing,
        Phoenix, Arrow, Gold, Silver, Bronze };

    /**
     * Enum that stores the phases of a standard game.
     */
    enum class Phase : uint8_t
    { Standby, Placement, Running };
        
    const SmallPoint2 UBD_PT2 { UNBOUNDED, UNBOUNDED }; /**< Unbounded SmallPoint2. */
    const SmallPoint3 UBD_PT3 { UNBOUNDED, UNBOUNDED, UNBOUNDED }; /**< Unbounded SmallPoint3. */

    /**
     * This class holds a move that a piece can use. A move is merely a vector since it has
     * a magnitude and a direction. To chain moves, a move can also hold a pointer to another
     * move. This functionalility should only be used if a move can't created using one move.
     * This is not a linked list!
     */
    class Move
    {
        using MagnitudeType = uint8_t;

        public:

            /**
             * This constructor instantiates a move (vector) using the given magnitude
             * and direction.
             * @param magnitude the desired magnitude
             * @param direction the desired direction
             */
            Move(const MagnitudeType& magnitude, const Direction& direction);

            /**
             * This constructor instantiates a move (vector) using the given magnitude
             * and direction, and will store a link to another move that it will construct
             * using the second set of parameters.
             * @param magnitude the desired magnitude
             * @param direction the desired direction
             * @param nextMagnitude the desired magnitude of the next move
             * @param nextDirection the desired direction of the next move
             */
            Move(const MagnitudeType& magnitude, const Direction& direction, 
                    const MagnitudeType& nextMagnitude, const Direction& nextDirection);

            /**
             * This destructor will free the memory used by the next move if the instantiation
             * used a next move.
             */
            ~Move();

            /**
             * This method returns the magnitude of the move.
             * @return the magnitude of the move
             */
            const MagnitudeType& getMagnitude() const;

            /**
             * This returns the direction of the move.
             * @return the direction of the move.
             */
            const Direction& getDirection() const;

            /**
             * This method returns a pointer to the next move.
             * @return a pointer to the next move.
             */
            Move* getNext() const;

        private:
            const MagnitudeType _magnitude; /**< The magnitude of the move. */ 
            const Direction _direction; /**< The direction of the move. */
            Move* _next; /**< Pointer to the next move, if used. */
    };
    
    /**
     * This class is a board piece. A board piece contains a Head and a Tail
     * value. This is a restricted mutable class. The Head and Tail values can
     * not be modified after instantiating. The active side flag (bool) can be
     * modified however.
     */
    class Piece
    {
        public:

            /**
             * This constructor will instatiate a null piece. The null-piece flag
             * is set to true.
             */
            Piece();

            /**
             * This constructor will instatiate a piece with the given
             * Head and Tail value. The on-head flag is set to true. The null-piece
             * flag is set to false.
             * @param head the desired head value
             * @param tail the desired tail value
             */
            Piece(const Head& head, const Tail& tail = Tail::None);

            /**
             * This method sets the internal on-head flag to the passed parameter.
             * @param onHead true if piece is on head side
             */
            void setSide(const bool& onHead);
            
            /**
             * This method will flip the side of the piece.
             */
            void flip();

            /**
             * This method returns the head value.
             * @return a const reference to the head value
             */
            const Head& getHead() const;

            /**
             * This method returns the tail value.
             * @return a const reference to the tail value.
             */
            const Tail& getTail() const;

            /**
             * This method returns the null flag value of the piece.
             * @return true if piece is null
             */
            bool isNull() const;

            /**
             * This method returns the on head flag value of the piece.
             * @return true if piece is on head side
             */
            bool onHead() const;

        protected:
            Head _head; /**<  The head value of the piece. */
            Tail _tail; /**< The tail value of the piece. */
            bool _nullPiece; /**< Null piece flag. */
            bool _onHead; /**< On head flag. */
    };
    
    const Piece NULL_PIECE { Head::None, Tail::None }; /**< A null piece. */

    /**
     * This convenience operator overload increments a tier enum.
     */
    Tier& operator ++(Tier& tier);

    /**
     * This convenience operator overload decrements a tier enum.
     */
    Tier& operator --(Tier& tier);
    
    /**
     * This convenience operator overload increments a phase enum.
     */
    Phase& operator ++ (Phase& phase);

    /**
     * This convenience operator overload decrements a phase enum.
     */
    Phase& operator -- (Phase& phase);

    /**
     * This functions checks where a pt is bounded.
     * @param pt2 point to evaluate
     * @return true if pt2 is unbounded
     */
    bool isUnbounded(const SmallPoint2& pt2);

    /**
     * This functions checks where a pt is bounded.
     * @param pt3 point to evaluate
     * @return true if pt3 is unbounded
     */
    bool isUnbounded(const SmallPoint3& pt3);

    using BoardState = Matrix3<bool, uint8_t>;
    using Indices3 = std::vector<SmallPoint3>;
    using StateFilter = bool(*)(const SmallPoint3& pt3, const Piece&);

    /**
     * This function will initialize a PieceSet to the standard pieces distributed to a
     * player. This function is required since PieceSet isn't a class but a specialization of 
     * std::vector.
     * @param pieceSet PieceSet to initiliaze
     */
    void initPieceSet(PieceSet& pieceSet);

    /**
     * This function returns the head rank value of the given piece.
     * @param piece the Piece to evaluate
     * @return piece's head rank value
     */
    RankSize getHeadValue(const Piece& piece);

    /**
     * This function returns the tail rank value of the given piece.
     * @param piece the Piece to evaluate
     * @return piece's tail rank value
     */
    RankSize getTailValue(const Piece& piece);

    /**
     * This function will append the moves that the commander can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     */
    void genCommanderMoveSet    (MoveSet& moveset);

    /**
     * This function will append the moves that the captain can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genCaptainMoveSet      (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the samurai can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genSamuraiMoveSet      (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the ninja can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genNinjaMoveSet        (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the catapult can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genCatapultMoveSet     (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the fortress can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genFortressMoveSet     (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the hidden dragon can use before being 
     * filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genHiddenDragonMoveSet (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the prodigy can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genProdigyMoveSet      (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the archer can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genArcherMoveSet       (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the soldier can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genSoldierMoveSet      (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the dragon king can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genDragonKingMoveSet   (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the lance can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genLanceMoveSet        (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the phoenix can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genPhoenixMoveSet      (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the jounin can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genJouninMoveSet       (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the pike can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genPikeMoveSet         (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the arrow can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genArrowMoveSet        (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the gold can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     */
    void genGoldMoveSet         (MoveSet& moveset);

    /**
     * This function will append the moves that the pistol can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genPistolMoveSet       (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the silver can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     * @param tier the Tier used to determine which set of mvoes to append
     */
    void genSilverMoveSet       (MoveSet& moveset, const Tier& tier);

    /**
     * This function will append the moves that the can use before being filtered out.
     * @param moveset a reference to a MoveSet to append to: an in-out parameter
     */
    void genBronzeMoveSet       (MoveSet& moveset);

    /**
     * This function will generate the correct moveset for the given piece (using its' Head value)
     * and its' current tier. Passing a null piece will generate an empty moveset.
     * @param piece a piece
     * @param tier the piece's tier
     * @return unfiltered moveset of the piece given its' tier
     */
    MoveSet genHeadMoveSet(const Piece& piece, const Tier& tier);

    /**
     * This function will generate the correct moveset for the given piece (using its' Tail value)
     * and its' current tier. Passing a null piece will generate an empty moveset.
     * @param piece a piece
     * @param tier the piece's tier
     * @return unfiltered moveset of the piece given its' tier
     */
    MoveSet genTailMoveSet(const Piece& piece, const Tier& tier);

    /**
     * This convenience function subtracts two unsigned operands. If lhs operand < rhs operand,
     * then the specified overflow value is returned.
     * @param lhs the left hand side operand
     * @param rhs the right hand side operand
     * @param overflow the overflow value to return if lhs < rhs
     * @return difference if lhs >= rhs, otherwise returns overflow
     */
    template <class SizeType>
    SizeType OverflowSub(const SizeType& lhs, const SizeType& rhs, const SizeType& overflow)
    {
        if (lhs < rhs)
            return overflow;
        else
            return lhs - rhs;
    }

    /**
     * This convenience function adds two unsigned operands. If the result > constraint,
     * then the specified overflow value is returned.
     * @param lhs the left hand side operand
     * @param rhs the right hand side operand
     * @param constraint the constraint value 
     * @param overflow the overflow value to return if result > constraint
     * @return sum if the result <= constraint, otherwise returns overflow
     */
    template <class SizeType>
    SizeType OverflowAdd(const SizeType& lhs, const SizeType& rhs,
            const SizeType& constraint, const SizeType& overflow)
    {
        SizeType res = lhs + rhs;
        return res < constraint ? res : overflow;
    }
   
    /**
     * This function will invert a negative orientation SmallPoint2 to its positive
     * value.
     * @param pt2 a point
     * @return the positive (inverse) of pt2
     */
    SmallPoint2 asPositive2(const SmallPoint2& pt2);
    
    /**
     * This function will invert a positive orientation SmallPoint2 to its negative
     * value.
     * @param pt2 a point
     * @return the negative (inverse) of pt2
     */
    SmallPoint2 asNegative2(const SmallPoint2& pt2);

    /**
     * This function will invert a positive orientation SmallPoint3 to its negative
     * SmallPoint2 value.
     * @param pt3 a point
     * @return the negative SmallPoint2 (inverse) of pt3
     */
    SmallPoint2 asPositive2(const SmallPoint3& pt3);

    /**
     * This function will invert a negative orientation SmallPoint3 to its positive
     * SmallPoint2 value.
     * @param pt3 a point
     * @return the positive SmallPoint2 (inverse) of pt3
     */
    SmallPoint2 asNegative2(const SmallPoint3& pt3);

    /**
     * This function will invert a negative orientation SmallPoint2 to its positive
     * SmallPoint3 value.
     * @param pt2 a point
     * @return the positive SmallPoint3 (inverse) of pt2
     */
    SmallPoint3 asPositive3(const SmallPoint2& pt2);

    /**
     * This function will invert a postive orientation SmallPoint2 to its negative
     * SmallPoint3 value.
     * @param pt2 a point
     * @return the negative SmallPoint3 (inverse) of pt2
     */
    SmallPoint3 asNegative3(const SmallPoint2& pt2);

    /**
     * This function will invert a negative orientation SmallPoint3 to its positive
     * SmallPoint3 value.
     * @param pt3 a point
     * @return the positive SmallPoint3 (inverse) of pt2
     */
    SmallPoint3 asPositive3(const SmallPoint3& pt3);

    /**
     * This function will invert a postive orientation SmallPoint3 to its negative
     * SmallPoint3 value.
     * @param pt3 a point
     * @return the negative SmallPoint3 (inverse) of pt3
     */
    SmallPoint3 asNegative3(const SmallPoint3& pt3);

    /**
     * This function returns true if the point on the board is a null piece. Note,
     * this does not bounds check. Out of bounds points produce undefined behavior.
     * The function will deal with negative to positive orientation conversion.
     * @param board a board to evaluate
     * @param pt3 a SmallPoint3
     * @param o the orientation to interpret the board from
     * @return true if index is a null piece
     */
    bool isNullAt(const Board& board, const SmallPoint3& pt3, 
            const Orientation& o = Orientation::None);
    /**
     * This function will set the board to a null piece at the given point. Note,
     * this does not bounds check. Out of bounds points produce undefined behavior.
     * The function will deal with negative to positive orientation conversion.
     * @param board a board to evaluate
     * @param pt3 a SmallPoint3
     * @param o the orientation to interpret the board from
     */
    void nullifyAt(Board& board, const SmallPoint3& pt3, const Orientation& o);
    /**
     * This function will return the lowest available tier at the given pt2. Note,
     * the pt2.x will correspond to board's x-coordinate, and pt2.y will correspond
     * to the board's z-coordinate.
     * The function will deal with negative to positive orientation conversion.
     * @param board a board to evaluate
     * @param pt2 x,y pair to evaluate
     * @param o the orientation to interpret the board from
     * @return index of lowest available tier, if no tier is available returns NO_TIERS_FREE
     * @see NO_TIERS_FREE
     */
    uint8_t availableTierAt(const Board& board, const SmallPoint2& pt2, 
            const Orientation& o = Orientation::None);
    /**
     * This function will return the lowest available tier at the given pt3. Note, the pt3
     * will 'collapse' to a SmalllPoint2 in this case as the y value of the pt3 is of no 
     * importance in this function.
     * The function will deal with negative to positive orientation conversion.
     * @param board a board to evaluate
     * @param pt3 x,z pair to evaluate
     * @param o the orientation to interpret the board from
     * @return index of lowest available tier, if no tier is available returns NO_TIERS_FREE
     * @see NO_TIERS_FREE
     */
    uint8_t availableTierAt(const Board& board, const SmallPoint3& pt3, 
            const Orientation& o = Orientation::None);
    /**
     * This functions will return true if the board has an available tier at the given pt2.
     * The function will deal with negative to positive orientation conversion.
     * @param board a board to evaluate
     * @param pt2 x,y pair to evaluate
     * @param o the orientation to interpret the board from
     * @return true if the given index has an open tier
     */
    bool hasOpenTierAt(const Board& board, const SmallPoint2& pt3, 
            const Orientation& o = Orientation::None);
    /**
     * This functions will return true if the board has an available tier at the given pt3.
     * The function will deal with negative to positive orientation conversion.
     * @param board a board to evaluate
     * @param pt2 x,z pair to evaluate
     * @param o the orientation to interpret the board from
     * @return true if the given index has an open tier
     */
    bool hasOpenTierAt(const Board& board, const SmallPoint3& pt3, 
            const Orientation& o = Orientation::None);

    /**
     * This function will place the piece on board using the specified point. This function
     * will collapse the piece unto the lowest available tier. If there are no open tiers,
     * this function does nothing.
     * @param board a board to modify
     * @param piece a piece to place
     * @param pt3 point to place piece in
     */
    void placeAt(Board& board, const Piece& piece, SmallPoint3 pt3);

    /**
     * This function will convert a pt2 and a move unto an index on the board.
     * The function will deal with negative to positive orientation conversion.
     * @param pt2 the starting point
     * @param move the vector to merge with pt2
     * @param o the current orientation of pt2
     * @return the result of applying move to pt2
     */
    SmallPoint2 genIndex2(SmallPoint2 pt2, const Move& move, 
            const Orientation& o = Orientation::None);

    /**
     * This function will convert a pt3 and a move unto an index on the board. The
     * pt3 will be 'collapsed' as the y-value of pt3 is of no importance to the function.
     * The function will deal with negative to positive orientation conversion.
     * @param pt3 the starting point
     * @param move the vector to merge with pt2
     * @param o the current orientation of pt3
     * @return the result of applying move to pt3
     */
    SmallPoint2 genIndex2(const SmallPoint3& pt3, const Move& move, 
            const Orientation& o = Orientation::None);
   
    /**
     * This function will generate a board state on the given set of indices using the filter
     * function.
     * @param board a board to evaluate
     * @param indices a set of indices to filter
     * @param filter a filter function 
     * @return the BoardState after applying the filter function
     */
    BoardState genBoardState(const Board& board, const Indices3& indices, StateFilter filter);

    /**
     * This method will evaluate if the given piece can be dropped('placed') at the given
     * pt3 using the given orientation.
     * @param board a game board
     * @param piece the piece
     * @param pt3 the desired pt3 to place the piece in
     * @param o the orientation in which to evaluate the piece
     * @return true if piece can be dropped on the specified pt3
     */
    bool validPlacementDrop(const Board& board, const Piece& piece, const SmallPoint3& pt3,
            const Orientation o = Orientation::None);
}

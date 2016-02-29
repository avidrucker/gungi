Changelog
=========

02/27/2016
----------
1.  Implemented Shared Pointer for _gameBoard on Player class and for _currentPlayer on Game class.
2.  Made _color and _orientation const for Player class.
3.  Made RULESET.md file (contains rules from Stickpage Forum)
4.  Added PieceFilter and TierFilter alias in Protocol.hpp ~Line 40
5.  Implemented towerMeets function in Protocol.hpp ~Line 600
6.  Added DROP_STACKABLE_PIECES constant in Protocol.hpp ~Line 74
7.  Implemented dropStackable() method for Piece class in Protocol.hpp ~Line 245
8.  Implemented validRunningDrop() function in Protocol.hpp ~Line 730
8.  Added Indices2 alias in Protocol.hpp ~Line 40
10. Moved genIndex2() to genIndices2() in Protocol.hpp ~Line 680

02/29/2016
----------
11. Made Move* _next a unique_ptr.
12. Removed genCatapultMoveSet & genFortressMoveSet functions from Protocol.hpp
13. Implemented genFortressRangeSet function in Prototol.hpp ~Line 450 & Protocol.cpp ~Line 680
14. Implemented genCatapultRangeSet function in Protocol.hpp ~Line 453 & Protocol.cpp ~Line 700
15. Moved genIndices2 to genIndex2Of function in Protocol.hpp ~Line 665 & Protocol.cpp ~Line 880
16. Implemented validRunningShift function in Protocol.hpp ~Line 720 & Protocol.cpp ~Line 1005
17. Implemented genInfluenceSource() function in Protocol.hpp ~Line 680 & Protocol.cpp ~Line 970

#pragma once

//#include <string>
#include <array>

namespace Gungi
{
    enum class FrontPiece : uint8_t
    { None, Commander, Captain, Samurai, Ninja,  Catapult, 
        Fortress, HiddenDragon , Prodigy, Archer, Soldier };

    enum class BackPiece : uint8_t
    { None, Pistol, Pike, Jounin, Lance, DragonKing,
        Phoenix, Arrow, Gold, Silver, Bronze };
     
    };

    constexpr uint8_t BOARD_SIZE = 9;
    constexpr uint8_t NUM_FRONT_PIECES = 10;
    constexpr uint8_t NUM_BACK_PIECES = 10; 

    constexpr std::array<const char*, NUM_FRONT_PIECES> TIER_ONE_FRONT_MOVES = 
    {
    "NW:+1,N:+1,NE:+1,E:+1,SE:+1,S:+1,SW:+1,W:+1", //  Commander
    "NW:+1,N:+1,NE:+1,E:+0,SE:+1,S:+0,SW:+1,W:+1", //  Captain
    " ", //  Samurai
    "", //  Ninja
    "", //  Catapult
    "", //  Fortress
    "", //  Hidden Dragon
    "", //  Prodigy
    "", //  Archer
    ""  //  Soldier
    };

    constexpr std::array<const char*, NUM_FRONT_PIECES> TIER_TWO_FRONT_MOVES =
    {
    "NW:+1,N:+1,NE:+1,E:+1,SE:+1,S:+1,SW:+1,W:+1", //  Commander
    "NW:+1,N:+1,NE:+1,E:+0,SE:+1,S:+1,SW:+1,W:+1", //  Captain
    "", //  Samurai
    "", //  Ninja
    "", //  Catapult
    "", //  Fortress
    "", //  Hidden Dragon
    "", //  Prodigy
    "", //  Archer
    ""  //  Soldier
    };

    constexpr std::array<const char*, NUM_FRONT_PIECES> TIER_THREE_FRONT_MOVES =
    {
    "NW:+1,N:+1,NE:+1,E:+1,SE:+1,S:+1,SW:+1,W:+1", //  Commander
    "", //  Captain
    "", //  Samurai
    "", //  Ninja
    "", //  Catapult
    "", //  Fortress
    "", //  Hidden Dragon
    "", //  Prodigy
    "", //  Archer
    ""  //  Soldier
    };

    constexpr std::array<const char*, NUM_BACK_PIECES> TIER_ONE_BACK_MOVES =
    {
    "", //  Pistol
    "", //  Pike
    "", //  Lance
    "", //  Lance
    "", //  Dragon King
    "", //  Phoenix
    "", //  Arrow
    "", //  Gold
    "", //  Silver
    ""  //  Bronze
    };

    constexpr std::array<const char*, NUM_BACK_PIECES> TIER_TWO_BACK_MOVES =
    {
    "", //  Pistol
    "", //  Pike
    "", //  Lance
    "", //  Lance
    "", //  Dragon King
    "", //  Phoenix
    "", //  Arrow
    "", //  Gold
    "", //  Silver
    ""  //  Bronze
    };

    constexpr std::array<const char*, NUM_BACK_PIECES> TIER_THREE_BACK_MOVES =
    {
    "", //  Pistol
    "", //  Pike
    "", //  Lance
    "", //  Lance
    "", //  Dragon King
    "", //  Phoenix
    "", //  Arrow
    "", //  Gold
    "", //  Silver
    ""  //  Bronze
    };
}

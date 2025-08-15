#ifndef STORGEPATHS_HPP
#define STORGEPATHS_HPP
#include "main.hpp"

const int MAX_HEALTH=100;
const int FIRST_MONEY=550;

namespace TexturePaths {
    namespace MAP{
        const string MAP1_ARS="../maps/1.txt";
    }

    namespace MUSIC{
        const string BACKGROUND_MUSIC = "assets/Gole-Yakh-Demo.ogg";
    }

    namespace UI {
        const string HEARTH_ICON="assets/sprites/toppanel/hearth_icon.png";
        const string COIN_ICON="assets/sprites/toppanel/coin.png";

    }
    namespace BUTTONS{
        const string NORMAL_TOWER="assets/sprites/Tower_Button/normal.jpg";
        const string ICE_TOWER="assets/sprites/Tower_Button/ice.jpg";
        const string BOMB_TOWER="assets/sprites/Tower_Button/bomb.jpg";
    }
    namespace BACKGROUND {
        const string MainMenu_background_ARS = "assets/sprites/main_menu/main_menu_pic.png";
        const string MAINMENU_BACKGROUND="MainMenu_background";
    }
    const string GAME_OVER_PIC = "assets/sprites/GameOver/game_over.png";
}

namespace FONTS{
    const string Arial="assets/fonts/arial.ttf";
    const string PressStart2P="assets/fonts/PressStart2P-Regular.ttf";
}

namespace BALLON {

    const string NORMAL_BALLON_PIC = "assets/sprites/normal.png";
    const string PREGNANT_BALLON_PIC = "assets/sprites/bardar.png";

    const string BALLON_DYE_SCENE = "assets/sprites/extra_sprite/balloon/base/200w(1).gif";
    const string PREGNANT = "Pregnant";
    const string ORDINARY = "Normal";
}

namespace TOWER {
    const string NORMAL_SHOOTER_ARS="assets/sprites/normal_shooter.png";
    const string ICE_SHOOTER_ARS="assets/sprites/ice_shooter.png";
    const string BOMB_SHOOTER_ARS="assets/sprites/cannon.png";

    const string NORMAL_TOWER = "normal_tower";
    const string ICE_TOWER = "ice_tower";
    const string BOMB_TOWER = "bomb_tower";
    const string BOMB = "bomb";
    const string ICEY = "icey";

    const int NORMAL_TOWER_PRICE=100;
    const int ICE_TOWER_PRICE=200;
    const int BOMB_TOWER_PRICE=300;
    const int NORMAL_TOWER_RANGE = 2;
    const int ICE_TOWER_RANGE = 2;
    const int BOMB_TOWER_RANGE = 2;
    const int NORMAL_TOWER_DELAY = 400;
    const int ICE_TOWER_DELAY = 700;
    const int BOMB_TOWER_DELAY = 500;

    const double BETWEEN_BOLLONS_RANGE = 20;

    const vector<string> DEFAULT_TEXTS={"Name:","Type:","Price:"};
    const vector<string> NORMAL_TOWER_TEXTS={"Normal","Attacker",to_string(NORMAL_TOWER_PRICE)};
    const vector<string> ICE_TOWER_TEXTS={"Ice","Suporter",to_string(ICE_TOWER_PRICE)};
    const vector<string> BOMB_TOWER_TEXTS={"Bomb","Attacker",to_string(BOMB_TOWER_PRICE)};
}

namespace INIT_POS{
    const int X_POS_START_TEXT=850;
    const int Y_POS_START_TEXT=400;
    const int X_POS_EXIT_TEXT=880;
    const int Y_POS_EXIT_TEXT=700;
    const int X_POS_NORMAL_TOWER_BUTTON=1387;
    const int Y_POS_NORMAL_TOWER_BUTTON=254;
    const int X_POS_ICE_TOWER_BUTTON=1541;
    const int Y_POS_ICE_TOWER_BUTTON=254;
    const int X_POS_BOMB_TOWER_BUTTON=1695;
    const int Y_POS_BOMB_TOWER_BUTTON=254;
    const int X_POS_TOWER_MENUS=1392;
    const int Y_POS_TOWER_MENUS=407;
    const int X_POS_DEF_TEXT=1400;
    const int Y_POS_DEF_TEXT=440;
    const int Y_CHANGE_TEXT=70;
    const int X_POS_NAME_TEXT=1550;
    const int X_POS_TOWER_TEXT_CHANGER=40;          
    const int X_POS_TOWER_SHOWER=1395;
    const int Y_POS_TOWER_SHOWER=630;
    const int X_POS_COIN=1341;
    const int Y_POS_COIN=0;
    const int X_POS_HEALTH_ICON=50;
    const int Y_POS_HEALTH_ICON=50;
}

namespace MAP_BACKGROUND1{
    const string ONLY_EARTH="assets/sprites/extra_sprite/tiles/00.png";
    const string ONLY_GRASS="assets/sprites/extra_sprite/tiles/PineTools.com_files/row-2-column-2.png";
    const string UP_GRASS="assets/sprites/extra_sprite/tiles/--.png";
    const string DOWN_GRASS="assets/sprites/extra_sprite/tiles/__.png";
    const string LEFT_GRASS="assets/sprites/extra_sprite/tiles/[.png";
    const string RIGHT_GRASS="assets/sprites/extra_sprite/tiles/].png";
    const string UP_RIGHT_GRASS="assets/sprites/extra_sprite/tiles/i2.png";
    const string UP_LEFT_GRASS="assets/sprites/extra_sprite/tiles/i1.png";
    const string DOWN_LEFT_GRASS="assets/sprites/extra_sprite/tiles/i3.png";
    const string DOWN_RIGHT_GRASS="assets/sprites/extra_sprite/tiles/i4.png";
    const string CORSS_UP_LEFT="assets/sprites/extra_sprite/tiles/o4.png";
    const string CORSS_UP_RIGHT="assets/sprites/extra_sprite/tiles/o3.png";
    const string CORSS_DOWN_LEFT="assets/sprites/extra_sprite/tiles/o2.png";
    const string CORSS_DOWN_RIGHT="assets/sprites/extra_sprite/tiles/o1.png";
} 

#endif
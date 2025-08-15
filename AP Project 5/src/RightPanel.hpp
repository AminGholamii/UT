#ifndef RIGHTPANEL_HPP
#define RIGHTPANEL_HPP

#include "main.hpp"
#include "StoragePaths.hpp"
#include "Towers.hpp"
#include "toppanel.hpp"
enum state{
    IN_GAME,
    PAUSE_,
    MAIN_MENU,
    VICTORY,
    LOSE,
    EXIT
};

enum ButtonHover
{
    NO_ONE,
    NORMAL,
    ICE,
    BOMB
};

class TowerButton{
public:
    virtual void render(RenderWindow &window) = 0;
};

class RightPanel{
public:
    RightPanel();
    void initRightPanel(RenderWindow &window,shared_ptr<Money> cash_ptr);
    void createButtons();
    void handleEvents(RenderWindow& window,shared_ptr<tower> management);
    void text_loader(vector<string> input,bool def,RenderWindow& window);
    void render(RenderWindow &window);
    void valid_location_writer(tuple<float,float,vector<tuple<int,int,bool>>> valid_locations_){
        valid_locations=valid_locations_;
    }
private:
    Font PressStart2P;
    Texture normal_tower_texture;
    Texture ice_tower_texture;
    Texture bomb_tower_texture;
    ButtonHover current_button_hover;
    ButtonHover current_button_selection;
    vector<shared_ptr<TowerButton>> buttons;
    RectangleShape rightRect;
    shared_ptr<tower> tower_management;
    shared_ptr<Money> cash_ptr;
    tuple<float,float,vector<tuple<int,int,bool>>> valid_locations;
};

class NormalTowerButton : public TowerButton{
public:
    NormalTowerButton();
    void render(RenderWindow &window) override{
        window.draw(normal_tower_button_sprite);
    };

    FloatRect getGlobalBounds() const{
        return normal_tower_button_sprite.getGlobalBounds();
    }

private:
    Texture normal_tower_button_texture;
    Sprite normal_tower_button_sprite;
};

class IceTowerButton : public TowerButton{
public:
    IceTowerButton();
    void render(RenderWindow &window) override{
        window.draw(ice_tower_button_sprite);
    };
        FloatRect getGlobalBounds() const{
        return ice_tower_button_sprite.getGlobalBounds();
    }

private:
    Texture ice_tower_button_texture;
    Sprite ice_tower_button_sprite;
};

class BombTowerButton : public TowerButton{
public:
    BombTowerButton();
    void render(RenderWindow &window) override{
        window.draw(bomb_tower_button_sprite);
    };
    FloatRect getGlobalBounds() const{
        return bomb_tower_button_sprite.getGlobalBounds();
    }

private:
    Texture bomb_tower_button_texture;
    Sprite bomb_tower_button_sprite;
};


#endif
#ifndef TOPPANEL_HPP
#define TOPPANEL_HPP

#include "main.hpp"
#include "StoragePaths.hpp"
#include "ReadInputFile.hpp"

class HealthBar{
public:
    HealthBar();
    void health_changer(int changed);
    void render(RenderWindow &window);
    int getHealth() { return current_health; }
    void reset();
private:
    int current_health=100;
    Texture health_texture;
    Sprite health_sprite;
    RectangleShape healthBarBack;
    RectangleShape healthBar;
};

class Money{
public:
    Money();
    void render(RenderWindow &window);
    void update();
    bool can_afford(int money_came);
private:
    void money_changer(int n){
    money-=n;}
    Clock moneyTimer;
    Font font;
    Text money_text;
    int money=FIRST_MONEY;
    Texture coin_texture;
    Sprite coin_sprite;
};

class TopPanel{
public:
    TopPanel();
    void render (RenderWindow &window);
    void update (RenderWindow &window);
    void handle_event();
    shared_ptr<Money> money_pointer_given(){
        return money;
    }
    shared_ptr<HealthBar> getHealthBar() { return healthbar; }
private:
    shared_ptr<Money> money;
    shared_ptr<HealthBar> healthbar;
    RectangleShape top_panel;
};
#endif

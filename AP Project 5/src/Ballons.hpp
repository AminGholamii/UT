#ifndef BALLON_HPP
#define BALLON_HPP

#include "main.hpp"
#include "StoragePaths.hpp"
#include "toppanel.hpp"

const int FREEZE_TIME = 2;
const int velocity = 5;

class ballon{
public:
    float getX(){ return x_; }
    float getY(){ return y_; }
    void move();
    void freeze();
    void showMove(RenderWindow& window);
    void takeBullet();
    bool isIcey() { return is_icey; }
    void setCoordinate(vector<pair<float, float> > movement_rule);
    vector<pair<float, float> > getCoordinate();
    bool isActive() { return active; }
    void setHealthBar(shared_ptr<HealthBar> hb) { healthbar = hb; }
    int get_wined_balls(){return win_ballons;}
    virtual void draw(RenderWindow& window)=0;
    virtual void dye() =0;

private :
    int win_ballons=0;
protected:
    float x_;
    float y_;
    int current_index = 0;
    bool active = true;
    string ballon_type_;
    bool is_icey = false;
    Clock freeze_clock;
    vector<pair<float, float> > coordinate_change;
    Texture ballon_texture;
    Sprite ballon_sprite;
    shared_ptr<HealthBar> healthbar = nullptr;
};


class ordinary_ballon : public ballon {
public:
    ordinary_ballon(float spawn_x, float spawn_y);
    void showDye(RenderWindow& window);
    void draw(RenderWindow& window);
    void dye();

};

class pregnant_ballon : public ballon {
public:
    pregnant_ballon(float spawn_x, float spawn_y);
    void draw(RenderWindow& window);
    void dye();
};


#endif
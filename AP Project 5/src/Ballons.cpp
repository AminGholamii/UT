#include "Ballons.hpp"

void ballon::setCoordinate(vector<pair<float, float> > movement_rule){
    
    coordinate_change = movement_rule;
}

vector<pair<float, float> > ballon::getCoordinate(){

    return coordinate_change;
}

void ballon::takeBullet(){
    this->dye();
}

void ballon::move() {

    if (is_icey){
        if (freeze_clock.getElapsedTime() > seconds(FREEZE_TIME)) 
            is_icey = false;

        else return;
    }

    if (current_index >= coordinate_change.size()-1 ){

        x_ = coordinate_change.back().first;
        y_ = coordinate_change.back().second;
        active = false;
        win_ballons++;
        if (healthbar) {
            healthbar->health_changer(-10);
        }
        return;
    }

    auto current = coordinate_change[current_index];
    auto next = coordinate_change[current_index + 1];
    bool moving_vertically = current.first == next.first;
    if (moving_vertically) {
        float targetY = next.second;
        float distance = fabs(targetY - y_);

        if (distance <= velocity + 0.01f) {
            y_ = targetY;
            current_index++;
        } 
        else {
            y_ += (targetY > y_) ? velocity : -velocity;
        }
    } 
    else {
        float targetX = next.first;
        float distance = fabs(targetX - x_);

        if (distance <= velocity + 0.01f) {
            x_ = targetX;
            current_index++;
        } 
        else {
            x_ += (targetX > x_) ? velocity : -velocity;
        }
    }
}

void ballon::showMove(RenderWindow& window){

    if (!active) 
        return;

    move();
    draw(window);
}

void ballon::freeze(){

    is_icey = true;
    freeze_clock.restart();
}

void ordinary_ballon::draw(RenderWindow& window){

    Sprite ballon_sprite(ballon_texture);
    ballon_sprite.setScale(0.25f, 0.25f);
    ballon_sprite.setPosition(x_, y_);
    window.draw(ballon_sprite);
}

ordinary_ballon::ordinary_ballon(float spawn_x, float spawn_y){
    x_ = spawn_x;
    y_ = spawn_y;
    ballon_type_ = BALLON::ORDINARY;
    is_icey = false;
    ballon_texture.loadFromFile(BALLON::NORMAL_BALLON_PIC);
}

void pregnant_ballon::draw(RenderWindow& window){

    Sprite ballon_sprite(ballon_texture);
    ballon_sprite.setScale(0.25f, 0.25f);
    ballon_sprite.setPosition(x_, y_);
    window.draw(ballon_sprite);
}

pregnant_ballon::pregnant_ballon(float spawn_x, float spawn_y){
    x_ = spawn_x;
    y_ = spawn_y;
    ballon_type_ = BALLON::PREGNANT;
    is_icey = false;
    ballon_texture.loadFromFile(BALLON::PREGNANT_BALLON_PIC);
}


void ordinary_ballon::dye(){
    this->active = false;
}

void pregnant_ballon::dye(){
     this->active = false;
}


#ifndef TOWERS_HPP
#define TOWERS_HPP

#include "main.hpp"
#include "Ballons.hpp"
#include "StoragePaths.hpp"
#include "toppanel.hpp"
class ordinary_tower {
public:
    ordinary_tower(float x, float y, pair<float,float> auto_scale,shared_ptr<Money> cash_ptr_); 
    shared_ptr<ballon> findBallonInRange(vector<shared_ptr<ballon> >& curr_wave);
    void shoot(vector<shared_ptr<ballon> >& curr_wave);
    void draw(RenderWindow &window){
        window.draw(normal_tower_sprite);
        window.draw(circle);
    }
private :
    Clock shot_clock;
    float x_;
    float y_;
    int cost_;
    int damage_range_;  
    string tower_type_;
    pair<float,float> auto_scale_;
    Texture normal_tower_texture;
    Sprite normal_tower_sprite;
    CircleShape circle;
    shared_ptr <Money> cash_ptr;
    float shot_delay_;
};

class icey_tower {
public:
    icey_tower(float x, float y, pair<float,float> auto_scale); 
    shared_ptr<ballon> findBallonInRange(vector<shared_ptr<ballon> >& curr_wave);
    void addFreezed(shared_ptr<ballon> freeze_this) { freezed.push_back(freeze_this); }
    void shoot(vector<shared_ptr<ballon> >& curr_wave);
    void draw(RenderWindow &window){
        window.draw(ice_tower_sprite);
        window.draw(circle);
    }
private :
    float x_;
    float y_;
    int cost_;
    int damage_range_;  
    float shot_delay_;
    vector<shared_ptr<ballon>> freezed;
    string tower_type_;
    pair<float,float> auto_scale_;
    Texture ice_tower_texture;
    Sprite ice_tower_sprite;
    CircleShape circle;
};

class super_tower {
public:
    super_tower(float x, float y, pair<float,float> auto_scale,shared_ptr<Money> cash_ptr_); 
    shared_ptr<ballon> findBallonInRange(vector<shared_ptr<ballon> >& curr_wave);
    void shoot(vector<shared_ptr<ballon> >& curr_wave);
    void draw(RenderWindow &window){
        window.draw(super_tower_sprite);
        window.draw(circle);
        
    }
private :
    Clock shot_clock;
    float x_;
    float y_;
    int cost_;
    int damage_range_;  
    float shot_delay_;
    string tower_type_;
    pair<float,float> auto_scale_;
    Texture super_tower_texture;
    Sprite super_tower_sprite;
    CircleShape circle;
    shared_ptr <Money> cash_ptr;
};

class tower {
public:
    void resetAll();
    void shoot();
    void setWave(vector<shared_ptr<ballon> > wave) { curr_wave = wave; }
    void ordinary_tower_push_backer(shared_ptr<class ordinary_tower> t){
        ordinary_towers.push_back(t);
    }
    void icey_tower_push_backer(shared_ptr<class icey_tower> t){
        icey_towers.push_back(t);   
    }
    void super_tower_push_backer(shared_ptr<class super_tower> t){
        super_towers.push_back(t); 
    }
    void render(RenderWindow &window);
private:
    vector<shared_ptr<ordinary_tower> > ordinary_towers;
    vector<shared_ptr<icey_tower> > icey_towers;
    vector<shared_ptr<super_tower> > super_towers;
    vector<shared_ptr<ballon> > curr_wave;
};


#endif

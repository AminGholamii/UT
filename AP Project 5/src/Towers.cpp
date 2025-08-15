#include "Towers.hpp"


ordinary_tower::ordinary_tower(float x, float y,pair<float,float> auto_scale,shared_ptr<Money> cash_ptr_){
    cash_ptr=cash_ptr_;
    x_ = x;
    y_ = y;
    auto_scale_=auto_scale;
    normal_tower_texture.loadFromFile(TOWER::NORMAL_SHOOTER_ARS);
    normal_tower_sprite.setTexture(normal_tower_texture);
    normal_tower_sprite.setPosition(x_,y_);
    normal_tower_sprite.scale(auto_scale_.first,auto_scale_.second);
    circle.setRadius(auto_scale_.first*normal_tower_texture.getSize().x);
    circle.setPosition(x_ - circle.getRadius()/2, y_ - circle.getRadius()/2+10);
    circle.setFillColor(Color(255, 255, 255, 128));
    cost_ = TOWER::NORMAL_TOWER_PRICE;
    damage_range_ = TOWER::NORMAL_TOWER_RANGE;
    shot_delay_ = TOWER::NORMAL_TOWER_DELAY / 1000.f;
    tower_type_ = TOWER::NORMAL_TOWER; 
}

icey_tower::icey_tower(float x, float y,pair<float,float> auto_scale){
    x_ = x;
    y_ = y;
    auto_scale_=auto_scale;
    ice_tower_texture.loadFromFile(TOWER::ICE_SHOOTER_ARS);
    ice_tower_sprite.setTexture(ice_tower_texture);
    ice_tower_sprite.setPosition(x_,y_);
    ice_tower_sprite.scale(auto_scale_.first,auto_scale_.second);
    circle.setRadius(auto_scale_.first*ice_tower_texture.getSize().x);
    circle.setPosition(x_ - circle.getRadius()/2, y_ - circle.getRadius()/2+5);
    circle.setFillColor(Color(255, 255, 255, 128));
    cost_ = TOWER::ICE_TOWER_PRICE;
    damage_range_ = TOWER::ICE_TOWER_RANGE;
    shot_delay_ = TOWER::ICE_TOWER_DELAY / 1000.f;  
    tower_type_ = TOWER::ICE_TOWER;
}

super_tower::super_tower(float x, float y,pair<float,float> auto_scale,shared_ptr<Money> cash_ptr_){
    cash_ptr=cash_ptr_;
    x_ = x;
    y_ = y;
    auto_scale_=auto_scale;
    super_tower_texture.loadFromFile(TOWER::BOMB_SHOOTER_ARS);
    super_tower_sprite.setTexture(super_tower_texture);
    super_tower_sprite.setPosition(x_,y_);
    super_tower_sprite.scale(auto_scale_.first,auto_scale_.second);
    circle.setRadius(auto_scale_.first*super_tower_texture.getSize().x);
    circle.setPosition(x_ - circle.getRadius()/1.9, y_ - circle.getRadius()/3.5);
    circle.setFillColor(Color(255, 255, 255, 128));
    cost_ = TOWER::BOMB_TOWER_PRICE;
    damage_range_ = TOWER::BOMB_TOWER_RANGE;
    shot_delay_ = TOWER::BOMB_TOWER_DELAY / 1000.f;
    tower_type_ = TOWER::BOMB_TOWER;
}

void tower::render(RenderWindow &window){
    for (auto temp_ordinary_tower:ordinary_towers){
        temp_ordinary_tower->draw(window);
    }
    for (auto temp_ice_tower:icey_towers){
        temp_ice_tower->draw(window);
    }
    for (auto temp_super_tower:super_towers){
        temp_super_tower->draw(window);
    }
}

void tower::shoot(){
    for (auto temp_ordinary_tower:ordinary_towers){
        temp_ordinary_tower->shoot(curr_wave);
    }
    for (auto temp_ice_tower:icey_towers){
        temp_ice_tower->shoot(curr_wave);
    }
    for (auto temp_super_tower:super_towers){
        temp_super_tower->shoot(curr_wave);
    }
}

void tower::resetAll(){
    ordinary_towers.clear();
    icey_towers.clear();
    super_towers.clear();
}

shared_ptr<ballon> ordinary_tower::findBallonInRange(vector<shared_ptr<ballon>>& curr_wave) {
    sf::Vector2f circle_pos = circle.getPosition();
    float radius = circle.getRadius();
    float x_center = circle_pos.x + radius;
    float y_center = circle_pos.y + radius;

    vector<pair<shared_ptr<ballon>, double>> desirables;
    for (auto& ballon_ : curr_wave) {
        double dx = ballon_->getX() - x_center;
        double dy = ballon_->getY() - y_center;
        double distance = sqrt(dx * dx + dy * dy);

        if (distance <= radius) {
            desirables.emplace_back(ballon_, distance);
        }
    }

    if (desirables.empty()) return nullptr;

    sort(desirables.begin(), desirables.end(),
         [](auto& a, auto& b) { return a.second > b.second; });
    auto it=desirables.back().first;
    desirables.pop_back();
    return it;
}


shared_ptr<ballon> icey_tower::findBallonInRange(vector<shared_ptr<ballon>>& curr_wave) {
    sf::Vector2f circle_pos = circle.getPosition(); // top-left corner
    float radius = circle.getRadius();
    float x_center = circle_pos.x + radius;
    float y_center = circle_pos.y + radius;

    vector<pair<shared_ptr<ballon>, double>> desirables;
    for (auto& ballon_ : curr_wave) {
        if (ballon_->isIcey()) continue;

        double dx = ballon_->getX() - x_center;
        double dy = ballon_->getY() - y_center;
        double distance = sqrt(dx * dx + dy * dy);

        if (distance <= radius) {
            desirables.emplace_back(ballon_, distance);
        }
    }

    if (desirables.empty()) return nullptr;

    sort(desirables.begin(), desirables.end(),
         [](auto& a, auto& b) { return a.second > b.second; });
    auto it=desirables.back().first;
    desirables.pop_back();
    return it;
}

shared_ptr<ballon> super_tower::findBallonInRange(vector<shared_ptr<ballon>>& curr_wave) {
    sf::Vector2f circle_pos = circle.getPosition(); // top-left corner
    float radius = circle.getRadius();
    float x_center = circle_pos.x + radius;
    float y_center = circle_pos.y + radius;

    map<shared_ptr<ballon>, int> desirables;

    for (auto& ballon_ : curr_wave) {
        double dx = ballon_->getX() - x_center;
        double dy = ballon_->getY() - y_center;
        double distance = sqrt(dx * dx + dy * dy);

        if (distance <= radius) {
            int neighbor_count = 0;
            for (auto& other : curr_wave) {
                if (other == ballon_) continue;

                double ddx = ballon_->getX() - other->getX();
                double ddy = ballon_->getY() - other->getY();
                double dist_between = sqrt(ddx * ddx + ddy * ddy);

                if (dist_between <= TOWER::BETWEEN_BOLLONS_RANGE) {
                    neighbor_count++;
                }
            }
            desirables[ballon_] = neighbor_count;
        }
    }

    if (desirables.empty()) return nullptr;

    auto best = max_element(
        desirables.begin(), desirables.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

    return best->first;
}


void ordinary_tower::shoot(std::vector<std::shared_ptr<ballon>>& curr_wave) {
    cout << shot_clock.getElapsedTime().asSeconds() <<"         "<<shot_delay_<<endl;
        if (shot_clock.getElapsedTime().asSeconds() < shot_delay_)
            return; 
    
        auto target_ballon = findBallonInRange(curr_wave);
        if (target_ballon != nullptr && shot_clock.getElapsedTime().asSeconds() > shot_delay_) {
            if (cash_ptr->can_afford(10)) {
                cash_ptr->can_afford(-10);
                target_ballon->takeBullet();
                shot_clock.restart();  
            }
        }
    }

void icey_tower::shoot(vector<shared_ptr<ballon> >& curr_wave){

    shared_ptr<ballon> target_ballon = findBallonInRange(curr_wave);
    bool alreadyFreezed = find(freezed.begin(), freezed.end(), target_ballon) != freezed.end();
    if ( target_ballon != nullptr && !alreadyFreezed ){
        target_ballon->freeze();
        freezed.push_back(target_ballon);
    }
}

void super_tower::shoot(vector<shared_ptr<ballon> >& curr_wave){

        //cout << shot_clock.getElapsedTime().asSeconds() <<"         "<<shot_delay_<<endl;
        if (shot_clock.getElapsedTime().asSeconds() < shot_delay_)
            return; 

        auto target_ballon = findBallonInRange(curr_wave);
        if (target_ballon != nullptr) {
            if (cash_ptr->can_afford(10)) {
                cash_ptr->can_afford(-10);
                target_ballon->takeBullet();
                shot_clock.restart();  
            }
        }
    }


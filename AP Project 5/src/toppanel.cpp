#include "toppanel.hpp"

TopPanel::TopPanel(){
    healthbar=make_shared <HealthBar>();
    money=make_shared <Money>();

    top_panel.setPosition(0,0);
    top_panel.setSize(Vector2f(1920, 253));
    top_panel.setFillColor(Color(135, 206, 235));
}

HealthBar::HealthBar(){
    health_texture.loadFromFile(TexturePaths::UI::HEARTH_ICON);
    health_sprite.setTexture(health_texture);
    health_sprite.setPosition(INIT_POS::X_POS_HEALTH_ICON,INIT_POS::Y_POS_HEALTH_ICON);
    health_sprite.scale(0.5f,0.5f);
    healthBarBack.setSize(Vector2f(600, 25));
    healthBarBack.setFillColor(Color(50, 50, 50));
    healthBarBack.setPosition(health_texture.getSize().x/2+ INIT_POS::X_POS_HEALTH_ICON,INIT_POS::Y_POS_HEALTH_ICON+health_texture.getSize().y/4);
    healthBar.setSize(Vector2f(600, 25));
    healthBar.setFillColor(Color::Green);
    healthBar.setPosition(health_texture.getSize().x/2+ INIT_POS::X_POS_HEALTH_ICON,INIT_POS::Y_POS_HEALTH_ICON+health_texture.getSize().y/4);
}

Money::Money(){
    coin_texture.loadFromFile(TexturePaths::UI::COIN_ICON);
    coin_sprite.setTexture(coin_texture);
    coin_sprite.setPosition(INIT_POS::X_POS_COIN,INIT_POS::Y_POS_COIN);
    coin_sprite.scale(0.25f,0.25f);
    readfont(FONTS::PressStart2P,font);
    money_text.setFont(font);
    money_text.setCharacterSize(24);
    money_text.setFillColor(Color::Yellow);
    money_text.setPosition(coin_texture.getSize().x/4+INIT_POS::X_POS_COIN,INIT_POS::Y_POS_COIN+115); 
}

void Money::update(){

    if (moneyTimer.getElapsedTime().asSeconds() > 2.0f) {
        money += 5;
        moneyTimer.restart();
        if (money_text.getFillColor()==Color::Red)
        money_text.setFillColor(Color::Yellow);
    }
    stringstream ss;
    ss << "Money: " << money;
    money_text.setString(ss.str());
}

bool Money::can_afford(int money_came){
    if (money>=money_came){
        money_changer(money_came);
        return true;
    }
    else{
        money_text.setFillColor(Color::Red);
        return false;
    }
}

void TopPanel::render(RenderWindow &window){
    window.draw(top_panel);
    healthbar->render(window);
    money->render(window);
}

void TopPanel::update(RenderWindow &window){
    money->update();      
}

void HealthBar::render(RenderWindow &window){
    window.draw(healthBarBack);
    window.draw(healthBar);
    window.draw(health_sprite);
}

void HealthBar::reset(){
    current_health = MAX_HEALTH;
    healthBar.setSize(Vector2f(600, 25));  // Or whatever the full size is.
    healthBar.setFillColor(Color::Green);
}

void Money::render(RenderWindow &window){
    window.draw(coin_sprite);
    window.draw(money_text);
}
void HealthBar::health_changer(int changed){
    current_health += changed;
    float healthPercent = static_cast<float>(current_health) / MAX_HEALTH;
    healthBar.setSize(Vector2f(600 * healthPercent, 25));
    if (healthPercent > 0.6f)
            healthBar.setFillColor(sf::Color::Green);
        else if (healthPercent > 0.3f)
            healthBar.setFillColor(sf::Color::Yellow);
        else
            healthBar.setFillColor(sf::Color::Red);
}
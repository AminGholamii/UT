#include "RightPanel.hpp"

RightPanel::RightPanel()
{
    PressStart2P.loadFromFile(FONTS::PressStart2P);
    normal_tower_texture.loadFromFile(TOWER::NORMAL_SHOOTER_ARS);
    ice_tower_texture.loadFromFile(TOWER::ICE_SHOOTER_ARS);
    bomb_tower_texture.loadFromFile(TOWER::BOMB_SHOOTER_ARS);
}

NormalTowerButton::NormalTowerButton()
{
    normal_tower_button_texture.loadFromFile(TexturePaths::BUTTONS::NORMAL_TOWER);
    normal_tower_button_sprite.setTexture(normal_tower_button_texture);
    normal_tower_button_sprite.setPosition(INIT_POS::X_POS_NORMAL_TOWER_BUTTON, INIT_POS::Y_POS_NORMAL_TOWER_BUTTON);
    normal_tower_button_sprite.scale(static_cast<float>(INIT_POS::X_POS_BOMB_TOWER_BUTTON - INIT_POS::X_POS_ICE_TOWER_BUTTON) / normal_tower_button_texture.getSize().x, static_cast<float>(INIT_POS::X_POS_BOMB_TOWER_BUTTON - INIT_POS::X_POS_ICE_TOWER_BUTTON) / normal_tower_button_texture.getSize().x);
}

IceTowerButton::IceTowerButton()
{
    ice_tower_button_texture.loadFromFile(TexturePaths::BUTTONS::ICE_TOWER);
    ice_tower_button_sprite.setTexture(ice_tower_button_texture);
    ice_tower_button_sprite.setPosition(INIT_POS::X_POS_ICE_TOWER_BUTTON, INIT_POS::Y_POS_ICE_TOWER_BUTTON);
    ice_tower_button_sprite.scale(static_cast<float>(INIT_POS::X_POS_BOMB_TOWER_BUTTON - INIT_POS::X_POS_ICE_TOWER_BUTTON) / ice_tower_button_texture.getSize().x, static_cast<float>(INIT_POS::X_POS_BOMB_TOWER_BUTTON - INIT_POS::X_POS_ICE_TOWER_BUTTON) / ice_tower_button_texture.getSize().x);
}

BombTowerButton::BombTowerButton()
{
    bomb_tower_button_texture.loadFromFile(TexturePaths::BUTTONS::BOMB_TOWER);
    bomb_tower_button_sprite.setTexture(bomb_tower_button_texture);
    bomb_tower_button_sprite.setPosition(INIT_POS::X_POS_BOMB_TOWER_BUTTON, INIT_POS::Y_POS_BOMB_TOWER_BUTTON);
    bomb_tower_button_sprite.scale(static_cast<float>(INIT_POS::X_POS_BOMB_TOWER_BUTTON - INIT_POS::X_POS_ICE_TOWER_BUTTON) / bomb_tower_button_texture.getSize().x, static_cast<float>(INIT_POS::X_POS_BOMB_TOWER_BUTTON - INIT_POS::X_POS_ICE_TOWER_BUTTON) / bomb_tower_button_texture.getSize().x);
}

void RightPanel::initRightPanel(RenderWindow &window, shared_ptr<Money> cash_ptr_)
{
    cash_ptr = cash_ptr_;
    Vector2u windowSize = window.getSize();
    float panelWidth = windowSize.x * 0.25f; // 25% of window width
    rightRect.setSize(Vector2f(panelWidth, windowSize.y));
    rightRect.setFillColor(Color(210, 180, 140));
    rightRect.setPosition(windowSize.x - panelWidth, 0.f);
}

void RightPanel::createButtons()
{
    buttons.push_back(static_pointer_cast<TowerButton>(make_shared<NormalTowerButton>()));
    buttons.push_back(static_pointer_cast<TowerButton>(make_shared<IceTowerButton>()));
    buttons.push_back(static_pointer_cast<TowerButton>(make_shared<BombTowerButton>()));
}

void RightPanel::handleEvents(RenderWindow &window, shared_ptr<tower> management)
{
    tower_management = management;
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(mousePos);
    current_button_hover = NO_ONE;
    for (auto &button : buttons)
    {
        if (auto normalButton = dynamic_pointer_cast<NormalTowerButton>(button))
            if (normalButton->getGlobalBounds().contains(worldPos))
            {
                current_button_hover = NORMAL;
                break;
            }
        if (auto iceButton = dynamic_pointer_cast<IceTowerButton>(button))
            if (iceButton->getGlobalBounds().contains(worldPos))
            {
                current_button_hover = ICE;
                break;
            }
        if (auto bombButton = dynamic_pointer_cast<BombTowerButton>(button))
        {
            if (bombButton->getGlobalBounds().contains(worldPos))
            {
                current_button_hover = BOMB;
                break;
            }
        }
    }
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        for (auto &button : buttons)
        {
            if (auto normalButton = dynamic_pointer_cast<NormalTowerButton>(button))
                if (normalButton->getGlobalBounds().contains(worldPos))
                {
                    current_button_selection = NORMAL;
                    break;
                }
            if (auto iceButton = dynamic_pointer_cast<IceTowerButton>(button))
                if (iceButton->getGlobalBounds().contains(worldPos))
                {
                    current_button_selection = ICE;
                    break;
                }
            if (auto bombButton = dynamic_pointer_cast<BombTowerButton>(button))
            {
                if (bombButton->getGlobalBounds().contains(worldPos))
                {
                    current_button_selection = BOMB;
                    break;
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        current_button_selection = NO_ONE;
}

void RightPanel::text_loader(vector<string> input, bool def, RenderWindow &window)
{

    int x_;
    if (def)
        x_ = INIT_POS::X_POS_DEF_TEXT;
    else
        x_ = INIT_POS::X_POS_NAME_TEXT;

    int y_ = INIT_POS::Y_POS_DEF_TEXT;
    int counter = 0;
    Text temp;
    for (auto temp_text : input)
    {
        if (def)
        {
            temp.setFont(PressStart2P);
            temp.setString(temp_text);
            temp.setCharacterSize(30);
            temp.setPosition(x_, y_);
            temp.setFillColor(Color::Black);
            window.draw(temp);
        }
        else
        {
            temp.setFont(PressStart2P);
            temp.setString(temp_text);
            temp.setCharacterSize(30);
            temp.setPosition(x_, y_);
            temp.setFillColor(Color::Black);
            window.draw(temp);
            counter++;
        }
        y_ += INIT_POS::Y_CHANGE_TEXT;
        if (counter == 2)
            x_ += INIT_POS::X_POS_TOWER_TEXT_CHANGER;
    }
}

void RightPanel::render(RenderWindow &window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    window.draw(rightRect);
    for (auto &button : buttons)
    {
        button->render(window);
    }
    if (current_button_hover != NO_ONE)
    {
        RectangleShape tower_menu;
        Sprite temp_sprite;
        temp_sprite.setPosition(INIT_POS::X_POS_TOWER_SHOWER, INIT_POS::Y_POS_TOWER_SHOWER);
        tower_menu.setPosition(INIT_POS::X_POS_TOWER_MENUS, INIT_POS::Y_POS_TOWER_MENUS);
        tower_menu.setSize(Vector2f(window.getSize().x - INIT_POS::X_POS_TOWER_MENUS, window.getSize().y - INIT_POS::Y_POS_TOWER_MENUS));
        if (current_button_hover == NORMAL)
        {
            tower_menu.setFillColor(Color(255, 225, 122));
            window.draw(tower_menu);
            temp_sprite.setTexture(normal_tower_texture);
            temp_sprite.setScale(0.7f, 0.7f);
            window.draw(temp_sprite);
            text_loader(TOWER::DEFAULT_TEXTS, true, window);
            text_loader(TOWER::NORMAL_TOWER_TEXTS, false, window);
        }
        else if (current_button_hover == ICE)
        {
            tower_menu.setFillColor(Color(163, 235, 223));
            window.draw(tower_menu);
            temp_sprite.setTexture(ice_tower_texture);
            temp_sprite.setScale(0.77f, 0.74f);
            window.draw(temp_sprite);
            text_loader(TOWER::DEFAULT_TEXTS, true, window);
            text_loader(TOWER::ICE_TOWER_TEXTS, false, window);
        }
        else
        {
            temp_sprite.setPosition(INIT_POS::X_POS_TOWER_MENUS + 150, INIT_POS::Y_POS_TOWER_MENUS + 150);
            tower_menu.setFillColor(Color(222, 195, 142));
            window.draw(tower_menu);
            temp_sprite.setTexture(bomb_tower_texture);
            temp_sprite.setScale(2.f, 2.f);
            window.draw(temp_sprite);
            text_loader(TOWER::DEFAULT_TEXTS, true, window);
            text_loader(TOWER::BOMB_TOWER_TEXTS, false, window);
        }
    }
    if (current_button_selection != NO_ONE)
    {
        Sprite temp_sprite;
        if (current_button_selection == NORMAL)
        {
            for (auto temp : get<2>(valid_locations))
            {
                if (mousePos.x > get<0>(temp) && mousePos.x < get<0>(temp) + get<0>(valid_locations) * 1.4 && mousePos.y > get<1>(temp) && mousePos.y < get<1>(temp) + get<1>(valid_locations) * 1.4 && !get<2>(temp))
                {
                    float x = get<0>(temp) - get<0>(valid_locations) / normal_tower_texture.getSize().x;
                    float y = get<1>(temp) - get<1>(valid_locations) / normal_tower_texture.getSize().y;
                    pair<float, float> auto_scale = {(get<0>(valid_locations) / normal_tower_texture.getSize().x) * 1.8, (get<1>(valid_locations) / normal_tower_texture.getSize().y) * 1.4};
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        if (cash_ptr->can_afford(TOWER::NORMAL_TOWER_PRICE))
                        {
                            get<2>(temp)=true;
                            auto t = make_shared<ordinary_tower>(x, y, auto_scale,cash_ptr);
                            tower_management->ordinary_tower_push_backer(t);
                        }
                        current_button_selection = NO_ONE;
                    }
                    temp_sprite.setTexture(normal_tower_texture);
                    temp_sprite.setPosition(x, y);
                    temp_sprite.setScale(auto_scale.first, auto_scale.second);
                    window.draw(temp_sprite);
                    return;
                }
            }
            temp_sprite.setTexture(normal_tower_texture);
            temp_sprite.setPosition(mousePos.x - (get<0>(valid_locations) / normal_tower_texture.getSize().x) * 600, mousePos.y - get<1>(valid_locations) / normal_tower_texture.getSize().y * 600);
            temp_sprite.setScale(static_cast<float>(get<0>(valid_locations) / normal_tower_texture.getSize().x) * 1.8, static_cast<float>(get<1>(valid_locations) / normal_tower_texture.getSize().y) * 1.8);
            window.draw(temp_sprite);
        }
        else if (current_button_selection == ICE)
        {
            for (auto temp : get<2>(valid_locations))
            {
                float x = get<0>(temp) - get<0>(valid_locations) / ice_tower_texture.getSize().x;
                float y = get<1>(temp) - get<1>(valid_locations) / ice_tower_texture.getSize().y;
                pair<float, float> auto_scale = {(get<0>(valid_locations) / ice_tower_texture.getSize().x) * 1.9, (get<1>(valid_locations) / ice_tower_texture.getSize().y) * 1.4};
                if (mousePos.x > get<0>(temp) && mousePos.x < get<0>(temp) + get<0>(valid_locations) * 1.4 && mousePos.y > get<1>(temp) && mousePos.y < get<1>(temp) + get<1>(valid_locations) * 1.4 && !get<2>(temp))
                {
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        if (cash_ptr->can_afford(TOWER::ICE_TOWER_PRICE)){
                            get<2>(temp)=true;
                            auto t = make_shared<icey_tower>(x, y, auto_scale);
                            tower_management->icey_tower_push_backer(t);
                        }
                        current_button_selection = NO_ONE;
                    }
                    temp_sprite.setTexture(ice_tower_texture);
                    temp_sprite.setPosition(x, y);
                    temp_sprite.setScale(auto_scale.first,auto_scale.second);
                    window.draw(temp_sprite);
                    return;
                }
            }
            temp_sprite.setTexture(ice_tower_texture);
            temp_sprite.setPosition(mousePos.x - (get<0>(valid_locations) / ice_tower_texture.getSize().x) * 600, mousePos.y - get<1>(valid_locations) / ice_tower_texture.getSize().y * 350);
            temp_sprite.setScale(static_cast<float>(get<0>(valid_locations) / ice_tower_texture.getSize().x)*1.9, static_cast<float>(get<1>(valid_locations) / ice_tower_texture.getSize().y)*1.4);
            window.draw(temp_sprite);
        }
        else if (current_button_selection == BOMB)
        {
            for (auto temp : get<2>(valid_locations))
            {
                float x = get<0>(temp) + get<0>(valid_locations) / bomb_tower_texture.getSize().x*10.0;
                float y = get<1>(temp) - get<1>(valid_locations) / bomb_tower_texture.getSize().y*50.5;
                pair<float, float> auto_scale = {(get<0>(valid_locations) / bomb_tower_texture.getSize().x)*1.9, (get<1>(valid_locations) / bomb_tower_texture.getSize().y*1.5)};
                if (mousePos.x > get<0>(temp) && mousePos.x < get<0>(temp) + get<0>(valid_locations) && mousePos.y > get<1>(temp) && mousePos.y < get<1>(temp) + get<1>(valid_locations) && !get<2>(temp))
                {
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        if (cash_ptr->can_afford(TOWER::BOMB_TOWER_PRICE))
                        {
                                get<2>(temp)=true;
                                auto t = make_shared<super_tower>(x, y, auto_scale,cash_ptr);
                                tower_management->super_tower_push_backer(t);
                        }
                        current_button_selection = NO_ONE;
                    }
                    temp_sprite.setTexture(bomb_tower_texture);
                    temp_sprite.setPosition(x,y);
                    temp_sprite.setScale(auto_scale.first,auto_scale.second);
                    window.draw(temp_sprite);
                    return;
                }
            }

            temp_sprite.setTexture(bomb_tower_texture);
            temp_sprite.setPosition(mousePos.x - (get<0>(valid_locations) / bomb_tower_texture.getSize().x) * 62.5, mousePos.y - get<1>(valid_locations) / bomb_tower_texture.getSize().y * 62.5);
            temp_sprite.setScale(static_cast<float>(get<0>(valid_locations) / bomb_tower_texture.getSize().x), static_cast<float>(get<1>(valid_locations) / bomb_tower_texture.getSize().y));
            window.draw(temp_sprite);
        }
    }
}

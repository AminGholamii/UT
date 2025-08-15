#include "GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(int width,int height){
    window.create(VideoMode(width,height),"FOZOLI?");
    window.setFramerateLimit(refresh_rate);
    current_state = MAIN_MENU;
    right_panel=make_shared<RightPanel>();
    top_panel=make_shared<TopPanel>();
    tower_management=make_shared<tower>();
    game_over.load();
    background_music.openFromFile(TexturePaths::MUSIC::BACKGROUND_MUSIC);
}

MainMenu::MainMenu(){
    readtexture(TexturePaths::BACKGROUND::MainMenu_background_ARS,background_texture,background_sprite);
    readfont(FONTS::Arial,arial_font);
    start_text.setFont(arial_font);
    exit_text.setFont(arial_font);
    start_text.setString("START");
    start_text.setCharacterSize(40);
    start_text.setPosition(INIT_POS::X_POS_START_TEXT,INIT_POS::Y_POS_START_TEXT);
    start_text.setFillColor(Color::White);
    start_text.setOutlineColor(Color::Black);
    start_text.setOutlineThickness(10);
    exit_text.setString("EXIT");
    exit_text.setCharacterSize(40);
    exit_text.setPosition(INIT_POS::X_POS_EXIT_TEXT,INIT_POS::Y_POS_EXIT_TEXT);
    exit_text.setFillColor(Color::White);
    exit_text.setOutlineColor(Color::Black);
    exit_text.setOutlineThickness(10);
}

pair<float,float> GameMenu::auto_scale_founder(Texture temp_texture){
    int rows = tiles_places.size();
    int columns = tiles_places[0].size();
    float mapSizeX = map_texture.getSize().x;
    float mapSizeY = map_texture.getSize().y;
    float blocksizex=1390/columns*0.677777;
    float blocksizey=750/rows*0.87777;
    return {blocksizex/mapSizeX,blocksizey/mapSizeY};
}

void GameMenu::draw(RenderWindow& window, string file_path, int x, int y,bool twox){
    map_texture.loadFromFile(file_path);
    Sprite map_sprite(map_texture);
    map_sprite.setPosition(x, y);    
    int auto_scalex=auto_scale_founder(map_texture).first;
    int auto_scaley=auto_scale_founder(map_texture).second;
    if (twox){
            if (!first_draw)
        {
            get<0>(valid_locations)=auto_scalex*map_texture.getSize().x;
            get<1>(valid_locations)=auto_scaley*map_texture.getSize().y;
            get<2>(valid_locations).push_back({x,y,0});
        }
        map_sprite.scale(auto_scalex*2,auto_scaley*2);}
    else
        map_sprite.scale(auto_scalex,auto_scaley);
        
    window.draw(map_sprite);
}

void GameMenu::renderMap(RenderWindow& window) {
    int rows = tiles_places.size();
    int columns = tiles_places[0].size();
    float effective_width  = window.getSize().x * 0.75f;
    float effective_height = window.getSize().y * 0.75f;
    float cell_width  = effective_width / columns;
    float cell_height = effective_height / rows;
    float start_x = 0;
    float start_y = window.getSize().y * 0.25f;
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < columns; j++) {
            float cell_x = start_x + j * cell_width;
            float cell_y = start_y + i * cell_height;
            auto cell_tuple = tiles_places[i][j];
            if (get<0>(cell_tuple) == "") 
                draw(window, get<1>(cell_tuple), cell_x, cell_y,true);
            else {
                
                draw(window, get<0>(cell_tuple), cell_x, cell_y,false);
                draw(window, get<1>(cell_tuple), cell_x + cell_width / 2, cell_y,false);
                draw(window, get<2>(cell_tuple), cell_x, cell_y + cell_height / 2,false);
                draw(window, get<3>(cell_tuple), cell_x + cell_width / 2, cell_y + cell_height / 2,false);}
    }
    first_draw=true;
}

void GameMenu::renderGameMenu(RenderWindow& window){
  /*  Vector2u windowSize = window.getSize();
    RectangleShape topRect(Vector2f(static_cast<float>(windowSize.x), windowSize.y * 0.25f));
    RectangleShape rightRect(Vector2f(windowSize.x * 0.25f, static_cast<float>(windowSize.y)));
    topRect.setFillColor(Color(255,239, 213));
    rightRect.setFillColor(Color(210, 180, 140));
    topRect.setPosition(0.f, 0.f);
    rightRect.setPosition(static_cast<float>(windowSize.x) - rightRect.getSize().x, 0.f);
    window.draw(rightRect);
    window.draw(topRect);
    window.display();*/
}

void GameMenu::createWave(){

    if (waves.size() <= level) {
        waves.resize(level + 1);
    }
    move_index = 0;

    int diff = ATTACKING_PLAN[level].enemyLaunchGapMs.second - ATTACKING_PLAN[level].enemyLaunchGapMs.first;
    in_wave_spawn_delay_ = rand()%diff + ATTACKING_PLAN[level].enemyLaunchGapMs.first;
    Vector2f start = {coordinate_change[0].first, coordinate_change[0].second};
    for ( auto [ballon_type, count] : ATTACKING_PLAN[level].enemiesCount ){
        
        if ( ballon_type == BALLON::ORDINARY ){

            for ( int i=1 ; i<=count ; i++ ){
                shared_ptr<ordinary_ballon> new_ballon(new ordinary_ballon(start.x, start.y));
                new_ballon->setHealthBar(health_bar);
                new_ballon->setCoordinate(coordinate_change);
                waves[level].push_back(new_ballon);
            }
        }

        else if ( ballon_type == BALLON::PREGNANT ){

            for ( int i=1 ; i<=count ; i++ ){
                shared_ptr<pregnant_ballon> new_ballon(new pregnant_ballon(start.x, start.y));
                new_ballon->setHealthBar(health_bar);
                new_ballon->setCoordinate(coordinate_change);
                waves[level].push_back(new_ballon);
            }
        }
    }
    randomizeWave(waves[level]);
    in_wave_spawn_delay.restart();
}

void GameMenu::randomizeWave(vector<shared_ptr<ballon> >& wave){

    if ( wave.size() <= 1 ) 
        return;

    int rand_idx = rand()%(wave.size());
    for ( int i=0 ; i<wave.size() ; i++ ){

        while ( wave[rand_idx] == wave[i] ){
            rand_idx = rand()%(wave.size());
        }

        auto temp = wave[i];
        wave[i] = wave[rand_idx];
        wave[rand_idx] = temp;
    }
}

void GameMenu::moveBallons(RenderWindow &window) {

    vector<shared_ptr<ballon>> &current_wave = waves[level];
    wined_ballons=0;
    for (int i=0; i <= move_index && i < current_wave.size(); i++) {
        current_wave[i]->showMove(window);
        wined_ballons+=current_wave[i]->get_wined_balls();
    }
    
    if (move_index < current_wave.size()-1) {
        if (in_wave_spawn_delay.getElapsedTime().asMilliseconds() >= in_wave_spawn_delay_) {
            move_index++;
            in_wave_spawn_delay.restart();
        }
    }
    return ;
}

void GameMenu::updateWaves() {

    shared_ptr<ballon> last_ballon = waves[level].back();
    if (last_ballon->isActive())
        return;
    
    if (!wave_delay_started) {
        between_waves_delay.restart();
        wave_delay_started = true;
    }
    
    if (between_waves_delay.getElapsedTime().asSeconds() >= WAVE_LAUNCH_GAP_SECS) {
        wave_delay_started = false; 
        level++;
        if (level < ATTACKING_PLAN.size()) {
            createWave();
        }
        between_waves_delay.restart();
    }
}

void GameOver::load() {
    if (!is_texture_loaded) {
        texture.loadFromFile(TexturePaths::GAME_OVER_PIC);
        sprite.setTexture(texture);
        is_texture_loaded = true;
    }
}

void GameOver::render(RenderWindow& window) {
    if (is_texture_loaded) {
        Vector2u windowSize = window.getSize();
        Vector2u textureSize = texture.getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(0, 0);
        window.draw(sprite);
    }
}

void GameOver::handleEvents(RenderWindow &window, state &currentState) {
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(mousePos);

    FloatRect yesButtonRect(650.f, 750.f, 200.f, 100.f);
    FloatRect noButtonRect(950.f, 750.f, 300.f, 100.f);

    if (Mouse::isButtonPressed(Mouse::Left)) {

        if (yesButtonRect.contains(worldPos)) {  
            currentState = MAIN_MENU;
        }
        else if (noButtonRect.contains(worldPos)) {
            currentState = EXIT;
        }
    }
}

void GraphicsEngine::run(){
    srand(time(0));
    while (window.isOpen() && current_state!=EXIT){
        update();
        render();
        handleEvents();
    }
}

void GraphicsEngine::setupGame() {

    if ( game_menu.getMap().size() == 0 )
        game_menu.map_geter(current_map.map_handler(TexturePaths::MAP::MAP1_ARS,window));
    game_initialized = true;
}

void GraphicsEngine::update(){

    switch (current_state){
        case IN_GAME:
            if (!game_initialized){
                background_music.setLoop(true);
                background_music.setVolume(50);
                background_music.play();
                setupGame();
                game_menu.setCoordinate(current_map.getMovementRule());
                right_panel->initRightPanel(window,top_panel->money_pointer_given());
                right_panel->createButtons();
                game_menu.setHealthBar(top_panel->getHealthBar());
                game_menu.createWave(); 
            }
            right_panel->handleEvents(window,tower_management);
            top_panel->update(window);
            if ( top_panel->getHealthBar()->getHealth() <= 0 )
                current_state = LOSE;
            break;
        case PAUSE_ :    
            break;
        case MAIN_MENU : 
            main_menu.handleEvents(window, current_state);
            if (current_state == IN_GAME) {  
                resetGame();
            }
            break;
        case VICTORY :
            break;
        case LOSE :
            game_over.handleEvents(window, current_state);
            break;
        case EXIT :
            break;
    }
}

void GraphicsEngine::render(){
    window.clear();
    switch (current_state){
        case IN_GAME:
            if(game_initialized){
                game_menu.renderMap(window);
                game_menu.renderGameMenu(window);
                right_panel->render(window);
                top_panel->render(window);
                game_menu.updateWaves();
                game_menu.moveBallons(window);
                if (first_validate_move){
                    right_panel->valid_location_writer(game_menu.valid_locations_geter());
                    first_validate_move=false;
                }
                tower_management->setWave(game_menu.getCurrentWave());
                tower_management->render(window);
                tower_management->shoot();
                }
            break;
        case PAUSE_ :    
            break;
        case MAIN_MENU : 
            main_menu.draw(window);
            break;
        case VICTORY :
            break;
        case LOSE :
            game_over.render(window);
            break;
        case EXIT :
            window.close();
            break;
    }
    window.display();
}

void GraphicsEngine::handleEvents(){
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
}

void GraphicsEngine::resetGame(){

    top_panel->getHealthBar()->reset();
    tower_management->resetAll();
    game_initialized = false;
    game_menu.reset();
}

void GameMenu::reset(){
    waves.clear();
    in_wave_spawn_delay.restart();
    between_waves_delay.restart();
    level = 0;
    move_index = 0;
    wave_delay_started = false;
}

void MainMenu::handleEvents(sf::RenderWindow& window, state& currentState) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));    
    start_text.setFillColor(start_text.getGlobalBounds().contains(mousePos) ? Color::Green : Color::White);
    exit_text.setFillColor(exit_text.getGlobalBounds().contains(mousePos) ? Color::Red : Color::White);
    if (Mouse::isButtonPressed(Mouse::Left)) {
        if (start_text.getGlobalBounds().contains(mousePos)) {
            MAP main_map;
            currentState= IN_GAME;
            window.clear();
            }
        else if (exit_text.getGlobalBounds().contains(mousePos)) 
            currentState= EXIT;
    }
}

void MainMenu::draw(RenderWindow& window) {
    window.draw(background_sprite);
    window.draw(start_text);
    window.draw(exit_text);
    window.display();
}



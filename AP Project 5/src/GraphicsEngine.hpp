#ifndef GRAPHICSENGINE_HPP
#define GRAPHICSENGINE_HPP

#include "main.hpp"
#include "ReadInputFile.hpp"
#include "Ballons.hpp"
#include "WaveConfigs.hpp"
#include "Towers.hpp"
#include "MapSystem.hpp"
#include "StoragePaths.hpp"
#include "RightPanel.hpp"
#include "toppanel.hpp"
const int refresh_rate = 60;

enum MenuOption{
    START_B,
    QUIT
};

class MainMenu{
public:
    MainMenu();
    void handleEvents(RenderWindow &window, state &currentState);
    void update();
    void draw(RenderWindow &window);

private:
    MenuOption current_option;
    Texture background_texture;
    Sprite background_sprite;
    Font arial_font;
    Text start_text;
    Text exit_text;
};

class GameOver {
public:
    void load();
    void render(RenderWindow& window);
    void handleEvents(RenderWindow &window, state &currentState);

private:
    Texture texture;
    Sprite sprite;
    bool is_texture_loaded = false;
};

class GameMenu{
public:
    void reset();
    void map_geter(vector<vector<tuple<string, string, string, string>>> input){
        tiles_places = input;
    }
    auto getMap() { return tiles_places; }
    void setCoordinate(vector<pair<float, float>> movement_rule){
        coordinate_change = movement_rule;
    }
    void draw(RenderWindow &window, string file_path, int x, int y, bool twox);
    void renderGameMenu(RenderWindow &window);
    void renderMap(RenderWindow &window);
    pair<float, float> auto_scale_founder(Texture temp_texture);
    void createWave();
    void moveBallons(RenderWindow &window);
    void randomizeWave(vector<shared_ptr<ballon>> &wave);
    void updateWaves();
    tuple<float,float,vector<tuple<int,int,bool>>> valid_locations_geter(){
        return valid_locations;}
    int get_wined_ballon(){
        return wined_ballons;
    }
    void setHealthBar(shared_ptr<HealthBar> hb) { health_bar = hb; }
    vector<shared_ptr<ballon> > getCurrentWave() { return waves[level]; }
    
private:
    vector<vector<tuple<string, string, string, string>>> tiles_places;
    Texture map_texture;
    Sprite map_sprite;
    vector<pair<float, float>> coordinate_change;
    vector<vector<shared_ptr<ballon> > > waves;
    int in_wave_spawn_delay_;
    int level = 0;
    Clock in_wave_spawn_delay;
    int move_index = 0;
    Clock between_waves_delay;
    bool wave_delay_started = false;
    bool first_draw=false;
    tuple<float,float,vector<tuple<int,int,bool>>> valid_locations;
    int wined_ballons=0;
    shared_ptr<HealthBar> health_bar;
};

class GraphicsEngine{
public:
    GraphicsEngine(int width, int height);
    void run();

private:
    void setupGame();
    void update();
    void render();
    void handleEvents();
    void resetGame();

    Music background_music;
    SoundBuffer buffer;
    Sound sound;
    GameMap current_map;
    bool game_initialized = false;
    bool first_validate_move=true;
    MainMenu main_menu;
    GameMenu game_menu;
    GameOver game_over;
    RenderWindow window;
    shared_ptr<tower> tower_management;
    shared_ptr<RightPanel> right_panel;
    shared_ptr<TopPanel> top_panel;

protected:
    state current_state;
};

#endif
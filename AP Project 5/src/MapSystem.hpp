#ifndef MAPSYSTEM_HPP
#define MAPSYSTEM_HPP
#include "main.hpp"
#include "StoragePaths.hpp"
#include "ReadInputFile.hpp"

class GameMap{
public:
    vector<vector<tuple<string,string,string,string>>> map_handler(string path_to_map,RenderWindow &window);
    void init_map_values(RenderWindow &window);
    vector<pair<float, float> > getMovementRule();
private:
    void dash_finder();
    void map_input_reader(vector<vector<int>> input);
    void start_point_modify();
    void up_shifted_way_tile_modifier(pair<int,int> temp_move);
    void down_shifted_way_tile_modifier(pair<int,int> temp_move);
    void right_shifted_way_tile_modifier(pair<int,int> temp_move);
    void left_shifted_way_tile_modifier(pair<int,int> temp_move);
    void continue_way_tile_modifier();
    void movement_function(pair<int,int> temp_move);
    void start_point_finder();
    void path_finder();
    void last_tile();
    bool crosscheck();
    void cross_modify();
    void printer();
    bool left_right_up_down_o_finder(pair<int,int> temp_movement);
    void start_point_modify(pair<int,int> temp_mov);
    void movement_rule_finder(int i,int j);
    int rows ;
    int columns ;
    float effective_width  ;
    float effective_height ;
    float cell_width  ;
    float cell_height ;
    float start_x = 0;
    float start_y ; 
    pair<int,int> current_movement;
    pair<int,int> start_point; 
    vector<vector<tuple<string,string,string,string>>> ouput;
    vector<vector<int>> input;
    vector<pair<float,float>> movement_rule;
    pair<int,int> current_pos;
    bool find_end=false;
    bool modify_start=false;
};
#endif
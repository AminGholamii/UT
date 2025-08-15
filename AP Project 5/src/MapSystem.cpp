#include "MapSystem.hpp"

namespace movement{
    const pair<int,int> LEFT ={{0},{-1}};
    const pair<int,int> RIGHT ={{0},{1}};
    const pair<int,int> DOWN ={{1},{0}};
    const pair<int,int> UP ={{-1},{0}};
    vector<pair<pair<int,int>,pair<int,int>>> turn = {{LEFT,RIGHT},{RIGHT,LEFT},{DOWN,UP},{UP,DOWN}};
}

void GameMap::map_input_reader(vector<vector<int>> input_){
    input.resize(input_.size());
    for (size_t i = 0; i < input_.size(); i++){
        for (auto temp:input_[i]){
            input[i].push_back(temp);}
        }
    ouput.resize(input.size());
    for (auto& row : ouput)  
    {
        row.resize(input[0].size());
    }
}

void GameMap::movement_rule_finder(int i,int j){
    float x=start_x+(j*cell_width+cell_width/2);
    float y=start_y+(i*cell_height+cell_height/2);
    movement_rule.push_back({x,y});
}

void GameMap::start_point_finder(){
    for (size_t i = 0; i < input.size(); i++)
        for (size_t j = 0; j < input[i].size(); j++){
            if (input[i][j]==START){
                start_point={i,j};
                current_pos=start_point;
                return;
            }
        }
}

void GameMap::last_tile(){
    movement_rule_finder(current_pos.first,current_pos.second);
    if (current_movement==movement::LEFT)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_GRASS};
    else if(current_movement==movement::RIGHT)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::DOWN_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};
    else if(current_movement==movement::UP)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS};
    else 
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};   
}
void GameMap::continue_way_tile_modifier(){
    if (current_movement==movement::UP||current_movement==movement::DOWN)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS,MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS};
    else if (current_movement==movement::RIGHT||current_movement==movement::LEFT)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::DOWN_GRASS,MAP_BACKGROUND1::DOWN_GRASS};
    return;
}

bool GameMap::crosscheck(){  
    int counter=0;
        if (!((current_pos.first-1>=0 )&& (current_pos.second-1>=0)&&(current_pos.first+1<input.size())&&(current_pos.second+1<input[0].size()))&&!find_end)
        return false;
    for(auto temp_move:movement::turn){
        pair<int,int>cur_point=current_pos;
        cur_point.first+=temp_move.first.first;
        cur_point.second+=temp_move.first.second;
        if (input[cur_point.first][cur_point.second]==PATH){
            counter++;
        }
    }
    if (counter==4)
        return true;
    else
        return false;
}

void GameMap::up_shifted_way_tile_modifier(pair<int,int> temp_move){
    if (temp_move==movement::RIGHT)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::CORSS_DOWN_RIGHT};
    else 
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::CORSS_DOWN_LEFT,MAP_BACKGROUND1::RIGHT_GRASS};
}

void GameMap::down_shifted_way_tile_modifier(pair<int,int> temp_move){
    if (temp_move==movement::RIGHT)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::CORSS_UP_RIGHT,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_GRASS};
   else 
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::CORSS_UP_LEFT,MAP_BACKGROUND1::RIGHT_GRASS,MAP_BACKGROUND1::DOWN_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};
}

void GameMap::left_shifted_way_tile_modifier(pair<int,int> temp_move){
    if (temp_move==movement::UP)
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::CORSS_UP_RIGHT,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_GRASS};
    else
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::CORSS_DOWN_RIGHT};
}

void GameMap::right_shifted_way_tile_modifier(pair<int,int> temp_move){
    if (temp_move==movement::UP){
    ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::CORSS_UP_LEFT,MAP_BACKGROUND1::RIGHT_GRASS,MAP_BACKGROUND1::DOWN_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};
    }
    else 
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::CORSS_DOWN_LEFT,MAP_BACKGROUND1::RIGHT_GRASS};
       }


bool GameMap::left_right_up_down_o_finder(pair<int,int> temp_move){
    if (!((current_pos.first+temp_move.first>=0 )&& (current_pos.second+temp_move.second>=0)&&(current_pos.first+temp_move.first<input.size())&&(current_pos.second+temp_move.second<input[0].size())))
        return false;
    if ((input[current_pos.first+temp_move.first][current_pos.second+temp_move.second]==PATH)||(input[current_pos.first+temp_move.first][current_pos.second+temp_move.second]==FINISH)){
        if (current_movement==temp_move){
            continue_way_tile_modifier();
            return true;
        }
        else if(current_movement==movement::UP){
            movement_rule_finder(current_pos.first,current_pos.second);
            up_shifted_way_tile_modifier(temp_move);
            return true;
        }
        else if(current_movement==movement::DOWN){
            movement_rule_finder(current_pos.first,current_pos.second);
            down_shifted_way_tile_modifier(temp_move);
            return true;
        }
        else if(current_movement==movement::RIGHT){
            movement_rule_finder(current_pos.first,current_pos.second);
            right_shifted_way_tile_modifier(temp_move);
            return true;
        }
        else {
            movement_rule_finder(current_pos.first,current_pos.second);
            left_shifted_way_tile_modifier(temp_move);
            return true;
        return false;
        }
    }
    return false;
}

void GameMap::cross_modify(){
    ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::CORSS_UP_LEFT,MAP_BACKGROUND1::CORSS_UP_RIGHT,MAP_BACKGROUND1::CORSS_DOWN_LEFT,MAP_BACKGROUND1::CORSS_DOWN_RIGHT};
    if(current_movement==movement::LEFT){
        current_pos.first+=current_movement.first;
        current_pos.second+=current_movement.second;
        movement_function(movement::LEFT);}
    else if(current_movement==movement::RIGHT){
        current_pos.first+=current_movement.first;
        current_pos.second+=current_movement.second;
        movement_function(movement::RIGHT);}
    else if(current_movement==movement::UP){
        current_pos.first+=current_movement.first;
        current_pos.second+=current_movement.second;
        movement_function(movement::UP); }
    else {
        current_pos.first+=current_movement.first;
        current_pos.second+=current_movement.second;
        movement_function(movement::DOWN); }
}

void GameMap::start_point_modify(){
    
 for (auto temp_move : movement::turn){
    if (find_end) return;
  int new_x = current_pos.first + temp_move.first.first;
    int new_y = current_pos.second +temp_move.first.second;
    if (new_x >= 0 && new_y >= 0 && new_x < input.size() && new_y < input[0].size()){
    if ((input[current_pos.first+temp_move.first.first][current_pos.second+temp_move.first.second]==PATH)||(input[current_pos.first+temp_move.first.first][current_pos.second+temp_move.first.second]==FINISH)){
    if (temp_move.first==movement::RIGHT){
        ouput[current_pos.first+temp_move.first.first][current_pos.second+temp_move.first.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_GRASS};
        current_movement=temp_move.first;
        movement_function(temp_move.first);
    }
    else if (temp_move.first==movement::UP){
       ouput[current_pos.first+temp_move.first.first][current_pos.second+temp_move.first.second]={MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};
        current_movement=temp_move.first;
        movement_function(temp_move.first);
    }
    else if (temp_move.first==movement::DOWN){
        ouput[current_pos.first+temp_move.first.first][current_pos.second+temp_move.first.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS};
        current_movement=temp_move.first;
        movement_function(temp_move.first);
    }
    else {
        ouput[current_pos.first+temp_move.first.first][current_pos.second+temp_move.first.second]={MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::DOWN_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};
        current_movement=temp_move.first;
        movement_function(temp_move.first);
    }
}
}}}
void GameMap::start_point_modify(pair<int,int> temp_mov){
     if (temp_mov==movement::RIGHT){
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_GRASS};
    }
    else if (temp_mov==movement::UP){
       ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS,MAP_BACKGROUND1::DOWN_LEFT_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};
    }
    else if (temp_mov==movement::DOWN){
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_LEFT_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::LEFT_GRASS,MAP_BACKGROUND1::RIGHT_GRASS};
    }
    else {
        ouput[current_pos.first][current_pos.second]={MAP_BACKGROUND1::UP_GRASS,MAP_BACKGROUND1::UP_RIGHT_GRASS,MAP_BACKGROUND1::DOWN_GRASS,MAP_BACKGROUND1::DOWN_RIGHT_GRASS};
    }
}

void GameMap::movement_function(pair<int,int> temp_move){
    int counter=0;
    if (!((current_pos.first+temp_move.first>=0 )&& (current_pos.second+temp_move.second>=0)&&(current_pos.first+temp_move.first<input.size())&&(current_pos.second+temp_move.second<input[0].size()))&&!find_end)
        return;
    else if(current_movement.first==0&&current_movement.second==0&&modify_start){
        modify_start=true;
        start_point_modify();
        return;
    }

    else if(crosscheck()){
        cross_modify();
        return;
    }
    else if(!find_end){
        for (auto temp_mov:movement::turn){
            if (current_movement==temp_mov.second){
                continue;}
            else if(find_end||counter)return;
            else if(left_right_up_down_o_finder(temp_mov.first)){
                if (input[current_pos.first][current_pos.second]==START)
                start_point_modify(temp_mov.first);
                current_pos.first+=temp_mov.first.first;
                current_pos.second+=temp_mov.first.second;
                if (find_end) break;
                current_movement=temp_mov.first;
                if (input[current_pos.first][current_pos.second]==FINISH){
                find_end=true;
                last_tile();
                left_right_up_down_o_finder(current_movement);
                return;
                }
                else
                movement_function(temp_mov.first);
                counter++;
            }
        }   
    }
}

vector<pair<float, float> > GameMap::getMovementRule(){

    return movement_rule;
}

void GameMap::path_finder(){
    for (auto temp_move:movement::turn){
        if(find_end) return;
        movement_function(temp_move.first);
    }
}

void GameMap::dash_finder(){
    for (size_t i = 0; i < ouput.size(); i++)
        for (size_t j = 0; j < ouput[i].size(); j++)
            if(get<0>(ouput[i][j])=="")
                ouput[i][j]={"",MAP_BACKGROUND1::ONLY_GRASS,"",""};
}

void GameMap::init_map_values(RenderWindow &window){
     rows=input.size();
     columns=input[0].size();
     effective_width = window.getSize().x * 0.75f;
     effective_height = window.getSize().y * 0.75f;
     cell_width  = effective_width / columns;
     cell_height = effective_height / rows;
     start_x = 0;
     start_y =window.getSize().y * 0.25f;
}

vector<vector<tuple<string,string,string,string>>> GameMap::map_handler(string path_to_map,RenderWindow &window){
    MAP main_map;  
    readInputFile(main_map,path_to_map);
    map_input_reader(main_map);
    init_map_values(window);
    start_point_finder();
    path_finder();
    dash_finder();
    int i=0;
    return ouput;
}
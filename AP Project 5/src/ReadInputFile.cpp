#include "ReadInputFile.hpp"

void readInputFile(MAP& main_map, string file_name){
    ifstream map_file("maps/1.txt");
    string row;
    int i=0;
    while ( getline(map_file, row) ) {

        main_map.resize(main_map.size()+1);
        for ( int j=0 ; j<row.length() ; j++ ){
            
            main_map[i].resize(main_map[i].size()+1);
            switch (row[j])
            {
                case 'S':
                    main_map[i][j] = START;
                    break;

                case 'O':
                    main_map[i][j] = PATH;
                    break;
                
                case '-':
                    main_map[i][j] = TOWER_POINT;
                    break;

                case 'F':
                    main_map[i][j] = FINISH;
                    break;
            }
        }
        i++;
    }
}

void readtexture(string path,Texture &texture,Sprite &sprite){
    texture.loadFromFile(TexturePaths::BACKGROUND::MainMenu_background_ARS);
    sprite.setTexture(texture);
    return;
}
void readfont(string path,Font &font){
    if (!font.loadFromFile(path)) 
        cerr<<"failed to load "<<path<<"."<<endl;
}
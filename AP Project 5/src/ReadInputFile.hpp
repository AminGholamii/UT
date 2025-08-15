#ifndef READFILE_HPP
#define READFILE_HPP

#include "main.hpp"
#include "StoragePaths.hpp"
void readInputFile(MAP& main_map, string file_name);
void readtexture(string path,Texture &texture,Sprite &sprite);
void readfont(string path,Font &font);

#endif
#ifndef MAIN_HPP
#define MAIN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <tuple>
#include <memory>
#include <math.h>
#include <ctime>
#include <sstream>
#include <functional>

using namespace sf;
using namespace std;

enum CELL_SYMBOL{ START=0 , PATH=1 , TOWER_POINT=2 , FINISH=3 };
typedef vector<vector<int> > MAP;

#endif 
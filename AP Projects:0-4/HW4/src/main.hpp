#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
using namespace std;

enum SCORE_INDEX { CORRECT = 0 , INCORRECT = 1 , BLANK = 2 };
const string EASY = "easy";
const string MEDIUM = "medium";
const string HARD = "hard";
const string CREATE_TEMPLATE = "create_template";
const string GENERATE_TEST = "generate_test";
const string ATTEND = "attend";
const string AUTO_GENERATE = "auto_generate";
const string REPORT = "report";

class question;
class template_inf;
class quiz_template;
class test;
class test_score;

typedef vector<shared_ptr<question> > BANK;
typedef vector<shared_ptr<quiz_template> > TEMPLATES;
typedef vector<shared_ptr<test_score> > SCORES;

#endif //main.hpp
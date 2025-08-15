#include "classes.hpp"

question::question(string question_txt, vector<string> options, int correct_ans,
    string difficulty, string subj){
        question_txt_ = question_txt;
        options_ = options;
        correct_ans_ = correct_ans;
        difficulty_ = difficulty;
        subj_ = subj;
        num_of_corrects_ = 0;
        num_of_blanks_ = 0;
        num_of_incorrects_ = 0;
        last_answer_ = 0;
};
void question::setLastAnswer(int num){ last_answer_ = num; }
void question::answeredCorrectly() { num_of_corrects_++; }
void question::answeredIncorrectly() { num_of_incorrects_++; }
void question::leftBlank() { num_of_blanks_++; }
string question::getText() const { return question_txt_; }
string question::getSubj() const { return subj_; }
string question::getDifficulty() const { return difficulty_; }
vector<string> question::getOptions() const { return options_; }
int question::getNumOfCorrects() const { return num_of_corrects_; }
int question::getCorrectAnswer() const { return correct_ans_; }
int question::getLastAnswer() const { return last_answer_; }
int question::getPriority() const { 
    return (3*num_of_incorrects_ + num_of_blanks_ - 2*num_of_corrects_ );
}


template_inf::template_inf(string subj, string difficulty, int count){
    subj_ = subj;
    difficulty_ = difficulty;
    count_ = count;
}
string template_inf::getSubj() const { return subj_; }
string template_inf::getDifficulty() const { return difficulty_; } 
int template_inf::getCount() const { return count_; }


quiz_template::quiz_template(string name, vector<template_inf> infos){
    name_ = name;
    infos_ = infos;
}
void quiz_template::addTest(shared_ptr<test> new_test) { tests_.push_back(new_test); }
string quiz_template::getName() const { return name_; }
vector<template_inf> quiz_template::getInfos() const { return infos_; }
vector<shared_ptr<test> > quiz_template::getTests() const { return tests_; }


test::test(string name, BANK questions){
    name_ = name;
    questions_ = questions;
}
string test::getName() const { return name_; }
BANK test::getQuestions() const{ return questions_; } 


test_score::test_score(shared_ptr<test> curr_test, vector<pair<shared_ptr<question>,int> > questions){
    curr_test_ = curr_test;
    questions_ = questions;
}
vector<pair<shared_ptr<question>,int> > test_score::getQuestions() const { return questions_; }
string test_score::getTestName() const { return curr_test_->getName(); } 

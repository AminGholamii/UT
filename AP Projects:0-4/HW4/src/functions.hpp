#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "classes.hpp"

void readQuestionsFile(string file_name, BANK& question_banks);
bool getAndApplyCommand(const BANK& question_banks, TEMPLATES& templates, SCORES& tests_scores);
void createTemplate(TEMPLATES& templates, string template_name, const vector<template_inf>& infos);
bool duplicateTemplateName(const TEMPLATES& templates, string template_name);
shared_ptr<quiz_template> findTemplate(const TEMPLATES& templates, string search);
void generateTest(const BANK& question_banks, shared_ptr<quiz_template> curr_template, string test_name);
BANK findDesirables(const BANK& question_banks, shared_ptr<quiz_template> curr_template);
void sortQuestions(BANK& desirables);
BANK chooseQuestions(const BANK& desirables, vector<template_inf> infos);
void attendTest(shared_ptr<test> curr_test, SCORES& tests_scores);
shared_ptr<test> findTest(const TEMPLATES& templates, string test_name);
void differentAnswers(BANK& questions, BANK::iterator curr_que, int& question_num);
void answerQuestion(BANK& questions, BANK::iterator curr_que, int& question_num);
void autoGenerate(const BANK& question_banks, TEMPLATES& templates, const SCORES& tests_scores, string test_name);
vector<string> findTwoLowestSubjs(const SCORES& tests_scores);
void Report(SCORES& tests_scores);
void reportAll(const SCORES& tests_scores);
SCORES::iterator findTestInTestScores(SCORES& tests_scores, string test_name);
void reportTest(SCORES::iterator choosed_test);
void reportTests(const SCORES& tests_scores);
void reportSubject(const SCORES& tests_scores, string subj_name);


#endif //functions.hpp
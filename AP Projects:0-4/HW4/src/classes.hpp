#ifndef CLASSES_HPP 
#define CLASSES_HPP
#include "main.hpp"

class question {
public:
    question(string question_txt, vector<string> options, int correct_ans,
        string difficulty, string subj);

    void setLastAnswer(int);
    void answeredCorrectly();
    void answeredIncorrectly();
    void leftBlank();

    string getText() const;
    string getSubj() const;
    string getDifficulty() const;
    vector<string> getOptions() const;
    int getNumOfCorrects() const;
    int getCorrectAnswer() const;
    int getLastAnswer() const;
    int getPriority() const;
    
private:
    string question_txt_;
    vector<string> options_;
    int correct_ans_;
    string difficulty_;
    string subj_;
    int num_of_corrects_;
    int num_of_blanks_;
    int num_of_incorrects_;
    int last_answer_;
};

class template_inf {
public:
    template_inf(string subj, string difficulty, int count);

    string getSubj() const;
    string getDifficulty() const;
    int getCount() const;

private:
    string subj_;
    string difficulty_;
    int count_;
};

class quiz_template {
public:
    quiz_template(string name, vector<template_inf> infos);

    void addTest(shared_ptr<test> new_test);
    string getName() const;
    vector<template_inf> getInfos() const;
    vector<shared_ptr<test> > getTests() const;

private:
    string name_;
    vector<template_inf> infos_;
    vector<shared_ptr<test> > tests_;
};

class test {
public:
    test(string name, BANK questions);

    string getName() const;
    BANK getQuestions() const;

private:
    string name_;
    BANK questions_;
};

class test_score {
public:
    test_score(shared_ptr<test> curr_test, vector<pair<shared_ptr<question>,int> > questions);

    vector<pair<shared_ptr<question>,int> > getQuestions() const;
    string getTestName() const;

private:
    shared_ptr<test> curr_test_;
    vector<pair<shared_ptr<question>,int> > questions_;
};

#endif //classes.hpp
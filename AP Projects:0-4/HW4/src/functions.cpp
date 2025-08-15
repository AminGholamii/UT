#include "functions.hpp"

void readQuestionsFile(string file_name, BANK& question_banks){

    ifstream file(file_name);
    string line;
    getline(file, line);
    while ( getline(file, line) ){

        istringstream strstream(line);
        string subj, question_txt, option1, option2, option3, option4, correct_ans;
        string difficulty;
 
        getline(strstream, question_txt, ',');
        getline(strstream, option1, ',');
        getline(strstream, option2, ',');
        getline(strstream, option3, ',');
        getline(strstream, option4, ',');
        vector<string> options = {option1, option2, option3, option4};
        getline(strstream, correct_ans, ',');
        getline(strstream, difficulty, ',');
        strstream >> subj;

        shared_ptr<question> new_que(new question(question_txt, options, stoi(correct_ans), difficulty, subj));
        question_banks.push_back(new_que);
    }
}

bool getAndApplyCommand(const BANK& question_banks, TEMPLATES& templates, SCORES& tests_scores){

    string command;
    cin >> command;

    if ( cin.eof() )
        return false;
    
    if ( command == CREATE_TEMPLATE ){

        getchar() && getchar();
        string template_name;
        getline(cin, template_name, '\'');
        getchar();
        
        vector<template_inf> infos;
        string all_infos, temp;
        getline(cin, all_infos);
        istringstream strstream(all_infos);

        while ( strstream >> temp ){

            string subj, difficulty, count_str;
            istringstream strstream2(temp);
            getline(strstream2, subj, ':');
            getline(strstream2, difficulty, ':');
            getline(strstream2, count_str);
            template_inf new_inf(subj, difficulty, stoi(count_str));
            infos.push_back(new_inf);
        }

        if ( duplicateTemplateName(templates, template_name) ){
            cout << "Duplicate name: \'" << template_name << '\'' << endl;
            return true;
        }
        
        createTemplate(templates, template_name, infos);
        cout << "Template \'" << template_name << "\' was created successfully." << endl;
    }

    else if ( command == GENERATE_TEST ){

        getchar() && getchar();
        string test_name, template_name;
        getline(cin, test_name, '\'');
        getchar() && getchar();
        getline(cin, template_name, '\'');
        getchar();

        shared_ptr<quiz_template> curr_template = findTemplate(templates, template_name);
        if ( curr_template == NULL  ){
            cout << "Could not find template: \'" << template_name << '\'' << endl;
            return true;
        }
        
        generateTest(question_banks, curr_template, test_name);
        cout << "Test \'" << test_name << "\' was generated successfully." << endl;
    }

    else if ( command == ATTEND ){

        getchar() && getchar();
        string test_name;
        getline(cin, test_name, '\'');
        getchar();

        shared_ptr<test> curr_test = findTest(templates, test_name);
        if ( curr_test == NULL ){
            cout << "Could not find test: \'" << test_name << '\'' << endl;
            return true;
        }
        
        cout << test_name << ":\n" << endl;
        attendTest(curr_test, tests_scores);
        cout << "\nFinished " << test_name << '.' << endl;
    }

    else if ( command == AUTO_GENERATE ){

        getchar() && getchar();
        string test_name;
        getline(cin, test_name, '\'');
        getchar();

        autoGenerate(question_banks, templates, tests_scores, test_name);
    }

    else if ( command == REPORT ){
        Report(tests_scores);
    }

    return true;
}

void createTemplate(TEMPLATES& templates, string template_name, const vector<template_inf>& infos){

    shared_ptr<quiz_template> new_template(new quiz_template(template_name, infos));
    templates.push_back(new_template);
}

bool duplicateTemplateName(const TEMPLATES& templates, string template_name){

    for ( auto temp : templates )
        if ( temp->getName() == template_name )
            return true;

    return false;
}

shared_ptr<quiz_template> findTemplate(const TEMPLATES& templates, string search){
    
    for ( auto temp : templates )
        if ( temp->getName() == search )
            return temp;

    return NULL;
}

void generateTest(const BANK& question_banks, shared_ptr<quiz_template> curr_template, string test_name){

    
    BANK desirables = findDesirables(question_banks, curr_template);
    sortQuestions(desirables);
    auto infos = curr_template->getInfos();
    BANK choosed_questions = chooseQuestions(desirables, infos);
    shared_ptr<test> new_test(new test(test_name, choosed_questions));
    curr_template->addTest(new_test);
}

BANK findDesirables(const BANK& question_banks, shared_ptr<quiz_template> curr_template){

    BANK desirables;
    vector<template_inf> infos = curr_template->getInfos();

    for ( auto info : infos )
        for ( auto que : question_banks )
            if ( que->getDifficulty() == info.getDifficulty() && que->getSubj() == info.getSubj() )
                desirables.push_back(que);
    
    return desirables;
}

void sortQuestions(BANK& desirables){

    sort(desirables.begin(), desirables.end(),[](shared_ptr<question> a, shared_ptr<question> b){
        
        if ( a->getPriority() == b->getPriority() )
            return a->getText() < b->getText();

        return a->getPriority() > b->getPriority();
    });
}

BANK chooseQuestions(const BANK& desirables, vector<template_inf> infos){

    BANK choosed_questuions;
    vector<pair<string, string> > choosed_formats;
    
    for ( int i=0 ; i<desirables.size() ; i++ ){

        int repeatative = 0;
        for ( auto pair : choosed_formats ){
            if ( desirables[i]->getSubj() == pair.first && desirables[i]->getDifficulty() == pair.second ){
                repeatative = 1;
                break;
            }
        }

        if ( repeatative ) continue;
        for ( auto info : infos ){

            string subj = info.getSubj();
            string difficulty = info.getDifficulty();

            if ( desirables[i]->getSubj() == subj && desirables[i]->getDifficulty() == difficulty ){
                
                choosed_questuions.push_back(desirables[i]);
                int check = 1;
                for ( int j=i+1 ; check!=info.getCount() && j<desirables.size() ; j++ ){
                    if ( desirables[j]->getSubj() == subj && desirables[j]->getDifficulty() == difficulty ){
                        choosed_questuions.push_back(desirables[j]);
                        check++;
                    }
                }
                choosed_formats.push_back({subj, difficulty});
                break;
            }
        }        
    }
    return choosed_questuions;
}

void attendTest(shared_ptr<test> curr_test, SCORES& tests_scores){

    BANK questions = curr_test->getQuestions();

    sort(questions.begin(), questions.end(),[](shared_ptr<question> a, shared_ptr<question> b){
        
        if (a->getSubj() == b->getSubj()) {
            return a->getText() < b->getText(); 
        }
        return a->getSubj() < b->getSubj();
    });

    auto curr_que = questions.begin();
    int question_num = 1;
    answerQuestion(questions, curr_que, question_num);
    vector<pair<shared_ptr<question>, int> > questions_scores;

    for ( auto que : questions ){

        if ( que->getLastAnswer() != 0 ){

            if ( que->getLastAnswer() == que->getCorrectAnswer() ){
                que->answeredCorrectly();
                questions_scores.push_back({que, CORRECT});
            }
            else {
                que->answeredIncorrectly();
                questions_scores.push_back({que, INCORRECT});
            }
            que->setLastAnswer(0);
        }
        else {
            que->leftBlank();
            questions_scores.push_back({que, BLANK});
        }
    }

    shared_ptr<test_score> new_score(new test_score(curr_test, questions_scores));
    tests_scores.push_back(new_score);
}

shared_ptr<test> findTest(const TEMPLATES& templates, string test_name){

    for ( auto temp : templates ){

        auto total_tests = temp->getTests();
        for ( auto each_test : total_tests ){
            if ( each_test->getName() == test_name )
                return each_test;
        }
    }
    return NULL;
}

void differentAnswers(BANK& questions, BANK::iterator curr_que, int& question_num){

    cout << "Your answer: ";
    string answer;
    getline(cin, answer);

    if ( answer.empty() ){

        cout << endl;
        if ( *(curr_que) == *(questions.rbegin()) ){
            return;
        }
        (*curr_que)->setLastAnswer(0);
        return answerQuestion(questions, next(curr_que), ++question_num);
    }

    else if ( answer=="1" || answer=="2" || answer=="3" || answer=="4" ){

        cout << endl;
        if ( *(curr_que) == *(questions.rbegin()) ){
            (*curr_que)->setLastAnswer(stoi(answer));
            return;
        }
        (*curr_que)->setLastAnswer(stoi(answer));
        return answerQuestion(questions, next(curr_que), ++question_num);
    }
    
    else if ( answer == "previous" ){

        if ( *(curr_que) == *(questions.begin()) ){
            cout << "Invalid answer, please try again." << endl;
            return differentAnswers(questions, curr_que, question_num);
        }
        cout << endl;
        return answerQuestion(questions, prev(curr_que), --question_num);
    }

    else {
        cout << "Invalid answer! please try again." << endl;
        return differentAnswers(questions, curr_que, question_num);
    }
}

void answerQuestion(BANK& questions, BANK::iterator curr_que, int& question_num){

    vector<string> options = (*curr_que)->getOptions();

    cout << question_num << ") " << (*curr_que)->getText() << endl;

    for ( int i=0 ; i<4 ; i++ ){
        if ( (*curr_que)->getLastAnswer() == i+1 )
            cout << "    " << i+1 << ". " << options[i] << " <-" << endl;
        else 
            cout << "    " << i+1 << ". " << options[i] << endl;
    } 
    differentAnswers(questions, curr_que, question_num);
}

void autoGenerate(const BANK& question_banks, TEMPLATES& templates, const SCORES& tests_scores, string test_name){

    vector<string> two_lowests = findTwoLowestSubjs(tests_scores);

    if ( two_lowests.empty() ) return;

    vector<template_inf> infos;
    template_inf info1(two_lowests[0], EASY, 3);
    template_inf info2(two_lowests[0], MEDIUM, 2);
    template_inf info3(two_lowests[0], HARD, 1);
    template_inf info4(two_lowests[1], EASY, 2);
    template_inf info5(two_lowests[1], MEDIUM, 1);
    template_inf info6(two_lowests[1], HARD, 1);
    infos = {info1, info2, info3, info4, info5, info6};

    string template_name = test_name;
    createTemplate(templates, template_name, infos);
    shared_ptr<quiz_template> curr_template = findTemplate(templates, template_name);
    generateTest(question_banks, curr_template, test_name);
    cout << "Test \'" << test_name << "\' was generated successfully." << endl;
}

vector<string> findTwoLowestSubjs(const SCORES& tests_scores){
    
    map<string, pair<int, int>> subj_stats; 

    for (auto each_test : tests_scores) {
        for (auto pair : each_test->getQuestions()) {
            string subject = pair.first->getSubj();

            subj_stats[subject].first++;
            if (pair.second == CORRECT) { 
                subj_stats[subject].second++;
            }
        }
    }

    vector<pair<string, double> > subj_percentage;
    for (auto [subject, stats] : subj_stats) {
        double percentage = (stats.second / (double)stats.first) * 100.0;
        subj_percentage.push_back({subject, percentage});
    }

    if ( subj_percentage.size() < 2 ) return {};

    sort(subj_percentage.begin(), subj_percentage.end(), [](pair<string, double> a,pair<string, double> b){

        if ( a.second == b.second )
            return a.first < b.first;

        return a.second < b.second;
    });
    return {subj_percentage[0].first, subj_percentage[1].first};
}

void Report(SCORES& tests_scores){
    
    string report_what;
    cin >> report_what;

    if ( cin.eof() )
        return;

    if ( report_what == "all" ){
        getchar();
        reportAll(tests_scores);
    }

    else if ( report_what == "test" ){
        getchar() && getchar();
        string test_name;
        getline(cin, test_name, '\'');
        getchar();
        SCORES::iterator choosed_test = findTestInTestScores(tests_scores, test_name);
        if ( choosed_test != tests_scores.end() )
            reportTest(choosed_test);
    }

    else if ( report_what == "tests" ){
        reportTests(tests_scores);
    }

    else if ( report_what == "subject" ){
        getchar();
        string subj_name;
        getline(cin, subj_name);
        reportSubject(tests_scores, subj_name);
    }
}

void reportAll(const SCORES& tests_scores){

    map<string, vector<int> > subj_stats;
    vector<int> total_report(3,0);
    for ( auto each_test : tests_scores ){
        
        for ( auto pair : each_test->getQuestions() ){  
            subj_stats[pair.first->getSubj()].resize(3,0);
        }
    }

    for ( auto each_test : tests_scores ){
        
        for ( auto pair : each_test->getQuestions() ){ 
            int index = pair.second;
            subj_stats[pair.first->getSubj()][index]++;
            total_report[index]++;
        }
    }

    vector<pair<string, vector<int> > > subj_stats_;
    for ( auto [subj, stats] : subj_stats )
        subj_stats_.push_back({subj, stats});

    sort ( subj_stats_.begin(), subj_stats_.end(), [](pair<string, vector<int> > a, pair<string, vector<int> > b){
        return a.first < b.first;
    });

    cout << "Total report:\n" << endl;

    for ( auto [subj, stats] : subj_stats_ ){

        double score = (double)stats[CORRECT] / (stats[CORRECT]+stats[INCORRECT]+stats[BLANK]) * 100.0;

        cout << subj << ": " << stats[CORRECT] << " corrects, " << stats[INCORRECT] << " incorrects and "
            << stats[BLANK] << " blanks. ";
        printf("Score: %.3lf%%.\n", score);
    }

    double total_score = (double)total_report[CORRECT] / (total_report[CORRECT]+total_report[INCORRECT]+total_report[BLANK]) * 100.0;
    cout << "\nTotal results: " << total_report[CORRECT] << " corrects, " << total_report[INCORRECT] 
        << " incorrects and " << total_report[BLANK] << " blanks." << endl;
    printf("Total score: %.3lf%%.", total_score);
    cout << endl;
}

SCORES::iterator findTestInTestScores(SCORES& tests_scores, string test_name){

    for ( SCORES::iterator it = tests_scores.begin() ; it != tests_scores.end() ; it++ )
        if ( (*it)->getTestName() == test_name )
            return it;
    return tests_scores.end();
}

void reportTest(SCORES::iterator choosed_test){

    map<string, vector<int> > subj_stats;
    vector<int> total_report(3,0);  

    for ( auto pair : (*choosed_test)->getQuestions() ){
        subj_stats[pair.first->getSubj()].resize(3,0);
    }

    for ( auto pair : (*choosed_test)->getQuestions() ){
        int index = pair.second;
        subj_stats[pair.first->getSubj()][index]++;
        total_report[index]++;
    }

    vector<pair<string, vector<int> > > subj_stats_;
    for ( auto [subj, stats] : subj_stats )
        subj_stats_.push_back({subj, stats});

    sort ( subj_stats_.begin(), subj_stats_.end(), [](pair<string, vector<int> > a, pair<string, vector<int> > b){
        return a.first < b.first;
    });

    cout << "Results for " << (*choosed_test)->getTestName() << ":\n" << endl;

    for ( auto [subj, stats] : subj_stats_ ){

        double score = (double)stats[CORRECT] / (stats[CORRECT]+stats[INCORRECT]+stats[BLANK]) * 100.0;
        cout << subj << ": " << stats[CORRECT] << " corrects, " << stats[INCORRECT] 
        << " incorrects and "<< stats[BLANK] << " blanks. ";
        printf("Score: %.3lf%%.", score);
        cout << endl;
    }

    double total_score = (double)total_report[CORRECT] / (total_report[CORRECT]+total_report[INCORRECT]+total_report[BLANK]) * 100.0;
    cout << "\nTotal results: " << total_report[CORRECT] << " corrects, " << total_report[INCORRECT] 
        << " incorrects and " << total_report[BLANK] << " blanks." << endl;
    printf("Total score: %.3lf%%.", total_score);
    cout << endl;
}

void reportTests(const SCORES& tests_scores){

    vector<pair<string, vector<int> > > test_stats;

    for (auto each_test : tests_scores) {
        
        test_stats.push_back({each_test->getTestName(), vector<int>(3, 0)});
        for (auto pair : each_test->getQuestions()) {  
            int index = pair.second;
            test_stats.back().second[index]++;
        }
    }

    cout << "Results per attended tests:\n" << endl;
    for ( auto [test_name, stats] : test_stats ){

        double score = (double)stats[CORRECT] / (stats[CORRECT]+stats[INCORRECT]+stats[BLANK]) * 100.0;
        cout << test_name << ": " << stats[CORRECT] << " corrects, " << stats[INCORRECT] 
            << " incorrects and " << stats[BLANK] << " blanks. ";
        printf("Score: %.3lf%%.", score);
        cout << endl;
    }
}

void reportSubject(const SCORES& tests_scores, string subj_name){

    map<string, vector<int> > subj_stats;
    vector<int> total_report(3,0);
    subj_stats[EASY].resize(3,0);
    subj_stats[MEDIUM].resize(3,0);
    subj_stats[HARD].resize(3,0);
    
    for ( auto each_test : tests_scores ){

        for ( auto pair : each_test->getQuestions() ){

            if ( pair.first->getSubj() == subj_name ){

                int index = pair.second;
                if ( pair.first->getDifficulty() == EASY )
                    subj_stats[EASY][index]++;
                
                else if ( pair.first->getDifficulty() == MEDIUM )
                    subj_stats[MEDIUM][index]++;
                
                else if ( pair.first->getDifficulty() == HARD )
                    subj_stats[HARD][index]++;
                
                total_report[index]++;
            }
        }
    }

    cout << "Results for " << subj_name << ":\n" << endl;
    for ( auto [level, stats] : subj_stats ){

        string level_name;
        if ( level == EASY ) level_name = "Easy";
        else if ( level == MEDIUM ) level_name = "Medium";
        else if ( level == HARD ) level_name = "Hard";

        cout << level_name << ": " << stats[CORRECT] << " corrects, " << stats[INCORRECT]
             << " incorrects and " << stats[BLANK] << " blanks." << endl; 
    }
    double total_score = (double)total_report[CORRECT] / (total_report[CORRECT]+total_report[INCORRECT]+total_report[BLANK]) * 100.0;
    printf("\nTotal score: %.3lf%%.", total_score);
    cout << endl;
}
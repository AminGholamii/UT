#include "functions.hpp"

int main(int argc, char* argv[]) {

    BANK question_bank;
    TEMPLATES templates;
    SCORES tests_scores;
    readQuestionsFile(argv[1], question_bank);

    while ( getAndApplyCommand(question_bank, templates, tests_scores) );
    return 0;
}

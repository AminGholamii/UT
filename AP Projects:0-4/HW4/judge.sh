#?/bin/bash

GREEN="\033[38;5;10m"
RED="\033[38;5;160m"
YELLOW="\033[38;5;185m"
NC="\033[0m"

COMPILER=g++
FLAGS=-std=c++20
MAIN_CPP=src/main.cpp
OUTPUT=MAIN_EXE.out
TESTS=tests

${COMPILER} ${FLAGS} ${MAIN_CPP} -o ${OUTPUT}

if [ $? -ne 0 ]; then
    echo -e "${RED}CompileError occured!${NC}"
    exit 1
fi

total_cnt=0
passed_cnt=0
failed_cnt=0
TIME_LIMIT=10

for test_folder in ${TESTS}/*; do

    if [ -d ${test_folder} ]; then

        total_cnt=$((total_cnt+1))
        test_name=$(basename ${test_folder})
        input_file="$test_folder/*.in"
        expected_output_file="$test_folder/*.out"
        code_output_file="$test_folder/expected.temp"
        error_file="$test_folder/error_log.err"
        
        timeout ${TIME_LIMIT} ./${OUTPUT} ./csv/questions.csv < ${input_file} > ${code_output_file}

        if [ $? -ne 0 ]; then
            failed_cnt=$((failed_cnt+1))
            echo -e "${RED}Test named $test_name failed.Probably due to timeout error!${NC}"
        
        else 

            if diff -q -Z ${code_output_file} ${expected_output_file} > /dev/null; then

                passed_cnt=$((passed_cnt+1))
                echo -e "${GREEN}Test named $test_name passed.${NC}"
                rm ${code_output_file}
                if [ -f ${error_file} ]; then
                    rm ${error_file}
                fi

            else 

                diff -y -Z ${code_output_file} ${expected_output_file} > ${error_file}
                failed_cnt=$((failed_cnt+1))
                echo -e "${RED}Test named $test_name failed.${NC}"
            
            fi
        fi
    fi

done

rm ${OUTPUT}
echo -e "${YELLOW}--------------------"
echo -e "Total Summary:"
echo -e "Total tests: $total_cnt${NC}"
echo -e "${GREEN}Passed tests: $passed_cnt${NC}"
echo -e "${RED}Failed tests: $failed_cnt${NC}"

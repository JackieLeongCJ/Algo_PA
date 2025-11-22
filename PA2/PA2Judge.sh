#!/bin/bash

#############################################################################
# File       [ PA2Judge.sh ]
# Author     [ Bigbee ]
# Synopsis   [ Check your solution in PA2 is correct ]
# Date       [ 2024/10/31 ]
#############################################################################

RED='\e[31m'
GREEN='\e[32m'
YELLOW='\e[33m'
RESET='\e[0m'
Tese_case_names=("Public 1 (N=6)" "Public 2 (N=500)" "Public 3 (N=5000)" "Public 4 (N=30000)" "Public 5 (N=50000)" "Private 1 (N=10000)" "Private 2 (N=20000)" "Private 3 (N=40000)" "Private 4 (N=60000)" "Private 5 (N=90000)" "Additional 1 (N=90000, neighborhood)" "Additional 2 (N=90000, nearby-tangled)" "Additional 3 (N=90000, bestcase)" "Additional 4 (N=90000, random)" "Additional 5 (N=1)")
Tese_case_inputs=("12.in" "1000.in" "10000.in" "60000.in" "100000.in" "P20000.in" "P40000.in" "P80000.in" "P120000.in" "P180000.in" "PP1.in" "PP2.in" "PP3.in" "PP4.in" "PP5.in")
Tese_case_outputs=("public-1.out" "public-2.out" "public-3.out" "public-4.out" "public-5.out" "private-1.out" "private-2.out" "private-3.out" "private-4.out" "private-5.out" "additional-1.out" "additional-2.out" "additional-3.out" "additional-4.out" "additional-5.out")

if [ "$1" == "help" ]; then
    echo "use './PA2Judge.sh' to run all test cases."
    echo "use './PA2Judge.sh [0-9]' to select specific test case."
    exit 0
fi

make
MAKE_STATUS=$?

if [ $MAKE_STATUS -ne 0 ]; then
    echo -e "${RED}PA2Judge: Make failed, please check your makefile.${RESET}"
    exit 1
fi

if [ ! -f "./bin/mps" ]; then
    echo -e "${RED}PA2Judge: Output file (./bin/mps) not found.${RESET}"
    exit 1
fi

TIME_LIMIT=600
mkdir testout
ulimit -s 262144

if [ "$1" == "" ]; then
    echo -e "${YELLOW}PA2Judge: Running Public Sets${RESET}"

    for i in {0..4}; do
        echo -e "${YELLOW}PA2Judge: ${Tese_case_names[$i]}: Running...${RESET}"
        output=$( /usr/bin/time -v timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} 2>&1 )
        real_time=$(echo "$output" | grep "Elapsed (wall clock) time" | awk -F': ' '{print $2}' | awk '{print $1}')
        peak_memory_kb=$(echo "$output" | grep "Maximum resident set size" | awk '{print $6}')
        peak_memory_gb=$(echo "scale=3; $peak_memory_kb / 1024 / 1024" | bc)
        echo "PA2Judge: Runtime: ${real_time}. Peak Memory: ${peak_memory_gb}GB" | tee -a results.txt
        # runtime=$( { time timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} ; } 2>&1 | grep real | awk '{print $2}' )
        # echo "PA2Judge: Runtime: ${runtime}."
        ./PA2JudgeChecker ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} $i
        status=$?
        if [ $status -eq 0 ]; then
            echo -e "${GREEN}PA2Judge: ${Tese_case_names[$i]}: Accepted.${RESET}"
        else
            echo -e "${RED}PA2Judge: ${Tese_case_names[$i]}: Wrong Answer.${RESET}"
        fi
    done

    echo -e "${YELLOW}PA2Judge: Running Private Sets${RESET}"
    ./PA2TestDataGenerator

    for i in {5..9}; do
        echo -e "${YELLOW}PA2Judge: ${Tese_case_names[$i]}: Running...${RESET}"
        output=$( /usr/bin/time -v timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} 2>&1 )
        real_time=$(echo "$output" | grep "Elapsed (wall clock) time" | awk -F': ' '{print $2}' | awk '{print $1}')
        peak_memory_kb=$(echo "$output" | grep "Maximum resident set size" | awk '{print $6}')
        peak_memory_gb=$(echo "scale=3; $peak_memory_kb / 1024 / 1024" | bc)
        echo "PA2Judge: Runtime: ${real_time}. Peak Memory: ${peak_memory_gb}GB" | tee -a results.txt
        # runtime=$( { time timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} ; } 2>&1 | grep real | awk '{print $2}' )
        # echo "PA2Judge: Runtime: ${runtime}."
        ./PA2JudgeChecker ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} $i
        status=$?
        if [ $status -eq 0 ]; then
            echo -e "${GREEN}PA2Judge: ${Tese_case_names[$i]}: Accepted.${RESET}"
        else
            echo -e "${RED}PA2Judge: ${Tese_case_names[$i]}: Wrong Answer.${RESET}"
        fi
    done

    echo -e "${YELLOW}PA2Judge: Running Additional Sets${RESET}"
    ./PA2TestDataGeneratorNeo

    for i in {10..14}; do
        echo -e "${YELLOW}PA2Judge: ${Tese_case_names[$i]}: Running...${RESET}"
        output=$( /usr/bin/time -v timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} 2>&1 )
        real_time=$(echo "$output" | grep "Elapsed (wall clock) time" | awk -F': ' '{print $2}' | awk '{print $1}')
        peak_memory_kb=$(echo "$output" | grep "Maximum resident set size" | awk '{print $6}')
        peak_memory_gb=$(echo "scale=3; $peak_memory_kb / 1024 / 1024" | bc)
        echo "PA2Judge: Runtime: ${real_time}. Peak Memory: ${peak_memory_gb}GB" | tee -a results.txt
        # runtime=$( { time timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} ; } 2>&1 | grep real | awk '{print $2}' )
        # echo "PA2Judge: Runtime: ${runtime}."
        ./PA2JudgeChecker ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} $i
        status=$?
        if [ $status -eq 0 ]; then
            echo -e "${GREEN}PA2Judge: ${Tese_case_names[$i]}: Accepted.${RESET}"
        else
            echo -e "${RED}PA2Judge: ${Tese_case_names[$i]}: Wrong Answer.${RESET}"
        fi
    done

    rm -rf ./testout/
    rm -f ./inputs/P*.in
    exit 0
fi

if [ $1 -ge 5 ] && [ $1 -le 9 ]; then
    ./PA2TestDataGenerator
fi
if [ $1 -ge 10 ]; then
    ./PA2TestDataGeneratorNeo
fi

echo -e "${YELLOW}PA2Judge: ${Tese_case_names[$1]}: Running...${RESET}"
# output=$( /usr/bin/time -v timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$i]} ./testout/${Tese_case_outputs[$i]} 2>&1 )
# real_time=$(echo "$output" | grep "Elapsed (wall clock) time" | awk -F': ' '{print $2}' | awk '{print $1}')
# peak_memory_kb=$(echo "$output" | grep "Maximum resident set size" | awk '{print $6}')
# peak_memory_gb=$(echo "scale=3; $peak_memory_kb / 1024 / 1024" | bc)
# echo "PA2Judge: Runtime: ${real_time}. Peak Memory: ${peak_memory_gb}GB" | tee -a results.txt
runtime=$( { time timeout $TIME_LIMIT ./bin/mps ./inputs/${Tese_case_inputs[$1]} ./testout/${Tese_case_outputs[$1]} ; } 2>&1 | grep real | awk '{print $2}' )
echo "PA2Judge: Runtime: ${runtime}."
./PA2JudgeChecker ./inputs/${Tese_case_inputs[$1]} ./testout/${Tese_case_outputs[$1]} $1
status=$?
if [ $status -eq 0 ]; then
    echo -e "${GREEN}PA2Judge: ${Tese_case_names[$1]}: Accepted.${RESET}"
else
    echo -e "${RED}PA2Judge: ${Tese_case_names[$1]}: Wrong Answer.${RESET}"
fi

rm -rf ./testout/
if [ $1 -ge 5 ]; then
    rm -f ./inputs/P*.in
fi
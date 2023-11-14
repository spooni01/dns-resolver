#!/bin/bash
root_dir="tests"
sub_dir="spec"
counterError=0
counterTest=0
numOfTests=2

# Print first text
echo -e "\n************************"
echo -e "*      TESTS START     *"
echo -e "************************"

#
# Do tests
#
for (( i=0; i<$numOfTests; i++ )); do
    counterTest=$((counterTest + 1))
    read -r args < $root_dir/$sub_dir/$counterTest.in

    # Using the variables in the paths
    ./bin/dns $args > "$root_dir/$sub_dir/$counterTest.programOut"
    result=$(diff -b "$root_dir/$sub_dir/$counterTest.expectedOut" "$root_dir/$sub_dir/$counterTest.programOut")

    if [ -n "$result" ]; then
        echo -e "[ \033[0;31mERR\033[0m ] TEST $counterTest: Unxpected result"
        echo "$result\n"
        counterError=$((counterError + 1))
    else
        echo -e "[ \033[0;32mOK\033[0m ] TEST $counterTest: Correct result"
    fi
done

#
# Print results
#
if [ "$counterError" -eq 0 ]; then
    echo -e "\n\033[0;32mALL TESTS PASSES ($numOfTests/$numOfTests)\033[0m\n"
    exit 0
else
    success=$((numOfTests - counterError))
    echo -e "\n\n\033[0;31mERRORS IN RESULTS ($success/$numOfTests)\033[0m\n"
    exit 1
fi

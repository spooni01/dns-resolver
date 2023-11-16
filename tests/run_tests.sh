#!/bin/bash
numOfTests_A=2
numOfTests_AAAA=2
numOfTests_errors=4

numOfTests=$((numOfTests_A + numOfTests_AAAA + numOfTests_errors))
root_dir="tests"
counterError=0

# Print first text
echo -e "\n************************"
echo -e "*      TESTS START     *"
echo -e "************************"

#
# Do tests `A`
#
echo -e "*****   BASIC TESTS: A   *****"
sub_dir="tests_A"
for (( i=1; i<=$numOfTests_A; i++ )); do
    read -r args < $root_dir/$sub_dir/$i.in

    # Using the variables in the paths
    ./dns $args > "$root_dir/$sub_dir/$i.programOut"
    result=$(diff -b "$root_dir/$sub_dir/$i.expectedOut" "$root_dir/$sub_dir/$i.programOut")

    if [ -n "$result" ]; then
        echo -e "[ \033[0;31mERR\033[0m ] TEST $i: Unxpected result"
        echo "$result\n"
        counterError=$((counterError + 1))
    else
        echo -e "[ \033[0;32mOK\033[0m ] TEST $i: Correct result"
    fi
done

#
# Do tests `AAAA`
#
echo -e "\n****   BASIC TESTS: AAAA  ****"
sub_dir="tests_AAAA"
for (( i=1; i<=$numOfTests_AAAA; i++ )); do
    read -r args < $root_dir/$sub_dir/$i.in

    # Using the variables in the paths
    ./dns $args > "$root_dir/$sub_dir/$i.programOut"
    result=$(diff -b "$root_dir/$sub_dir/$i.expectedOut" "$root_dir/$sub_dir/$i.programOut")

    if [ -n "$result" ]; then
        echo -e "[ \033[0;31mERR\033[0m ] TEST $i: Unxpected result"
        echo "$result\n"
        counterError=$((counterError + 1))
    else
        echo -e "[ \033[0;32mOK\033[0m ] TEST $i: Correct result"
    fi
done

#
# Do tests `AAAA`
#
echo -e "\n****   ERROR TESTS   ****"
sub_dir="tests_errors"
for (( i=1; i<=$numOfTests_errors; i++ )); do
    read -r args < $root_dir/$sub_dir/$i.in

    # Using the variables in the paths
    ./dns $args > "$root_dir/$sub_dir/$i.programOut"
    result=$(diff -b "$root_dir/$sub_dir/$i.expectedOut" "$root_dir/$sub_dir/$i.programOut")

    if [ -n "$result" ]; then
        echo -e "[ \033[0;31mERR\033[0m ] TEST $i: Unxpected result"
        echo "$result\n"
        counterError=$((counterError + 1))
    else
        echo -e "[ \033[0;32mOK\033[0m ] TEST $i: Correct result"
    fi
done

#
# Print results
#
if [ "$counterError" -eq 0 ]; then
    echo -e "\033[0;32mALL TESTS PASSES ($numOfTests/$numOfTests)\033[0m\n"
    exit 0
else
    success=$((numOfTests - counterError))
    echo -e "\033[0;31mERRORS IN RESULTS ($success/$numOfTests)\033[0m\n"
    exit 60
fi

#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"VAR test_case_cat.txt"
)

declare -a extra=(
    "-s test_1_cat.txt"
    "-b -e -n -s -t -v test_1_cat.txt"
    "-t test_3_cat.txt"
    "-n test_3_cat.txt"
    "-n test_2_cat.txt"
    "no_file.txt"
    "-n -b test_1_cat.txt"
    "-s -n -e test_4_cat.txt"
    "-s -n -e test_5_cat.txt"
    "test_1_cat.txt -n"
    "-n test_1_cat.txt"
    "-n test_1_cat.txt test_2_cat.txt test_3_cat.txt"
    "-v test_5_cat.txt"
)

testing() {
    t=$(echo $@ | sed "s/VAR/$var/")
    ./my_cat $t > cat_test.log
    cat $t > cat_test_sys.log
    DIFF_RES="$(diff -s cat_test.log cat_test_sys.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files cat_test.log and cat_test_sys.log are identical" ]

    then 
        (( SUCCESS++ ))
            echo 
                "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033
                [0m/$COUNTER \033[32msuccess\033[0m cat $t"
    else 
        (( FAIL++ ))
            echo 
                "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033
                [0m/$COUNTER \033[31mfail\033[0m cat $t"
    fi 
    rm cat_test.log cat_test_sys.log                        
}

# specific tests

for i in "${extra[@]}"
do
    var="-"
    testing $i
done 

# first parameter 
for var1 in b e n s t v
do 
    for i in "${tests[@]}"
    do 
        var="-$var1"
        testing $i
    done
done

# second parameter
for var1 in b e n s t v 
do 
    for var2 in b e n s t v 
    do 
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do 
                var="-$var1 -$var2"
                testing $i
            done 
        fi
    done
done

# third parameter
for var1 in b e n s t v
do
    for var2 in b e n s t v
    do 
        for var3 in b e n s t v
        do 
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && 
            [ $var3 != $var1 ]
            then 
                for i in "${tests[@]}"
                do 
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# fourth paremeter 
for var1 in b e n s t v 
do
    for var2 in b e n s t v 
    do
        for var3 in b e n s t v 
        do 
            for var4 in b e n s t v
            do
                if [ $var1 != $var2 ] && [ $var != $var3 ] && [ $var1 != $var4 ] && 
                [ $var2 != $var3 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do 
                        var="-$var1 -$var2 -$var3 -$var4"
                        testint $i 
                    done
                fi
            done
        done
    done
done

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
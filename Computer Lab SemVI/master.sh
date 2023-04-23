#!/bin/bash

#no spaces around = operator
# name="Husain"

# printf "Hello, %s\n" "$name"

# if pwd
# then 
#     echo "It Workes"
# fi

# file="states"

# for state in $(cat $file)
# do
#     echo "Visit beautiful $state"
# done

#for file in /home/rich/test/*
#find . -type f -newermt 2007-06-07 ! -newermt 2007-06-08
#cp /path/to/source/foo.txt /path/to/target/folder/
#echo "${array[0]}"

# $files=$(find -type f)
for file in $(find -type f)
do
    month=$(date -r $file "+%b")
    echo "$month"
    
done
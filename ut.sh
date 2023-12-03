#!/bin/bash

# go to the cpp files dir
dir=$1
cd ${dir}

ut_file_ext="ut.exe"

files=(*.cpp)
for file in "${files[@]}"
do
    if [ "${file}" != "main.cpp" ]; then
        ut_file="${file}.${ut_file_ext}"

        g++ ${file} -o "${ut_file}"
        chmod 755 "${ut_file}"
        
        "./${file}.${ut_file_ext}"
        
        rm -f "${ut_file}"
    fi
done

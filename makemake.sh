#! /bin/bash
# Christopher Chen (997549548) , Wai Shing Yung (996936848)

num=$#
name=$1
shift
options=$@
if [[ "$num" -lt 1 ]]; then
        echo Executable name required.
        echo usage: makemake.sh executable_name

else
        echo -n $name :" "> Makefile #line 1
        for filename in *.cpp; do
                echo -e -n ${filename%.cpp}.o" " >> Makefile
        done #line 1
        echo -e -n "\n"'\t'g++ -ansi -Wall -g -o $name $options" ">> Makefile #line 2
        for filename in *.cpp ; do
                echo -e -n ${filename%.cpp}.o" " >> Makefile
        done #line 2
        echo >> Makefile
        for filename in *.cpp ; do
                echo -e -n "\n"${filename%.cpp}.o :" "$filename" " >> Makefile
                awk '/#include \".*\"/ {print}' $filename | sed 's/#include "//g' | sed 's/"//g' | tr '\n' ' '   >>Makefile
                echo -e  "\n""\t"g++ -ansi -Wall -g -c $options" "$filename >>Makefile
        
        done
        echo -e "\n"clean: >>Makefile
        echo -e -n "\t"rm -f $name" ">> Makefile
for filename in *.cpp ; do
    echo -e -n ${filename%.cpp}.o" ">>Makefile
done
fi

#!/usr/bin/env bash

g++ -std=c++17 -Werror -Wall -g *.cpp -o Lab3

for i in {1..10}; do
	if [ $i -lt '5' ]; then
		./Lab3 in3.txt query${i}
	elif [ $i -lt '6' ]; then
		./Lab3 in3.txt rename
	elif [ $i -lt '7' ]; then
		./Lab3 in3.txt project
	elif [ $i -lt '8' ]; then
		./Lab3 in3.txt select1-1
	elif [ $i -lt '9' ]; then
		./Lab3 in3.txt select1-2
	elif [ $i -lt '10' ]; then
		./Lab3 in3.txt select2-1
	else
		./Lab3 in3.txt select2-2
	fi
done

rm Lab3
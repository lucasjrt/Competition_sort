#!/bin/bash

java Generator $1 $2 > input.txt
(cat input.txt | ./special_sort) > output.txt
(cat input.txt | sort -g) > result.txt
cmp output.txt result.txt

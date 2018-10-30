#!/bin/bash

count=0
charCount="^$2"

for ((count=1; count<$3; count++))
do
     dot="."
	 charCount="$charCount$dot"
done
charCount="$charCount$"
echo "ls $1 | grep $charCount | wc -w"

ls $1 | grep $charCount | wc -w

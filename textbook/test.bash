#!/bin/bash

for file in `ls *.$1`; do 
	if [[ -f $file && `more $file | wc -c` -gt $2 ]]; then
		echo $file
	fi
done

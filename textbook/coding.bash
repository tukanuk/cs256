#!/bin/bash

for file in `ls *.$1` ; do
	if [[ `more $file | wc -c` -gt $2 ]]; then
		echo $file
	fi
done


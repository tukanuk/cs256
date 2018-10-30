#!/bin/bash

# run to create sample files
# use -r to remove the created files

delete="-r"
if [ $1 = $delete ]; then
	rm *.doc
	rm *.txt
	rm *.ppt
else
	for (( i=0; i<20; i++ ))
	do
		>> test$i.doc
		>> test$i.txt
		>> test$i.ppt
	done
fi



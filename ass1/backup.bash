#!/bin/bash

# use testfiles.bash to create test files
 
args=$*
datestamp=$(date | tr -d ' ' | tr -d ':')
tFlag="-t"
backupTypes=""

echo "The date stamp is $datestamp"
echo "Arg count: $#"
echo "The args are: ${args[@]}"

if [ $1 == $tFlag ]; then
	target_directory=($2)
	mkdir $target_directory
else 
	target_directory="."
fi

echo "The target is $target_directory"


if [ $# -lt 2 ]; then 
	echo "Usage: $0 [-t] <target-directory> <suffix-list...>"
fi

for ext in $args
do
	if [[ $ext != $tFlag && $ext != $target_directory ]]; then
		backupTypes+="*.$ext "
	fi
done

echo "backup types: ${backupTypes[*]}"

target_directory=$target_directory/$datestamp
mkdir -p $target_directory
echo the final TD is: $target_directory

for ext in ${backupTypes[*]}
do
	cp ${ext} $target_directory
	echo Copied "$ext" files to $target_directory
done


cd $target_directory && tar -cf ~/archive.tar .
cd ..
mv ~/archive.tar $target_directory


for ext in ${backupTypes[*]}
do
	rm $target_directory/$ext
done

echo Source files deleted


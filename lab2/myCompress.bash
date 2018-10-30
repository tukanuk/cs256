#!/bin/bash
types="" # args
ext=""   # ext to tar
for types in $*
do
	echo $types
	ext="$ext *.$types"
done

echo "$ext"
echo $types

echo tar -cf backup.tar "$ext" # to supress pathname expansion
tar -cf backup.tar $ext 

#done

 #!/bin/bash
  V=0
  for file in ‘ls‘ ; do
    if [[ -f $file && `more $file | wc -c` > $V ]]; then
       V=`more $file | wc -c`
       N=$file
fi done
echo $N $V


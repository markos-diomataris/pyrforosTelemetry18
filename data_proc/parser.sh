#!/bin/bash
if [[ $# -ne 1 ]]; then
  echo "give data log file"
  exit 1
fi
pat='.*,.*'
c1=0
c2=0
# 0.01785714
# remove first line (garbage), Carage Returns and keep only
# measurements and possible GPS data
sed '1d' < $1 |
sed 's/\r$//' |
grep -o ',A,[^,]*,N,[^,]*,W\|m:[0-9]*' |
sed 's/m://g' |
sed 's/,A,//g' |
sed 's/,N,/ , /g' |
sed 's/,W//g'| {
  while read line; do
  if [[ $line =~ $pat ]]; then
    c1=`echo $line | sed 's/,.*//g'`
    c2=`echo $line | sed 's/[^,]*,//g'`
    c1=`./convertcoord $c1`
    c2=`./convertcoord $c2`
  else
    echo "$c1 , $c2 , $line"
  fi
  done
}

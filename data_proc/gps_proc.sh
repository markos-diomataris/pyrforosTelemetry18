#!/bin/bash
rm $1
while read line; do
c1=`echo $line | sed 's/,.*//g'`
c2=`echo $line | sed 's/[^,]*,//g'`
c1=`./convertcoord $c1`
c2=`./convertcoord $c2`
echo "$c1 , $c2" >> $1
done

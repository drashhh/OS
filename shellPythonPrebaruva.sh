#!/bin/bash
if [ $# -ge 2 ]
then 
x = `echo $1 | grep py3$`
if [ -n "$x" ]
then 
    skripta = $1
    shift
else 
    skripta = "prva.py3"
fi
zbor = $1 
shift
y = `find . -name $skripta`
if [ -n "$y" ]
then 
    vkupno=0
    for d in $@
    do 
    k='$skripta $zbor f $d'
    vkupno='expr $vkupno \+ $k'
done
echo $vkupno

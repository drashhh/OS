#!/bin/bash
ls | grep *.crypto$
X = find /-name *.crypto
if[-n "$X"]
then
    for dat in $x
    do
    Y = cat $dat | grep -e

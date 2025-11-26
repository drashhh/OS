#!/usr/bin/python3
import sys

if len(sys.argv) < 4:
    print("Nemas dovolno argumenti vneseno\n")
    print("Mora da se povika so prva.py (zbor) (zname) (fajl)\n")
    exit(1)

if len(sys.argv) > 4:
    print("Imas premnogu argumenti\n")
    exit(1)

zbor = sys.argv[1]
zname = sys.argv[2]
fajl = sys.argv[3]

if zname != 'f' and zname != 'l' and zname != 'w':
    print("Greska vneseno zname poddrzuva (f, l, w)\n")
    exit(1)

f = open(fajl, "r")
for linii in f:
    f.readline()

if zname == "l":
    for l in linii:
        print(l)
        zborPojavuvanje = l.find(zbor)
        if zborPojavuvanje != -1:
            print("Go ima zborot vo linijata\n")
            print("Gi ima slednive broevi > ")
            for word in l.split():
                if word.isdigit():
                    print(word)


f.close()



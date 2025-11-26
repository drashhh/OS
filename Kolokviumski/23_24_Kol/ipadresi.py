#!/usr/bin/python3
import sys

f = open(sys.argv[1])
fajl = f.read()
f.close()

linii = fajl.splitlines()

print("Cel fajl > "+fajl)
print("Linija po linija")
# for l in linii:
#     print(l)

for i, linija in enumerate(linii):
    for zbor in linija.split(): #zbor po zbor
        moznaip = zbor.split(".")
        if len(moznaip) == 4:
            print(moznaip)
            # moznaipstr = map(str, moznaip)
            # ip = ".".join(moznaipstr)
            # print(ip)
            ip = [str(i) for i in moznaip]
            a = ip[0]
            b = ip[1]
            c = ip[2]
            d = ip[3]
            for a in range(int(a), 256):
                for b in range(int(b), 256):
                    for c in range(int(c), 256):
                        for d in range(int(d), 256):
                            print(a, b, c, d, sep=".")
                        d = 0
                    c = 0
                b = 0
            a = 0





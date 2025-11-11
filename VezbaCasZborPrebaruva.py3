import sys

if len(sys.argv) < 3: 
    print("Nepravilno povikuvanje!")
    quit()

zbor = sys.argv[1]
zname = sys.argv[2]
imedatoteka = sys.argv[3]
if zname != "l" and zname != "w" and zname != "f":
    print("Nevalidno zname!")
    quit()

brZ = 0
linija = 1
kolku = 0
dat = open(imedatoteka, "r")
lines = dat.readlines()
for l in lines:
    words = l.split(" ")
    for w in words:
        if w == zbor:
            kolku = kolku + 1
            if zname == "l":
                print(linija)
                break
            elif zname == "w":
                print(brZ)
        brZ = brZ + 1
    linija = linija + 1 
if zname == "f":
    print(kolku)
elif kolku == 0:
    if zname == "l":
        print(-1)
    else:
        print(0)
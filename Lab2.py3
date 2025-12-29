import sys
if(len(sys.argv) < 2):
    print("Ne pravilno povikuvanje, potrebni se barem 2 argumenti")
    quit()

godina = "2025"
mesec = "11"
if(len(sys.argv) >= 3):
    imedatoteka = sys.argv[1]
    datum = sys.argv[2]

    #YYYY-MM-DD
    godina = datum[0:3]
    mesec = datum[5:6]
    den = datum[8:9]


d = open(imedatoteka, "r")
red = d.readline()
while True:
    red = d.readline()
    if not red:
        break
    datumFajl = red.split()
    #print(datumFajl[-4])
    godinaFajl = int(datumFajl[-4][0:3])
    godinaUser = int(godina)
    mesecFajl= int(datumFajl[-4][5:6])
    mesecUser = int(mesec)
    denFajl = int(datumFajl[-4][8:9])
    denUser = int(den)
    if(godinaFajl >= godinaUser):
        print(red)


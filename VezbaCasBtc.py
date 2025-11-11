import sys

if len(sys.argv) < 2:
    print("Nedovolno argumenti!")
    sys.exit()

dat = open(sys.argv[1], "r")
pole = dat.read().split(" ")
kripto = ["ETH", "BTC", "Doge", "EOS", "XPM"]
kriptoAll = {"ETH":[], "BTC":[],
            "DOGE":[], "EOS":[], "XPM":[]}
for i in range(len(pole)):
    if pole[i] in kripto:
        vrednost = float(pole[i+1][1:])
        kriptoAll[pole[i]].append(vrednost)

for k in kriptoAll.keys():
    maxUP = 0
    maxUPi = -1
    maxDown = 0
    maxDowni = -1
    if len(kriptoAll[k]) > 1:
        for i in range(len(kriptoAll[k])-1):
            razlika = kriptoAll[k][i+1] - kriptoAll[k][i]
            if razlika > 0 and razlika > maxUP:
                maxUP = razlika
                maxUPi = i
            elif razlika < 0 and razlika*(-1) > maxDown:
                maxDown = razlika*(-1)
                maxDowni = i

    if maxUP == 0:
        print(k + " najgolemo pokacuvanje 0")
    else:
        print(k + " najgolemo pokacuvanje " + str(maxUP) + " pomegu " + str(kriptoAll[k][maxUPi] + " i " + str(kriptoAll[k][maxUPi + 1])))

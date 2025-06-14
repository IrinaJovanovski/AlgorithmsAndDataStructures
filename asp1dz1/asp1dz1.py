import time
#LKG
def brojevi(num):
    a = 429493445
    c = 907633385
    m = 4294967296 #2^32
    num = a*num + c
    num = num % m
    return num,m
def konverzija(num):
    num,m = brojevi(num)
    br = num / m
    if (br < 0.5):
        x = 0
    else:
        x = 1
    return x,num

#kockica i bacanje

def kocka(num):
    binary = 0
    x,num = konverzija(num)
    binary += x
    x,num = konverzija(num)
    binary += x * 2
    x,num = konverzija(num)
    binary += x * 4
    binary += 1
    return binary,num
def bacanje(s):
    cube = []
    num = time.time()  # seed
    for a in range(s):
        binary,num = kocka(num)
        while (binary > 6):
            binary,num = kocka(num)
        cube.append(binary)
    return cube

# konverzija matrice

def conversion(retkaMatrica):
    columns = retkaMatrica[0]
    first = retkaMatrica[0][1]
    second = retkaMatrica[0][2]
    third = retkaMatrica[0][3]
    rows = retkaMatrica[1]
    values = retkaMatrica[2]
    prvi = rows[0:first]
    valOne = values[0:first]
    drugi = rows[first:second]
    valTwo = values[first:second]
    treci = rows[second:third]
    valThree = values[second:third]

    nova = [[],[],[]]
    for t in range(3):
        lis = nova[t]
        for x in range(10):
            lis.append(x)
    row = []
    value = []
    for col in range(3):
        if col == 0:
            row = prvi
            value = valOne
        elif col == 1:
            row = drugi
            value = valTwo
        elif col == 2:
            row = treci
            value = valThree
        for j in range(1,11):
            if j in row:
                r = j - 1
                ind = row.index(j)
                nova[col][r] = value[ind]
            else:
                r = j - 1
                nova[col][r] = '/'
    return retkaMatrica

#polja redova

def prazno(retkaMatrica):
    ist = True
    return ist
def precrtavanje(retkaMatrica):
    ist = prazno(retkaMatrica)
    # if True then vrednost polja == 0
    return 0
def numbers(cuvanje,mesto):
    print("Da li zelite da precrtate polje\n"
          '1. Da\n'
          '2. Ne\n')
    w = int(input())
    if w == 1:
        suma = precrtavanje(retkaMatrica)
        return suma
    if mesto == 1:
        suma = sum(cuvanje)
        return suma
    if mesto == 2:
        suma = sum(cuvanje)
        return suma
    if mesto == 3:
        suma = sum(cuvanje)
        return suma
    if mesto == 4:
        suma = sum(cuvanje)
        return suma
    if mesto == 5:
        suma = sum(cuvanje)
        return suma
    if mesto == 6:
        suma = sum(cuvanje)
        return suma
def kenta(throw,retkaMatrica):
    print("Da li zelite da precrtate polje\n"
          '1. Da\n'
          '2. Ne\n')
    w = int(input())
    if w == 1:
        suma = precrtavanje(retkaMatrica)
        return suma
    if throw == 1:
        suma = 66
        return suma
    elif throw == 2:
        suma = 56
        return suma
    elif throw == 3:
        suma = 46
        return suma
def ful(cuvanje,retkaMatrica):
    print("Da li zelite da precrtate polje\n"
          '1. Da\n'
          '2. Ne\n')
    w = int(input())
    if w == 1:
        suma = precrtavanje(retkaMatrica)
        return suma
    suma = 30 + sum(cuvanje)
    return suma
def poker(cuvanje,retkaMatrica):
    print("Da li zelite da precrtate polje\n"
          '1. Da\n'
          '2. Ne\n')
    w = int(input())
    if w == 1:
        suma = precrtavanje(retkaMatrica)
        return suma
    suma = 40 + sum(cuvanje)
    return suma
def jamb(cuvanje,retkaMatrica):
    print("Da li zelite da precrtate polje\n"
          '1. Da\n'
          '2. Ne\n')
    w = int(input())
    if w == 1:
        suma = precrtavanje(retkaMatrica)
        return suma
    suma = 50 + sum(cuvanje)
    return suma

#polja kolone

def gore(cuvanje,throw,retkaMatrica,place):
    p = 0
    for el in retkaMatrica:
        for e in el:
            p += 1
    if place[1] == 1 or place[1] == 2 or place[1] == 3 or place[1] == 4 or place[1] == 5 or place[1] == 6:
        print("Popunjavate red ", place[1])
        suma = numbers(cuvanje,place[1])
        if p>=44:
            retkaMatrica[place[1]][2] = suma
        else:
            indeks = retkaMatrica[0][1] - retkaMatrica[0][0]
            indeks += retkaMatrica[0][2] - retkaMatrica[0][1]
            retkaMatrica[1].insert(indeks, place[1])
            retkaMatrica[2].insert(indeks, suma)
            retkaMatrica[0][2] += 1
            retkaMatrica[0][3] += 1
        place[1] -= 1
        return
    elif place[1] == 7:
        print("Popunjavate red kenta")
        suma = kenta(throw, retkaMatrica)
        if p>=44:
            retkaMatrica[place[1]][2] = suma
        else:
            indeks = retkaMatrica[0][1] - retkaMatrica[0][0]
            indeks += retkaMatrica[0][2] - retkaMatrica[0][1]
            retkaMatrica[1].insert(indeks, place[1])
            retkaMatrica[2].insert(indeks, suma)
            retkaMatrica[0][2] += 1
            retkaMatrica[0][3] += 1
        place[1] -= 1
        return
    elif place[1] == 8:
        print("Popunjavate red ful")
        suma = ful(cuvanje, retkaMatrica)
        if p>=44:
            retkaMatrica[place[1]][2] = suma
        else:
            indeks = retkaMatrica[0][1] - retkaMatrica[0][0]
            indeks += retkaMatrica[0][2] - retkaMatrica[0][1]
            retkaMatrica[1].insert(indeks, place[1])
            retkaMatrica[2].insert(indeks, suma)
            retkaMatrica[0][2] += 1
            retkaMatrica[0][3] += 1
        place[1] -= 1
        return
    elif place[1] == 9:
        print("Popunjavate red poker")
        suma = poker(cuvanje, retkaMatrica)
        if p>=44:
            retkaMatrica[place[1]][2] = suma
        else:
            indeks = retkaMatrica[0][1] - retkaMatrica[0][0]
            indeks += retkaMatrica[0][2] - retkaMatrica[0][1]
            retkaMatrica[1].insert(indeks, place[1])
            retkaMatrica[2].insert(indeks, suma)
            retkaMatrica[0][2] += 1
            retkaMatrica[0][3] += 1
        place[1] -= 1
        return
    elif place[1] == 10:
        print("Popunjavate red jamb")
        suma = jamb(cuvanje, retkaMatrica)
        if p>=44:
            retkaMatrica[place[1]][2] = suma
        else:
            indeks = retkaMatrica[0][1] - retkaMatrica[0][0]
            indeks += retkaMatrica[0][2] - retkaMatrica[0][1]
            retkaMatrica[1].insert(indeks, place[1])
            retkaMatrica[2].insert(indeks, suma)
            retkaMatrica[0][2] += 1
            retkaMatrica[0][3] += 1
        place[1] -= 1
        return
def dole(cuvanje,throw,retkaMatrica,place):
    p = 0
    for el in retkaMatrica:
        for e in el:
            p += 1
    if place[0] == 1 or place[0] == 2 or place[0] == 3 or place[0] == 4 or place[0] == 5 or place[0] == 6:
        print("Popunjavate red ",place[0])
        suma = numbers(cuvanje,place[0])
        if p>=44:
            retkaMatrica[place[0]][1] = suma
        else:
            retkaMatrica[0][1] += 1
            retkaMatrica[0][2] += 1
            retkaMatrica[1].insert(0,place[0])
            retkaMatrica[2].insert(0,suma)
            retkaMatrica[0][3] += 1
        place[0] += 1
        return
    elif place[0] == 7:
        print("Popunjavate red kenta")
        suma = kenta(throw,retkaMatrica)
        if p>=44:
            retkaMatrica[place[0]][1] = suma
        else:
            retkaMatrica[0][1] += 1
            retkaMatrica[0][2] += 1
            retkaMatrica[1].insert(0, place[0])
            retkaMatrica[2].insert(0, suma)
            retkaMatrica[0][3] += 1
        place[0] += 1
        return
    elif place[0] == 8:
        print("Popunjavate red ful")
        suma = ful(cuvanje,retkaMatrica)
        if p>=44:
            retkaMatrica[place[0]][1] = suma
        else:
            retkaMatrica[0][1] += 1
            retkaMatrica[0][2] += 1
            retkaMatrica[1].insert(0, place[0])
            retkaMatrica[2].insert(0, suma)
            retkaMatrica[0][3] += 1
        place[0] += 1
        return
    elif place[0] == 9:
        print("Popunjavate red poker")
        suma = poker(cuvanje,retkaMatrica)
        if p>=44:
            retkaMatrica[place[0]][1] = suma
        else:
            retkaMatrica[0][1] += 1
            retkaMatrica[0][2] += 1
            retkaMatrica[1].insert(0, place[0])
            retkaMatrica[2].insert(0, suma)
            retkaMatrica[0][3] += 1
        place[0] += 1
        return
    elif place[0] == 10:
        print("Popunjavate red jamb")
        suma = jamb(cuvanje,retkaMatrica)
        if p>=44:
            retkaMatrica[place[0]][1] = suma
        else:
            retkaMatrica[0][1] += 1
            retkaMatrica[0][2] += 1
            retkaMatrica[1].insert(0, place[0])
            retkaMatrica[2].insert(0, suma)
            retkaMatrica[0][3] += 1
        place[0] += 1
        return
def rucna(cuvanje,throw,retkaMatrica,R):
    R.append(1)
    print("Upis:")
    str = "1. 1,2,3,4,5,6"
    if 1 in popunjena:
        str = str.replace('1,','')
    if 2 in popunjena:
        str = str.replace('2,', '')
    if 3 in popunjena:
        str = str.replace('3,', '')
    if 4 in popunjena:
        str = str.replace('4,', '')
    if 5 in popunjena:
        str = str.replace('5,', '')
    if 6 in popunjena:
        str = str.replace('6', '')
    print(str)
    if 7 not in popunjena:
        print("2. Kenta 66 56 46")
    if 8 not in popunjena:
        print("3. Ful 30")
    if 9 not in popunjena:
        print("4. Poker 40")
    if 10 not in popunjena:
        print("5. Jamb 50")
    q = int(input())
    p = 0
    for el in retkaMatrica:
        for e in el:
            p += 1
    # cuvati print kao listu i
    if q == 1:
        mesto = cuvanje[0]
        popunjena.append(mesto)
        suma = numbers(cuvanje,mesto)
        if p >= 44:
            retkaMatrica[mesto][3] = suma
        else:
            retkaMatrica[1].append(mesto)
            retkaMatrica[2].append(suma)
            retkaMatrica[0][3] += 1
        return
    elif q == 2:
        mesto = 7
        popunjena.append(mesto)
        suma = kenta(throw, retkaMatrica)
        if p >= 44:
            retkaMatrica[mesto][3] = suma
        else:
            retkaMatrica[1].append(mesto)
            retkaMatrica[2].append(suma)
            retkaMatrica[0][3] += 1
        return
    elif q == 3:
        mesto = 8
        popunjena.append(mesto)
        suma = ful(cuvanje, retkaMatrica)
        if p >= 44:
            retkaMatrica[mesto][3] = suma
        else:
            retkaMatrica[1].append(mesto)
            retkaMatrica[2].append(suma)
            retkaMatrica[0][3] += 1
        return
    elif q == 4:
        mesto = 9
        popunjena.append(mesto)
        suma = poker(cuvanje, retkaMatrica)
        if p >= 44:
            retkaMatrica[mesto][3] = suma
        else:
            retkaMatrica[1].append(mesto)
            retkaMatrica[2].append(suma)
            retkaMatrica[0][3] += 1
        return
    elif q == 5:
        mesto = 10
        popunjena.append(mesto)
        suma = jamb(cuvanje, retkaMatrica)
        if p >= 44:
            retkaMatrica[mesto][3] = suma
        else:
            retkaMatrica[1].append(mesto)
            retkaMatrica[2].append(suma)
            retkaMatrica[0][3] += 1
        return

#potez za polje

def sacuvani(cuvanje,s,bac):
    print("Unesite redne brojeve kockica koje zelite da sacuvate (odvojiti brojeve space-om):\n")
    b = input()
    if b == '':
        return cuvanje,s
    else:
        b = b.split(' ')
        for el in b:
            e = int(el)
            s -= 1
            cuvanje.append(bac[e - 1])
        print(cuvanje)
    return cuvanje,s
def potez(retkaMatrica,place,R):
    s = 5
    bac = bacanje(s)
    print(bac)
    cuvanje = []
    cuvanje,s = sacuvani(cuvanje,s,bac)
    throw = 1
    sumR = sum(R)
    print("Da li zelite da upisete rezultat?:")
    if sumR<10:
        print("1. Da, u kolonu rucna")
    if place[0]<= 10 or place[1]>=1:
        print("2. Da, na gore/na dole")
    print("3. Ne")
    c = int(input())
    if c == 1:
        popunjena = rucna(cuvanje,throw,retkaMatrica,R)
    elif c == 2:
        print("Upis:")
        if place[0] <= 10:
            print("1. Na dole")
        if place[1] >= 1:
            print("2. Na gore")
        con = int(input())
        if con == 1:
            dole(cuvanje, throw, retkaMatrica, place)
        elif con == 2:
            gore(cuvanje, throw, retkaMatrica, place)
    else:
        for i in range(2):
            if i > 0:
                print("Da li zelite da upisete rezultat?:\n"
                      "1. Da (na gore / na dole)\n"
                      "2. Ne\n")
                c = int(input())
                if c == 1 or len(cuvanje) == 5:
                    break
            bac = bacanje(s)
            print(bac)
            cuvanje,s = sacuvani(cuvanje,s,bac)
            throw += 1
        print(cuvanje)
        print("Upis:")
        if place[0] <= 10:
            print("1. Na dole")
        if place[1] >= 1:
            print("2. Na gore")
        p = int(input())
        if p == 1:
            dole(cuvanje,throw,retkaMatrica,place)
        elif p == 2:
            gore(cuvanje, throw,retkaMatrica,place)
    return

#finalna suma

def sumaUkupna(retkaMatrica):
    p = 0
    for el in retkaMatrica:
        for e in el:
            p += 1
    if p>=44:
        zbir = 0
        for i in range(11):
            for j in range(4):
                if i == 0 or j == 0:
                    continue
                if retkaMatrica[i][j] != '/':
                    zbir += retkaMatrica[i][j]
    else:
        zbir = sum(retkaMatrica[2])
    return zbir
retkaMatrica = [[0,0,0,0],[],[]]
# C = retkaMatrica[0]
# R = retkaMatrica[1]
# V = retkaMatrica[2]
talon = []
place=[1,10]
#      d,g
popunjena = []
R = []
# meni

while True:
    su = sum(R)
    if place[0] == 10 and place[1] == 1 and su == 10:
        break
    beta = 0
    for es in retkaMatrica:
        for ese in es:
            beta += 1
    if beta >= 44:
        retkaMatrica = conversion(retkaMatrica)
    print("------MENI-----\n"
          "Izaberite opciju:\n"
          "1. Kreiranje praznog talona\n"
          "2. Baci kockice\n"
          "3. Ispisi trenutno stanje talona\n"
          "4. Pomoc prijatelja\n"
          "5. Kraj programa\n")

    try:
        u = int(input())
        if u < 1 or u > 5:
            print("Unesite ispravnu opciju\n")
            continue
    except:
        print("Unesite broj kao opciju\n")
        continue
    if u == 1:
        talon = [['     JAMB     ', '↓', '↑', 'Rucna'],
                 ['      1       ', '/', '/', '/'],
                 ['      2       ', '/', '/', '/'],
                 ['      3       ', '/', '/', '/'],
                 ['      4       ', '/', '/', '/'],
                 ['      5       ', '/', '/', '/'],
                 ['      6       ', '/', '/', '/'],
                 ['Кента 66 56 46', '/', '/', '/'],
                 ['Фул 30        ', '/', '/', '/'],
                 ['Покер 40      ', '/', '/', '/'],
                 ['Јамб 50       ', '/', '/', '/'],]
        for line in talon:
            print(*line)
    elif u == 2:
        alpha = 0
        for eleme in retkaMatrica:
            for ele in eleme:
                alpha += 1
        if alpha >= 44:
            potez(talon,place,R)
        else:
            potez(retkaMatrica,place,R)

    elif u == 3:
        so = 0
        for el in retkaMatrica:
            for e in el:
                so += 1
        if so>=44:
            for line in talon:
                print(*line)
            print("Ukupna suma: ", sumaUkupna(talon))
            continue

        nadole = retkaMatrica[0][1]
        nagore = retkaMatrica[0][2]
        ruc = retkaMatrica[0][3]
        cn = 0
        col = 1
        row = []
        colona = 1
        for v in retkaMatrica[2]:
            red = retkaMatrica[1][cn]
            cn += 1
            if cn<=nadole:
                colona = 1
            elif cn<=nagore and cn>=nadole:
                colona = 2
            elif cn<=ruc and cn>=nagore:
                colona = 3
            if talon[red][colona] == '/':
                talon[red][colona] = v

        for line in talon:
            print(*line)
        print("Ukupna suma: ",sumaUkupna(retkaMatrica))
    elif u == 4:
        for line in retkaMatrica:
            print(*line)
        break
    elif u == 5:
        break

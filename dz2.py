import copy
class Cvor:
    def __init__(self, data, vijabilnost, parent):
        self.data = data
        self.leaf = vijabilnost
        self.children = []
        self.parent = parent
    def add_children(self, data):
        self.children.append(data)
        return
def correct(nd,positives,negatives):
    duplikati = []
    for n in range(N):
        for m in range(M):
            if nd[m][n] == 0:
                continue
            duplikati.append(nd[m][n])
    originali = set(duplikati)
    if len(originali) < len(duplikati):
        return False
    for n in range(N):
        for m in range(M):
            for neg in negatives:
                if m == (M - 1):
                    if nd[m][n] in neg:
                        if nd[0][n] in neg:
                            return False
                else:
                    if (nd[m][n] in neg) and (nd[m+1][n] in neg):
                        return False
            for pos in positives:
                if m == (M - 1):
                    if (nd[m][n] in pos) and (nd[0][n] in pos):
                        return True
                else:
                    if (nd[m][n] in pos) and (nd[m+1][n] in pos):
                        return True
    return True
def noviCvorovi(newNode,tabela,N,M,positive,negative,vijabilnost,root):
    for ini in range(M):
        temp = newNode.data
        poj = set(pojmovi[ini])
        variable = poj.difference(tabela[i])
        variable = list(variable)
        parent = newNode
        if variable == {}:
            continue
        elif len(variable) == 1:
            for j in range(N):
                if tabela[ini][j] != 0:
                    continue
                temp[ini][j] = variable[0]
                t = copy.deepcopy(temp)
                vijabilnost = correct(t, positive, negative)
                if newNode == root:
                    newNode.add_children(Cvor(t, vijabilnost, newNode))
                else:
                    newNode.add_children(Cvor(t, vijabilnost, newNode))
                temp[ini][j] = 0
        else:
            for k in range(N):
                if temp[ini][k] != 0:
                    continue
                for j in range(len(variable)):
                    temp[ini][k] = variable[j]
                    t = copy.deepcopy(temp)
                    vijabilnost = correct(t, positive, negative)
                    if newNode == root:
                        newNode.add_children(Cvor(t, vijabilnost, newNode))
                    else:
                        newNode.add_children(Cvor(t, vijabilnost, newNode))
                    temp[ini][k] = 0
    return newNode
def decaDece(newNode,N,M,positive,negative,vijabilnost,root):
    for child in newNode.children:
        tabela = child.data
        newNode = noviCvorovi(child,tabela,N,M,positive,negative,vijabilnost,root)
        if newNode.leaf:
            decaDece(newNode, N, M, positive, negative, vijabilnost,root)
    return
def stablo(tabela,N,M,positive,negative,vijabilnost):
    table = copy.deepcopy(tabela)
    root = Cvor(table,True,None)
    newNode = root
    newNode = noviCvorovi(newNode,table,N,M,positive,negative,vijabilnost,root)
    decaDece(newNode,N,M,positive,negative,vijabilnost,root)
    return root,vijabilnost
def ispisStabla(root,vijabilnost):
    stack = [root]
    if stack == [[]]:
        return
    while len(stack) > 0:
        c = stack.pop(0)
        print(c.data)
        print(c.leaf,end=', ')
        if c.parent == None:
            print('Nema roditelja')
        else:
            print(c.parent.data)
        print('\n')
        for u in range(len(c.children) - 1, -1, -1):
            stack.insert(0, c.children[u])
    return
def relations(tabela,rel,terms):
    pojmovi = set(tabela[0])
    positive = []
    negative = []
    mult = {}
    mulp = {}
    for r in rel:
        if '+' in r:
            positive.append(r)
        elif '-' in r:
            negative.append(r)
    i = 0
    for p in positive:
        positive[i] = p.split('+')
        i += 1
    i = 0
    for n in negative:
        negative[i] = n.split('-')
        i += 1
    for n in negative:
        if n[1] not in mult:
            mult[n[1]] = [n[0]]
        else:
            mult[n[1]].append(n[0])
    for p in positive:
        for z in range(M):
            if p[0] in terms[z]:
                for tab in terms[z]:
                    if tab != p[0]:
                        negative.append([tab, p[1]])
            if p[1] in terms[z]:
                for tab in terms[z]:
                    if tab != p[1]:
                        negative.append([p[0], tab])
    temp = []
    for key in mult.keys():
        if len(mult[key]) > 1:
            temp = pojmovi.difference(set(mult[key]))
            temp = list(temp)
            if len(temp) == 1:
                positive.append([temp[0],key])
    return positive, negative
def potez(tabela,root):
    if tabela == root.data:
        print(root.data)
        print("Na dobrom ste putu!")
        print("Da li zelite da vidite opcije za naredni potez?\n")
        print("1. Da\n"
              "2. Ne\n")
        p = int(input())
        if p == 1:
            for ch in root.children:
                print(ch.data,end='\t')
                print('\n')
        else:
            return
    else:
        stack = [root]
        c = stack.pop(0)
        print(c.data)
        if c.leaf:
            if c.data == tabela:
                print("Na dobrom ste putu!")
                print("Da li zelite da vidite opcije za naredni potez?\n")
                print("1. Da\n"
                      "2. Ne\n")
                p = int(input())
                if p == 1:
                    for kid in c.children:
                        print(kid.data,end='\t')
                        print('\n')
                else:
                    return
        else:
            print("Niste na dobrom putu.")
            return
        for u in range(len(c.children) - 1, -1, -1):
            stack.insert(0, c.children[u])
    return tabela
def hint(tabela,root):
    stack = [root]
    if stack == [[]]:
        return
    while len(stack) > 0:
        c = stack.pop(0)
        print(c.data)
        if c.data == tabela:
            maks = []
            for k in c.children:
                p = 0
                stack = [k]
                while len(stack) > 0:
                    p += 1
                    o = stack.pop(0)
                    for q in range(len(o.children) - 1, -1, -1):
                        stack.insert(0, o.children[q])
                maks.append(p)
            hg = max(maks)
            indeks = maks.index(hg)
            dete = c.children[indeks]
            tabela = dete.data
            return tabela
        for u in range(len(c.children) - 1, -1, -1):
            stack.insert(0, c.children[u])
    return tabela
pojmovi = []
rel = []
tabela = []
vijabilnost = True
while True:
    print("\n------MENI-----\n"
          "Izaberite opciju:\n"
          "1. Ucitaj podatke sa konzole\n"
          "2. Ucitaj podatke iz fajla\n"
          "3. Ispisi stablo\n"
          "4. Odigraj potez\n"
          "5. Ispisi trenutno stanje stabla\n"
          "6. Zavrsi igru\n")

    try:
        x = int(input())
        if x < 0 or x > 6:
            print("Unesite ispravnu opciju\n")
            continue
    except:
        print("Unesite broj kao opciju\n")
        continue

    if x == 1:
        # broj grupa - M
        M = int(input())
        # broj pojmova - N
        N = int(input())

        for i in range(M):
            pojmovi.append(input())
            pojmovi[i] = pojmovi[i].split(',')

        while True:
            el = input()
            if el != '':
                rel.append(el)
                continue
            break

        tabela.append(pojmovi[0])
        for i in range(M - 1):
            tabela.append([0]*N)
        positive, negative = relations(tabela, rel,pojmovi)
        root, vijabilnost = stablo(tabela,N,M,positive,negative,vijabilnost)

    elif x == 2:
        print("Unesite ime fajla:")
        file = input()
        with open(file, 'r+') as f:
            text = f.read()
            text = text.split('\n')
            M = int(text[0])
            text.pop(0)
            N = int(text[0])
            text.pop(0)
            for i in range(M):
                pojam = text[i].split(',')
                pojmovi.append(pojam)
            for i in range(M):
                text.pop(0)
            rel = text
        tabela.append(pojmovi[0])
        for i in range(M - 1):
            tabela.append([0]*N)
        positive,negative = relations(tabela,rel,pojmovi)
        root, vijabilnost = stablo(tabela,N,M,positive,negative,vijabilnost)

    elif x == 3:
        ispisStabla(root,vijabilnost)

    elif x == 4:
        while True:
            print("\n------MENI-----\n"
                  "Izaberite opciju:\n"
                  "1. Upisi pojam u tabelu\n"
                  "2. Pomoc/upisivanje narednog koraka\n"
                  "3. Nema resenja (zavrsetak igre)\n")

            try:
                e = int(input())
                if e < 0 or e > 3:
                    print("Unesite ispravnu opciju\n")
                    continue
            except:
                print("Unesite broj kao opciju\n")
                continue
            if e == 1:
                print("Unesite broj reda:\n")
                row = int(input())
                row -= 1
                print("Unesite broj kolone:\n")
                column = int(input())
                column -= 1
                print("Unesite ime pojma koji zelite da upisete u polje:\n")
                pojam = input()
                tabela[row][column] = pojam
                tabela = potez(tabela,root)
                break
            elif e == 2:

                tabela = hint(tabela,root)
                break
            elif e == 3:
                break
    elif x == 5:
        stek = [root]
        if stek == [[]]:
            continue
        while len(stek) > 0:
            ce = stek.pop(0)
            print(ce.data)
            print(ce.leaf, end=', ')
            if ce.parent == None:
                print('Nema roditelja')
            else:
                print(ce.parent.data)
            print('\n')
            if ce.data == tabela:
                break
            for u in range(len(ce.children) - 1, -1, -1):
                stek.insert(0, ce.children[u])

    elif x == 6:
        break

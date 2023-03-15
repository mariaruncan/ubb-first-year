def ui_dif_contrare():
#functia determina lungimea maxima a unei secvente de numere intregi cu proprietatea ca diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1]) au semne contrare
    lmax=0
    lun=len(lst)
    for x in range(lun-3):
        for y in range(x+3,lun):
            l=y-x
            aux=lst[x:y]
            if dif_contrare(aux):
                if l>lmax:
                    lmax=l
            else:
                break
    print_dif_contrare(lmax,lun)


def dif_contrare(x):
#functia verifica daca lista de numere intregi x are proprietatea ca diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1]) au semne contrare
#date de intrare: x - lista de nr intregi
#date de iesire: True , daca lista are proprietatea ceruta
#                False , altfel
    for i in range(len(x)-2):
        if (x[i+1]-x[i])*(x[i+2]-x[i+1])>=0:
            return False
    return True

def print_dif_contrare(l,lun):
#functia afiseaza toate secventele de numere intregi de lungime maxima ale liste lst cu proprietatea ca diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1]) au semne contrare sau un mesaj in caz contrar
    if l<3:
        print("Nu exista o secventa cu proprietatea ca diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1]) au semne contrare")
    else:
        for j in range(lun-l):
            aux=lst[j:j+l]
            if dif_contrare(aux):
                print(lst[j:j+l])


def ui_semne_contrare():
#functia determina lungimea maxima a unei secvente de numere intregi cu elementele alaturate de semne contrare
    lmax=0
    lun=len(lst)
    for x in range(lun-2):
        for y in range(x+2,lun):
            l=y-x
            aux=lst[x:y]
            if semne_contrare(aux):
                if l>lmax:
                    lmax=l
            else:
                break
    print_semne_contrare(lmax,lun)


def semne_contrare(v):
#functia verifica daca lista de numere intregi v are toate elementele alaturate de semne contrare
#date de intrare: v - lista de nr intregi
#date de iesire: True , daca elementele alaturate au semne contrare
#                False , altfel
    for i in range(len(v)-1):
        if v[i]*v[i+1]>=0:
            return False
    return True


def print_semne_contrare(l,lun):
#functia afiseaza toate secventele de numere intregi de lungime maxima ale listei lst cu proprietatea ca elementele alaturate au semne contrare sau un mesaj in caz contrar
    if l==0:
        print("Nu exista o secventa cu proprietatea ca elementele sunt de semne contrare")
    else:
        for x in range(lun-l):
            aux=lst[x:x+l]
            if semne_contrare(aux):
                print(lst[x:x+l])


def ui_elem_distincte():
#functia determina lungimea maxima a unei secvente de numere intregi cu elementele nr distincte
    lmax=0
    lun=len(lst)
    for x in range(lun-2):
        for y in range(x+2,lun):
            l=y-x
            aux=lst[x:y]
            if elem_distincte(aux):
                if l>lmax:
                    lmax=l
            else:
                break
    print_elem_distincte(lmax,lun)

        
def elem_distincte(v):
#date de intrare: v - lista de nr intregi
#date de iesire: True , daca elementele sunt distincte
#                False , altfel
    v.sort()
    for i in range(len(v)-1):
        if v[i]==v[i+1]:
            return False
    return True


def print_elem_distincte(l, lun):
#functia afiseaza toate secventele de numere intregi de lungime maxima ale listei lst cu proprietatea ca elementele sunt distincte sau un mesaj in caz contrar
    if l==0:
        print("Nu exista o secventa cu proprietatea ca elementele sunt distincte")
    else:
        for x in range(lun-l):
            aux=lst[x:x+l]
            if elem_distincte(aux):
                print(lst[x:x+l])


def ui_citire_lista():
#functia citeste nr de elemente n ale listei lst
    n=input("Introduceti cate elemente va avea lista: ")
    n=int(n)
    citire_lista(n)

    
def citire_lista(n):
#functia citeste cele n nr intregi ale listei lst
    
    print("Introduceti elementele listei: ")
    for i in range (n):
        elem=int(input())
        lst.append(elem)
    print(lst)

    
def run():
    comenzi={
        "1":ui_citire_lista,
        "2":ui_elem_distincte,
        "3":ui_semne_contrare,
        "4":ui_dif_contrare
        }
    while True:
        print("""1. Citeste lista de numere intregi
2. Gaseste secventa de lungime maxima cu toate elementele distincte
3. Gaseste secventa de lungime maxima cu elemente alaturate de semne contrare
4. Gaseste secventa de lungime maxima cu diferentele a doua nr alaturate de semne contrare
5. Iesire din aplicatie""")
        cmd=input("Introduceti o comanda: ")
        if cmd=="5":
            print("EXIT")
            return
        if cmd in comenzi:
            try:
                comenzi[cmd]()
            except ValueError as ve:
                print("Comanda invalida")
        else:
            print("Comanda invalida")

        
lst=[]
run()

from domain.entitati import cloneaza_cheltuiala


def cloneaza_lista(lista):
    # functia construieste in lista clona o lista identica cu lista lista
    # date d eintrare: lista
    # date de iesire: clona
    clona = []
    for el in lista:
        clona.append(cloneaza_cheltuiala(el))
    return clona


def sterge_index(lista, poz):
    # functia sterge din lista lista elementul de pe pozitia poz
    # date de intrare: lista
    #                  poz - nr intreg pozitiv
    # date de iesire: -
    del lista[poz]


def indexul_maximului_lista(lista):
    # functia determina indexul elementului cu valoare maxima din lista lista
    # date de intrare: lista
    # date de iesire: poz - int (indexul elementului cu valoare maxima din lista lista)
    elmax = 0
    poz = -1
    for i in range(len(lista)):
        if lista[i] > elmax:
            elmax = lista[i]
            poz = i
    return poz

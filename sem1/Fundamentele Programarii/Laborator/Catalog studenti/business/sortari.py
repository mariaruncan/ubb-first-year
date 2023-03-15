def quick_sort(lista, key=lambda x: x, reverse=False):
    # functia sorteaza lista (reverse=False - crescator, reverse=True - descrescator) in urmatorul mod:
    # se ia un pivot la intamplare si se formeaza doua subliste: lista cu elementele mai mici decat pivotul si
    # lista cu elemente mai mari decat pivotul; apoi aceste subliste sunt sortate folosind apeluri ale acestei functii
    # date de intrare: lista - lista cu elemente oarecare
    #                  key - criteriu de sortare
    #                  reverse - True sau False
    # date de iesire: lista sortata
    if len(lista) <= 1:
        return lista
    pivot = lista.pop()
    mai_mic = quick_sort([x for x in lista if key(x) < key(pivot)], key, reverse)
    mai_mare = quick_sort([x for x in lista if key(x) > key(pivot)], key, reverse)
    lista_sorata = mai_mic + [pivot] + mai_mare
    if not reverse:
        return lista_sorata
    else:
        lista_sorata.reverse()
        return lista_sorata


def shake_sort(lista, key=lambda x: x, reverse=False):
    # se mai numeste cocktail sort sau bidirectional bubble sort
    # se completeaza lista sortata alternand ( se pune la locul sau cel mai mare element, apoi cel mai mic, apoi al
    # doilea cel mai mare, al doilea cel mai mic etc.
    # date de intrare: lista - lista cu elemente oarecare
    #                  key - criteriu de sortare
    #                  reverse - True sau False
    # date de iesire: lista sortata
    n = len(lista)
    sortat = True
    start = 0
    stop = n - 1
    while sortat:
        # presupunem ca lista este sortata
        sortat = False
        # pune cel mai mare element la locul sau
        for i in range(start, stop):
            if key(lista[i]) > key(lista[i + 1]):
                lista[i], lista[i + 1] = lista[i + 1], lista[i]
                sortat = True
        # daca nu facem nicio modificare, lista este sortata
        if not sortat:
            break
        # presupunem ca lista este sortata
        sortat = False
        # parcurgem lista pana la stop - 1 deoarece cel mai mare elem este la locul sau
        stop = stop - 1
        # pune cel mai mic element la locul sau
        for i in range(stop - 1, start - 1, -1):
            if key(lista[i]) > key(lista[i + 1]):
                lista[i], lista[i + 1] = lista[i + 1], lista[i]
                sortat = True
        # cel mai mic element este la locul sau
        start = start + 1
    if not reverse:
        return lista
    else:
        lista.reverse()
        return lista

def adauga_cheltuiala_lista(lista, ch):
    # functia adauga listei lista elementul ch
    # date de intrare:  lista
    #                   ch
    # date de iesire: -
    lista.append(ch)


def gaseste_cheltuiala(lista_cheltuieli, ch):
    # functia returneaza pozitia elementului ch in lista lista_cheltuieli
    # date de intrare: lista_cheltuieli
    #                  ch
    # date de iesire: i - int (pozitia lui ch in lista_cheltuieli)
    # ridica exceptie de tipul Exception cu mesajul "Cheltuiala inexistenta!\n" daca cheltuiala nu este gasita
    for i in range(len(lista_cheltuieli)):
        if lista_cheltuieli[i] == ch:
            return i
    raise Exception("Cheltuiala inexistenta!\n")


def sortare_sume_pe_zile(lista_cheltuieli):
    # functia construieste lista_sume_zile, unde lista_sume_zile[i] este obtinut prin adunarea sumelor cheltuielilor
    # ce au ziua i
    # date de intrare: lista_cheltuieli
    # date de iesire: lista_sume_zile ( lista nou construita)
    lista_sume_zile = [0] * 32
    for el in lista_cheltuieli:
        poz = int(el["zi"])
        lista_sume_zile[poz] += el["suma"]
    return lista_sume_zile

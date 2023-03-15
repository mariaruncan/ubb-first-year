from utils.utilitare import cloneaza_lista, sterge_index, indexul_maximului_lista
from infrastructure.colectii import adauga_cheltuiala_lista, sortare_sume_pe_zile
from domain.entitati import creeaza_cheltuiala
from validation.validare import valideaza_zi, valideaza_suma, valideaza_tip, valideaza_cheltuiala


def srv_adauga_cheltuiala_lista(lista_cheltuieli, z, s, t, lista_undo):
    # functia adauga la lista lista_cheltuieli o cheltuiala cu ziua z, suma s si tipul t
    # date de intrare: lista_cheltuieli, lista_undo - liste
    #                  z - int
    #                  s - float
    #                  t - string
    # date de iesire: -
    # ridica exceptie de tipul Exception cu mesajul
    #   - exceptie de validare daca cheltuiala nu este valida
    cheltuiala = creeaza_cheltuiala(z, s, t)
    valideaza_cheltuiala(cheltuiala)
    lista_undo.append(cloneaza_lista(lista_cheltuieli))
    adauga_cheltuiala_lista(lista_cheltuieli, cheltuiala)


def srv_actualizeaza_zi(lista_cheltuieli, poz, val, lista_undo):
    # functia modifica ziua cheltuielii de pe pozitia poz din lista_cheltuieli cu noua valoare val
    # date de intrare: lista_cheltuieli, lista_undo - liste
    #                  poz, val - int
    # date de iesire: -
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca ziua val nu este valida
    valideaza_zi(val)
    lista_undo.append(cloneaza_lista(lista_cheltuieli))
    lista_cheltuieli[poz]["zi"] = val


def srv_actualizeaza_suma(lista_cheltuieli, poz, val, lista_undo):
    # functia modifica suma cheltuielii de pe pozitia poz din lista_cheltuieli cu noua valoare val
    # date de intrare: lista_cheltuieli, lista_undo - liste
    #                  poz - int
    #                  val - float
    # date de iesire: -
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca suma val nu este valida
    valideaza_suma(val)
    lista_undo.append(cloneaza_lista(lista_cheltuieli))
    lista_cheltuieli[poz]["suma"] = val


def srv_actualizeaza_tip(lista_cheltuieli, poz, val, lista_undo):
    # functia modifica tipul cheltuielii de pe pozitia poz din lista_cheltuieli cu noua valoare val
    # date de intrare: lista_cheltuieli, lista_undo - liste
    #                  poz - int
    #                  val - string
    # date de iesire: -
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca tipul val nu este valid
    valideaza_tip(val)
    lista_undo.append(cloneaza_lista(lista_cheltuieli))
    lista_cheltuieli[poz]["tip"] = val


def srv_sterge_zi(lista_cheltuieli, z, lista_undo):
    # functia parcurge lista_cheltuieli si sterge cheltuielile facute in ziua z
    # date de intrare: lista_cheltuieli, lista_undo - liste
    #                  z - int
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca ziua z nu este valida
    valideaza_zi(z)
    lista_undo.append(cloneaza_lista(lista_cheltuieli))
    for i in range(len(lista_cheltuieli) - 1, -1, -1):
        if lista_cheltuieli[i]["zi"] == z:
            sterge_index(lista_cheltuieli, i)


def srv_sterge_interval(lista_cheltuieli, ini, sf, lista_undo):
    # functia parcurge lista_cheltuieli si sterge cheltuielile facute in intervalul [ini, sf]
    # date de intrare: lista_cheltuieli, lista_undo - liste
    #                  ini, sf - int
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca ziua ini sau ziua sf nu este valida
    valideaza_zi(ini)
    valideaza_zi(sf)
    lista_undo.append(cloneaza_lista(lista_cheltuieli))
    for i in range(len(lista_cheltuieli) - 1, -1, -1):
        if ini <= lista_cheltuieli[i]["zi"] <= sf:
            sterge_index(lista_cheltuieli, i)


def srv_sterge_tip(lista_cheltuieli, t, lista_undo):
    # functia parcurge lista_cheltuieli si sterge cheltuielile de tipul t
    # date de intrare: lista_cheltuieli, lista_undo - liste
    #                  t - string
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca tipul t nu este valid
    valideaza_tip(t)
    lista_undo.append(cloneaza_lista(lista_cheltuieli))
    for i in range(len(lista_cheltuieli) - 1, -1, -1):
        if lista_cheltuieli[i]["tip"] == t:
            sterge_index(lista_cheltuieli, i)


def srv_cautare_mai_mare_suma(lista_cheltuieli, s):
    # functia salveaza in lista_noua elementele din lista_cheltuieli care au suma mai mare decta o suma data s
    # date de intrare: lista_cheltuieli
    #                  s - float
    # date de iesire: lista_noua - lista cu toate cheltuielile ce au suma mai mare decat s
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca suma s nu este valida
    valideaza_suma(s)
    lista_noua = []
    for el in lista_cheltuieli:
        if el["suma"] > s:
            lista_noua.append(el)
    return lista_noua


def srv_cautare_inainte_zi_mai_mic_suma(lista_cheltuieli, z, s):
    # functia salveaza in lista_noua elementele din lista_cheltuieli care au suma mai mica decta o suma data s
    # si sunt efectuate inainte de ziua z
    # date de intrare: lista_cheltuieli
    #                  z - int
    #                  s - float
    # date de iesire: lista_noua - lista cu toate cheltuielile ce au suma mai mica decat s si au fost efectuate
    #                              inainte de ziua z
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca ziua z sau suma s nu sunt valide
    valideaza_zi(z)
    valideaza_suma(s)
    lista_noua = []
    for el in lista_cheltuieli:
        if el["suma"] < s and el["zi"] < z:
            lista_noua.append(el)
    return lista_noua


def srv_cautare_tip(lista_cheltuieli, t):
    # functia salveaza in lista_noua elementele din lista_cheltuieli care au tipul t
    # date de intrare: lista_cheltuieli
    #                  t - string
    # date de iesire: lista_noua - lista cu toate cheltuielile ce au tipul t
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca tipul t nu este valid
    valideaza_tip(t)
    lista_noua = []
    for el in lista_cheltuieli:
        if el["tip"] == t:
            lista_noua.append(el)
    return lista_noua


def srv_raport_suma_totala_tip(lista_cheltuieli, t):
    # functia calculeaza suma cheltuielilor de tipul t din lista_cheltuieli
    # date de intrare: lista_cheltuieli
    #                  t - string
    # date de iesire: s - float (suma cheltuielilor de tip t din lista_cheltuieli)
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca tipul t nu este valid
    valideaza_tip(t)
    s = 0
    for el in lista_cheltuieli:
        if el["tip"] == t:
            s += el["suma"]
    return s


def srv_raport_zi_cu_suma_maxima(lista_cheltuieli):
    # functia calculeaza suma cheltuielilor din lista_cheltuieli pentru fiecare zi si returneaza ziua cu suma maxima
    # date de intrare: lista_cheltuieli
    # date de iesire: z - ziua care are suma cheltuielilor maxima
    lista_sume_zile = sortare_sume_pe_zile(lista_cheltuieli)
    z = indexul_maximului_lista(lista_sume_zile)
    return z


def srv_raport_cu_suma_data(lista_cheltuieli, s):
    # functia construieste o lista cu toate elementele din lista_cheltuieli care au suma egala cu s
    # date de intrare: lista_cheltuieli
    #                  s - float
    # date de iesire: lista (lista nou formata)
    # ridica exceptie de tipul Exception:
    #   - exceptie de validare daca suma s nu este valida
    valideaza_suma(s)
    lista = []
    for el in lista_cheltuieli:
        if el["suma"] == s:
            lista.append(el)
    return lista


def srv_raport_cheltuieli_sortate_tip(lista_cheltuieli):
    # functia construieste in lista_noua o lista cu elementele listei lista sortate dupa tip
    # date de intrare: lista
    # date de iesire: lista_noua (lista nou formata)
    lista_noua = []
    for t in ["altele", "imbracaminte", "intretinere", "mancare", "telefon"]:
        lista_noua = lista_noua + srv_cautare_tip(lista_cheltuieli, t)
    return lista_noua


def srv_filtrare_tip(lista_cheltuieli, t):
    # functia construieste o lista cu toate elementele din lista_cheltuieli care au tipul diferit de t
    # date de intrare: lista_cheltuieli
    #                  t - string
    # date de iesire: lista (lista nou formata)
    # ridica exceptie de tipul Exception
    #   - exceptie de validare daca tipul t nu este valid
    valideaza_tip(t)
    lista = []
    for el in lista_cheltuieli:
        if el["tip"] != t:
            lista.append(el)
    return lista


def srv_filtrare_mai_mici_suma(lista_cheltuieli, s):
    # functia construieste o lista cu toate elementele din lista_cheltuieli care au suma mai mare sau egala cu s
    # date de intrare: lista_cheltuieli
    #                  s - nr intreg
    # date de iesire: lista (lista nou formata)
    # ridica exceptie de tipul Exception
    #   - exceptie de validare daca suma s nu este valida
    valideaza_suma(s)
    lista = []
    for el in lista_cheltuieli:
        if el["suma"] >= s:
            lista.append(el)
    return lista


def srv_undo(lista_cheeltuieli, lista_undo):
    # functia readunce lista lista_cheltuieli la forma sa dinaintea ultimea operatii ce a modificat-o in memorie
    # date de intrare: lista_cheltuieli, lista_undo - liste
    # date de iesire: -
    # ridica exceptie de tipul Eception cu mesajul "Nu se mai poate face undo!" daca lista_undo este goala
    if len(lista_undo) == 0:
        raise Exception("Nu se mai poate face undo!")
    lista_cheeltuieli[:] = cloneaza_lista(lista_undo[-1])
    lista_undo.pop()

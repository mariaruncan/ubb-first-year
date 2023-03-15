def creeaza_cheltuiala(z, s, t):
    # functia creeaza o cheltuiala cu ziua z, suma s si tipul t
    # date de intrare: z - int
    #                  s - float
    #                  t - string
    # date de iesire: cheltuiala
    return {
        "zi": z,
        "suma": s,
        "tip": t
    }


def cloneaza_cheltuiala(cheltuiala):
    # functia cloneaza o cheltuiala
    # date de intrare: cheltuiala
    # date de iesire: clona1_chletuiala
    return {
        "zi": cheltuiala["zi"],
        "suma": cheltuiala["suma"],
        "tip": cheltuiala["tip"]
    }


def egal_cheltuieli(ch1, ch2):
    # functia verifica daca cheltuielile ch1 si ch2 sunt egale
    # date de intrare: ch1, ch2 - cheltuieli
    # date de iesire: True, daca ch1 si ch2 sunt egale
    #                 False, altfel
    return ch1["zi"] == ch2["zi"] and abs(ch1["suma"] - ch2["suma"]) < 0.00001 and ch1["tip"] == ch2["tip"]

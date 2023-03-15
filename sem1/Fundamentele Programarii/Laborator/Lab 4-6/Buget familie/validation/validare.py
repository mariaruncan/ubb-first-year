def valideaza_cheltuiala(cheltuiala):
    # functia verifica daca ziua cheltuielii este nr intreg din intervalul [1, 31], daca suma este nr real >0 si daca
    # tipul este altele, imbracaminte, intretinere, mancare sau telefon
    # date de intrare: cheltuiala
    # date de iesire: -
    # ridica exceptie de tipul Exception co mesajul:
    #   - "Zi invalida!\n" daca ziua z nu este nr intreg din intervalul [1, 31]
    #   - "Suma invalida!\n" daca suma s nu este nr real >0
    #   - "Tip invalid!\n" daca tipul t nu este altele, imbracaminte, intretinere, mancare sau telefon
    erori = ""
    if cheltuiala["zi"] < 1 or cheltuiala["zi"] > 31:
        erori += "Zi invalida!\n"
    if cheltuiala["suma"] <= 0:
        erori += "Suma invalida!\n"
    if cheltuiala["tip"] not in ["altele", "imbracaminte", "intretinere", "mancare", "telefon"]:
        erori += "Tip invalid!\n"
    if len(erori) > 0:
        raise Exception(erori)


def valideaza_zi(z):
    # functia verifica daca ziua val este un  numar intreg din intervalul [1, 31]
    # date de intrare: z - nr intreg
    # date de iesire: -
    # ridica exceptie de tipul Exception
    #   - "Zi invalida!\n" daca nr intreg z nu face parte din intervalul [1, 31]
    z = int(z)
    if 0 < z < 32:
        pass
    else:
        raise Exception("Zi invalida!\n")


def valideaza_suma(s):
    # functia verifica daca suma val este numar real >0
    # date de intrare: s - nr real >0
    # date de iesire: -
    # ridica exceptie de tipul Exception
    #   - "Suma invalida!\n" daca val este nr real <=0
    s = float(s)
    if s > 0:
        pass
    else:
        raise Exception("Suma invalida!\n")


def valideaza_tip(t):
    # functia verifica daca tipul val este mancare, intretinere, telefon, imbracaminte sau altele
    # date de intrare: t - string
    # date de iesire: -
    # ridica exceptie de tipul Exception
    #   - "Tip invalid!\n" daca tipul nu este mancare, intretinere, telefon, imbracaminte sau altele
    if t in ["mancare", "intretinere", "telefon", "imbracaminte", "altele"]:
        pass
    else:
        raise Exception("Tip invalid!\n")

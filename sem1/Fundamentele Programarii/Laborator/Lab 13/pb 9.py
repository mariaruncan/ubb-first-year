def print_punct(punct):
    print("(" + str(punct[0]) + ", " + str(punct[1]) + ")")


def print_solutie(puncte, solutie):
    global nr_solutii
    nr_solutii += 1
    print("\nSolutia " + str(nr_solutii) + ":")
    i = 0
    while i < len(solutie):
        print_punct(puncte[solutie[i]])
        i += 1


def determinant(a, b, c):
    return a[0] * b[1] + b[0] * c[1] + a[1] * c[0] - b[1] * c[0] - a[1] * b[0] - c[1] * a[0]


def este_solutie(puncte, solutie):
    # functia verifica daca avem o solutie, adica daca punctele cu indicii in lista solutie constituie o solutie valida
    # o solutie condidat este solutie pentru problema daca oricare 3 puncte cu indicii in lista solutie sunt
    # coliniare; coliniaritatea se verifica prin calculul unui determinant ce trebuie sa fie aproximativ 0
    # date de intrare: puncte - lista de puncte(un punct este o lista cu doua componente reala)
    #                  solutie - lista de intregi, intregi ce reprezinta indicii unor puncte ce ar putea constitui o
    #                            solutie pentru problema
    # este solutie pt. a[0] * b[1] + b[0] * c[1] + a[1] * c[0] - b[1] * c[0] - a[1] * b[0] - c[1] * a[0] = 0, pentru
    # orice puncte a,b si  c
    if len(solutie) < 3:
        return False
    for i in range(len(solutie) - 2):
        for j in range(i + 1, len(solutie) - 1):
            for k in range(j + 1, len(solutie)):
                det = determinant(puncte[solutie[i]], puncte[solutie[j]], puncte[solutie[k]])
                if abs(det) < 0.000000001:
                    return True
    return False


def backtracking_recursiv(puncte, solutie=[]):
    # in lista solutie pastram indicii punctelor din lista puncte care ar putea forma o solutie
    if len(solutie) == 0:
        start = 0
    else:
        start = solutie[-1] + 1

    for i in range(start, len(puncte)):
        solutie.append(i)  # linia 42 si 45 se asigura ca toate componentele listei solutie sunt diferite
        if este_solutie(puncte, solutie):
            print_solutie(puncte, solutie)
        if len(solutie) < len(puncte):
            # conditie necesara pentru o solutie candidat; in caz ca nu este indeplinita, inseamna ca s-a testat
            # inclusiv multimea tuturor punctelor si se iese din backtracking_recursiv
            backtracking_recursiv(puncte, solutie)
        solutie.pop()


def backtracking_iterativ(puncte):
    solutie = [-1]  # solutie candidat
    while len(solutie):
        ok = False
        while not ok and len(solutie) <= len(puncte) and solutie[-1] < len(puncte) - 1:
            # linia anterioara de cod reprezinta conditia ca o solutie partiala sa fie solutie candidat
            solutie[-1] += 1  # creste ultima componenta
            ok = True
        if not ok:
            solutie = solutie[: - 1]  # facem back
        else:
            if este_solutie(puncte, solutie):
                print_solutie(puncte, solutie)
            solutie.append(solutie[-1])  # extindem solutia condidat


def run():
    print("Problema 9")
    print("Se dau coordonatele pentru n puncte in plan.")
    print("Determinati toate multimile de puncte cu proprietatea ca cel putin trei puncte din multime sunt coliniare.")
    print("Tipariti un mesaj daca problema nu are solutie.")

    try:
        n = int(input("\nn = "))
    except ValueError as ve:
        print(ve)
        return

    lista_puncte = []
    for i in range(n):
        try:
            x = float(input("\nx" + str(i) + " = "))
        except ValueError as ve:
            print(ve)
            return
        try:
            y = float(input("y" + str(i) + " = "))
        except ValueError as ve:
            print(ve)
            return
        lista_puncte.append([x, y])
        print_punct(lista_puncte[i])

    if n < 3:
        print("\nNu exista solutie!")
        return

    global nr_solutii
    print("\nVarianta recursiva:")
    backtracking_recursiv(lista_puncte)
    if nr_solutii == 0:
        print("Nu exista solutie!")
    print("\nVarianta iterativa:")
    nr_solutii = 0
    backtracking_iterativ(lista_puncte)
    if nr_solutii == 0:
        print("Nu exista solutie!")


nr_solutii = 0
run()

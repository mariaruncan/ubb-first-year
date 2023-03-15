from domeniu.entitati import Student, Disciplina, Nota
from Lib import random, string
from erori.exceptii import RepoError


def random_studenti_discipline_note(repo_stud, repo_discipline, repo_note):
    n = int(input("nr studenti de adaugat:"))
    for i in range(n):
        id_stud = random.randrange(100, 999)
        litere = string.ascii_lowercase
        nume = ''.join(random.choice(litere) for i in range(6))
        try:
            repo_stud.adauga(Student(id_stud, nume))
        except RepoError as re:
            print(re)

    print("")
    lista_studenti = repo_stud.get_all()
    for el in lista_studenti:
        print(el)
    print("")

    m = int(input("nr discipline de adaugat:"))
    for i in range(m):
        id_disciplina = random.randrange(100, 999)
        litere = string.ascii_uppercase
        nume = ''.join(random.choice(litere) for i in range(4))
        litere = string.ascii_lowercase
        profesor = ''.join(random.choice(litere) for i in range(7))
        try:
            repo_discipline.adauga(Disciplina(id_disciplina, nume, profesor))
        except RepoError as re:
            print(re)

    print("")
    lista_disicpline = repo_discipline.get_all()
    for el in lista_disicpline:
        print(el)
    print("")

    for s in lista_studenti:
        for d in lista_disicpline:
            valoare = random.randrange(1, 10)
            repo_note.adauga(Nota(s, d, valoare))

    print("")
    lista_note = repo_note.get_all()
    for el in lista_note:
        print(el)
    print("")
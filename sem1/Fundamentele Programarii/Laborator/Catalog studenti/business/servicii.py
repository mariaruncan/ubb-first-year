from domeniu.entitati import Student, Disciplina, Nota, MedieDTO
from validare.validatori import ValidatorMedie
from business.sortari import quick_sort, shake_sort


class ServiceStudenti(object):
    # tip abstract de data pentru srv_stud

    def __init__(self, valid, repo):
        # functia initializeaza un obiect de tip ServiceStudenti
        # date de intrare: valid - ValidatorStudenti, repo - RepositoryStudenti
        self.__valid = valid
        self.__repo = repo

    def adauga_student(self, id_stud, nume):
        # functia creeaza un student, il valideaza si il adauga la repo
        # date de intrare: id_stud - int, nume - string
        # date de iesire: -
        # poate ridica exceptie de tipul ValidError sau RepoError - vezi metoda valideaza din clasa ValidatorStudent
        #                                                           si metoda adauga din clasa RepositoryStudenti
        student = Student(id_stud, nume)
        self.__valid.valideaza(student)
        self.__repo.adauga(student)

    def cauta_student(self, id_stud):
        # functia cauta in repo studentul cu id-ul id_stud si il returneaza
        # date de intrare: id_stud - int
        # date de iesire: student - Student, unde student are id-ul id_stud
        # poate ridica exceptie de tipul RepoError - vezi metoda cauta_dupa_id din clasa RepositoryStudenti
        return self.__repo.cauta_dupa_id(id_stud)

    def get_studenti(self):
        # functia returneaza lista tuturor studentilor
        # date de intrare: -
        # date de iesire: lista de studenti
        return self.__repo.get_all()


class ServiceDiscipline(object):
    # tip abstract de data pentru srv_discipline

    def __init__(self, valid, repo):
        # functia initializeaza un obiect de tip ServiceDiscipline
        # date de intrare: valid - ValidatorDisciplina, repo_discipline - RepositoryDiscipline,
        #                  repo_note - RepositoryNote
        self.__valid = valid
        self.__repo = repo

    def adauga_disciplina(self, id_disciplina, nume, profesor):
        # functia creeaza o disciplina, o valideaza si o adauga la repo
        # date de intrare: id_disciplina - int, nume - string, profesor - string
        # date de iesire: -
        # poate ridica exceptie de tipul ValidError sau RepoError - vezi metoda valideaza din clasa ValidatorDisciplina
        #                                                           si metoda adauga din clasa RepositoryDiscipline
        disciplina = Disciplina(id_disciplina, nume, profesor)
        self.__valid.valideaza(disciplina)
        self.__repo.adauga(disciplina)

    def cauta_disciplina(self, id_disciplina):
        # functia cauta in repo disciplina cu id-ul id_disciplina si o returneaza
        # date de intrare: id_disciplina - int
        # date de iesire: disciplina - Disciplina, unde disciplina are id-ul id_disciplina
        # poate ridica exceptie de tipul RepoError - vezi metoda cauta_dupa_id din clasa RepositoryDiscipline
        return self.__repo.cauta_dupa_id(id_disciplina)

    def get_discipline(self):
        # functia returneaza lista tuturor disciplinelor
        # date de intrare: -
        # date de iesire: lista de discipline
        return self.__repo.get_all()


class ServiceNote(object):
    # tip abstract de data pentru srv_note

    def __init__(self, valid_note, valid_stud, valid_dis, repo_note, repo_stud, repo_dis):
        # functia initializeaza un obiect de tip ServiceNote
        # date de intrare: valid - ValidatorNota, repo_note - RepositoryNote
        #                  repo_stud - RepositoryStudenti, repo_discipline - RepositoryDiscipline
        self.__valid_note = valid_note
        self.__valid_stud = valid_stud
        self.__valid_dis = valid_dis
        self.__repo_note = repo_note
        self.__repo_stud = repo_stud
        self.__repo_dis = repo_dis

    def adauga_nota(self, id_stud, id_disciplina, valoare):
        # functia creeaza nota pe baza id_nota, id_stud, id_disciplina si valoare, o valideaza si apoi o adauga in repo
        # date de intrare: id_nota, id_stud, id_disciplina, valoare - int
        # date de iesire: -
        # poate ridica exceptie de tipul ValidError sau RepoError - vezi metoda valideaza din clasa ValidatorNota,
        # cauta_dupa_id din RepositoryStudenti si RepositoryDiscipline, adauga din RepositoryNote
        student = self.__repo_stud.cauta_dupa_id(id_stud)
        disciplina = self.__repo_dis.cauta_dupa_id(id_disciplina)
        nota = Nota(student, disciplina, valoare)
        self.__valid_note.valideaza(nota)
        self.__repo_note.adauga(nota)

    def sterge_student(self, id_stud):
        # functia sterge din repo_stud studentii cu id-ul id_stud si din repo_note notele care il au ca atribut pe
        # studentul respectiv
        # date de intrare: id_stud - int
        # date de iesire: -
        # poate ridica exceptie de tipul RepoError - vezi metoda sterge_dupa_id din clasa RepositoryStudenti
        student = self.__repo_stud.cauta_dupa_id(id_stud)
        self.__repo_note.sterge(student, Disciplina(0, "", ""))
        self.__repo_stud.sterge_dupa_id(id_stud)

    def modifica_student(self, id_stud, nume_nou):
        # functia modifica studentul cu id-ul id_stud, actualizandu-i numele cu nume_nou
        # date de intrare: id_stud - int, nume_nou - string
        # date de iesire: -
        # poate ridica exceptie de tipul RepoError - vezi metoda modifica din clasa RepositoryStudenti
        student_nou = Student(id_stud, nume_nou)
        self.__valid_stud.valideaza(student_nou)
        self.__repo_note.modifica(student_nou, Disciplina(0, "", ""))
        self.__repo_stud.modifica(student_nou)

    def sterge_disciplina(self, id_disciplina):
        # functia sterge din repo_discipline disciplina cu id-ul id_disciplina si din repo_note notele care au
        # disciplina respectiva ca atribut
        # date de intrare: id_disciplina - int
        # date de iesire: -
        # poate ridica exceptie de tipul RepoError - vezi metoda sterge_dupa_id din clasa RepositoryDiscipline
        disciplina = self.__repo_dis.cauta_dupa_id(id_disciplina)
        self.__repo_note.sterge(Student(0, ""), disciplina)
        self.__repo_dis.sterge_dupa_id(id_disciplina)

    def modifica_disciplina(self, id_disciplina, nume_nou, profesor_nou):
        # functia modifica disciplina cu id-ul id_disciplina, actualizandu-i numele cu nume_nou si
        # profesorul cu profesor_nou
        # date de intrare: id_disciplina - int, nume_nou - string, profesor_nou - string
        # date de iesire: -
        # poate ridica exceptie de tipul RepoError - vezi metoda modifica din clasa RepositoryDiscipline
        disciplina_noua = Disciplina(id_disciplina, nume_nou, profesor_nou)
        self.__valid_dis.valideaza(disciplina_noua)
        self.__repo_note.modifica(Student(0, ""), disciplina_noua)
        self.__repo_dis.modifica(disciplina_noua)

    def get_note(self):
        # functia returneaza lista tuturor notelor
        # date de intrare: -
        # date de iesire: lista de note
        return self.__repo_note.get_all()

    def get_note_student(self, id_stud):
        # functia returneaza lista notelor studentului cu id-ul id_stud
        # date de intrare: id_stud - int
        # date de iesire: lista notelor studentului
        # ridica exceptie de tipul RepoError cu mesajul - vezi metoda cauta_dupa_id() din clasa RepositoryStudenti
        student = self.__repo_stud.cauta_dupa_id(id_stud)
        return self.__repo_note.cauta_note(student, Disciplina(0, "", ""))

    def get_note_disciplina(self, id_disciplina):
        # functia returneaza lista notelor de la disciplina cu id-ul id_disciplina
        # date de intrare: id_disciplina - int
        # date de iesire: lista notelor de la disciplina
        # ridica exceptie de tipul RepoError cu mesajul - vezi metoda cauta_dupa_id() din clasa RepositoryDiscipline
        disciplina = self.__repo_dis.cauta_dupa_id(id_disciplina)
        return self.__repo_note.cauta_note(Student(0, ""), disciplina)

    def note_disciplina_sortate(self, id_disciplina):
        # functia returneaza lista notelor de la disciplina cu id-ul id_disciplina, sortate alfabetic dupa numele
        # studentului si descrescator dupa nota
        # date de intrare: id_disciplina - int
        # date de iesire: lista notelor de la disciplina
        # ridica exceptie de tipul RepoError cu mesajul - vezi metoda cauta_dupa_id() din clasa RepositoryDiscipline
        lista = self.get_note_disciplina(id_disciplina)
        return quick_sort(lista, key=lambda x: (x.get_student().get_nume(), - x.get_valoare()))
        # lista.sort(key=lambda x: (x.get_student().get_nume(), - x.get_valoare()))
        # return lista

    def sortare_stud_dupa_medie(self):
        # functia construieste o lista sortata de dictionare, unde fiecare disctionar are la cheia "student" un anumit
        # student si la cheia "medie" media acestuia alcatuita din suma notelor la toata disciplinele impartita la
        # numarul de discipline
        # date de intare: -
        # date de iesire: lista de studenti cu mediile lor
        studenti = self.__repo_stud.get_all()
        note = self.__repo_note.get_all()
        discipline = self.__repo_dis.get_all()
        lista = []
        for s in studenti:
            medie = 0
            for n in note:
                if n.get_student() == s:
                    medie += n.get_valoare()
            medie = medie / len(discipline)
            lista.append(MedieDTO(s, medie))
        return shake_sort(lista, key=lambda x: x.get_medie(), reverse=True)
        # lista.sort(key=lambda x: x.get_medie(), reverse=True)
        # return lista

    def medie_in_interval(self, ini, sf):
        # functia returneaza o lista a caror elemente sunt formate dintr-un student si media sa, medie aflata in
        # intervalul [ini, sf]
        # date de intrare: ini, sf - nr reale
        # date de iesire: lista de studenti cu mediile lor
        lista = self.sortare_stud_dupa_medie()
        valid = ValidatorMedie()
        valid.valideaza(ini)
        valid.valideaza(sf)
        if len(lista) == 0:
            return []
        lista_interval = []
        for el in lista:
            if ini <= el.get_medie() <= sf:
                lista_interval.append(el)
        return lista_interval

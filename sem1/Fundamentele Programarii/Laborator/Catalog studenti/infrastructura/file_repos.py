from infrastructura.repos import RepositoryStudenti, RepositoryDiscipline, RepositoryNote
from domeniu.entitati import Student, Disciplina, Nota


class FileRepositoryStudenti(RepositoryStudenti):

    def __init__(self, filename):
        self.__filename = filename
        RepositoryStudenti.__init__(self)

    def __citeste_tot_din_fisier(self):
        with open(self.__filename, "r") as f:
            self._elems = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    student = Student(int(parts[0]), parts[1])
                    self._elems.append(student)

    def __append_student_fisier(self, student):
        with open(self.__filename, "a") as f:
            f.write(str(student.get_id_stud()) + ";" + student.get_nume() + "\n")

    def __scrie_tot_in_fisier(self):
        with open(self.__filename, "w") as f:
            for student in self._elems:
                f.write(str(student.get_id_stud()) + ";" + student.get_nume() + "\n")

    def adauga(self, student):
        self.__citeste_tot_din_fisier()
        RepositoryStudenti.adauga(self, student)
        self.__append_student_fisier(student)

    def modifica(self, student_nou):
        self.__citeste_tot_din_fisier()
        RepositoryStudenti.modifica(self, student_nou)
        self.__scrie_tot_in_fisier()

    def sterge_dupa_id(self, id_stud):
        self.__citeste_tot_din_fisier()
        RepositoryStudenti.sterge_dupa_id(self, id_stud)
        self.__scrie_tot_in_fisier()

    def get_all(self):
        self.__citeste_tot_din_fisier()
        return RepositoryStudenti.get_all(self)

    def __len__(self):
        self.__citeste_tot_din_fisier()
        return RepositoryStudenti.__len__(self)

    def cauta_dupa_id(self, id_stud):
        self.__citeste_tot_din_fisier()
        return RepositoryStudenti.cauta_dupa_id(self, id_stud)


class FileRepositoryDiscipline(RepositoryDiscipline):

    def __init__(self, filename):
        self.__filename = filename
        RepositoryDiscipline.__init__(self)

    def __citeste_tot_din_fisier(self):
        with open(self.__filename, "r") as f:
            self._elems = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    disciplina = Disciplina(int(parts[0]), parts[1], parts[2])
                    self._elems.append(disciplina)

    def __append_disciplina_fisier(self, disciplina):
        with open(self.__filename, "a") as f:
            f.write(str(disciplina.get_id_disciplina()) + ";" + disciplina.get_nume() + ";" +
                    disciplina.get_profesor() + "\n")

    def __scrie_tot_in_fisier(self):
        with open(self.__filename, "w") as f:
            for disciplina in self._elems:
                f.write(str(disciplina.get_id_disciplina()) + ";" + disciplina.get_nume() + ";" +
                        disciplina.get_profesor() + "\n")

    def adauga(self, disciplina):
        self.__citeste_tot_din_fisier()
        RepositoryDiscipline.adauga(self, disciplina)
        self.__append_disciplina_fisier(disciplina)

    def modifica(self, disciplina_noua):
        self.__citeste_tot_din_fisier()
        RepositoryDiscipline.modifica(self, disciplina_noua)
        self.__scrie_tot_in_fisier()

    def sterge_dupa_id(self, id_disciplina):
        self.__citeste_tot_din_fisier()
        RepositoryDiscipline.sterge_dupa_id(self, id_disciplina)
        self.__scrie_tot_in_fisier()

    def get_all(self):
        self.__citeste_tot_din_fisier()
        return RepositoryDiscipline.get_all(self)

    def __len__(self):
        self.__citeste_tot_din_fisier()
        return RepositoryDiscipline.__len__(self)

    def cauta_dupa_id(self, id_disciplina):
        self.__citeste_tot_din_fisier()
        return RepositoryDiscipline.cauta_dupa_id(self, id_disciplina)


class FileRepositoryNote(RepositoryNote):

    def __init__(self, filename):
        self.__filename = filename
        RepositoryNote.__init__(self)

    def __citeste_tot_din_fisier(self):
        with open(self.__filename, "r") as f:
            self._elems = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    student = Student(int(parts[0]), parts[1])
                    disciplina = Disciplina(int(parts[2]), parts[3], parts[4])
                    valoare = int(parts[5])
                    nota = Nota(student, disciplina, valoare)
                    self._elems.append(nota)

    def __append_nota_fisier(self, nota):
        with open(self.__filename, "a") as f:
            f.write(str(nota.get_student().get_id_stud()) + ";" + nota.get_student().get_nume() + ";" +
                    str(nota.get_disciplina().get_id_disciplina()) + ";" + nota.get_disciplina().get_nume() + ";" +
                    nota.get_disciplina().get_profesor() + ";" + str(nota.get_valoare()) + "\n")

    def __scrie_tot_in_fisier(self):
        with open(self.__filename, "w") as f:
            for nota in self._elems:
                f.write(str(nota.get_student().get_id_stud()) + ";" + nota.get_student().get_nume() + ";" +
                        str(nota.get_disciplina().get_id_disciplina()) + ";" + nota.get_disciplina().get_nume() + ";" +
                        nota.get_disciplina().get_profesor() + ";" + str(nota.get_valoare()) + "\n")

    def adauga(self, nota):
        self.__citeste_tot_din_fisier()
        RepositoryNote.adauga(self, nota)
        self.__append_nota_fisier(nota)

    def modifica(self, student, disciplina):
        self.__citeste_tot_din_fisier()
        RepositoryNote.modifica(self, student, disciplina)
        self.__scrie_tot_in_fisier()

    def sterge(self, student, disciplina):
        self.__citeste_tot_din_fisier()
        RepositoryNote.sterge(self, student, disciplina)
        self.__scrie_tot_in_fisier()

    def get_all(self):
        self.__citeste_tot_din_fisier()
        return RepositoryNote.get_all(self)

    def __len__(self):
        self.__citeste_tot_din_fisier()
        return RepositoryNote.__len__(self)

    def cauta_note(self, student, disciplina):
        self.__citeste_tot_din_fisier()
        return RepositoryNote.cauta_note(self, student, disciplina)

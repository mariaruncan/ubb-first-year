from erori.exceptii import ValidError, RepoError


class UI(object):
    def __ui_adauga_student(self):
        id_stud = int(input("introduceti id:"))
        nume = input("introduceti nume:")
        self.__srv_stud.adauga_student(id_stud, nume)

    def __ui_sterge_student(self):
        id_stud = int(input("introduceti id-ul studentului:"))
        self.__srv_note.sterge_student(id_stud)

    def __ui_modifica_student(self):
        id_stud = int(input("introduceti id-ul studentului:"))
        nume_nou = input("introduceti numele nou:")
        self.__srv_note.modifica_student(id_stud, nume_nou)

    def __ui_cauta_student(self):
        id_stud = int(input("introduceti id-ul studentului:"))
        print(self.__srv_stud.cauta_student(id_stud))

    def __ui_print_studenti(self):
        studenti = self.__srv_stud.get_studenti()
        if len(studenti) == 0:
            print("nu exista studenti in lista!")
            return
        for student in studenti:
            print(student)

    def __ui_adauga_disciplina(self):
        id_disciplina = int(input("introduceti id:"))
        nume = input("introduceti nume:")
        profesor = input("introduceti profesor:")
        self.__srv_dis.adauga_disciplina(id_disciplina, nume, profesor)

    def __ui_sterge_disciplina(self):
        id_disciplina = int(input("introduceti id-ul disciplinei:"))
        self.__srv_dis.sterge_disciplina(id_disciplina)

    def __ui_modifica_disciplina(self):
        id_disciplina = int(input("introduceti id-ul disciplinei:"))
        nume_nou = input("introduceti numele nou:")
        profesor_nou = input("introduceti profesorul nou:")
        self.__srv_dis.modifica_disciplina(id_disciplina, nume_nou, profesor_nou)

    def __ui_cauta_disciplina(self):
        id_disciplina = int(input("introduceti id-ul disciplinei:"))
        print(self.__srv_dis.cauta_disciplina(id_disciplina))

    def __ui_print_discipline(self):
        discipline = self.__srv_dis.get_discipline()
        if len(discipline) == 0:
            print("nu exista discipline in lista!")
            return
        for disciplina in discipline:
            print(disciplina)

    def __ui_adauga_nota(self):
        id_student = int(input("introduceti id-ul studentului:"))
        id_disciplina = int(input("introduceti id-ul disciplinei:"))
        valoare = int(input("introduceti valoarea notei:"))
        self.__srv_note.adauga_nota(id_student, id_disciplina, valoare)

    def __ui_print_note_student(self):
        id_stud = int(input("introduceti id-ul studentului:"))
        lista_note = self.__srv_note.get_note_student(id_stud)
        if len(lista_note) == 0:
            print("nu exista note pentru studentul ", self.__srv_stud.cauta_student(id_stud))
        else:
            for el in lista_note:
                print(el)

    def __ui_print_note_disciplina(self):
        id_disciplina = int(input("introduceti id-ul disciplinei:"))
        lista_note = self.__srv_note.get_note_disciplina(id_disciplina)
        if len(lista_note) == 0:
            print("nu exista note la disciplina ", self.__srv_dis.cauta_disciplina(id_disciplina))
        else:
            for el in lista_note:
                print(el)

    def __ui_print_note(self):
        lista_note = self.__srv_note.get_note()
        if len(lista_note) == 0:
            print("nu exista note in lista!")
        else:
            for el in lista_note:
                print(el)

    def __ui_lista_stud_note_disciplina_sortate(self):
        id_disciplina = int(input("introduceti id-ul disciplinei:"))
        disciplina = self.__srv_dis.cauta_disciplina(id_disciplina)
        lista = self.__srv_note.note_disciplina_sortate(id_disciplina)
        if len(lista) == 0:
            print("nu exista note la disiciplina ", disciplina)
        else:
            print(disciplina)
            for el in lista:
                print(el.get_student(), " ", str(el.get_valoare()))

    def __ui_primii_20_stud_dupa_medie(self):
        lista = self.__srv_note.sortare_stud_dupa_medie()
        if len(lista) == 0:
            print("nu exista studenti in lista!")
        else:
            if len(lista) <= 5:
                print(lista[0].get_student().get_nume() + str(lista[0].get_medie()))
            else:
                for i in range(len(lista) + 1):
                    print(lista[i].get_student().get_nume() + " " + str(lista[i].get_medie()))

    def __ui_medie_in_interval(self):
        ini = float(input("inceput interval:"))
        sf = float(input("sfarsit interval:"))
        lista = self.__srv_note.medie_in_interval(ini, sf)
        if len(lista) == 0:
            print("nu exista studenti cu media in intervalul dat!")
        else:
            for i in range(len(lista)):
                print(lista[i]["student"].get_nume(), lista[i]["medie"])

    def __init__(self, srv_studenti, srv_discipline, srv_note):
        self.__srv_stud = srv_studenti
        self.__srv_dis = srv_discipline
        self.__srv_note = srv_note
        self.__comenzi = {"1": self.__comanda1,
                          "2": self.__comanda2,
                          "3": self.__comanda3,
                          "4": self.__comanda4
                          }
        self.__comenzi_studenti = {"1": self.__ui_adauga_student,
                                   "2": self.__ui_sterge_student,
                                   "3": self.__ui_modifica_student,
                                   "4": self.__ui_cauta_student,
                                   "5": self.__ui_print_studenti
                                   }
        self.__comenzi_discipline = {"1": self.__ui_adauga_disciplina,
                                     "2": self.__ui_sterge_disciplina,
                                     "3": self.__ui_modifica_disciplina,
                                     "4": self.__ui_cauta_disciplina,
                                     "5": self.__ui_print_discipline
                                     }
        self.__comenzi_note = {"1": self.__ui_adauga_nota,
                               "2": self.__ui_print_note_student,
                               "3": self.__ui_print_note_disciplina,
                               "4": self.__ui_print_note
                               }
        self.__comenzi_rapoarte = {"1": self.__ui_lista_stud_note_disciplina_sortate,
                                   "2": self.__ui_primii_20_stud_dupa_medie,
                                   "3": self.__ui_medie_in_interval
                                   }

    def __comanda1(self):
        while True:
            print("""1. adauga student
2. sterge student
3. modifica student
4. cauta student
5. printare lista studenti
6. inapoi la meniul principal""")
            cmd = input(">>>")
            if cmd == "6":
                return
            elif cmd in self.__comenzi_studenti:
                try:
                    self.__comenzi_studenti[cmd]()
                except ValueError:
                    print("valoare numerica invalida!\n")
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
            else:
                print("comanda invalida!")

    def __comanda2(self):
        while True:
            print("""1. adauga disciplina
2. sterge disciplina
3. modifica disciplina
4. cauta disciplina
5. printare lista discipline
6. inapoi la meniul principal""")
            cmd = input(">>>")
            if cmd == "6":
                return
            elif cmd in self.__comenzi_discipline:
                try:
                    self.__comenzi_discipline[cmd]()
                except ValueError:
                    print("valoare numerica invalida!\n")
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
            else:
                print("comanda invalida!")

    def __comanda3(self):
        while True:
            print("""1. adauga nota
2. printeaza notele unui student
3. printeaza notele de la o disciplina
4. printeaza toate notele
5. inapoi la meniul principal""")
            cmd = input(">>>")
            if cmd == "5":
                return
            elif cmd in self.__comenzi_note:
                try:
                    self.__comenzi_note[cmd]()
                except ValueError:
                    print("valoare numerica invalida!\n")
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
            else:
                print("comanda invalida!")

    def __comanda4(self):
        while True:
            print("""1. printare studenti si notele lor la o disciplina data, ordonati alfabetic dupa nume, descrescator după nota
2. printare primii 20% din studenti sortati dupa media de la toate disciplinele (nume si nota)
3. printeaza studentii cu media intr-un interval dat
4. inapoi la meniul principal""")
            cmd = input(">>>")
            if cmd == "4":
                return
            elif cmd in self.__comenzi_rapoarte:
                try:
                    self.__comenzi_rapoarte[cmd]()
                except ValueError:
                    print("valoare numerica invalida!\n")
                except RepoError as re:
                    print(re)
            else:
                print("comanda invalida!")

    def run(self):
        while True:
            print("""1. comenzi studenti
2. comenzi discipline
3. comenzi note
4. rapoarte
5. iesire din aplicatie""")
            cmd = input(">>>")
            print("\n")
            if cmd == "5":
                print("EXIT")
                return
            elif cmd in self.__comenzi:
                self.__comenzi[cmd]()
            else:
                print("comanda invalida!")

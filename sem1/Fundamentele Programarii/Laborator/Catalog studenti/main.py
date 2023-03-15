from infrastructura.file_repos import FileRepositoryStudenti, FileRepositoryDiscipline, FileRepositoryNote
from business.servicii import ServiceStudenti, ServiceDiscipline, ServiceNote
from validare.validatori import ValidatorStudent, ValidatorDisciplina, ValidatorNota
from presentation.consola import UI


if __name__ == "__main__":
    repo_studenti = FileRepositoryStudenti("studenti.txt")
    repo_discipline = FileRepositoryDiscipline("discipline.txt")
    repo_note = FileRepositoryNote("note.txt")
    valid_student = ValidatorStudent()
    valid_disciplina = ValidatorDisciplina()
    valid_nota = ValidatorNota()
    srv_studenti = ServiceStudenti(valid_student, repo_studenti)
    srv_discipline = ServiceDiscipline(valid_disciplina, repo_discipline)
    srv_note = ServiceNote(valid_nota, valid_student, valid_disciplina, repo_note, repo_studenti, repo_discipline)
    consola = UI(srv_studenti, srv_discipline, srv_note)
    consola.run()

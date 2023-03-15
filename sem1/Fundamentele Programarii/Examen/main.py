from business.servicii import ServiceCarti
from infrastructura.file_repo import RepositoryCarti
from prezentare.consola import UI
from testare.testare import Teste

if __name__ == '__main__':
    teste = Teste()
    teste.ruleaza_teste()
    repo = RepositoryCarti("carti.txt")
    srv = ServiceCarti(repo, ["", -1], [])
    consola = UI(srv)
    consola.run()

#include <iostream>
#include <map>
#include <queue>
using namespace std;

struct Nod{
    char ch;
    int fr;
    Nod *st, *dr;

    Nod(char ch, int fr) {
        st = dr = nullptr;
        this->ch = ch;
        this->fr = fr;
    }
};

vector<pair<char, int>> initializare_alfabet() {
    vector<pair<char, int>> alfabet;
    alfabet.push_back(make_pair('a', 45));
    alfabet.push_back(make_pair('b', 17));
    alfabet.push_back(make_pair('c', 10));
    alfabet.push_back(make_pair('d', 25));
    alfabet.push_back(make_pair('e', 30));
    return alfabet;
}

struct compara {
    bool operator()(Nod* n1, Nod* n2) {
        return n1->fr < n2->fr;
    }
};

void obtine_coduri(map<char, string>& coduri, struct Nod* nod, string str) {
    if(!nod)
        return;

    if (nod->ch != '#') {
        coduri[nod->ch] = str;
    }

    obtine_coduri(coduri, nod->st, str + "0");
    obtine_coduri(coduri, nod->dr, str + "1");
}

map<char, string> codare_huffman(vector<pair<char, int>> alfabet, int size) {
    struct Nod* st, * dr, * nou;
    priority_queue<Nod*, vector<Nod*>, compara> q;

    for (int i = 0; i < size; i++) { // coada cu prioritati va avea alfabetul cu frecventele 
        q.push(new Nod(alfabet[i].first, alfabet[i].second));
    }

    for(int i = 1; i <= size - 1; i++) {
        st = q.top();
        q.pop();

        dr = q.top();
        q.pop();

        nou = new Nod('#', st->fr + dr->fr);
        nou->st = st;
        nou->dr = dr;

        q.push(nou);
    }
    map<char, string> coduri;
    obtine_coduri(coduri, q.top(), "");

    return coduri;
}

int main() {

    vector<pair<char, int>> alfabet = initializare_alfabet();
    int size = alfabet.size();
    map<char, string> coduri = codare_huffman(alfabet, size);
    cout << "Codurile sunt:\n";
    for (const pair<char, string>& el : coduri) {
        cout << el.first << " : " << el.second << "\n";
    }
    while (true) {
        cout << "\n1. Codare Huffman\n2. Decodare Huffman\n0. Exit\n>>>";
        int cmd;
        cin >> cmd;
        if (cmd == 0)
            break;
        else if (cmd == 1) {
            cout << "Introduceti secventa pentru codarea Huffman:";
            string sec;
            cin >> sec;
            cout << "Secventa codata este: ";
            for (int i = 0; i < sec.size(); i++) {
                cout << coduri[sec[i]];
            }
            cout << "\n";
        }
        else {
            cout << "Introduceti secventa pentru decodarea Huffman:";
            string sec;
            cin >> sec;
            cout << "Secventa decodata este: ";
            while (!sec.empty()) {
                string aux = "";
                while (true) {
                    aux = aux + sec[0];
                    sec.erase(0, 1);
                    bool gasit = false;
                    for (const pair<char, string>& el : coduri) {
                        if (el.second == aux) {
                            cout << el.first;
                            gasit = true;
                            break;
                        }
                    }
                    if (gasit) {
                        break;
                    }
                }
            }
            cout << "\n";
        }
    }
}

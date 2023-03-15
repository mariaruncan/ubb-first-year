#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Muchie {
    int x, y, w;

    Muchie(int x, int y, int w) {
        this->x = x;
        this->y = y;
        this->w = w;
    }
};

struct Graf {
    int V, E;
    vector<Muchie> muchii;

    Graf(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void add_muchie(int u, int v, int w) {
        muchii.push_back(Muchie(u, v, w));
    }
};

vector<Muchie> kruskal(Graf& g) {
    vector<Muchie> t;
    vector<vector<int>> vectori;
    for (int i = 1; i <= g.E; i++) {
        vector<int> vec;
        vec.push_back(i);
        vectori.push_back(vec);
    }

    sort(g.muchii.begin(), g.muchii.end(), [](const Muchie& m1, const Muchie& m2) {return m1.w < m2.w; });

    for (const Muchie& m : g.muchii) {
        auto it1 = find_if(vectori.begin(), vectori.end(), [=](const vector<int>& el) {
            return el.end() != find_if(el.begin(), el.end(), [=](int u) {return u == m.x; });
            });
        auto it2 = find_if(vectori.begin(), vectori.end(), [=](const vector<int>& el) {
            return el.end() != find_if(el.begin(), el.end(), [=](int u) {return u == m.y; });
            });
        if (it1 != it2) {
            t.push_back(m);
            for (int el : *it2) {
                (*it1).push_back(el);
            }
            vectori.erase(it2);
        }
    }
    return t;
}

int main() {
    ifstream fin("in.txt");
    int V, E;
    fin >> V >> E;
    Graf g{ V, E };
    for (int i = 1; i <= E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        g.add_muchie(u, v, w);
    }
    vector<Muchie> t = kruskal(g);
    int s = 0;
    for (const auto& el : t) {
        cout << "Muchia (" << el.x << ", " << el.y << ") Costul " << el.w << "\n";
        s = s + el.w;
    }
    cout << "Costul minim este: " << s;
}

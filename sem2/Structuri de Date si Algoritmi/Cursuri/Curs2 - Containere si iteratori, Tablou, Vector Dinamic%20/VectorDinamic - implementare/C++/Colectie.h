//tip de data generic (pentru moment este intreg)
typedef int TElem;
class Iterator;
class Colectie {
private:
	//pentru redimensionare
public:
	//pentru ca Iteratorul sa poata accesa reprezentarea vectorului
	//dimensiunea colectiei (numar de elemente)
	//adaugare elmnt in colectie

	//alte operatii specifice
	//constructor copiere, operator atribuire...
};

class Iterator {
private:
	//iteratorul contine o referinta catre container
	//pozitia curenta in iterator
	//varianta 2
public:
	//constructor
	//operatii pe iterator
	void urmator();
	TElem element() const;
	bool valid() const;
};

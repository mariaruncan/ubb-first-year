#pragma once

template <typename Telem>
class IteratorV;

template <typename Telem>
class MyVector {

private:

	Telem* elems;
	int capacity;
	int size;

	/*
		Resize the allocated space
		Post: capacity of the vector is twice as large
	*/
	void redim();

public:

	/*
		Default constructor for MyVector
		Allocate memory for 2 elements
	*/
	MyVector() : elems{ new Telem[1] }, capacity{ 1 }, size{ 0 } {
	}

	/*
		Copy constructor
	*/
	MyVector(const MyVector& v);

	/*
		Destructor for MyVector
	*/
	~MyVector() {
		delete[] elems;
	}

	/*
		Assignement operator
	*/
	MyVector& operator=(const MyVector& ot);

	/*
		Dereferencing operator
	*/
	Telem& operator[](int i);

	/*
		Add an element at the end of the array
		Pre: e is a generic element
		Post: e is added at the end of the array
	*/
	void add(const Telem& e);

	/*
		Delete the element from the given position
		Pre: poz - the position, poz >= 0 and poz < size
		Post: the element is no longer in the list, returns the deleted element
	*/
	void remove(int poz);

	/*
		Update an element for a given position
		Pre: poz - the position, poz >= 0 and poz < size, el - Telem object 
		Post: the element on position poz is el
	*/
	void update(int poz, const Telem& el);

	/*
		Acces the element from a given position
		Pre: poz - the position, poz >= 0 and poz < size
		Post: returns the element from position poz
	*/
	Telem& get(int poz) const noexcept;

	/*
		Return the size of MyVector
	*/
	int get_size() const noexcept;


	friend class IteratorV<Telem>;
	/*
		Return an iterator that points to the first element of MyVector
	*/
	IteratorV<Telem> begin() noexcept;
	/*
		Return an iterator that points after the last element of MyVector
	*/
	IteratorV<Telem> end() noexcept;
};

template<typename Telem>
void MyVector<Telem>::redim() {
	Telem* aux = new Telem[2 * capacity];
	for (int i = 0; i < size; i++) {
		*(aux + i) = elems[i];
	}
	delete[] elems;
	elems = aux;
	capacity = 2 * capacity;
}

template<typename Telem>
inline MyVector<Telem>::MyVector(const MyVector& v) {
	cout << "Copy constructor MyVector\n";
	this->capacity = v.capacity;
	this->size = v.size;
	this->elems = new Telem[this->capacity];
	for (int i = 0; i < v.size; i++) {
		*(this->elems + i) = v.elems[i];
	}
}

template<typename Telem>
MyVector<Telem>& MyVector<Telem>::operator=(const MyVector& ot) {
	if (this == &ot) {
		return *this; // protect against self-assignement
	}
	delete[] this->elems;
	this->elems = new Telem[ot.capacity];
	for (int i = 0; i < ot.size; i++) {
		*(this->elems + i) = ot.elems[i];
	}
	this->capacity = ot.capacity;
	this->size = ot.size;
	return *this;
}

template<typename Telem>
Telem& MyVector<Telem>::operator[](int i) {
	return elems[i];
}

template<typename Telem>
void MyVector<Telem>::add(const Telem& e) {
	if (size == capacity) {
		redim();
	}
	elems[size] = e;
	size++;
}

template<typename Telem>
void MyVector<Telem>::remove(int poz) {
	for (int i = poz; i < size - 1; i++) {
		elems[i] = elems[i + 1];
	}
	size--;
}

template<typename Telem>
void MyVector<Telem>::update(int poz, const Telem& el) {
	elems[poz] = el;
}

template<typename Telem>
Telem& MyVector<Telem>::get(int poz) const noexcept {
	return elems[poz];
}

template<typename Telem>
int MyVector<Telem>::get_size() const noexcept {
	return size;
}

template<typename Telem>
IteratorV<Telem> MyVector<Telem>::begin() noexcept{
	return IteratorV<Telem>{*this};
}

template<typename Telem>
IteratorV<Telem> MyVector<Telem>::end() noexcept{
	return IteratorV<Telem>{*this, size};
}



template <typename Telem>
class IteratorV {

private:
	int curent = 0;
	const MyVector<Telem>& vec;

public:
	/*
		Creates an iterator that points to the first element of MyVector
	*/
	IteratorV(const MyVector<Telem>& v) noexcept;
	
	/*
		Creates an iterator that points after the element n-th poz
	*/
	IteratorV(const MyVector<Telem>& v, int n) noexcept;
	
	/*
		Verify if iterator is valid
		Post: returns true, if iterator points to an element of MyVector
					  false, otherwise
	*/
	bool valid() const;

	/*
		Return the element refrenced by iterator
		Post: return a Telem object
	*/
	Telem& element() const noexcept;

	/*
		Move the itarator to the next element
	*/
	void next() noexcept;

	/*
		Overloading * operator
	*/
	Telem& operator*() noexcept;
	
	/*
		Overloading ++ operator
	*/
	IteratorV& operator++() noexcept;

	/*
		Overloading == operator
	*/
	bool operator==(const IteratorV& ot) noexcept;

	/*
		Overloading != operator
	*/
	bool operator!=(const IteratorV& ot) noexcept;
};

template<typename Telem>
IteratorV<Telem>::IteratorV(const MyVector<Telem>& v) noexcept : vec{ v } {
}

template<typename Telem>
IteratorV<Telem>::IteratorV(const MyVector<Telem>& v, int n) noexcept : vec{ v }, curent{ n } {
}

template<typename Telem>
bool IteratorV<Telem>::valid() const {
	return curent < vec.size;
}

template<typename Telem>
Telem& IteratorV<Telem>::element() const noexcept{
	return vec.elems[curent];
}

template<typename Telem>
void IteratorV<Telem>::next() noexcept{
	curent++;
}

template<typename Telem>
Telem& IteratorV<Telem>::operator*() noexcept{
	return element();
}

template<typename Telem>
IteratorV<Telem>& IteratorV<Telem>::operator++() noexcept{
	next();
	return *this;
}

template<typename Telem>
bool IteratorV<Telem>::operator==(const IteratorV& ot) noexcept {
	return curent == ot.curent;
}

template<typename Telem>
bool IteratorV<Telem>::operator!=(const IteratorV& ot) noexcept {
	return curent != ot.curent;
}


#include <initializer_list>
#include <iostream>
#include <cmath>
class Vector {
	double* array;
	std::size_t size;
public:
	//Parametr typu std::initializer_list pozwoli na uruchomienie
	//konstruktora z dowoln¹ liczb¹ wyst¹pieñ liczb typu double.
	// Bêdzie to wygl¹da³o jak inicjalizacja tablicy. Przyk³ad:
	//Vector v1({1,2,3,4,5,5.5});
	//lub
	//Vector v1{1,2,3,4,5,5.5};
	//lub
	//Vector v1 = {1,2,3,4,5,5.5};
	//Jest to cecha C++11
	Vector(std::initializer_list<double> initList)
		: size{ initList.size() }, array{ new double[initList.size()] }
	{
		std::size_t i = 0;
		for (double v : initList)
		{
			array[i] = v;
			i++;
		}
	}
	Vector(const Vector& other) //Konstruktor kopiujacy
		: size(other.size), array{ new double[other.size] } {
		std::cout << "Vector(const Vector&)" << std::endl;

		for (std::size_t i = 0; i < size; i++)
			array[i] = other.array[i];
	}
	Vector(Vector&& other) {
		std::cout << "Vector(Vector&&)" << std::endl;
		array = other.array; //Pobranie wskaŸnika na dane
		size = other.size; //Kopiowanie rozmiaru wektora
		other.array = nullptr; //Usuwanie odniesienia do danych obiekcie other
		other.size = 0; //Ustawianie rozmiaru wektora na 0
	}
	Vector(const size_t i)
		: size(i), array{ new double[i] } {
		std::cout << "Vector(" << i << ")" << std::endl;
	}

	std::size_t GetSize() const {
		return size;
	}

	const double& operator[](std::size_t i) const {
		return array[i];
	}
	double& operator[](std::size_t i)
	{
		return array[i];
	}
	Vector& operator=(const Vector& right) {
		std::cout << "operator=(const Vector&)" << std::endl;
		Vector tmp = right; //Tworzenie obiektu tymczasowego
		//Zamiana wskaŸników na tablice miejscami
		std::swap(array, tmp.array);
		//Zamiana informacji o wielkoœci tablicy
		std::swap(size, tmp.size);
		return *this;
	}
	Vector& operator=(Vector&& right) {
		std::cout << "operator=(Vector&&)" << std::endl;
		std::swap(array, right.array); //Zamiana wskaŸników na tablice miejscami
		std::swap(size, right.size); //Zamiana informacji o wielkoœc tablicy
		return *this;
	}
	~Vector()
	{
		std::cout << "~Vector()" << std::endl;
		if (array != nullptr)
		{
			std::cout << "Releasing memory " << array << std::endl;
			delete[] array;
		}
	}
};


Vector generuj(double poczatek, double koniec, double krok)
{
	std::size_t liczba = floor((koniec - poczatek) / krok);
	Vector result(liczba);
	for (std::size_t i = 0; i < liczba; i++)
	{
		result[i] = poczatek + i * krok;
	}
	return result;
}
std::ostream& operator<<(std::ostream& ostr, const Vector& v) {
	ostr << "Vector{";
	for (std::size_t i = 0; i < v.GetSize(); i++)
	{
		if (i > 0)
			ostr << ',';
		ostr << v[i];
	}
	ostr << '}';
	return ostr;
}

void wypisz1(Vector v)
{
	std::cout << v << std::endl;
}
void wypisz2(Vector& v)
{
	std::cout << v << std::endl;
}

Vector podzielPrzez2(const Vector& arg)
{
	std::cout << "podzielPrzez2(const Vector&)" << std::endl;
	Vector result = arg;
	for (std::size_t i = 0; i < result.GetSize(); i++)
	{
		result[i] = result[i] / 2;
	}
	return result;
}
Vector podzielPrzez2(Vector&& arg)
{
	std::cout << "podzielPrzez2(Vector&&)" << std::endl;
	/*
	* Mimo i¿ arg jest R-referencj¹, nale¿y zastosowaæ std::move,
	* aby wykorzystaæ jej w³aœciwoœci. Bez tego zostanie wywo³any
	* konstruktor kopiuj¹cy. Jest to cecha jêzyka wymuszaj¹ca na
	* programiœcie jawne okreœlenie miejsca w którym zostaj¹ u¿yte
	* specjalne w³aœciwoœci R-referencji.
	*/
	Vector result = std::move(arg);
	for (std::size_t i = 0; i < result.GetSize(); i++)
	{
		result[i] = result[i] / 2;
	}
	return result;
}

class Envelope
{
	Vector vector;
	friend std::ostream& operator<<(std::ostream&, const Envelope&);
public:
	Envelope(const Vector& vector) :
		vector{ vector } {
		std::cout << "Envelope(const Vector&)" << std::endl;
	}
	Envelope(Vector&& vector) :
		vector{ std::move(vector) } {
		std::cout << "Envelope(Vector&&)" << std::endl;
	}
	Envelope(const Envelope& other) :
		vector{ other.vector } {
		std::cout << "Envelope(const Envelope&)" << std::endl;
	}
	Envelope(Envelope&& other) :
		vector{ std::move(other.vector) } {
		std::cout << "Envelope(Envelope&&)" << std::endl;
	}
	Envelope& operator=(const Envelope& right) {
		std::cout << "operator=(const Envelope&)" << std::endl;
		Envelope tmp(right);
		std::cout << "operator=(const Envelope&) swap pocz¹tek" <<
			std::endl;
		std::swap(vector, tmp.vector);
		std::cout << "operator=(const Envelope&) swap koniec" <<
			std::endl;
		return *this;
	}
	Envelope& operator=(Envelope&& right) {
		std::cout << "operator=(Envelope&&)" << std::endl;
		vector = std::move(right.vector);
		return *this;
	}
	~Envelope() {
		std::cout << "~Envelope()" << std::endl;
	}
};
std::ostream& operator<<(std::ostream& ostr, const Envelope& e)
{
	ostr << "Envelope{vector: " << e.vector << '}';
	return ostr;
}

/*
int main(int argc, char** argv) {
	std::cout << "Konstruktor z r-referencj¹" << std::endl;
	Envelope e1{ Vector{1,2,3} };
	std::cout << "e1: " << e1 << std::endl;
	std::cout << "Konstrukor przenosz¹cy" << std::endl;
	Envelope e2 = std::move(e1);
	std::cout << "e1: " << e1 << std::endl;
	std::cout << "e2: " << e2 << std::endl;
	std::cout << "Przenosz¹cy operator przypisania" << std::endl;
	e1 = std::move(e2);
	std::cout << "e1: " << e1 << std::endl;
	std::cout << "e2: " << e2 << std::endl;
	std::cout << "operator przypisania copy-swap pocz¹tek" << std::endl;
	e2 = e1;
	std::cout << "operator przypisania copy-swap koniec" << std::endl;
	std::cout << "e1: " << e1 << std::endl;
	std::cout << "e2: " << e2 << std::endl;
}
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Sejur
{
	unsigned const int id;
	//static unsigned int idgen;
	char* destinatie;
	int pretBaza;
	int nrExcursiiOptionale;
	unsigned int pretExcursie;
public:
	Sejur(unsigned const int fid) : destinatie(NULL), pretBaza(0), nrExcursiiOptionale(0), pretExcursie(0), id(fid) {}
	Sejur(int fid, const char* fdestinatie, int fpretBaza, int fnrExcursiiOptionale, unsigned int fpretExcursie) : id(fid), pretBaza(fpretBaza), nrExcursiiOptionale(fnrExcursiiOptionale), pretExcursie(fpretExcursie)
	{
		if (fdestinatie)
		{
			destinatie = new char[strlen(fdestinatie) + 1];
			strcpy(destinatie, fdestinatie);
		}
	}
	~Sejur()
	{
		delete[] destinatie;
	}
	int getNrMaximExcursii(float bugetMaximSejur) const
	{
		return int((bugetMaximSejur - pretBaza) / pretExcursie);
	}
	Sejur(const Sejur& s) : id(s.id), pretBaza(s.pretBaza), nrExcursiiOptionale(s.nrExcursiiOptionale), pretExcursie(s.pretExcursie)
	{
		destinatie = new char[strlen(s.destinatie) + 1];
		strcpy(destinatie, s.destinatie);
	}
	Sejur& operator=(const Sejur& s)
	{
		if (this == &s) return *this;
		this->pretBaza = s.pretBaza;
		this->nrExcursiiOptionale = s.nrExcursiiOptionale;
		this->pretExcursie = s.pretExcursie;
		delete[] destinatie;
		destinatie = nullptr;
		destinatie = new char[strlen(s.destinatie) + 1];
		strcpy(destinatie, s.destinatie);
		return *this;
	}
	explicit operator float() const
	{
		return (pretBaza + nrExcursiiOptionale * pretExcursie);
	}
	friend ostream& operator<<(ostream& os, Sejur& s)
	{
		os << "Id: " << s.id << endl;
		os << "Destinatie:" << (s.destinatie ? s.destinatie : "(null)") << endl; //ms chat
		os << "Pret baza: " << s.pretBaza << endl;
		os << "Nr excursii optionale: " << s.nrExcursiiOptionale << endl;
		os << "Pret excursii: " << s.pretExcursie << endl;
		return os;
	}
	friend istream& operator>>(istream& is, Sejur& s) { //ms chat
		char buffer[256];

		cout << "Destinatie: ";
		is >> ws;                 // sare peste spatii/newline
		is.getline(buffer, 256);  // citeste cu spatii

		delete[] s.destinatie;
		s.destinatie = new char[strlen(buffer) + 1];
		strcpy(s.destinatie, buffer);

		cout << "Pret baza: ";
		is >> s.pretBaza;

		cout << "Numar excursii: ";
		is >> s.nrExcursiiOptionale;

		cout << "Pret excursie: ";
		is >> s.pretExcursie;

		return is;
	}
};

//unsigned int Sejur::idgen = 0;

int main()
{
	Sejur s1(10);
	Sejur s2(20, "Bucuresti", 10, 3, 5);
	cout << s2.getNrMaximExcursii(102) << endl;
	cin >> s1;
	cout << s1 << s2;

	return 0;
}
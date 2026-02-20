#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Sejur
{
	unsigned const int id;
	char* destinatie;
	int pretBaza;
	int nrExcursiiOptionale;
	float* pretExcursie;
	void alocareDin(const float* v, const int num)
	{
		delete[] pretExcursie;
		pretExcursie = nullptr;
		nrExcursiiOptionale = 0;
		if (v != nullptr && num > 0)
		{
			pretExcursie = new float[num];
			for (int i = 0; i < num; i++)
				pretExcursie[i] = v[i];
			nrExcursiiOptionale = num;
		}
	}
public:
	Sejur(int fid) : id(fid), destinatie(NULL), pretBaza(0), nrExcursiiOptionale(0), pretExcursie(NULL){}
	Sejur(int fid, const char* fdestinatie, int pretBaza, int fnrExcursiiOptionale, float* v) : id(fid), pretBaza(pretBaza)
	{
		if (fdestinatie)
		{
			destinatie = new char[strlen(fdestinatie) + 1];
			strcpy(destinatie, fdestinatie);
		}
		alocareDin(v, fnrExcursiiOptionale);
	}
	int getNrMaximExcursii(float bugetMaximSejur)
	{
		float rest;
		rest = bugetMaximSejur - pretBaza;
		float pretTotalExcursii = 0;
		for (int i = 0; i < nrExcursiiOptionale; i++)
		{
			pretTotalExcursii += pretExcursie[i];
		}
		return int(rest / pretTotalExcursii);
	}
	Sejur(const Sejur& s) : id(s.id), pretBaza(s.pretBaza), nrExcursiiOptionale(s.nrExcursiiOptionale)
	{
		if (s.destinatie)
		{
			destinatie = new char[strlen(s.destinatie) + 1];
			strcpy(destinatie, s.destinatie);
		}
		alocareDin(s.pretExcursie, s.nrExcursiiOptionale);
	}
	Sejur& operator=(const Sejur& s)
	{
		if (this == &s) return *this;
		delete[] destinatie;
		destinatie = nullptr;
		if (s.destinatie)
		{
			destinatie = new char[strlen(s.destinatie) + 1];
			strcpy(destinatie, s.destinatie);
		}
		alocareDin(s.pretExcursie, s.nrExcursiiOptionale);
		return *this;
	}
	explicit operator float() const
	{
		float sum = 0;
		for (int i = 0; i < nrExcursiiOptionale; i++)
			sum += pretExcursie[i];
		return sum;
	}
	friend ostream& operator<<(ostream& os, Sejur& s)
	{
		os << "ID: " << s.id << endl;
		os << "Destinatie: " << (s.destinatie ? s.destinatie : "(NULL)") << endl;
		os << "Pret baza: " << s.pretBaza << endl;
		os << "Numar excursii optionale: " << s.nrExcursiiOptionale << endl;
		for (int i = 0; i < s.nrExcursiiOptionale; i++)
		{
			os << "Excursia cu numarul " << i + 1 << " are un pret de " << s.pretExcursie[i] << endl;
		}
		return os;
	}
	friend istream& operator>>(istream& is, Sejur& s)
	{
		char buffer[256];
		cout << "Destinatie: ";
		is >> ws;
		is.getline(buffer, 256);

		delete[] s.destinatie;
		s.destinatie = new char[strlen(buffer) + 1];
		strcpy(s.destinatie, buffer);
		cout << "Pret de baza: "; is >> s.pretBaza;
		cout << "Numar excursii optionale: "; is >> s.nrExcursiiOptionale;
		delete[] s.pretExcursie;
		s.pretExcursie = new float[s.nrExcursiiOptionale];
		for (int i = 0; i < s.nrExcursiiOptionale; i++)
		{
			cout << "Introduceti pretul excursiei " << i + 1 << ": ";
			is >> s.pretExcursie[i];
		}
		return is;
	}

	bool operator<(float num) const
	{
		float max = 0;
		for (int i = 0; i < nrExcursiiOptionale; i++)
			if (max < pretExcursie[i])
				max = pretExcursie[i];
		return max < num;
	}
	bool operator>=(float num) const
	{
		float max = 0;
		for (int i = 0; i < nrExcursiiOptionale; i++)
			if (max < pretExcursie[i])
				max = pretExcursie[i];
		return num >= max;
	}
	~Sejur()
	{
		delete[] pretExcursie;
		delete[] destinatie;
	}
};


int main()
{
	float v[] = { 15.4, 12.3, 18.1, 6.7 };
	Sejur s1(10), s2(10, "Bucuresti", 13, 4, v);
	cout << s2;
	//cin >> s1;
	//cout << s1;
	cout << (s2 < 10.5);
	cout << (s2 >= 18.1);
	return 0;
}
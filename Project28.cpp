#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

using namespace std;
class PoateAtaca
{
public:
	virtual void ataca() = 0;
};
class Personaje : public PoateAtaca
{
	const int cod;
	string nume;
	string* numeAbilitati;
	float* costAbilitati;
	int nrAbilitati;
public:
	Personaje() : cod(0), nume("Unknown"), numeAbilitati(nullptr), costAbilitati(nullptr), nrAbilitati(0){}
	Personaje(const int cod, string nume, const string* fnumeAbilitati, const float* fcostAbilitati, int nrAbilitati) : cod(cod), nume(nume), numeAbilitati(nullptr), costAbilitati(nullptr), nrAbilitati(nrAbilitati)
	{
		if (fnumeAbilitati != nullptr && nrAbilitati > 0)
		{
			numeAbilitati = new string[nrAbilitati];
			for (int i = 0; i < nrAbilitati; i++)
				numeAbilitati[i] = fnumeAbilitati[i];
		}
		if (fcostAbilitati != nullptr && nrAbilitati > 0)
		{
			costAbilitati = new float[nrAbilitati];
			for (int i = 0; i < nrAbilitati; i++)
				costAbilitati[i] = fcostAbilitati[i];
		}
	}
	Personaje(const Personaje& p) : cod(p.cod), nume(p.nume), numeAbilitati(nullptr), costAbilitati(nullptr), nrAbilitati(p.nrAbilitati)
	{
		if (p.numeAbilitati != nullptr && p.nrAbilitati > 0)
		{
			numeAbilitati = new string[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				numeAbilitati[i] = p.numeAbilitati[i];
		}
		if (p.costAbilitati != nullptr && p.nrAbilitati > 0)
		{
			costAbilitati = new float[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				costAbilitati[i] = p.costAbilitati[i];
		}
	}
	Personaje& operator=(const Personaje& p)
	{
		if (this == &p) return *this;
		this->nume = p.nume;
		this->nrAbilitati = p.nrAbilitati;
		if (p.numeAbilitati != nullptr && p.nrAbilitati > 0)
		{
			delete[] numeAbilitati;
			numeAbilitati = nullptr;
			numeAbilitati = new string[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				numeAbilitati[i] = p.numeAbilitati[i];
		}
		if (p.costAbilitati != nullptr && p.nrAbilitati > 0)
		{
			delete[] costAbilitati;
			costAbilitati = nullptr;
			costAbilitati = new float[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				costAbilitati[i] = p.costAbilitati[i];
		}
		return *this;
	}
	virtual ~Personaje()
	{
		delete[] numeAbilitati;
		delete[] costAbilitati;
	}
	string getNume()
	{
		return this->nume;
	}
	void setNume(string numeNou)
	{
		this->nume = numeNou;
	}
	void operator+(float num)
	{
		if(num > 0)
			for (int i = 0; i < this->nrAbilitati; i++)
				this->costAbilitati[i] += num;
	}
	friend ostream& operator<<(ostream& os, const Personaje& p)
	{
		os << " " << p.cod << " " << p.nume;
		for (int i = 0; i < p.nrAbilitati; i++)
		{
			os << " " << p.numeAbilitati[i] << ":";
			os << " " << p.costAbilitati[i] << "\n";
		}
		os << " " << p.nrAbilitati;
		return os;
	}
	void ataca() override 
	{
		cout << this->nume << " ataca!";
	}
};

class Master : public Personaje, public PoateAtaca
{
	string titlu;
	string finalBoss;
public:
	Master() : Personaje(), titlu("Unknown"), finalBoss("Unknown") {}
	Master(const int cod, string nume, const string* numeAbilitati, const float* costAbilitati, int nrAbilitati, string titlu,string finalBoss) : Personaje(cod,nume,numeAbilitati,costAbilitati,nrAbilitati), titlu(titlu), finalBoss(finalBoss){}
	void ataca() override
	{
		cout << this->titlu << this->finalBoss << " ataca!";
	}

};


int main()
{
	string v1[] = { "q", "w", "e", "r" };
	float v2[] = { 13.2,22.3,12.2,11.1 };

	Personaje p1, p2(10,"Tataia tare-n coaie", v1,v2,4);
	Master m1;
	Personaje* p3 = &m1; //Upcasting
	Personaje* p4 = new Master();
	Master* m2 = dynamic_cast<Master*>(p4);//Downcasting;
	cout << p2;
	p2 + 10;
	cout << p2;
	p2.ataca();
	return 0;
}
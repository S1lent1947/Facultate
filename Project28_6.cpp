#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

using namespace std;


class Personaje
{
private:
	string nume;
	int nrAbilitati;
	string* numeAbilitati;
	float* costAbilitati;
	const int codPersonaj;
public:
	Personaje() : nume("Unknown"), nrAbilitati(0), numeAbilitati(nullptr), costAbilitati(nullptr), codPersonaj(0){}
	Personaje(string nume, int nrAbilitati, const string* fnumeAbilitati, const float* fcostAbilitati, const int codPersonaj) : nume(nume), nrAbilitati(nrAbilitati), codPersonaj(codPersonaj), numeAbilitati(nullptr),costAbilitati(nullptr)
	{
		if (fnumeAbilitati != nullptr && nrAbilitati > 0)
		{
			this->numeAbilitati = new string[nrAbilitati];
			for (int i = 0; i < nrAbilitati; i++)
				this->numeAbilitati[i] = fnumeAbilitati[i];
		}
		if (fcostAbilitati != nullptr && nrAbilitati > 0)
		{
			this->costAbilitati = new float[nrAbilitati];
			for (int i = 0; i < nrAbilitati; i++)
				this->costAbilitati[i] = fcostAbilitati[i];
		}
	}
	Personaje(const Personaje& p) : nume(p.nume), nrAbilitati(p.nrAbilitati), codPersonaj(p.codPersonaj), numeAbilitati(nullptr), costAbilitati(nullptr)
	{
		if (p.numeAbilitati != nullptr && p.nrAbilitati > 0)
		{
			this->numeAbilitati = new string[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				this->numeAbilitati[i] = p.numeAbilitati[i];
		}
		if (p.costAbilitati != nullptr && p.nrAbilitati > 0)
		{
			this->costAbilitati = new float[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				this->costAbilitati[i] = p.costAbilitati[i];
		}
	}
	Personaje operator++(int)
	{
		Personaje p = (*this);
		p.nrAbilitati++;
		string* tempNume = new string[p.nrAbilitati];
		float* tempCost = new float[p.nrAbilitati];
		for (int i = 0; i < p.nrAbilitati - 1; i++)
		{
			tempNume[i] = p.numeAbilitati[i];
			tempCost[i] = p.costAbilitati[i];
		}
		string tempString;
		float tempCostAbilitati;
		cin >> tempCostAbilitati >> tempString;
		tempNume[p.nrAbilitati - 1] = tempString;
		tempCost[p.nrAbilitati - 1] = tempCostAbilitati;
		delete[] p.numeAbilitati;
		delete[] p.costAbilitati;
		p.numeAbilitati = nullptr;
		p.costAbilitati = nullptr;
		p.numeAbilitati = new string[p.nrAbilitati];
		p.costAbilitati = new float[p.nrAbilitati];
		p.numeAbilitati = tempNume;
		p.costAbilitati = tempCost;
		return p;
	}
	Personaje& operator++()
	{
		nrAbilitati++;
		string* tempNume = new string[nrAbilitati];
		float* tempCost = new float[nrAbilitati];
		for (int i = 0; i < nrAbilitati - 1; i++)
		{
			tempNume[i] = numeAbilitati[i];
			tempCost[i] = costAbilitati[i];
		}
		string tempString;
		float tempCostAbilitati;
		cin >> tempCostAbilitati >> tempString;
		tempNume[nrAbilitati - 1] = tempString;
		tempCost[nrAbilitati - 1] = tempCostAbilitati;
		delete[] numeAbilitati;
		delete[] costAbilitati;
		numeAbilitati = nullptr;
		costAbilitati = nullptr;
		numeAbilitati = new string[nrAbilitati];
		costAbilitati = new float[nrAbilitati];
		numeAbilitati = tempNume;
		costAbilitati = tempCost;
		return *this;
	}
	Personaje& operator=(const Personaje& p)
	{
		if (this == &p) return *this;
		this->nume = p.nume;
		this->nrAbilitati = p.nrAbilitati;
		this->numeAbilitati = nullptr;
		this->costAbilitati = nullptr;
		if (p.numeAbilitati != nullptr && p.nrAbilitati > 0)
		{
			delete[] numeAbilitati;
			this->numeAbilitati = new string[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				this->numeAbilitati[i] = p.numeAbilitati[i];
		}
		if (p.costAbilitati != nullptr && p.nrAbilitati > 0)
		{
			delete[] costAbilitati;
			this->costAbilitati = new float[p.nrAbilitati];
			for (int i = 0; i < p.nrAbilitati; i++)
				this->costAbilitati[i] = p.costAbilitati[i];
		}
		return *this;
	}
	string getNume()
	{
		return this->nume;
	}

	void setNume(string numeNou)
	{
		this->nume = numeNou;
		return;
	}
	~Personaje()
	{
		delete[] numeAbilitati;
		delete[] costAbilitati;
	}
	Personaje operator+(float num)
	{
		Personaje p = *this;
		for (int i = 0; i < p.nrAbilitati; i++)
			p.costAbilitati[i] += num;
		return p;
	}
	
	friend ostream& operator<<(ostream& os, const Personaje& p)
	{
		os << p.nume << " " << p.nrAbilitati << endl;
		for (int i = 0; i < p.nrAbilitati; i++)
			os << " " << p.numeAbilitati[i] << " :" << p.costAbilitati[i] << endl;
		os << "  " << p.codPersonaj << endl;
		return os;
	}
};

int main()
{
	string v1[] = { "q", "w" ,"e" };
	float v2[] = { 13.2,12.1,11.8 };
	Personaje p1, p2("Batman", 3, v1,v2,67 );
	cout << p2 + 10 << endl;
	cout << p2;
	//cout << p2++ << endl;
	//cout << p2;
	cout << ++p2 << endl;
	cout << p2;
	return 0;
}
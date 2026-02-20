#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

enum Tip
{
	EROU,
	ANTAGONIST
};
class Rucsac
{
	float capacitate;
public:
	Rucsac() : capacitate(0){}
	Rucsac(int capacitate) : capacitate(capacitate){}
	Rucsac(const Rucsac& r) : capacitate(r.capacitate){}
	~Rucsac(){}
	friend ostream& operator<<(ostream& os, const Rucsac& r)
	{
		os << r.capacitate;
		return os;
	}
};
class Om
{
public:
	virtual void saluta() const
	{
		cout << "Salut!";
	}
	virtual void prezinta() const = 0;
	virtual ~Om() {}
};
class Personaje : public Om
{
	string nume;
	Tip tip;
	float* greutateBagaje;
	int nrBagaje;
	Rucsac rucsac;
public:
	Personaje() : nume("Unknown"), tip(EROU), greutateBagaje(nullptr), nrBagaje(0), rucsac(0){}
	Personaje(string nume, Tip tip, const float* fgreutateBagaje, int fnrBagaje, float capacitate, Rucsac r) : nume(nume), tip(tip), greutateBagaje(nullptr), nrBagaje(fnrBagaje), rucsac(r)
	{
		if (fgreutateBagaje && fnrBagaje > 0)
		{
			greutateBagaje = new float[fnrBagaje];
			for (int i = 0; i < fnrBagaje; i++)
				greutateBagaje[i] = fgreutateBagaje[i];
		}
	}
	Personaje(const Personaje& p) : nume(p.nume), tip(p.tip), nrBagaje(p.nrBagaje), greutateBagaje(nullptr), rucsac(p.rucsac)
	{
		if (p.greutateBagaje && p.nrBagaje > 0)
		{
			greutateBagaje = new float[p.nrBagaje];
			for (int i = 0; i < p.nrBagaje; i++)
				greutateBagaje[i] = p.greutateBagaje[i];
		}
	}
	Personaje& operator=(const Personaje& p)
	{
		if (this == &p) return *this;
		this->nume = p.nume;
		this->tip = p.tip;
		this->nrBagaje = p.nrBagaje;
		if (p.greutateBagaje && p.nrBagaje > 0)
		{
			this->greutateBagaje = new float[p.nrBagaje];
			for (int i = 0; i < p.nrBagaje; i++)
				this->greutateBagaje[i] = p.greutateBagaje[i];
		}
		return *this;
	}
	~Personaje(){}
	Tip getTip()
	{
		return this->tip;
	}
	void setTip(int newTip)
	{
		this->tip = (Tip)newTip;
	}
	void CodRosu()
	{
		float totalGreutate = 0;
		for (int i = 0; i < nrBagaje; i++)
			totalGreutate += greutateBagaje[i];
		cout << " \n" << totalGreutate << endl;
		nrBagaje = 0;
		delete[] greutateBagaje;
		greutateBagaje = nullptr;
	}
	void setNrBagaje(int num)
	{
		this->nrBagaje = num;
	}
	void setGreutate(const float* v, const int num)
	{
		if (v != nullptr && num > 0)
		{
			delete[] greutateBagaje;
			greutateBagaje = nullptr;
			greutateBagaje = new float[num];
			for (int i = 0; i < num; i++)
			{
				greutateBagaje[i] = v[i];
			}
		}
	}
	bool operator!=(Tip compTip)
	{
		return (this->tip != compTip);
	}
	friend ostream& operator<<(ostream& os, const Personaje& p)
	{
		os << p.nume << " " << p.tip <<" " << p.nrBagaje;
		if (p.nrBagaje != 0)
		{
			for (int i = 0; i < p.nrBagaje; i++)
				os << " " << p.greutateBagaje[i];
		}
		else
			os << "\n" << "Numarul de bagaje este 0!" << endl;
		return os;
	}
	 void prezinta() const override
	{
		 cout << "Eu sunt aventurierul! " << nume << endl;
	}
	 friend ofstream& operator<<(ofstream& of, const Personaje& p)
	 {
		 of << p.nume << " " << p.tip << " " << p.nrBagaje;
		 for (int i = 0; i < p.nrBagaje; i++)
			 of << " " << p.greutateBagaje[i];
		 return of;
	 }
	 friend ifstream& operator>>(ifstream& ifs, Personaje& p)
	 {
		 ifs >> p.nume;
		 int newTip;
		 ifs >> newTip;
		 p.setTip(newTip);
		 int num;
		 ifs >> num;
		 p.setNrBagaje(num);
		 float* v = new float[num];
		 for (int i = 0; i < num; i++)
			 ifs >> v[i];
		 p.setGreutate(v, num);
		 return ifs;
	 }
};


int main()
{
	float v[] = { 13.4, 15.2, 11.0 };
	Personaje p1, p2("Batman", EROU, v, 3, 14.87,10);
	cout << p2;
	//p2.CodRosu();
	//cout << p2;
	ofstream fout;
	fout.open("Personaje.txt", ofstream::out);
	if (fout.is_open())
	{
		fout << p2;
		fout.close();
	}
	ifstream fin;
	fin.open("Personaje.txt", ifstream::in);
	if (fin.is_open())
	{
		fin >> p1;
		fin.close();
	}
	cout << "\n" << p1;
		
	return 0;
}
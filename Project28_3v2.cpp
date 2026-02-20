#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class Petitii
{
private:
	static int idgen;
	int id;
	char* data;
	string nume;
	string prenume;
	bool stare; //deschis -> false , rezolvata -> true;
	int zileDepunere;
public:
	Petitii() : id(idgen++), data(nullptr), nume("Unknown"), prenume("Unknown"), stare(false), zileDepunere(0) {}
	Petitii(const char* fdata, string nume, string prenume, bool stare, int zileDepunere) : id(idgen++),data(nullptr), nume(nume), prenume(prenume), stare(stare), zileDepunere(zileDepunere)
	{
		if (fdata)
		{
			data = new char[strlen(fdata) + 1];
			strcpy(data, fdata);
		}
	}
	Petitii(const Petitii& p) : data(nullptr), id(idgen++),nume(p.nume), prenume(p.prenume), stare(p.stare), zileDepunere(p.zileDepunere)
	{
		if (p.data)
		{
			data = new char[strlen(p.data) + 1];
			strcpy(data, p.data);
		}
	}
	virtual ~Petitii()
	{
		delete[] data;
	}
	virtual char* getData()
	{
		return this->data;
	}
	virtual void setData(const char* newData)
	{
		if (newData)
		{
			delete[] data;
			data = nullptr;
			data = new char[strlen(newData) + 1];
			strcpy(data, newData);
		}
	}
	friend ostream& operator<<(ostream& os, const Petitii& p)
	{
		os << p.id << p.data << p.nume << p.prenume << p.stare << p.zileDepunere << endl;
		return os;
	}
	bool operator!()
	{
		return !(stare && zileDepunere > 30);
	}
	Petitii& operator~()
	{
		this->stare = true;
		return *this;
	}

	friend ofstream& operator<<(ofstream& of, const Petitii& p)
	{
		of << p.id << " " << p.data << " " << p.nume <<" " << p.prenume <<" " << p.stare <<" " << p.zileDepunere << endl;
		return of;
	}
	friend ifstream& operator>>(ifstream& ifs, Petitii& p)
	{
		ifs >> p.id;
		char buffer[20];
		ifs >> buffer;
		p.setData(buffer);

		ifs >> p.nume >> p.prenume >> p.stare >> p.zileDepunere;

		return ifs;
	}

};

class petitiiOnline : public Petitii
{
private:
	string adresaEmail;
public:
	petitiiOnline() : Petitii(), adresaEmail("Unknown"){}
	petitiiOnline(const char* fdata, string nume, string prenume, bool stare, int zileDepunere, string adresaEmail) : Petitii(fdata, nume,prenume,stare,zileDepunere), adresaEmail(adresaEmail){}
	petitiiOnline(const petitiiOnline& p) : Petitii(p) , adresaEmail(p.adresaEmail){}
	virtual ~petitiiOnline(){}
};	
int Petitii::idgen = 1000;
int main()
{
	Petitii p1, p2("17-03-2024", "Bosorog", "Tataie", false, 40);
	cout << p2;
	cout << !p2;
	cout << ~p2;
	ofstream fout;
	fout.open("Tataie.txt", ofstream::out);
	if (fout.is_open())
	{
		fout << p2;
		fout.close();
	}
	ifstream fin;
	fin.open("Tataie.txt", ifstream::in);
	if (fin.is_open())
	{
		fin >> p1;
		fin.close();
	}
	cout << p1;
	return 0;
}
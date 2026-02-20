#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

class Marfa
{
protected:
	string cod;
	string nume;
	double pretUnitar;
	int anFabricatie;
	string tara;
	double indiceCalitate;
public:
	Marfa() : cod("Unknown"), nume("Unknown"), pretUnitar(0), anFabricatie(2025), tara("Unknown"), indiceCalitate(1){}
	Marfa(string cod, string nume, double pretUnitar, int anFabricatie, string tara, double indiceCalitate) : cod(cod), nume(nume),pretUnitar(pretUnitar),anFabricatie(anFabricatie),tara(tara),indiceCalitate(indiceCalitate){}
	Marfa(const Marfa& m) : cod(m.cod), nume(m.nume), pretUnitar(m.pretUnitar), anFabricatie(m.anFabricatie), tara(m.tara), indiceCalitate(m.indiceCalitate){}
	friend ostream& operator<<(ostream& os, const Marfa& m)
	{
		os << "Cod: " << m.cod << endl;
		os << "Nume: " << m.nume << endl;
		os << "Pret unitar: " << m.pretUnitar << endl;
		os << "An fabricatie: " << m.anFabricatie << endl;
		os << "Tara: " << m.tara << endl;
		os << "Indice calitate: " << m.indiceCalitate << endl;
		return os;
	}
	virtual string getTipTransport() = 0;
	virtual double getPretFinal()
	{
		return this->pretUnitar;
	}
	virtual ~Marfa(){}
	string getCod()
	{
		return this->cod;
	}
};

class MarfaGenerala : public Marfa
{
protected:
	double greutate;
	double volum;
public:
	MarfaGenerala() : Marfa(), greutate(0), volum(0){}
	MarfaGenerala(string cod, string nume, double pretUnitar, int anFabricatie, string tara, double indiceCalitate, double greutate, double volum) : Marfa(cod,nume,pretUnitar,anFabricatie,tara,indiceCalitate), greutate(greutate), volum(volum){}
	string getTipTransport() override
	{
		return "Naval";
	}
	double getPretFinal() override
	{
		if (greutate > 1000)
			return pretUnitar *= 1.2;
		return pretUnitar;
	}
	friend ostream& operator<<(ostream& os, const MarfaGenerala& m)
	{
		os << "Cod: " << m.cod << endl;
		os << "Nume: " << m.nume << endl;
		os << "Pret unitar: " << m.pretUnitar << endl;
		os << "An fabricatie: " << m.anFabricatie << endl;
		os << "Tara: " << m.tara << endl;
		os << "Indice calitate: " << m.indiceCalitate << endl;
		os << "Greutate: " << m.greutate << endl;
		os << "Volum: " << m.volum << endl;
		return os;
	}
	~MarfaGenerala(){}
};


class MarfaPerisabila : public Marfa
{
protected:
	double temperaturaDepozitare;
	int durataValabilitate;
public:
	MarfaPerisabila() : Marfa(), temperaturaDepozitare(0), durataValabilitate(0){}
	MarfaPerisabila(string cod, string nume, double pretUnitar, int anFabricatie, string tara, double indiceCalitate, double temperaturaDepozitare, int durataValabilitate) : Marfa(cod,nume,pretUnitar,anFabricatie,tara,indiceCalitate), temperaturaDepozitare(temperaturaDepozitare), durataValabilitate(durataValabilitate){}
	string getTipTransport() override
	{
		return "aerian";
	}
	double getPretFinal()override
	{
		return pretUnitar *= 1.5;
	}
	friend ostream& operator<<(ostream& os, const MarfaPerisabila& m)
	{
		os << "Cod: " << m.cod << endl;
		os << "Nume: " << m.nume << endl;
		os << "Pret unitar: " << m.pretUnitar << endl;
		os << "An fabricatie: " << m.anFabricatie << endl;
		os << "Tara: " << m.tara << endl;
		os << "Indice calitate: " << m.indiceCalitate << endl;
		os << "Temperatura de depozitare: " << m.temperaturaDepozitare << endl;
		os << "Durata valabilitate: " << m.durataValabilitate << endl;
		return os;
	}
	~MarfaPerisabila(){}
};

class MarfaDigitala : public MarfaGenerala
{
protected:
	int codLicenta;
public:
	MarfaDigitala() : MarfaGenerala(), codLicenta(0){}
	MarfaDigitala(string cod, string nume, double pretUnitar, int anFabricatie, string tara, double indiceCalitate, double greutate, double volum, int codLicenta) : MarfaGenerala(cod, nume, pretUnitar, anFabricatie, tara, indiceCalitate, greutate, volum), codLicenta(codLicenta){}
	string getTipTransport() override
	{
		return "electronic";
	}
	double getPretFinal()override
	{
		return pretUnitar *= 0.6;
	}
	friend ostream& operator<<(ostream& os, const MarfaDigitala& m)
	{
		os << "Cod: " << m.cod << endl;
		os << "Nume: " << m.nume << endl;
		os << "Pret unitar: " << m.pretUnitar << endl;
		os << "An fabricatie: " << m.anFabricatie << endl;
		os << "Tara: " << m.tara << endl;
		os << "Indice calitate: " << m.indiceCalitate << endl;
		os << "Greutate: " << m.greutate << endl;
		os << "Volum: " << m.volum << endl;
		os << "Cod licenta: " << m.codLicenta << endl;
		return os;
	}
	~MarfaDigitala(){}
};

class Firma
{
protected:
	vector<Marfa*> marfuri;
	double profitTotal;
	map<string, int> tranzactii;
public:
	Firma() : profitTotal(0){}
	~Firma() {
		for (auto me : marfuri)
			delete me;
		marfuri.clear();
	}
	void adaugaMarfa(Marfa* marfa)
	{
		if (marfa == nullptr) return;
		for (auto me : marfuri)
			if (me->getCod() == marfa->getCod())
				return;
			
		marfuri.push_back(marfa);
	}
	friend ostream& operator<<(ostream& os, const Firma& f)
	{
		os << "Profit total: " << f.profitTotal;
		for (const auto me : f.marfuri)
		{
			os << me;
		}
		for (const auto me : f.tranzactii)
		{
			os << me.first << "->" << me.second << endl;
		}
		return os;
	}

};


int main()
{

	return 0;
}
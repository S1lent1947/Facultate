#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>

using namespace std;


class bateriiExterne
{
private:
	static int idgen;
	const int id;
	char* producator;
	int capacitate;
	int nivelCurent; //1-100%
public:
	bateriiExterne(const char* fproducator = "Anonim") : id(idgen++), capacitate(0), nivelCurent(0)
	{
		if (fproducator)
		{
			this->producator = new char[strlen(fproducator) + 1];
			strcpy(this->producator, fproducator);
		}
	}
	bateriiExterne(const char* fproducator, int capacitate, int nivelCurent) : id(idgen++), capacitate(capacitate), nivelCurent(nivelCurent)
	{
		if (fproducator)
		{
			this->producator = new char[strlen(fproducator) + 1];
			strcpy(this->producator, fproducator);
		}
	}
	bateriiExterne(const bateriiExterne& b) : id(idgen++), capacitate(b.capacitate), nivelCurent(b.nivelCurent)
	{
		if (b.producator)
		{
			this->producator = new char[strlen(b.producator) + 1];
			strcpy(this->producator, b.producator);
		}
	}
	char* getProducator()
	{
		return this->producator;
	}
	void setProducator(char* nume)
	{
		if (nume)
		{
			delete[] producator;
			producator = nullptr;
			producator = new char[strlen(nume) + 1];
			strcpy(producator, nume);
		}
	}
	int getID()
	{
		return this->id;
	}
	~bateriiExterne()
	{
		delete[] producator;
	}
	friend ostream& operator<<(ostream& os, bateriiExterne& b)
	{
		os << "ID: " << b.id << endl;
		os << "Producator: " << (b.producator ? b.producator : "(NULL)") << endl;
		os << "Capacitate: " << b.capacitate << endl;
		os << "Nivel curent: " << b.nivelCurent << endl;
		return os;
	}
	bateriiExterne& operator+=(int num)
	{
		this->nivelCurent += num;
		return *this;
	}
	bateriiExterne& operator-=(int num)
	{
		this->nivelCurent -= num;
		return *this;
	}
	bool operator==(const bateriiExterne& b)
	{
		if (capacitate != b.capacitate) return false;
		if (nivelCurent != b.nivelCurent) return false;

		if (producator == nullptr && b.producator == nullptr) return true;
		if (producator == nullptr || b.producator == nullptr) return false;
		
		return strcmp(producator, b.producator) == 0;
	}
};

int bateriiExterne::idgen = 1000;
// FC = fast charge
class bateriiExterneFC : public bateriiExterne
{
private:
	float capacitateIncarcare;
public:
	bateriiExterneFC() : bateriiExterne(), capacitateIncarcare(0){}
	bateriiExterneFC(const char* fproducator, int capacitate, int nivelCurent, float capacitateIncarcare) : bateriiExterne(fproducator,capacitate,nivelCurent),capacitateIncarcare(capacitateIncarcare){}
	bateriiExterneFC(const bateriiExterneFC& b) : bateriiExterne(b), capacitateIncarcare(b.capacitateIncarcare){}
	~bateriiExterneFC(){}

	friend ostream& operator<<(ostream& os, bateriiExterneFC& b)
	{
		os << "Capacitate Incarcare: " << b.capacitateIncarcare << endl;
		return os;
	}
};
int main()
{
	bateriiExterne b1, b2("Sonny", 100, 89);
	bateriiExterne b3(b2);
	cout << b2;
	bool valoare;
	valoare = b3 == b2;
	cout << valoare << endl;
	valoare = b1 == b2;
	cout << valoare << endl;
	bateriiExterneFC b4;
	cout << b4;
	return 0;
}
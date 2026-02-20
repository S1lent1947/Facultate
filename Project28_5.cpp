#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>

using namespace std;

class Bascket
{
	const string nume;
	int numarJucatori;
	string* numeleJucatorilor;
	double bugetAnual;
	static double bugetMinim;
public:
	Bascket() : nume("Unknown"), numarJucatori(0), numeleJucatorilor(nullptr), bugetAnual(0){}
	Bascket(const string nume, int numarJucatori, const string* fnumeleJucatorilor, double bugetAnual) : nume(nume), numarJucatori(numarJucatori), bugetAnual(bugetAnual), numeleJucatorilor(nullptr)
	{
		if (fnumeleJucatorilor != nullptr && numarJucatori > 0)
		{
			numeleJucatorilor = new string[numarJucatori];
			for (int i = 0; i < numarJucatori; i++)
				numeleJucatorilor[i] = fnumeleJucatorilor[i];
		}
	}
	Bascket(const Bascket& b) : nume(b.nume), numarJucatori(b.numarJucatori), bugetAnual(b.bugetAnual), numeleJucatorilor(nullptr)
	{
		if (b.numeleJucatorilor != nullptr && b.numarJucatori > 0)
		{
			numeleJucatorilor = new string[numarJucatori];
			for (int i = 0; i < numarJucatori; i++)
				numeleJucatorilor[i] = b.numeleJucatorilor[i];
		}
	}
	Bascket& operator=(const Bascket& b)
	{
		if (this == &b) return *this;
		this->numarJucatori = b.numarJucatori;
		this->bugetAnual = b.bugetAnual;
		if (b.numeleJucatorilor != nullptr && b.numarJucatori > 0)
		{
			delete[] numeleJucatorilor;
			numeleJucatorilor = nullptr;
			for (int i = 0; i < b.numarJucatori; i++)
			{
				numeleJucatorilor[i] = b.numeleJucatorilor[i];
			}
		}
	}
	~Bascket()
	{
		delete[] numeleJucatorilor;
	}
	double getBugetAnual()
	{
		return this->bugetAnual;
	}
	void setBugetAnual(double num)
	{
		this->bugetAnual = num;
	}

	Bascket& operator +=(double num)
	{
		if (num >= 0)
			bugetAnual += num;
		else
			cout << "Valoarea introdusa este una negativa!" << endl;
		return *this;
	}
	 operator float() const
	{
		 if (bugetAnual > bugetMinim)
			 cout << "Poate participa! ";
		 else
			 cout << "Nu poate participa! ";
		 return bugetAnual;
	}
	 virtual void printInfo()
	 {
		 cout << nume << " " << numarJucatori;
		 for (int i = 0; i < numarJucatori; i++)
			 cout << " " << numeleJucatorilor[i];
		 cout << bugetAnual << " " << bugetMinim << endl;
	 }
	 friend ostream& operator<<(ostream& os, const Bascket& b)
	 {
		 os << b.nume << " " << b.numarJucatori;
		 for (int i = 0; i < b.numarJucatori; i++)
			 os << " " << b.numeleJucatorilor[i];
		 os << b.bugetAnual << endl;
		 os << b.bugetMinim << endl;
		 return os;
	 }
};
double Bascket::bugetMinim=10000;


class EchipePro : public Bascket
{
	string denumireSponsor;
public:
	EchipePro() : Bascket(), denumireSponsor("Unknown"){}
	EchipePro(const string nume, int numarJucatori, const string* fnumeleJucatorilor, double bugetAnual, string denumireSponsor) : Bascket(nume,numarJucatori,fnumeleJucatorilor,bugetAnual),denumireSponsor(denumireSponsor){}
	virtual void printInfo()
	{
		Bascket::printInfo();
		cout << denumireSponsor;
	}
};
int main()
{
	string v[] = { "Tataie", "Bosorogul", "C" };
	Bascket b1, b2("Real Madrid", 3, v, 2000);
	cout << b2 << endl;
	b2.printInfo();
	(float)b2;
	return 0;
}
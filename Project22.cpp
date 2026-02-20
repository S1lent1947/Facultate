#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class TrotinetaElectrica
{
	float nivelBaterie;
	float consumPerKm;
	float* kmPersSesiuneInchiriere;
	int nrSesiuniInchiriere;
	void alocareDin(const float* v, int num)
	{
		delete[] kmPersSesiuneInchiriere;
		kmPersSesiuneInchiriere = nullptr;
		nrSesiuniInchiriere = 0;

		if (v != nullptr && num > 0)
		{
			kmPersSesiuneInchiriere = new float[num];
			for (int i = 0; i < num; i++)
				kmPersSesiuneInchiriere[i] = v[i];
			nrSesiuniInchiriere = num;
		}
	}

public:
	TrotinetaElectrica(const float* v = nullptr, int nrSesiuni = 0 ) : nivelBaterie(0), consumPerKm(0), kmPersSesiuneInchiriere(nullptr), nrSesiuniInchiriere(0)
	{
		alocareDin(v, nrSesiuni);
	}
	TrotinetaElectrica(const float* fv, const int fnrSesiuniInchiriere, float fnivelBaterie, float fconsumPerKm) : nivelBaterie(fnivelBaterie), nrSesiuniInchiriere(fnrSesiuniInchiriere), kmPersSesiuneInchiriere(nullptr), consumPerKm(fconsumPerKm)
	{
		alocareDin(fv, fnrSesiuniInchiriere);
	}
	~TrotinetaElectrica()
	{
		delete[] kmPersSesiuneInchiriere;
	}
	TrotinetaElectrica(const TrotinetaElectrica& t) : nivelBaterie(t.nivelBaterie), consumPerKm(t.consumPerKm), nrSesiuniInchiriere(0), kmPersSesiuneInchiriere(nullptr)
	{
		alocareDin(t.kmPersSesiuneInchiriere, t.nrSesiuniInchiriere);
	}
	TrotinetaElectrica operator=(const TrotinetaElectrica& t)
	{
		if (this == &t) return *this;
		alocareDin(t.kmPersSesiuneInchiriere, t.nrSesiuniInchiriere);
		this->consumPerKm = t.consumPerKm;
		this->nivelBaterie = t.nivelBaterie;
		return *this;
	}
	friend ostream& operator<<(ostream& os, const TrotinetaElectrica& t)
	{
		os << "Nivelul bateriei este: " << t.nivelBaterie << "\nConsumul per Km este de: " << t.consumPerKm << "\nNumarul de sesiuni este de: " << t.nrSesiuniInchiriere << endl;
		for (int i = 0; i < t.nrSesiuniInchiriere; i++)
		{
			os << "In sesiunea cu numarul " << i + 1 << " au fost parcursi " << t.kmPersSesiuneInchiriere[i] << "km!\n";
		}
		return os;
	}
	TrotinetaElectrica& operator+=(float km)
	{
		float* nou = new float[nrSesiuniInchiriere + 1];
		for (int i = 0; i < nrSesiuniInchiriere; i++)
			nou[i] = kmPersSesiuneInchiriere[i];

		nou[nrSesiuniInchiriere] = km;

		delete[] kmPersSesiuneInchiriere;
		kmPersSesiuneInchiriere = nou;
		nrSesiuniInchiriere++;

		return *this;
	}
};
int main()
{
	float v[] = { 5.5f, 7.2f, 10.0f };

	// constructor cu parametri
	TrotinetaElectrica t1(v, 3, 80.0f, 2.5f);

	// afisare (operator <<)
	cout << "t1 initial:\n" << t1 << "\n";

	// constructor de copiere
	TrotinetaElectrica t2 = t1;
	cout << "t2 (copie t1):\n" << t2 << "\n";

	// operator =
	TrotinetaElectrica t3;
	t3 = t1;
	cout << "t3 (dupa = t1):\n" << t3 << "\n";

	// operator += (adauga sesiune noua)
	t1 += 12.5f;
	cout << "t1 dupa += 12.5:\n" << t1 << "\n";

	return 0;
}

#include<iostream>
using namespace std;

class ProdR
{
protected:
	string np;
	int cm, cs, p;
	float pret;
	virtual void calcul_pret()
	{
		pret = cm + cs + p;
	}
public:
	ProdR() : np("Nedefinit"), cm(0), cs(0), p(0) {}
	ProdR(string fnp, int fcm, int fcs, int fp) : np(fnp), cm(fcm), cs(fcs), p(fp) {}
	friend ostream& operator<<(ostream& os, ProdR& obp)
	{
		obp->calcul_pret();
		os << "Produsul " << obp->np << " are pretul: " << obp->pret << endl;
		return os;
	}
};

class ProdA : public ProdR
{
	int ac;
	void calcul_pret()
	{
		ProdR::calcul_pret();
		pret += ac;
	}
public:
	ProdA() : ac(0) {}
	ProdA(string fnp, int fcm, int fcs, int fp, int fac) :ProdR(fnp, fcm, fcs, fp), ac(fac) {}

};

void main()
{
	ProdR* po1, * po2;
	po1 = new ProdR("Tabla", 100, 20, 5);
	po2 = new ProdA("Tigla", 180, 25, 5, 10);
	cout << po1 << po2;
}
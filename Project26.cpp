#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Imprimare
{
	//Mai multe comenzi si intr o comanda sa ai mai multe obiecte printate
	char* material; //materialul din care este facuta chestia aia
	const int id; //id ul comenzii
	static int idgen;
	int nrExemplare;//numarul de exemplare dintr o comanda
	float* preturiExemplar; //preturile sunt intr un vector alocat dinamic.
	void alocareDin(const float* v, const int num)
	{
		delete[] preturiExemplar;
		preturiExemplar = nullptr;
		nrExemplare = 0;
		if (v != nullptr && num > 0)
		{
			preturiExemplar = new float[num]; //alocarea dinamica pentru vectorul nostru
			for (int i = 0; i < num; i++)
			{
				preturiExemplar[i] = v[i];
			}
			nrExemplare = num;
		}
	}
public:

	Imprimare(const char* fmaterial = "Unknown") : id(idgen++), nrExemplare(0), preturiExemplar(nullptr)
	{
		material = new char[strlen(fmaterial) + 1];
		strcpy(material, fmaterial);
	}
	Imprimare(const char* fmaterial, int fnrExemplare, const float* v) : nrExemplare(fnrExemplare), id(idgen++)
	{

		alocareDin(v, fnrExemplare);
		if (fmaterial)
		{
			material = new char[strlen(fmaterial) + 1];
			strcpy(material, fmaterial);
		}
	}
	Imprimare(const Imprimare& is) : id(idgen++)
	{
		if (is.material)
		{
			material = new char[strlen(is.material) + 1];
			strcpy(material, is.material);
		}
		alocareDin(is.preturiExemplar, is.nrExemplare);
	}
	Imprimare operator=(const Imprimare& is)
	{
		this->idgen = is.id;
		if (this == &is) return *this;
		delete[] material;
		material = nullptr;
		if (is.material)
		{
			material = new char[strlen(is.material) + 1];
			strcpy(material, is.material);
		}
		alocareDin(is.preturiExemplar, is.nrExemplare);
		return *this;
	}
	virtual ~Imprimare()
	{
		delete[] preturiExemplar;
		delete[] material;
	}
	virtual float total() const
	{
		float suma = 0;
		for (int i = 0; i < nrExemplare; i++)
			suma += preturiExemplar[i];
		return suma;
	}
	virtual float pretDupaReducere()
	{
		float suma = 0;
		for (int i = 0; i < nrExemplare; i++)
			suma += preturiExemplar[i];
		if (nrExemplare > 3)
		{
			cout << "FELICITARI, BENEFICIEZI DE O REDUCERE DE 10%! (TATAIA SUGE PULA)";
			return suma - (suma / 10);
		}
		cout << "SUGI PULA, N AI REDUCERE!!!";
		return suma;
	}
	friend istream& operator>>(istream& is, Imprimare& im)
	{
		char buffer[256];
		cout << "Introduceti materialul: ";
		is >> ws;
		is.getline(buffer, 256);
		delete[] im.material;
		im.material = nullptr;
		im.material = new char[strlen(buffer) + 1];
		strcpy(im.material, buffer);
		cout << "Introduceti numarul de exemplare: "; is >> im.nrExemplare;
		delete[] im.preturiExemplar;
		im.preturiExemplar = nullptr;
		im.preturiExemplar = new float[im.nrExemplare];
		for (int i = 0; i < im.nrExemplare; i++)
		{
			cout << "Introduceti pretul exemplarului cu numarul " << i + 1 << " :";
			is >> im.preturiExemplar[i];
		}
		return is;
	}
	friend ostream& operator <<(ostream& os, Imprimare& is)
	{
		os << "ID: " << is.id << endl;
		os << "Nr exemplare: " << is.nrExemplare << endl;
		os << "Materialul folosit: " << (is.material ? is.material : "(NULL)") << endl; // os << "Material folosit" << i.material << endl;
		for (int i = 0; i < is.nrExemplare; i++)
		{
			os << "Exemplarul cu numarul " << i + 1 << " are pretul de: " << is.preturiExemplar[i] << endl;
		}
		return os;
	}
	bool operator<(const Imprimare& is) const //compararea dupa pret
	{
		float max1 = 0;
		float max2 = 0;
		for (int i = 0; i < nrExemplare; i++)
			max1 += preturiExemplar[i];
		for (int i = 0; i < is.nrExemplare; i++)
			max2 += is.preturiExemplar[i];
		return max2 < max1;
	}
	Imprimare& operator+=(const Imprimare& is)
	{
		if (nrExemplare > 0 && preturiExemplar != nullptr || is.nrExemplare > 0 && is.preturiExemplar != nullptr)
		{
			float* vNou = new float[nrExemplare + is.nrExemplare];

			for (int i = 0; i < nrExemplare; i++)
			{
				vNou[i] = preturiExemplar[i];
			}
			for (int i = nrExemplare; i < (nrExemplare + is.nrExemplare); i++)
			{
				vNou[i] = is.preturiExemplar[i - nrExemplare];
			}
			nrExemplare += is.nrExemplare;
			delete[] preturiExemplar;
			preturiExemplar = nullptr;
			preturiExemplar = new float[nrExemplare];
			preturiExemplar = vNou;
			/*
			for (int i = 0; i < nrExemplare; i++)
			{
				cout <<"Pozitia: " << i << " " << vNou[i] << endl;
				preturiExemplar[i] = vNou[i];
			}
			*/
			return *this;
		}
		return *this;
	}
	explicit operator int() const
	{
		float sum = 0;
		for (int i = 0; i < nrExemplare; i++)
			sum += preturiExemplar[i];
		return (int)(sum);
	}
	Imprimare& operator+(const float pret) //adaugare un nou exemplar
	{
		if (pret > 0)
		{

			float* vNou = new float[nrExemplare + 1];
			for (int i = 0; i < nrExemplare; i++)
				vNou[i] = preturiExemplar[i];
			vNou[nrExemplare] = pret;
			nrExemplare++;
			delete[] preturiExemplar;
			preturiExemplar = nullptr;
			preturiExemplar = vNou;
			return *this;
		}
	}
	Imprimare& operator++() //prefixat
	{
		for (int i = 0; i < nrExemplare; i++)
			preturiExemplar[i] = preturiExemplar[i] + preturiExemplar[i] / 10; //scumpire cu 10%
		return *this;
	}
	Imprimare operator++(int)
	{
		Imprimare im(*this);
		for (int i = 0; i < nrExemplare; i++)
			preturiExemplar[i] = preturiExemplar[i] - preturiExemplar[i] / 10; //ieftinire cu 10%
		return im;
	}
	float& operator[](int index)
	{
		if (index < 0 || index >= this->nrExemplare)
			throw out_of_range("Indexul este invalid");

		return this->preturiExemplar[index];
	}
};

	int Imprimare::idgen = 0;

int main()
{
	float v[] = { 10.27f , 12.67f, 9.69f, 14.87f };
	float v2[] = { 15.67f, 6.7f, 6.21f };
	float v3[] = { 6.89f, 12.87 };
	Imprimare im1, im2("Lemn", 4, v), im3("Plastic", 3, v2);
	cout << im2 << im1 << im3;
	//cout << (im2 < im1) << endl;
	
	if (im1 < im2)
	{
		cout << "Obiectul 1 are un pret total mai mare\n";
		cout << "Obiectul 2 are un pret total mai mic\n";
	}
	else
	{
		cout << "Obiectul 2 are un pret total mai mare\n";
		cout << "Obiectul 1 are un pret total mai mic\n";
	}
	//im2 += im3;
	//cout << im2;
	//cin >> im1;
	//cout << im1;
	//im2 = im3;
	//Imprimare im4(im3);
	//cout <<"Im4: " << im4 <<"Im2: " << im2;
	//cout << int(im3);
	//im2 + 13.4;
	//cout << im2;
	//++im2;
	//cout << im2;
	//im2++;
	//cout << im2;
	im2[2] = 13;
	cout << im2;
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define INF 99
int citire(int*** a, int* n)
{
	int vi, vf, cost, i, j, nm;
	FILE* f;
	fopen_s(&f, "lista.txt", "r");
	if (f != NULL)
	{
		fscanf_s(f, "%d", n);
		fscanf_s(f, "%d", &nm);
		(*a) = (int**)malloc((*n) * sizeof(int*));
		for (i = 0; i < *n; i++)
			(*a)[i] = (int*)calloc(*n, sizeof(int));
		for (i = 0; i < *n;i++)
			for (j = 0; j < *n; j++)
				(*a)[i][j] = INF;
		for (i = 0; i < nm;i++)
		{
			fscanf_s(f, "%d", &vi);
			fscanf_s(f, "%d", &vf);
			fscanf_s(f, "%d", &cost);
			(*a)[vi - 1][vf - 1] = (*a)[vf - 1][vi - 1] = cost;
		}
		fclose(f);
		return 1;
	}
	else
		return 0;
}

void afisare(int** a, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n;j++)
			printf("  %d  ", a[i][j]);
		printf("\n");
	}
}
void Roy_Floyd(int** a, int n, int*** m)
{
	int i, j, k;
	(*m) = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++)
		(*m)[i] = (int*)calloc(n, sizeof(int));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i != j)
				(*m)[i][j] = a[i][j];
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if ((*m)[i][j] > (*m)[i][k] + (*m)[k][j])(*m)[i][j] = (*m)[i][k] + (*m)[k][j];

}

void BF(int coada[], int parinte[], int m[], int* r, int** a, int vo, int n)
{
	int i, k, u, p, c[20];
	for (i = 0; i < n; i++)
		parinte[i] = -1;
	for (i = 0; i < n; i++)
		coada[i] = -1;
	for (i = 0; i < n; i++)
		m[i] = 0;
	c[0] = vo - 1;
	parinte[vo - 1] = -1;
	m[vo - 1] = 1;
	(*r) = 0;u = 0;p = 0;
	while (p <= u)
	{
		i = c[p];
		coada[(*r)] = i;
		(*r)++;
		for(k = 0; k< n; k++)
			if (a[i][k] < INF && m[k] == 0)
			{
				u++;
				c[u] = k;
				parinte[k] = i;
				m[k] = 1;
			}
		p++;
	}
}
void Roy_Warshall(int** a, int n, int*** m)
{
	int i, j, k;
	(*m) = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++)
		(*m)[i] = (int*)calloc(n, sizeof(int));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (a[i][j] >= INF)
				(*m)[i][j] = 0;
			else
				(*m)[i][j] = 1;
		}
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if ((*m)[i][j] ==0)(*m)[i][j] = (*m)[i][k] * (*m)[k][j];
}
int componente_conexe(int** m, int n)
{
	int* verificare = (int*)calloc(n, sizeof(int));
	int comp = 0;
	for(int i = 0; i < n; i++)
		if (verificare[i] == 0)
		{
			comp++;
			for (int j = 0; j < n; j++)
				if (m[i][j]==1)
					verificare[j] = 1;
			verificare[i] = 1;
		}
	free(verificare);
	return comp;
}
int main()
{
	int ok, n, ** a, i, j,**b,coada[20],vo, parinte[20],m[20],r,vi,vf;
	ok = citire(&a, &n);
	if (ok)
	{
		printf("Matricea costurilor este:\n");
		afisare(a, n);
		printf("Matricea lui Roy_Floyd\n");
		Roy_Floyd(a, n, &b);
		afisare(b, n);
		printf("Introduceti nodurile pentru a afla costul minim dintre acestea:\n");scanf_s("%d", &vi);scanf_s("%d", &vf);
		printf("Costul minim dintre nodurile alese este de %d!\n", b[vi-1][vf-1]);
		printf("Matricea existentei drumurilor:\n");
		Roy_Warshall(a, n, &b);
		afisare(b, n);
		int componente = componente_conexe(b, n);
		printf("Numarul de componente conexe este de %d!\n", componente);
		printf("Introduceti nodul de la care sa se inceapa parcurgerea vectorului:\n");scanf_s("%d", &vo);
		BF(coada, parinte, m, &r, a, vo, n);
		for (i = 0; i < n; i++)
			printf("Parintele nodului %d este %d!\n", i + 1, parinte[i] + 1);
		printf("Numarul de fii pe care il au un nodurile:\n");
		for (int i = 0; i < n; i++)
		{
			int fii = 0;
			for (int j = 0; j < n; j++)
				if ((i + 1) == parinte[j] + 1)
					fii++;
			printf("Nodul %d are %d fii!\n", i + 1, fii);
		}
	}
	else
		printf("Fisierul nu s-a putut deschide cu succes sau acesta nu exista!");
	return 0;
}
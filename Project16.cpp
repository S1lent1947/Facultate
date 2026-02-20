#include <stdio.h>
#include <stdlib.h>

int citire(int a[][20], int* n)
{
	int vi, vf, i, nm,j;
	FILE* f;
	fopen_s(&f, "lista.txt", "r");
	if (f != NULL)
	{
		fscanf_s(f, "%d", n);
		fscanf_s(f, "%d", &nm);
		//(*a) = (int**)malloc((*n) * sizeof(int*));
		for (i = 0; i < *n; i++)
			for (j = 0; j < *n; j++)
				a[i][j] = 0;
			//(*a)[i] = (int*)calloc((*n), sizeof(int));
		for (i = 0; i < nm; i++)
		{
			fscanf_s(f, "%d", &vi);
			fscanf_s(f, "%d", &vf);
			a[vi - 1][vf - 1] = a[vf - 1][vi - 1] = 1;
		}
		fclose(f);
		return 1;
	}
	else
		return 0;
}

void afisare(int a[][20], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf(" %d ", a[i][j]);
		printf("\n");
	}
}
void Roy_Warshall(int a[][20], int m[][20], int n)
{
	int i, j, k;
	//m = (int**)malloc(n * sizeof(int*));
	//for (i = 0; i < n; i++)
		//(*m)[i] = (int*)calloc(n, sizeof(int));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			m[i][j] = a[i][j];
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (m[i][j] == 0)m[i][j] = m[i][k] * m[k][j];
}
int componente_conexe(int m[20][20], int n)
{
	int* vizitat = (int*)calloc(n, sizeof(int));
	int comp = 0;
	for (int i = 0; i < n;i++)
		if (vizitat[i] == 0)
		{
			comp++;
			for (int j = 0; j < n;j++)
				if (m[i][j] == 1)
					vizitat[j] = 1;
			vizitat[i] = 1;
		}
	free(vizitat);
	return comp;
}

void noduri_de_grad_n(int a[20][20], int n, int grad_n)
{
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int j = 0; j < n; j++)
			if (a[i][j] == 1)
				count++;
		if (count == grad_n)
			printf("Nodul %d are gradul ales!\n", i + 1);
	}
}
void numarul_de_arce_din_noduri(int a[20][20], int n)
{
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int j = 0; j < n; j++)
			if (a[i][j] == 1)
				count++;
		printf("Numarul de arce din nodul %d este de %d\n", i + 1, count);
	}
}
void BF(int parinte[], int coada[], int m[], int* r, int a[][20], int n, int vo)
{
	int i, k, c[20],p,u;
	for (i = 0; i < n; i++)
		parinte[i] = -1;
	for (i = 0; i < n; i++)
		coada[i] = -1;
	for (i = 0; i < n; i++)
		m[i] = 0;
	parinte[vo - 1] = -1;
	c[0] = vo - 1;
	m[vo - 1] = 1;
	(*r) = 0;p = 0;u = 0;
	while (p <= u)
	{
		i = c[p];
		coada[*r] = i;
		(*r)++;
		for(k = 0; k < n; k++)
			if (a[i][k] == 1 && m[k] == 0)
			{
				u++;
				c[u] = k;
				parinte[k] = i;
				m[k] = 1;
			}
		p++;
	}
}
int main()
{
	int a[20][20], n, ok, b[20][20], i, j, grad_n, parinte[20], coada[20], m[20], r, vo;
	ok = citire(a, &n);
	if (ok)
	{
		printf("Matricea de adiacenta:\n");
		afisare(a, n);
		printf("Matricea de existenta a drumului:\n");
		Roy_Warshall(a, b, n);
		afisare(b, n);
		int componente = componente_conexe(b, n);
		printf("Numarul de componente conexe este de %d !\n", componente);
		int conex = 1;
		for (i = 0; i < n; i++)
			for (j = 0; j < n;j++)
				if (b[i][j] == 0)conex = 0;
		if (conex == 1)printf("Graful nostru este conex!\n");
		else printf("Graful nostru nu este conex!\n");
		printf("Introduceti gradul pe care il cautati la un nod:\n");scanf_s("%d", &grad_n);
		noduri_de_grad_n(a, n, grad_n);
		numarul_de_arce_din_noduri(a, n);
		printf("Introduceti nodul de la care sa inceapa parcurgerea:\n");scanf_s("%d", &vo);
		BF(parinte, coada, m, &r, a, n, vo);
		for (int i = 0; i < n; i++)
			printf("Parintele nodului %d este %d!\n", i + 1, parinte[i] + 1);
		printf("Ordinea in care au fost parcurse nodurile este:\n");
		for (int i = 0; i < r; i++)
			printf("Nodul %d a fost in vizita %d!\n", coada[i] + 1, i + 1);
		printf("Nodurile vizitate sunt:\n");
		for (int i = 0; i < r; i++)
			if (m[i] == 1)
				printf("%d\n",i+1);
	}
	else
		printf("Fisierul nu s-a putut deschide sau acesta nu exista!");
}
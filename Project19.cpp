#include <stdio.h>
#include <stdlib.h>

void sort(int v[], int n) {
   for(int i = 0; i < n-1; i++)
       for(int j = i+1; j < n; j++)
           if (v[i] < v[j])
           {
               int temp = v[i];
               v[i] = v[j];
               v[j] = temp;
           }
}

int citire(int* suma, int** v, int* n) {
    int i;
    FILE* f;
    fopen_s(&f, "bani.txt", "r");
    if (f != NULL) {
        fscanf_s(f, "%d", suma);
        fscanf_s(f, "%d", n);
        *v = (int*)calloc(*n, sizeof(int));
        for (i = 0; i < *n; i++) {
            fscanf_s(f, "%d", &(*v)[i]);
        }
        sort(*v, *n);
        fclose(f);
        return 1;
    }
    else {
        return 0;
    }
}

void achita_recursiv(int v[], int suma, int index, int n, int *count) 
{
    if (suma != 0)
    {
        if (v[index] <= suma)
        {
            (*count)++;
            achita_recursiv(v, suma - v[index], index, n,count);
        }
        else
            achita_recursiv(v, suma, index+1,n,count);
    }
    else
        return;
}
int main() {
    int n, * v, suma, count = 0, ok;
    ok = citire(&suma, &v, &n);
    if (ok) {
        achita_recursiv(v, suma, 0, n, &count);
        if (count != -1) {
            printf("Suma a fost achitata integral!\n");
            printf("Suma a fost achitata cu %d bancnote!\n", count);
        }
        else {
            printf("Suma nu poate fi achitata integral!\n");
        }
        free(v);
    }
    else {
        printf("Fisierul nu s-a putut deschide sau nu exista!\n");
    }
    return 0;
}
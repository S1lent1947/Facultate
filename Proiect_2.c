#include <stdio.h>
void amplitudine(int n, int m, float a[][40], float ampli[][2]){
int i, j;
float min, max;
for(i = 0 ; i < n; i++){
    min = a[i][0];
    max = a[i][0];
    for(j = 1; j < m; j++){
        if(min > a[i][j]){
            min = a[i][j];
        }
        if(max < a[i][j]){
            max = a[i][j];
        }
    }
    ampli[i][0] = min;
    ampli[i][1] = max;
}
}
void media_conv(int n, int m, float a[][40], float media[]){
int i, j;
float medie;
for(i = 0; i < n; i++){
    medie = 0;
    for(j = 0; j < m; j++){
        medie += a[i][j];
    }
    media[i] = (medie/m);
}

}
void ultimul_abonat(int n, int m, float a[][40], float valoarea_de_verificare[], int ultimul[]){
int i, j, ulti_ab;
for(i = 0; i < n; i++){
    ulti_ab = 0;
    for( j = 0; j < m; j++){
        if( valoarea_de_verificare[i] == a[i][j]){
            ulti_ab = j + 1;
        }
    }
    ultimul[i] = ulti_ab;
}
}
void sub_prag(int n, int m, float a[][40], float prag[], int luni_sub_prag[]){
int i, j, luni, suma;
for(i = 0; i < n; i++){
    luni = 0;
    suma = 0;
    for(j = 0; j < m; j++){
        suma += a[i][j];
        if( suma < prag[i]){
            luni += 1;
        }
    }
    luni_sub_prag[i] = luni;
}
}
int main(){
int n, m, i, j, ultimul[40], luni_sub_prag[40];
float a[40][40], ampli[40][2], media[40], valoarea_de_verificare[40], prag[40];
printf("Introduceti numarul de abonati: ");
scanf("%d", &m);
printf("Introduceti numarul de luni de convorbire: ");
scanf("%d", &n);
for(i = 0; i < n; i++){
    printf("Introduceti valoarea de verificare pentru ziua %d. ", i + 1);
    scanf("%f", &valoarea_de_verificare[i]);
    printf("Introduceti valoarea pragului pentru ziua %d. ", i + 1);
    scanf("%f", &prag[i]);
    for(j = 0; j < m; j++){
        printf("Introduceti costul convorbirilor abonatului %d din luna %d: ", j + 1, i + 1);
        scanf("%f", &a[i][j]);
    }
}
printf("------------------------------------------------------------------------------------ \n");
amplitudine(n, m , a , ampli);
for(i = 0; i < n; i++){
    if(a[i][0] == a[i][1]){
        printf("Costul din luna %d este unul constat, adica %4.2f$. \n", i + 1, a[i][0]);
    }
    else{
    printf("Costul minim din luna %d este %4.2f$, iar cel maxim este %4.2f$. \n", i + 1, ampli[i][0], ampli[i][1]);
    }
}
printf("------------------------------------------------------------------------------------ \n ");
media_conv(n, m, a, media);
for(i = 0; i < n; i++){
    printf("Media costului convorbirilor din luna %d este de %4.2f$. \n", i + 1, media[i]);
}
printf("------------------------------------------------------------------------------------ \n");
ultimul_abonat(n, m , a, valoarea_de_verificare, ultimul);
for(i = 0; i < n; i++){
    if( ultimul[i] == 0){
        printf("Nu a fost identificat niciun abonat cu convorbirile in valoare de %4.2f. \n", valoarea_de_verificare[i]);
    }
    else{
    printf("Ultimul abonat cu valoarea convorbirilor de %4.2f este %d. \n", valoarea_de_verificare[i], ultimul[i]);
    }
}
printf("------------------------------------------------------------------------------------ \n");
sub_prag(n, m, a, prag, luni_sub_prag);
for(i = 0; i < m; i++){
    if( luni_sub_prag[i] == 0 ){
        printf("Abonatul %d nu are nici o luna sub pragul stabilit. \n", i + 1);
    }
    else{
    printf("Abonatul %d are %d luni sub pragul stabilit. \n", i + 1, luni_sub_prag[i]);
    }
}
    return 0;
}
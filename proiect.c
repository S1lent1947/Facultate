#include <stdio.h>
#include <stdbool.h>
void crescator(int m, int n,int crest[], float a[][40], int *marime){
int i,j;
*marime = 0;
for(i=0; i < m; i++){
    bool creste = true;
    for (j=1; j < n; j++){
        if(a[i][j-1] > a[i][j]){
            creste = false;
            break;
        }
    }
    if(creste == true){
        crest[(*marime)++] = i + 1;
    }
    
  }
}

int main()
{
int m, n, i, j, marime, crest[40];
float a[40][40];
printf("introduceti nr de apartamente ");
scanf ("%d", &m); // m este numartul de apartamente / linia
printf("introduceti nr de zile: ");
scanf("%d", &n); // n este numarul de zile / coloana
for (i=0; i<m; i++){
    printf ("introduceti consumul de apa al ap: ");
    scanf("%f", &p[i]); //preturile vor fi stocate in vectorul p
}
return 0;
}

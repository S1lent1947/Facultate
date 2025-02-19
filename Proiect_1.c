#include <stdio.h>
#include <stdbool.h>
void zile_tinta(int *marime, float a[][40], float goal[], int m, int n, int sub_tinta[]){ //functia pentru aflarea zilelor cu venit sub obiectivul propus
int i, j;
float total_zi;
*marime = 0;
for(i=0; i < m; i++){ 
    total_zi = 0; //initializam suma vanzarilor pe ziua i cu 0
    for(j=0; j <n; j++){
        total_zi += a[i][j]; //facem vanzarea totala pe ziua respectiva
    }
    if(total_zi < goal[i]){ //verificam daca vanzarea totala este mai mica decata tinta propusa
        sub_tinta[(*marime)++] = i + 1; //ne folosim de pointerul marime pentru a regla marimea vectorului sub_tinta
    }
}
}
void vanzare_min(float a[][40], int minim_zi[], int m, int n){ // functie care gaseste vanzarea minima a unui produs dintr o zi
    int i, j;
    float minim;
    for(i = 0; i < m; i++){ //parcurgem matricea a ca sa aflam minimul
        minim = a[i][0]; // initializam minimul cu primul element de randul i
        for(j = 1; j < n; j++){
            if(minim > a[i][j]){
                minim = a[i][j]; // daca conditia de la if este indeplinita minimul isi schimba valoarea in elementul a[i][j]
            }
        }
        minim_zi[i] = minim; //elementul i din vectorul minim_zi ii ia valoarea lui minim
    }
}
void consecutiv(float a[][40], int m , int n, int zile_constante[], int *marime){ //functia pentru aflarea vanzarilor constate 
int i, j;
*marime = 0; // initializam pointerul marime cu 0
for(i = 0; i < m; i++){
    bool sunt_cons = true; // initializam sunt_cons cu true
    for(j = 1; j < n; j++){
        if(a[i][j-1] != a[i][j]){ // in caz ca conditia este indeplinita, sunt_cons va deveni false si se face executa break, astfel se va iesi din for loop.
            sunt_cons = false;
            break;
        }
    }
    if(sunt_cons == true){ // daca s-a iesit din al doilea for loop ,sunt_cons este false, se va trece inapoi la inceputul primului for loop si sunt_cons va deveni true
        zile_constante[(*marime)++] = i + 1; //se va trece in vectorul zile_constante ziua(i+1) daca toate vanzarile din ziua respectiva sunt egale.
    }
}
}
void amplitudine(int m, int n, float a[][40], int ampli[][2]){ //aceasta functie gaseste minimul si maximul vanzarilor dintr-o zi.
int i, j;
float minim, maxim;
for(i = 0; i < m; i++){ 
    minim = a[i][0]; //initializam minimul si maximul cu prima valoare de pe linia i din vectorul a
    maxim = a[i][0];
    for(j = 1; j<n; j++ ){
        if(minim > a[i][j]){ //daca conditia este adevarata minimul este egal cu a[i][j]
            minim = a[i][j];
        }
        if(maxim < a[i][j]){ //daca conditia este adevarata maximul este egal cu a[i][j]
            maxim = a[i][j];
        }
    }
    ampli[i][0] = minim; //pe prima coloana a vectorului ampli vom stoca valorile minime, iar pe cea de a doua coloana vom stoca valorile maxime.
    ampli[i][1] = maxim;
}

}

int main(){
int i, j, m, n, marime, sub_tina[40], minim_zi[40], zile_constante[40], ampli[40][2];
float a[40][40],goal[40];
printf("Scrieti numarul de produse: "); //stabilim numarul de produse cu care o sa lucram
scanf("%d", &n);
printf("Scrieti numarul de zile: "); //stabilim numarul de zile cu care o sa lucram
scanf("%d", &m);
for(i=0; i < m; i++){
    printf("Care este tinta pentru ziua %d?", i + 1);// stabilim tinta pentru ziua i+1 (la prima iteratie avem i=0 deci ziua 1)
        scanf("%f", &goal[i]);
    for(j=0; j < n; j++){ //parcugem matricea a[i][j] pentru care j sunt produsele, iar i sunt zilele
        printf("Produsul: %d din ziua: %d are vanzare de: ", j+1, i+1); //stabilim preturile pentru produsele din ziua i+1
        scanf("%f", &a[i][j]);
    }
}
printf("------------------------------------------------------------------------------------ \n");
zile_tinta(&marime, a, goal, m, n, sub_tina); // apelam functia zile_tinta
printf("Zilele care se afla sub tinta sunt: ");
for(i=0; i < marime ; i++){ //parcurgem vectorul sub_tinta si afisam zilele care se afla sub goal
    printf("%d ; ", sub_tina[i]);
}
printf("------------------------------------------------------------------------------------ \n");
vanzare_min(a, minim_zi, m ,n);// apelam functia vanzare_min
printf("\n");
for(i = 0; i < m; i++){ //parcurgem vectorul minim_zi si afisam minimul de vazari din ziua respectiva
printf("Minimul din ziua %d este de: %d \n", i+1, minim_zi[i]);
}
printf("------------------------------------------------------------------------------------ \n");
consecutiv(a, m, n , zile_constante, &marime); //apelam functia consecutiv
printf("Zilele care au vanzari constante sunt: ");
for(i = 0 ; i < marime; i++){
    printf(" %d ;", zile_constante[i]);
}
printf("------------------------------------------------------------------------------------ \n");
amplitudine(m, n, a, ampli);// apelam functia amplitudine
for(i = 0; i < m; i++){
    printf("In ziua %d: minimul = %d : maximul = %d \n ", i + 1, ampli[i][0], ampli[i][1]);
}

return 0;
}
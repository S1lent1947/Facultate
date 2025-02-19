#include <stdio.h>

// Subprogramul care verifică dacă un șir are valori crescătoare cu aceeași rată
int esteCrescator(int consumuri[], int zile) {
    if (zile < 2) {
        return 1; // Dacă sunt mai puține de două zile, este considerat valid
    }

    int rata = consumuri[1] - consumuri[0];
    for (int i = 1; i < zile; i++) {
        if (consumuri[i] - consumuri[i - 1] != rata) {
            return 0; // Nu este crescător cu aceeași rată
        }
    }
    return 1; // Este crescător cu aceeași rată
}

// Subprogramul principal care determină apartamentele cu consumuri crescătoare
void determinaApartamente(int matrice[][100], int apartamente, int zile, int rezultate[]) {
    for (int i = 0; i < apartamente; i++) {
        rezultate[i] = esteCrescator(matrice[i], zile);
    }
}

int main() {
    int m, n; // Numărul de apartamente și zile
    printf("Introduceți numărul de apartamente: ");
    scanf("%d", &m);
    printf("Introduceți numărul de zile: ");
    scanf("%d", &n);

    int matrice[100][100]; // Matricea consumurilor
    printf("Introduceți consumurile de apă:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrice[i][j]);
        }
    }

    int rezultate[100]; // Vector pentru a stoca rezultatele
    determinaApartamente(matrice, m, n, rezultate);

    // Afișarea apartamentelor care respectă condiția
    printf("Apartamentele cu consumuri crescătoare sunt:\n");
    for (int i = 0; i < m; i++) {
        if (rezultate[i]) {
            printf("Apartamentul %d\n", i + 1);
        }
    }

    return 0;
}
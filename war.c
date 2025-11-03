#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

// Definição da struct
typedef struct {
    char nome[50];
    char corExercito[30];
    int numTropas;
} Territorio;

int main() {
    Territorio territorios[QTD_TERRITORIOS];
    int i;

    printf("=== Cadastro de Territórios ===\n");

    // Cadastro dos territórios
    for (i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar(); // consome o '\n' deixado pelo scanf
    }

    // Exibição dos territórios
    printf("\n=== Estado Atual do Mapa ===\n");
    for (i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
    }

    return 0;
}
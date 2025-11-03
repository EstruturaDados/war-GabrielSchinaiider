#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

// Estrutura de dados para o território
typedef struct {
    char nome[50];
    char corExercito[30];
    int numTropas;
} Territorio;

// Função para simular um ataque
void simularAtaque(Territorio *atacante, Territorio *defensor) {
    int dadoAtaque, dadoDefesa;

    // Gera números aleatórios entre 1 e 6 (como dados)
    dadoAtaque = rand() % 6 + 1;
    dadoDefesa = rand() % 6 + 1;

    printf("\n🎲 %s atacou %s!\n", atacante->nome, defensor->nome);
    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtaque, dadoDefesa);

    // Lógica de batalha
    if (dadoAtaque > dadoDefesa) {
        defensor->numTropas--;
        printf("⚔️  %s venceu a rodada! %s perdeu 1 tropa.\n",
               atacante->nome, defensor->nome);

        // Se o defensor perdeu todas as tropas
        if (defensor->numTropas <= 0) {
            printf("🏁 %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);

            // Transferência simbólica de cor do exército
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->numTropas = 1; // Nova tropa colocada
            atacante->numTropas--;   // Uma tropa move para o território conquistado
        }
    } else {
        printf("🛡️  %s defendeu com sucesso!\n", defensor->nome);
    }
}

// Função para exibir o estado atual do mapa
void exibirMapa(Territorio *territorios, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
    }
}

int main() {
    int i;
    int opcao, atacante, defensor;
    Territorio *territorios;

    srand(time(NULL)); // inicializa gerador de números aleatórios

    // Alocação dinâmica com calloc
    territorios = (Territorio *)calloc(QTD_TERRITORIOS, sizeof(Territorio));

    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== Cadastro de Territórios ===\n");

    for (i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar();
    }

    // Loop de ataques
    do {
        exibirMapa(territorios, QTD_TERRITORIOS);

        printf("\nEscolha o território atacante (1 a %d): ", QTD_TERRITORIOS);
        scanf("%d", &atacante);
        printf("Escolha o território defensor (1 a %d): ", QTD_TERRITORIOS);
        scanf("%d", &defensor);
        getchar();

        // Validação simples
        if (atacante < 1 || atacante > QTD_TERRITORIOS ||
            defensor < 1 || defensor > QTD_TERRITORIOS ||
            atacante == defensor) {
            printf("⚠️  Escolha inválida. Tente novamente.\n");
        } else {
            simularAtaque(&territorios[atacante - 1], &territorios[defensor - 1]);
        }

        printf("\nDeseja realizar outro ataque? (1 - Sim | 0 - Não): ");
        scanf("%d", &opcao);
        getchar();

    } while (opcao != 0);

    // Libera memória
    free(territorios);

    printf("\nJogo encerrado. Obrigado por jogar WAR!\n");
    return 0;
}
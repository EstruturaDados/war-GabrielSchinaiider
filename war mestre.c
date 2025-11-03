#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

// Estrutura do território
typedef struct {
    char nome[50];
    char corExercito[30];
    int numTropas;
} Territorio;

// ===================== PROTÓTIPOS DE FUNÇÕES =====================
void inicializarTerritorios(Territorio *territorios);
void exibirMapa(const Territorio *territorios);
void simularAtaque(Territorio *atacante, Territorio *defensor);
void verificarMissao(const Territorio *territorios);
int contarTerritoriosPorCor(const Territorio *territorios, const char *cor);

// ===================== FUNÇÃO PRINCIPAL =====================
int main() {
    srand(time(NULL));
    Territorio *territorios;
    int opcao, atacante, defensor;

    // Alocação dinâmica
    territorios = (Territorio *)calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inicializarTerritorios(territorios);

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                exibirMapa(territorios);
                printf("\nEscolha o território atacante (1 a %d): ", QTD_TERRITORIOS);
                scanf("%d", &atacante);
                printf("Escolha o território defensor (1 a %d): ", QTD_TERRITORIOS);
                scanf("%d", &defensor);
                getchar();

                if (atacante < 1 || atacante > QTD_TERRITORIOS ||
                    defensor < 1 || defensor > QTD_TERRITORIOS ||
                    atacante == defensor) {
                    printf("⚠️  Escolha inválida!\n");
                } else {
                    simularAtaque(&territorios[atacante - 1], &territorios[defensor - 1]);
                }
                break;

            case 2:
                verificarMissao(territorios);
                break;

            case 0:
                printf("\nSaindo do jogo... Obrigado por jogar WAR!\n");
                break;

            default:
                printf("⚠️  Opção inválida.\n");
                break;
        }

    } while (opcao != 0);

    free(territorios);
    return 0;
}

// ===================== FUNÇÕES AUXILIARES =====================

// Inicializa automaticamente os territórios
void inicializarTerritorios(Territorio *territorios) {
    const char *nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Colômbia"};
    const char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Preto"};
    const int tropas[] = {5, 4, 6, 3, 5};

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].corExercito, cores[i]);
        territorios[i].numTropas = tropas[i];
    }

    printf("\n🌍 Territórios iniciais carregados com sucesso!\n");
}

// Exibe o estado atual do mapa
void exibirMapa(const Territorio *territorios) {
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
    }
}

// Simula uma rodada de ataque
void simularAtaque(Territorio *atacante, Territorio *defensor) {
    if (atacante->numTropas <= 1) {
        printf("⚠️  %s não possui tropas suficientes para atacar!\n", atacante->nome);
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n🎯 %s (%s) atacou %s (%s)\n",
           atacante->nome, atacante->corExercito,
           defensor->nome, defensor->corExercito);

    printf("🎲 Dado do ataque: %d | Dado da defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        defensor->numTropas--;
        printf("⚔️  Ataque bem-sucedido! %s perdeu 1 tropa.\n", defensor->nome);

        // Se o defensor perdeu todas as tropas, conquista o território
        if (defensor->numTropas <= 0) {
            printf("🏁 %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);

            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->numTropas = 1;
            atacante->numTropas--;
        }
    } else {
        printf("🛡️  Defesa bem-sucedida! %s resistiu ao ataque.\n", defensor->nome);
        atacante->numTropas--;
    }
}

// Verifica se o jogador venceu alguma missão
void verificarMissao(const Territorio *territorios) {
    printf("\n=== MISSÕES ===\n");
    printf("1. Destruir o exército Verde\n");
    printf("2. Conquistar 3 territórios\n");

    int destruido = contarTerritoriosPorCor(territorios, "Verde");
    int corJogador = contarTerritoriosPorCor(territorios, "Azul"); // jogador é azul nesse exemplo

    if (destruido == 0) {
        printf("\n✅ Missão 1 concluída: Exército Verde destruído!\n");
    } else {
        printf("\n❌ Missão 1 pendente: ainda restam territórios Verdes.\n");
    }

    if (corJogador >= 3) {
        printf("✅ Missão 2 concluída: o exército Azul conquistou 3 ou mais territórios!\n");
    } else {
        printf("❌ Missão 2 pendente: ainda faltam conquistas.\n");
    }

    if (destruido == 0 && corJogador >= 3) {
        printf("\n🎉 PARABÉNS! Você cumpriu TODAS as missões e venceu o jogo! 🏆\n");
    }
}

// Conta quantos territórios pertencem a uma cor específica
int contarTerritoriosPorCor(const Territorio *territorios, const char *cor) {
    int cont = 0;
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        if (strcmp(territorios[i].corExercito, cor) == 0)
            cont++;
    }
    return cont;
}
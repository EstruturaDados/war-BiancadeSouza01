#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIO 50
#define TAM_STRING 100

struct Territorio {
    char territorio[TAM_STRING];
    char cor[TAM_STRING];
    int tropa;
};

// limpa buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// número aleatório entre min e max
int aleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL)); // inicializa números aleatórios

    struct Territorio *lugar;
    lugar = (struct Territorio *) calloc(MAX_TERRITORIO, sizeof(struct Territorio));

    if (!lugar) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    int totalTerritorio = 0;

    printf("Vamos cadastrar os 5 territorios iniciais\n\n");

    while (totalTerritorio < 5) {
        printf("Cadastrando territorio %d:\n", totalTerritorio + 1);

        printf("Nome do territorio: ");
        fgets(lugar[totalTerritorio].territorio, TAM_STRING, stdin);
        lugar[totalTerritorio].territorio[strcspn(lugar[totalTerritorio].territorio, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(lugar[totalTerritorio].cor, TAM_STRING, stdin);
        lugar[totalTerritorio].cor[strcspn(lugar[totalTerritorio].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &lugar[totalTerritorio].tropa);
        limparBufferEntrada();

        printf("Território cadastrado!\n\n");
        totalTerritorio++;
    }

    // LISTA DE TERRITÓRIOS
    printf("\n=== LISTA DE TERRITÓRIOS ===\n");
    for (int i = 0; i < totalTerritorio; i++) {
        printf("Territorio: %s | Cor: %s | Tropas: %d\n",
               lugar[i].territorio,
               lugar[i].cor,
               lugar[i].tropa);
    }

    // FASE DE ATAQUE
    printf("\n===== FASE DE ATAQUE =====\n");

    int atacante, defensor;

    printf("Escolha o território atacante (1 a 5) ou 0 para sair: ");
    scanf("%d", &atacante);

    if (atacante == 0) {
        printf("Saindo...\n");
        return 0;
    }

    printf("Escolha o território defensor (1 a 5): ");
    scanf("%d", &defensor);

    if (atacante < 1 && atacante > 5 && defensor < 1 && defensor > 5) {
        printf("Erro: território inválido!\n");
        return 0;
    }

    if (atacante == defensor) {
        printf("Erro: atacante e defensor não podem ser iguais!\n");
        return 0;
    }

    atacante--;
    defensor--;

    printf("\nAtaque iniciado!\n");
    printf("Atacante: %s (tropas: %d)\n",
           lugar[atacante].territorio, lugar[atacante].tropa);

    printf("Defensor: %s (tropas: %d)\n",
           lugar[defensor].territorio, lugar[defensor].tropa);

    // ROLAR DADOS
    int dadoAtacante = aleatorio(1, 6);
    int dadoDefensor = aleatorio(1, 6);

    printf("\nDado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nAtacante venceu a batalha!\n");
    } else if (dadoDefensor > dadoAtacante) {
        printf("\nDefensor venceu a batalha!\n");
    } else {
        printf("\nEmpate! Ninguém perdeu tropas.\n");
    }

    return 0;
}

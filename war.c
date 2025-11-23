#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIO 50
#define TAM_STRING 100
#define MAX_ATACANTES 100
#define MAX_DEFENSORES 100

// === ESTRUTURAS ===
struct Territorio {
    char territorio[TAM_STRING];
    char cor[TAM_STRING]; 
    int tropa;
};

struct atacante {
    char nomeAtacante[TAM_STRING];
    int indiceTerritorio;
};

struct defensor {
    char nomeDefensor[TAM_STRING];
    int indiceTerritorio;
};

// === PROTÓTIPOS ===
void limparBufferEntrada();
void cadastrarTerritorio(struct Territorio *lugar, int *totalTerritorio);
void listarTerritorios(struct Territorio *lugar, int totalTerritorio);
void adicionarAtacante(struct atacante *atacantes, int *totalAtacantes, struct Territorio *lugar, int totalTerritorio);
void adicionarDefensor(struct defensor *defensores, int *totalDefesores, struct Territorio *lugar, int totalTerritorio);
int aleatorio(int min, int max);
void rolarDados(int *dado1, int *dado2);
void resolverBatalha(struct Territorio *lugar, int atacante, int defensor);
void liberarMemoria(struct Territorio *lugar);

// === IMPLEMENTAÇÕES ===
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarTerritorio(struct Territorio *lugar, int *totalTerritorio) {
    printf("Cadastro do território %d:\n", *totalTerritorio + 1);

    printf("Nome do territorio: ");
    fgets(lugar[*totalTerritorio].territorio, TAM_STRING, stdin);
    lugar[*totalTerritorio].territorio[strcspn(lugar[*totalTerritorio].territorio, "\n")] = '\0';

    printf("Cor do exercito: ");
    fgets(lugar[*totalTerritorio].cor, TAM_STRING, stdin);
    lugar[*totalTerritorio].cor[strcspn(lugar[*totalTerritorio].cor, "\n")] = '\0';

    printf("Numero de tropas: ");
    scanf("%d", &lugar[*totalTerritorio].tropa);
    limparBufferEntrada();

    (*totalTerritorio)++;
    printf("Território cadastrado!\n\n");
}

void listarTerritorios(struct Territorio *lugar, int totalTerritorio) {
    printf("\n=== LISTA DE TERRITÓRIOS ===\n");
    for (int i = 0; i < totalTerritorio; i++) {
        printf("%d - Território: %s | Cor: %s | Tropas: %d\n",
               i + 1,
               lugar[i].territorio,
               lugar[i].cor,
               lugar[i].tropa);
    }
    printf("\n");
}

void adicionarAtacante(struct atacante *atacantes, int *totalAtacantes, struct Territorio *lugar, int totalTerritorio) {
    printf("Nome do atacante: ");
    fgets(atacantes[*totalAtacantes].nomeAtacante, TAM_STRING, stdin);
    atacantes[*totalAtacantes].nomeAtacante[strcspn(atacantes[*totalAtacantes].nomeAtacante, "\n")] = '\0';

    printf("Escolha território atacante (1 a %d): ", totalTerritorio);
    scanf("%d", &atacantes[*totalAtacantes].indiceTerritorio);
    limparBufferEntrada();

    atacantes[*totalAtacantes].indiceTerritorio--;

    (*totalAtacantes)++;
}

void adicionarDefensor(struct defensor *defensores, int *totalDefesores, struct Territorio *lugar, int totalTerritorio) {
    printf("Nome do defensor: ");
    fgets(defensores[*totalDefesores].nomeDefensor, TAM_STRING, stdin);
    defensores[*totalDefesores].nomeDefensor[strcspn(defensores[*totalDefesores].nomeDefensor, "\n")] = '\0';

    printf("Escolha território defensor (1 a %d): ", totalTerritorio);
    scanf("%d", &defensores[*totalDefesores].indiceTerritorio);
    limparBufferEntrada();

    defensores[*totalDefesores].indiceTerritorio--;

    (*totalDefesores)++;
}

int aleatorio(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void rolarDados(int *dado1, int *dado2) {
    *dado1 = aleatorio(1, 6);
    *dado2 = aleatorio(1, 6);
}

void resolverBatalha(struct Territorio *lugar, int atacante, int defensor) {
    printf("\n=== BATALHA ===\n");

    int dadoA, dadoD;
    rolarDados(&dadoA, &dadoD);

    printf("Dado do Atacante (%s): %d\n", lugar[atacante].territorio, dadoA);
    printf("Dado do Defensor (%s): %d\n", lugar[defensor].territorio, dadoD);

    if (dadoA > dadoD) {
        printf("Atacante venceu!\n");
    } else if (dadoD > dadoA) {
        printf("Defensor venceu!\n");
    } else {
        printf("Empate! Nenhuma tropa perdida.\n");
    }
}

void liberarMemoria(struct Territorio *lugar) {
    free(lugar);
}

// === MAIN ===
int main() {
    srand(time(NULL));

    struct Territorio *lugar = calloc(MAX_TERRITORIO, sizeof(struct Territorio));
    if (!lugar) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    int totalTerritorio = 0;

    printf("Cadastro inicial de 5 territórios:\n\n");

    for (int i = 0; i < 5; i++) {
        cadastrarTerritorio(lugar, &totalTerritorio);
    }

    listarTerritorios(lugar, totalTerritorio);

    printf("Escolha território atacante: ");
    int atacante, defensor;

    scanf("%d", &atacante);
    printf("Escolha território defensor: ");
    scanf("%d", &defensor);

    atacante--;
    defensor--;

    resolverBatalha(lugar, atacante, defensor);

    liberarMemoria(lugar);
    return 0;
}
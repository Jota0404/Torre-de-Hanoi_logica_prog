#include <stdio.h>
#include <stdlib.h>
// TO DO: criar parâmetro de erro em caso de digitação não numérica entre 1-3
#define MAX_DISCOS 10 // Define o número máximo de discos permitidos

// Estrutura para representar as três torres
int torres[3][MAX_DISCOS];
int topo[3] = {-1, -1, -1}; // Controla o topo de cada torre (pilha)
int num_discos;

// Protótipos das funções
void inicializar_torres(int n);
void exibir_torres();
int movimento_valido(int origem, int destino);
void mover_disco(int origem, int destino);
int verificar_vitoria();

int main() {
    int origem, destino, movimentos = 0;

    printf("--- Torre de Hanoi ---\n");
    printf("Quantos discos você gostaria de jogar (1 a %d)? ", MAX_DISCOS);
    scanf("%d", &num_discos);

    if (num_discos < 1 || num_discos > MAX_DISCOS) {
        printf("Número de discos inválido. O jogo será encerrado.\n");
        return 1;
    }

    inicializar_torres(num_discos);

    while (!verificar_vitoria()) {
        exibir_torres();
        printf("\nMovimento %d:\n", movimentos + 1);
        printf("Mover do pilar (1-3): ");
        scanf("%d", &origem);
        printf("Para o pilar (1-3): ");
        scanf("%d", &destino);

        // Ajusta a entrada do usuário para o índice do array (0-2)
        origem--;
        destino--;

        if (movimento_valido(origem, destino)) {
            mover_disco(origem, destino);
            movimentos++;
        } else {
            printf("\nMovimento inválido! Tente novamente.\n");
        }
    }

    exibir_torres();
    printf("\nParabéns! Você completou a Torre de Hanoi em %d movimentos.\n", movimentos);

    return 0;
}

/**
 * @brief Inicializa as torres, colocando todos os discos na primeira torre.
 *
 * @param n O número de discos no jogo.
 */
void inicializar_torres(int n) {
    for (int i = 0; i < n; i++) {
        torres[0][i] = n - i;
    }
    topo[0] = n - 1;
}

/**
 * @brief Exibe o estado atual das três torres no console.
 */
void exibir_torres() {
    printf("\n--- TORRES ---\n");
    for (int i = num_discos - 1; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            if (i <= topo[j]) {
                printf("    %d    ", torres[j][i]);
            } else {
                printf("    |    ");
            }
        }
        printf("\n");
    }
    printf("====================\n");
    printf("    1        2        3\n");
}

/**
 * @brief Verifica se um movimento de um pilar de origem para um de destino é válido.
 *
 * @param origem O pilar de onde o disco será movido.
 * @param destino O pilar para onde o disco será movido.
 * @return 1 se o movimento for válido, 0 caso contrário.
 */
int movimento_valido(int origem, int destino) {
    // Verifica se os pilares de origem e destino são válidos
    if (origem < 0 || origem > 2 || destino < 0 || destino > 2) {
        return 0;
    }
    // Não pode mover de um pilar vazio
    if (topo[origem] == -1) {
        return 0;
    }
    // Pode mover para um pilar vazio
    if (topo[destino] == -1) {
        return 1;
    }
    // O disco do topo da origem deve ser menor que o do topo do destino
    if (torres[origem][topo[origem]] < torres[destino][topo[destino]]) {
        return 1;
    }
    return 0;
}

/**
 * @brief Move um disco de um pilar de origem para um de destino.
 *
 * @param origem O pilar de onde o disco será movido.
 * @param destino O pilar para onde o disco será movido.
 */
void mover_disco(int origem, int destino) {
    int disco = torres[origem][topo[origem]];
    topo[origem]--;
    topo[destino]++;
    torres[destino][topo[destino]] = disco;
}

/**
 * @brief Verifica se o jogo foi concluído (todos os discos no pilar 3).
 *
 * @return 1 se o jogo terminou, 0 caso contrário.
 */
int verificar_vitoria() {
    if (topo[2] == num_discos - 1) {
        return 1;
    }
    return 0;
}

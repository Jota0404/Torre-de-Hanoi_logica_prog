#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h> 

#define MAX_DISCOS 10 

// Estrutura para representar as três torres
int torres[3][MAX_DISCOS];
int topo[3] = {-1, -1, -1}; // Controla o topo de cada torre
int num_discos;

// Protótipos das funções
void inicializar_torres(int n);
void exibir_torres(); 
int movimento_valido(int origem, int destino);
void mover_disco(int origem, int destino);
int verificar_vitoria();
void limpar_buffer_entrada();

int main() {
    int origem, destino, movimentos = 0;
    int status_leitura;

    printf("--- Torre de Hanoi ---\n");
    printf("Quantos discos voce gostaria de jogar (1 a %d)? ", MAX_DISCOS);
    
    status_leitura = scanf("%d", &num_discos);
    limpar_buffer_entrada(); 

    if (status_leitura != 1 || num_discos < 1 || num_discos > MAX_DISCOS) {
        printf("\n***************************************************\n");
        printf("  ERRO: caractere ou numero invalido.\n");
        printf("  Por favor, insira um numero entre 1 e %d.\n", MAX_DISCOS);
        printf("***************************************************\n\n");
        printf("Reiniciando o jogo...\n\n");

        main(); 
        return 0;
    }

    inicializar_torres(num_discos); 

    while (!verificar_vitoria()) {
        exibir_torres();
        printf("\nMovimento %d:\n", movimentos + 1);
        
        printf("Mover do pilar (1-3): ");
        if (scanf("%d", &origem) != 1) {
            printf("\nEntrada invalida. Tente novamente.\n");
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();

        printf("Para o pilar (1-3): ");
        if (scanf("%d", &destino) != 1) {
            printf("\nEntrada invalida. Tente novamente.\n");
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();
        
        origem--;
        destino--;

        if (movimento_valido(origem, destino)) {
            mover_disco(origem, destino);
            movimentos++;
        } else {
            printf("\nMovimento invalido! Tente novamente.\n");
            // Adiciona uma pequena pausa para o usuário ler a mensagem
            // getchar(); // Limpa o buffer de entrada
            printf("Pressione Enter para continuar...");
            getchar(); // Espera o Enter
        }
    }

    exibir_torres();
    printf("\nParabens! Voce completou a Torre de Hanoi em %d movimentos.\n", movimentos);

    return 0;
}

/**
 * @brief Limpa o buffer de entrada (stdin) para evitar loops infinitos
 * causados por entradas inválidas.
 */
void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// --- DEMAIS FUNÇÕES ---

void inicializar_torres(int n) {
    for (int i = 0; i < n; i++) {
        // Os discos são representados por números (1, 2, 3...) que definem seu tamanho
        torres[0][i] = n - i;
    }
    topo[0] = n - 1;
    topo[1] = -1;
    topo[2] = -1;
}

/**
 * @brief Exibe o estado atual das três torres com uma representação visual dos discos.
 * *Usa vetores de tamanho fixo (baseado em MAX_DISCOS) 
 */
void exibir_torres() {
    // Define um tamanho máximo constante para os "pedaços" da torre.
    // (MAX_DISCOS * 2) + 1 para os caracteres, + 1 para o '\0'.
    const int TAM_MAX_PEDACO = (MAX_DISCOS * 2) + 2;

    // Vetor (buffer de string) para construir cada linha da saída
    char linha_buffer[512]; 
    
    // Vetores (buffers) para construir "pedaços" da torre
    char pedaco_torre[TAM_MAX_PEDACO];
    char pedaco_base[TAM_MAX_PEDACO];
    char pedaco_rotulo[TAM_MAX_PEDACO];

    int max_largura_disco = (num_discos * 2) - 1 + 2;
    printf("\n--- TORRE DE HANOI ---\n");

    // Itera de cima para baixo (do topo da torre para a base)
    for (int i = num_discos - 1; i >= 0; i--) {
        linha_buffer[0] = '\0'; 

        // Para cada uma das 3 torres
        for (int j = 0; j < 3; j++) {
            int k = 0; 
            int espacamento_lateral;

            if (i <= topo[j]) {
                // --- Gera o DISCO no vetor "pedaco_torre" ---
                int tamanho_disco = torres[j][i];
                int num_chars = (tamanho_disco * 2) - 1;
                int largura_visual_disco = num_chars + 2;
                espacamento_lateral = (max_largura_disco - largura_visual_disco) / 2;
                
                for(int l = 0; l < espacamento_lateral; l++) pedaco_torre[k++] = ' ';
                pedaco_torre[k++] = '(';
                for(int l = 0; l < num_chars; l++) pedaco_torre[k++] = '_';
                pedaco_torre[k++] = ')';
                for(int l = 0; l < espacamento_lateral; l++) pedaco_torre[k++] = ' ';

            } else {
                // --- Gera o MASTRO VAZIO no vetor "pedaco_torre" ---
                espacamento_lateral = (max_largura_disco - 1) / 2;
                for(int l = 0; l < espacamento_lateral; l++) pedaco_torre[k++] = ' ';
                pedaco_torre[k++] = '|';
                for(int l = 0; l < espacamento_lateral; l++) pedaco_torre[k++] = ' ';
            }
            // Termina a string do "pedaço"
            pedaco_torre[k] = '\0'; 

            // Concatena o pedaço da torre no vetor da linha
            strcat(linha_buffer, pedaco_torre);
            strcat(linha_buffer, "  "); // Adiciona o espaço entre as torres
        }
        // Imprime o vetor de linha (a linha inteira) de uma só vez
        printf("%s\n", linha_buffer);
    }

    // --- GERAÇÃO DA BASE ---
    linha_buffer[0] = '\0'; 
    
    memset(pedaco_base, '=', max_largura_disco); 
    pedaco_base[max_largura_disco] = '\0';

    for (int j = 0; j < 3; j++) {
        strcat(linha_buffer, pedaco_base);
        strcat(linha_buffer, "  ");
    }
    printf("%s\n", linha_buffer); 

    // --- GERAÇÃO DOS NÚMEROS ---
    linha_buffer[0] = '\0'; 

    for (int j = 1; j <= 3; j++) {
        int espacamento_lateral = (max_largura_disco - 1) / 2;
        
        // Usa sprintf para formatar o número com espaçamento diretamente no vetor
        sprintf(pedaco_rotulo, "%*s%d%*s", espacamento_lateral, "", j, espacamento_lateral, "");

        strcat(linha_buffer, pedaco_rotulo);
        strcat(linha_buffer, "  ");
    }
    printf("%s\n", linha_buffer); 
}


/**
 * @brief Verifica se um movimento de um pilar de origem para um de destino é válido.
 *
 * @param origem O pilar de onde o disco será movido.
 * @param destino O pilar para onde o disco será movido.
 * @return 1 se o movimento for válido, 0 caso contrário.
 */
int movimento_valido(int origem, int destino) {
    if (origem < 0 || origem > 2 || destino < 0 || destino > 2) return 0;
    if (topo[origem] == -1) return 0;
    if (topo[destino] == -1) return 1;
    if (torres[origem][topo[origem]] < torres[destino][topo[destino]]) return 1;
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
    return (topo[2] == num_discos - 1);
}
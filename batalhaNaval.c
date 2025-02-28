#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3
#define HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    // Imprimir números das colunas
    printf("  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Imprimir linha separadora
    printf("  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("--");
    }
    printf("\n");

    // Imprimir tabuleiro com números das linhas
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d| ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    if (direcao == 'H') {
        if (coluna + NAVIO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0;
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    } else if (direcao == 'V') {
        if (linha + NAVIO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    } else if (direcao == 'D') {
        if (linha + NAVIO > TAMANHO || coluna + NAVIO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) return 0;
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    } else if (direcao == 'A') {
        if (linha + NAVIO > TAMANHO || coluna - NAVIO + 1 < 0) return 0;
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna - i] != 0) return 0;
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    }
    return 1;
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char tipo) {
    // Verificar se as coordenadas iniciais são válidas
    if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
        printf("Erro: coordenadas fora do tabuleiro!\n");
        return;
    }

    if (tipo == 'C') { // Cone - forma triangular para baixo
        for (int i = 0; i < 3; i++) {
            for (int j = -i; j <= i; j++) {
                int x = linha + i, y = coluna + j;
                if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO) {
                    tabuleiro[x][y] = HABILIDADE;
                }
            }
        }
    } else if (tipo == 'X') { // Cruz - formato de cruz com 5 posições em cada direção
        for (int i = -2; i <= 2; i++) {
            // Aplicar na vertical
            if (linha + i >= 0 && linha + i < TAMANHO) {
                tabuleiro[linha + i][coluna] = HABILIDADE;
            }
            // Aplicar na horizontal
            if (coluna + i >= 0 && coluna + i < TAMANHO) {
                tabuleiro[linha][coluna + i] = HABILIDADE;
            }
        }
    } else if (tipo == 'O') { // Losango (diamante) de tamanho 5x5
        for (int i = -2; i <= 2; i++) {
            for (int j = -2 + abs(i); j <= 2 - abs(i); j++) {
                int x = linha + i, y = coluna + j;
                if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO) {
                    tabuleiro[x][y] = HABILIDADE;
                }
            }
        }
    } else {
        printf("Erro: tipo de habilidade '%c' inválido!\n", tipo);
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    printf("Posicionando navios...\n");

    // Posicionando navios em diferentes direções
    if (!posicionarNavio(tabuleiro, 2, 2, 'H')) {
        printf("Erro ao posicionar navio horizontal na posição (2,2)!\n");
    }
    if (!posicionarNavio(tabuleiro, 5, 5, 'V')) {
        printf("Erro ao posicionar navio vertical na posição (5,5)!\n");
    }
    if (!posicionarNavio(tabuleiro, 0, 0, 'D')) {
        printf("Erro ao posicionar navio diagonal principal na posição (0,0)!\n");
    }
    if (!posicionarNavio(tabuleiro, 0, 9, 'A')) {
        printf("Erro ao posicionar navio diagonal secundária na posição (0,9)!\n");
    }

    printf("\nAplicando habilidades...\n");

    // Aplicando diferentes tipos de habilidades
    aplicarHabilidade(tabuleiro, 4, 4, 'C'); // Cone
    aplicarHabilidade(tabuleiro, 7, 7, 'X'); // Cruz
    aplicarHabilidade(tabuleiro, 3, 3, 'O'); // Losango

    printf("\nTabuleiro final:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}

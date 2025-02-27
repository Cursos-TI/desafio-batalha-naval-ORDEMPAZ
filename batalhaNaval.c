#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar um navio no tabuleiro
int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') { // Horizontal
        if (coluna + NAVIO > TAMANHO) return 0; // Validação de borda
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0; // Verifica sobreposição
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    } else if (orientacao == 'V') { // Vertical
        if (linha + NAVIO > TAMANHO) return 0; // Validação de borda
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0; // Verifica sobreposição
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    } else if (orientacao == 'D') { // Diagonal principal
        if (linha + NAVIO > TAMANHO || coluna + NAVIO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) return 0;
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    } else if (orientacao == 'A') { // Diagonal secundária
        if (linha + NAVIO > TAMANHO || coluna - NAVIO < -1) return 0;
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna - i] != 0) return 0;
        }
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    } else {
        return 0; // Orientação inválida
    }
    return 1;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);
    
    // Definição das coordenadas dos navios (pré-definidas)
    int linha1 = 2, coluna1 = 3; // Navio horizontal
    int linha2 = 5, coluna2 = 6; // Navio vertical
    int linha3 = 0, coluna3 = 0; // Navio diagonal principal
    int linha4 = 0, coluna4 = 9; // Navio diagonal secundária
    
    // Posiciona os navios
    if (!posicionarNavio(tabuleiro, linha1, coluna1, 'H')) {
        printf("Erro ao posicionar o navio horizontal!\n");
    }
    if (!posicionarNavio(tabuleiro, linha2, coluna2, 'V')) {
        printf("Erro ao posicionar o navio vertical!\n");
    }
    if (!posicionarNavio(tabuleiro, linha3, coluna3, 'D')) {
        printf("Erro ao posicionar o navio diagonal principal!\n");
    }
    if (!posicionarNavio(tabuleiro, linha4, coluna4, 'A')) {
        printf("Erro ao posicionar o navio diagonal secundária!\n");
    }
    
    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);
    
    return 0;
}

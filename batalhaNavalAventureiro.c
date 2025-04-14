#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Exibe o tabuleiro com colunas A-J e linhas 1-10
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("    ");
    for (int col = 0; col < TAMANHO; col++) {
        printf("%c ", 'A' + col);
    }
    printf("\n");

    for (int linha = 0; linha < TAMANHO; linha++) {
        printf("%2d ", linha + 1);
        for (int col = 0; col < TAMANHO; col++) {
            printf("%d ", tabuleiro[linha][col]);
        }
        printf("\n");
    }
}

// Valida posicionamento horizontal
int podePosicionarHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) return 0;
    }
    return 1;
}

// Valida posicionamento vertical
int podePosicionarVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) return 0;
    }
    return 1;
}

// Valida posicionamento diagonal principal (↘)
int podePosicionarDiagonalPrincipal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO || coluna + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != AGUA) return 0;
    }
    return 1;
}

// Valida posicionamento diagonal secundária (↙)
int podePosicionarDiagonalSecundaria(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO || coluna - TAMANHO_NAVIO + 1 < 0) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != AGUA) return 0;
    }
    return 1;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0}; // Inicializa com água (0)

    // Coordenadas dos navios
    int linha_horizontal = 1, coluna_horizontal = 2;   // Horizontal: linha 2, coluna C
    int linha_vertical = 5, coluna_vertical = 7;       // Vertical: linha 6, coluna H
    int linha_diag_principal = 0, coluna_diag_principal = 0; // Diagonal principal: A1
    int linha_diag_secundaria = 0, coluna_diag_secundaria = 9; // Diagonal secundária: J1

    // Posiciona navio horizontal
    if (podePosicionarHorizontal(tabuleiro, linha_horizontal, coluna_horizontal)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_horizontal][coluna_horizontal + i] = NAVIO;
        }
    } else {
        printf("Erro: Não é possível posicionar o navio horizontalmente.\n");
    }

    // Posiciona navio vertical
    if (podePosicionarVertical(tabuleiro, linha_vertical, coluna_vertical)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_vertical + i][coluna_vertical] = NAVIO;
        }
    } else {
        printf("Erro: Não é possível posicionar o navio verticalmente.\n");
    }

    // Posiciona navio na diagonal principal
    if (podePosicionarDiagonalPrincipal(tabuleiro, linha_diag_principal, coluna_diag_principal)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_diag_principal + i][coluna_diag_principal + i] = NAVIO;
        }
    } else {
        printf("Erro: Não é possível posicionar o navio na diagonal principal.\n");
    }

    // Posiciona navio na diagonal secundária
    if (podePosicionarDiagonalSecundaria(tabuleiro, linha_diag_secundaria, coluna_diag_secundaria)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_diag_secundaria + i][coluna_diag_secundaria - i] = NAVIO;
        }
    } else {
        printf("Erro: Não é possível posicionar o navio na diagonal secundária.\n");
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
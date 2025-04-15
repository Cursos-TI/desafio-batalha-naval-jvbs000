#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define TAM_HABILIDADE 5 // Tamanho das matrizes de habilidade (5x5)

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
            int valor = tabuleiro[linha][col];
            if (valor == AGUA) printf("0 ");
            else if (valor == NAVIO) printf("3 ");
            else if (valor == HABILIDADE) printf("5 ");
            else printf("? "); // Valor inesperado
        }
        printf("\n");
    }
}

// Cria matriz de habilidade em formato de cone
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE - 1) / 2 - i && j <= (TAM_HABILIDADE - 1) / 2 + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Cria matriz de habilidade em formato de cruz
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Cria matriz de habilidade em formato de octaedro (losango), sem usar abs
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio_habilidade = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int dist_linha = (i - meio_habilidade >= 0) ? (i - meio_habilidade) : -(i - meio_habilidade);
            int dist_coluna = (j - meio_habilidade >= 0) ? (j - meio_habilidade) : -(j - meio_habilidade);
            if (dist_linha + dist_coluna <= meio_habilidade) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Sobrepõe matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
    int meio_habilidade = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha = origem_linha - meio_habilidade + i;
            int coluna = origem_coluna - meio_habilidade + j;

            if (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == AGUA) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

// Funções de validação de posicionamento de navios
int podePosicionarHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) return 0;
    }
    return 1;
}

int podePosicionarVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) return 0;
    }
    return 1;
}

int podePosicionarDiagonalPrincipal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO || coluna + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != AGUA) return 0;
    }
    return 1;
}

int podePosicionarDiagonalSecundaria(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO || coluna - TAMANHO_NAVIO + 1 < 0) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != AGUA) return 0;
    }
    return 1;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Posicionamento dos navios
    if (podePosicionarHorizontal(tabuleiro, 1, 2)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[1][2 + i] = NAVIO;
    }

    if (podePosicionarVertical(tabuleiro, 5, 7)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[5 + i][7] = NAVIO;
    }

    if (podePosicionarDiagonalPrincipal(tabuleiro, 0, 0)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[0 + i][0 + i] = NAVIO;
    }

    if (podePosicionarDiagonalSecundaria(tabuleiro, 0, 9)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[0 + i][9 - i] = NAVIO;
    }

    // Criação das matrizes de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicando habilidades em posições mais separadas
    aplicarHabilidade(tabuleiro, cone, 2, 2);         // Cone em linha 3, coluna C
    aplicarHabilidade(tabuleiro, cruz, 2, 7);         // Cruz em linha 3, coluna H
    aplicarHabilidade(tabuleiro, octaedro, 7, 4);     // Octaedro em linha 8, coluna E

    // Exibindo o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}

/*
Acho importante salientar que o conhecimento e o uso dos 
loops alinhados mais práticos foi essencial e como foi um
tema já estudado anteriormente não me limitei a usar somente
o "for" na resolução desse trabalho como mostrado nos exemplos
dos vídeos, usando também o "if" e o "else" aninhados, juntamente
com o "void", que também já foi ensinado.
*/
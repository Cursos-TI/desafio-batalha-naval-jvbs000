#include <stdio.h>

// Função para imprimir o tabuleiro no console com colunas como letras e linhas como números
void exibirTabuleiro(int tabuleiro[10][10]) {
    printf("    "); // Espaço para alinhar com os números das linhas
    for (int col = 0; col < 10; col++) {
        printf("%c ", 'A' + col); // Letras das colunas
    }
    printf("\n");

    for (int linha = 0; linha < 10; linha++) {
        printf("%2d ", linha +1); // Números das linhas e adição da função "%2d" para garantir que o tabuleiro fique alinhado
        for (int col = 0; col < 10; col++) {
            printf("%d ", tabuleiro[linha][col]);
        }
        printf("\n");
    }
}

// Função para verificar se é possível posicionar um navio horizontalmente
int podePosicionarHorizontal(int tabuleiro[10][10], int linha, int coluna, int tamanhoNavio) {
    if (coluna + tamanhoNavio > 10) return 0;
    for (int i = 0; i < tamanhoNavio; i++) {
        if (tabuleiro[linha][coluna + i] != 0) return 0;
    }
    return 1; // A função return 1 nâo foi ensinada até o momento desse nível do desafio, porém adquiri seu conhecimento nos materiais disponíveis para estudo
}

// Função para verificar se é possível posicionar um navio verticalmente
int podePosicionarVertical(int tabuleiro[10][10], int linha, int coluna, int tamanhoNavio) {
    if (linha + tamanhoNavio > 10) return 0;
    for (int i = 0; i < tamanhoNavio; i++) {
        if (tabuleiro[linha + i][coluna] != 0) return 0;
    }
    return 1;
}

// Função principal
int main() {
    int tamanhoNavio = 3;
    int valorMar = 0;
    int valorNavio = 3;

    // Inicializa o tabuleiro com água (valor 0)
    int tabuleiro[10][10] = {0};

    // Coordenadas iniciais dos navios (definidas diretamente)
    int linha_horizontal = 2, coluna_horizontal = 3; // Linha 2, Coluna D
    int linha_vertical = 5, coluna_vertical = 6;     // Linha 5, Coluna G

    // Verifica e posiciona o navio horizontal
    if (podePosicionarHorizontal(tabuleiro, linha_horizontal, coluna_horizontal, tamanhoNavio)) {
        for (int i = 0; i < tamanhoNavio; i++) {
            tabuleiro[linha_horizontal][coluna_horizontal + i] = valorNavio;
        }
    } else {
        printf("Erro: Não é possível posicionar o navio horizontalmente nas coordenadas fornecidas.\n");
    }

    // Verifica e posiciona o navio vertical
    if (podePosicionarVertical(tabuleiro, linha_vertical, coluna_vertical, tamanhoNavio)) {
        for (int i = 0; i < tamanhoNavio; i++) {
            tabuleiro[linha_vertical + i][coluna_vertical] = valorNavio;
        }
    } else {
        printf("Erro: Não é possível posicionar o navio verticalmente nas coordenadas fornecidas.\n");
    }

    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    return 0;
}
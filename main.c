#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000



typedef struct {
    unsigned char red, green, blue;
} Pixel;

typedef struct {
    int largura, altura;
    Pixel pixels[MAX_SIZE][MAX_SIZE];
} Image;

void rotacionarImagem(Image *original, Image *rotacao) {
    int i, j;

    rotacao->largura = original->altura;
    rotacao->altura = original->largura;

    for (i = 0; i < original->altura; i++) {
        for (j = 0; j < original->largura; j++) {
            rotacao->pixels[j][original->altura - 1 - i] = original->pixels[i][j];
        }
    }
}


void escalaDeCinza(Image *original, Image *tonsDeCinza) {
    int i, j;

    tonsDeCinza->largura = original->largura;
    tonsDeCinza->altura = original->altura;

    for (i = 0; i < original->altura; i++) {
        for (j = 0; j < original->largura; j++) {
            unsigned char gray = (original->pixels[i][j].red + original->pixels[i][j].green + original->pixels[i][j].blue) / 3;
            tonsDeCinza->pixels[i][j].red = tonsDeCinza->pixels[i][j].green = tonsDeCinza->pixels[i][j].blue = gray;
        }
    }
}

void ampliacaoDaImagem(Image *original, Image *aumentar) {
    int i, j;

    aumentar->largura = original->largura * 2;
    aumentar->altura = original->altura * 2;

  for (i = 0; i < original->altura; i++) {
        for (j = 0; j < original->largura; j++) {
            int x = j * 2; 
            int y = i * 2;

            aumentar->pixels[y][x] = original->pixels[i][j];
            aumentar->pixels[y][x + 1] = original->pixels[i][j];
            aumentar->pixels[y + 1][x] = original->pixels[i][j];
            aumentar->pixels[y + 1][x + 1] = original->pixels[i][j];
        }
    }
}


void reducaoDaImagem(Image *original, Image *reduzir) {
    int i, j;

    reduzir->largura = original->largura / 2;
    reduzir->altura = original->altura / 2;

    for (i = 0; i < reduzir->altura; i++) {
        for (j = 0; j < reduzir->largura; j++) {
            int row = i * 2;
            int col = j * 2;

            reduzir->pixels[i][j].red = (original->pixels[row][col].red + original->pixels[row][col + 1].red + original->pixels[row + 1][col].red + original->pixels[row + 1][col + 1].red) / 4;
            reduzir->pixels[i][j].green = (original->pixels[row][col].green + original->pixels[row][col + 1].green + original->pixels[row + 1][col].green + original->pixels[row + 1][col + 1].green) / 4;
            reduzir->pixels[i][j].blue = (original->pixels[row][col].blue + original->pixels[row][col + 1].blue + original->pixels[row + 1][col].blue + original->pixels[row + 1][col + 1].blue) / 4;
        }
    }
}

void lerImagem(Image *image) {
    char formato[3];
    int valorMaximoDaCor;
    int i, j;

    scanf("%s", formato);
    scanf("%d %d", &image->largura, &image->altura);
    scanf("%d", &valorMaximoDaCor);

    for (i = 0; i < image->altura; i++) {
        for (j = 0; j < image->largura; j++) {
            scanf("%hhu %hhu %hhu", &image->pixels[i][j].red, &image->pixels[i][j].green, &image->pixels[i][j].blue);
        }
    }
}

void escreverImagem(Image *image) {

    int i, j;

    printf("P3\n");
    printf("%d %d\n", image->largura, image->altura); 
    printf("255\n"); 

    for (i = 0; i < image->altura; i++) {
        for (j = 0; j < image->largura; j++) {
            printf("%hhu %hhu %hhu ", image->pixels[i][j].red, image->pixels[i][j].green, image->pixels[i][j].blue);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
      printf("   %s <operacao>\n", argv[0]);
      printf(" Bem vindo ao Programa de Processamento, essas são as formas de usar:\n");
      printf("  Onde <operacao> pode ser:\n");
      printf("    gray: para criar uma versão em escala de cinza da imagem original.\n");
      printf("    enlarge: para ampliar em 2x a imagem original.\n");
      printf("    reduce: para reduzir em 2x a imagem original.\n");
      printf("    rotate: para rotacionar 90 graus (sentido horário) a imagem original.\n");
      printf("    sharp: para aplicar um filtro de sharpening na imagem original.\n");
      printf("    blur: para aplicar um filtro de blurring na imagem original.\n\n");
      printf("    Como exemplo: ./main gray < imgs/nomeDoArquivo.ppm > imgs/gray.ppm\n\n");
      printf("  A imagem original será lida da entrada-padrão e a imagem transformada será enviada para a saída-padrão.\n\n");
            return 1;
    }

    char *transform = argv[1];

    if (strcmp(transform, "rotate") != 0 && strcmp(transform, "gray") != 0 && strcmp(transform, "enlarge") != 0 && strcmp(transform, "reduce") != 0) {
        printf("Invalid transformatoion\n");
        return 1;
    }

    Image original, transformed;

    lerImagem(&original);

    if (strcmp(transform, "rotate") == 0) {

        rotacionarImagem(&original, &transformed);
    } 

    else if (strcmp(transform, "gray") == 0) {
        escalaDeCinza(&original, &transformed);  
    } 

    else if (strcmp(transform, "enlarge") == 0) {
        ampliacaoDaImagem(&original, &transformed);  
    } 

    else if (strcmp(transform, "reduce") == 0) {
        reducaoDaImagem(&original, &transformed); 
    }

    escreverImagem(&transformed);

    return 0;
}


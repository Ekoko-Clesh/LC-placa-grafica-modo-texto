#include "LC_VIDEO_TEXT.h"
#include <go32.h> // Para _dos_ds e _farpokeb, acesso à memória
#include <sys/farptr.h> // Para _farpokeb

// Definições Locais para a memoria de video, para clareza
#define ENDERECO_VIDEO_LOCAL 0xB8000 // Endereço base da memória de vídeo em modo texto
#define LARGURA_LOCAL 80            // Largura do ecrã em modo texto
#define ALTURA_LOCAL 25             // Altura do ecrã em modo texto


/**
 * @brief Imprime um caractere na posição (x, y) com atributos específicos.
 * Esta função escreve um caractere na memória de vídeo em modo texto, usando o endereço base definido.
 * Caracter e os atributos são combinados em um único byte, onde os 8 bits mais significativos representam o caractere e os 8 bits menos significativos representam os atributos (cor, intensidade, etc.).
    * @param ch Caractere a ser impresso.
    * @param x Posição horizontal (coluna) onde o caractere será impresso.
    * @param y Posição vertical (linha) onde o caractere será impresso.
    * @param atributos Atributos do caractere (cor, intensidade, etc.).
    * @return VERDADE se a impressão for bem-sucedida, falso caso contrário.
 */
 Bool printCharAt(char ch, int x, int y, char atributos) {
    // verifica se as coordenadas estão dentro dos limites do ecrã
    if (x < 0 || x >= LARGURA_LOCAL || y < 0 || y >= ALTURA_LOCAL) {
        return FALSO; // Posição fora dos limites do ecrã
    }

    // Calcula o endereço na memória de vídeo
    unsigned long offset = 2 * (LARGURA_LOCAL * y + x); // Cada caractere ocupa 2 bytes (caractere + atributo)

    // Escreve o valor na memória de vídeo
    _farpokeb(_dos_ds, ENDERECO_VIDEO_LOCAL + offset, ch); // Escreve o caractere
    _farpokeb(_dos_ds, ENDERECO_VIDEO_LOCAL + offset + 1, atributos); // Escreve os atributos

    return VERDADE; // Impressão bem-sucedida
 }

 /**
  * @brief Imprime uma cadeia de caracteres na posição especificada do ecrã com atributos específicos.
  * Esta função percorre a cadeia de caracteres e chama printCharAt para cada caractere, garantindo que todos sejam impressos na posição correcta.
    * @param str Cadeia de caracteres a ser impressa.
    * @param x Posição horizontal (coluna) onde a cadeia será impressa.
    * @param y Posição vertical (linha) onde a cadeia será impressa.
    * @param atributos Atributos dos caracteres (cor, intensidade, etc.).
    * @return VERDADE se a impressão for bem-sucedida, falso caso contrário.
  */
  Bool printStringAt(const char *str, int x, int y, char atributos){
    //Verificar se a cadeia de caracteres é válida (não é um ponteiro nulo)
    if(str == (const char *) 0){
        return FALSO; // Cadeia de caracteres inválida
    }
    //Percorre a cadeia até encontrar o caracter de terminação nulo
    while(*str != '\0'){
        if(printCharAt(*str, x, y, atributos) == FALSO){
            return FALSO; // Falha ao imprimir um caractere
        }
        str++; // Avança para o próximo caractere
        x++ // Avança para a próxima coluna

        if(x >= LARGURA_LOCAL) {
            x = 0; // volta à primeira coluna
            y++; // Avança para a próxima linha
        }

        if(y >= ALTURA_LOCAL) {
            return FALSO; // Se y ultrapassar a altura do ecrã, retorna falso
        }
    }
    return VERDADE; // Impressão bem-sucedida
  }

  /**
   * @brief Desenha um quadro rectangular no ecrã com atributos específicos.
    * Esta função desenha um quadro rectangular na memória de vídeo, preenchendo os caracteres de borda e o interior com os atributos especificados.
    * @param atributos Os atributos do quadro (cor, intensidade).
    * @param titulo Título do quadro (opcional, pode ser NULL).
    * @param x Posição horizontal (coluna) do canto superior esquerdo do quadro.
    * @param y Posição vertical (linha) do canto superior esquerdo do quadro.
    * @param largura Largura do quadro.
    * @param altura Altura do quadro.
    * @return VERDADE se o quadro for desenhado com sucesso, falso caso contrário.
   */
Bool drawFrame(const char *titulo, char atributos, int x, int y, int largura, int altura) {
     int i, j;
     int comprimento_titulo = 0;
     const char *ponteiro_titulo = titulo;
     int posicao_inicio_titulo;
     if(largura < 2 || altura < 2 || x < 0 || y < 0 || x + largura > LARGURA_LOCAL || y + altura > ALTURA_LOCAL){
        return FALSO; // Verifica se o quadro está dentro dos limites do ecrã
     }

     //Desenha as bordas horizontais (superiores e inferiores)
     for (i = 0; i < largura; i++){
        //Borda superior
        if(printCharAt((i == 0 || i == largura - 1) ? '+' : '-', x + i, y, atributos) == FALSO){
            return FALSO; // Falha ao imprimir a borda superior
        }
        //Borda inferior
        if(printCharAt((i == 0 || i == largura - 1) ? '+' : '-', x + i, y + altura - 1, atributos) == FALSO){
            return FALSO; // Falha ao imprimir a borda inferior
        }
     }
     //Desenha as bordas verticais (esquerda e direita)
     for(j = 0; j < altura; j++){
        //Borda esquerda
        if(printCharAt((j == 0 || j == altura - 1) ? '+' : '|', x, y + j, atributos) == FALSO){
            return FALSO; // Falha ao imprimir a borda esquerda
        }
        //Borda direita
        if(printCharAt((j == 0 || j == altura - 1) ? '+' : '|', x + largura - 1, y + j, atributos) == FALSO){
            return FALSO; // Falha ao imprimir a borda direita
        }
     }
        // Se um título for fornecido, desenha-o no topo do quadro
        if(titulo != (const char *)0){
            while(*ponteiro_titulo != '\0') {
                comprimento_titulo++;
                ponteiro_titulo++;
            }
            
            posicao_inicio_titulo = x + (largura - comprimento_titulo) / 2; // Centraliza o título
            if(posicao_inicio_titulo < x + 1){
                posicao_inicio_titulo = x + 1; // Garante que o título não fique fora do quadro
            }
            if(posicao_inicio_titulo + comprimento_titulo > x + largura - 1){
                comprimento_titulo = largura - 2; // Garante que o título não ultrapasse a borda direita
            }else{
                if(printStringAt(titulo, posicao_inicio_titulo, y, atributos) == FALSO){
                    return FALSO; // Falha ao imprimir o título
                }
            }
            return VERDADE; // Quadro desenhado com sucesso
        }
}
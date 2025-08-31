#include "LC_VID.h"
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
        x++;// Avança para a próxima coluna

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
           
        }
         return VERDADE; // Quadro desenhado com sucesso
}

/**
 * @brief Imprime o mesmo carácter repetidamente numa linha.
 * 
 * Esta função é útil para desenhar linhas horizontais ou preencher áreas
 * com um padrão repetitivo, sem ter de chamar printCharAt múltiplas vezes.
 * 
 * @param ch O carácter a repetir.
 * @param contagem O número de vezes que o carácter deve ser repetido.
 * @param x A coordenada da coluna inicial.
 * @param y A coordenada da linha.
 * @param atributos Os atributos de cor e estilo.
 * @return VERDADE se a operação for bem-sucedida, FALSO caso ocorra um erro
 *         (e.g., tentativa de escrever fora dos limites do ecrã).
 */
Bool printCharRepeatedAt(char ch, int contagem, int x, int y, char atributos) {
    int i; // Contador
    for (i = 0; i < contagem; i++) {
        // Imprimimos o carácter na posição actual e avançamos a coluna.
        // Se printCharAt falhar, a nossa função também falha.
        if (printCharAt(ch, x + i, y, atributos) == FALSO) {
            return FALSO; // Erro ao imprimir um carácter repetido.
        }
    }
    return VERDADE; // Operação concluída com sucesso.
}

/**
 * @brief Limpa uma região retangular do ecrã com um atributo específico.
 * 
 * Esta função preenche uma área definida do ecrã com espaços (' ') e os
 * atributos de cor e estilo fornecidos. É essencial para 


remover conteúdo antigo ou preparar áreas para nova informação.
 * 
 * @param x A coordenada da coluna inicial da região a limpar.
 * @param y A coordenada da linha inicial da região a limpar.
 * @param largura A largura da região a limpar.
 * @param altura A altura da região a limpar.
 * @param atributos Os atributos de cor e estilo a usar para preencher a região limpa.
 * @return VERDADE se a operação for bem-sucedida, FALSO caso as dimensões ou
 *         posições sejam inválidas.
 */
Bool clearScreen(int x, int y, int largura, int altura, char atributos) {
    int i, j; // Contadores

    // Verificamos se a região a limpar está dentro dos limites do ecrã.
    if (x < 0 || y < 0 || 
        x + largura > LARGURA_LOCAL || y + altura > ALTURA_LOCAL) {
        return FALSO; // Região inválida.
    }

    // Percorremos cada célula da região e escrevemos um espaço com os atributos indicados.
    for (j = 0; j < altura; j++) {
        for (i = 0; i < largura; i++) {
            if (printCharAt(
                ' ', // O carácter a usar para limpar é um espaço
                x + i, 
                y + j, 
                atributos
            ) == FALSO) {
                return FALSO; // Se falhar a limpar um carácter, falha tudo.
            }
        }
    }
    return VERDADE; // Região limpa com sucesso.
}

/**
 * @brief Desloca o conteúdo de uma região do ecrã para cima.
 * 
 * Esta função simula um efeito de "scroll" (rolagem) dentro de uma área
 * retangular do ecrã. O conteúdo das linhas é movido para cima, e as
 * linhas que ficam vazias no fundo da região são preenchidas com espaços
 * e os atributos especificados.
 * 
 * @param x A coordenada da coluna inicial da região a deslocar.
 * @param y A coordenada da linha inicial da região a deslocar.
 * @param largura A largura da região a deslocar.
 * @param altura A altura da região a deslocar.
 * @param linhas O número de linhas a deslocar para cima. Se for 0 ou negativo,
 *               não faz nada. Se for maior ou igual à altura, limpa a região toda.
 * @param atributos Os atributos de cor e estilo para preencher as novas linhas vazias.
 * @return VERDADE se a operação for bem-sucedida, FALSO caso as dimensões ou
 *         posições sejam inválidas.
 */
Bool scrollRegion(int x, int y, int largura, int altura, int linhas, char atributos) {
    int i, j; // Contadores
    unsigned long offset_origem, offset_destino; // Offsets na memória de vídeo

    // Verificamos se a região é válida e se o número de linhas a deslocar é razoável.
    if (x < 0 || y < 0 || 
        x + largura > LARGURA_LOCAL || y + altura > ALTURA_LOCAL ||
        linhas < 0) {
        return FALSO; // Região ou número de linhas inválido.
    }

    // Se o número de linhas a deslocar for maior ou igual à altura da região,
    // significa que toda a região deve ser limpa.
    if (linhas >= altura) {
        return clearScreen(x, y, largura, altura, atributos); // Limpa a região toda.
    }

    // Percorremos as linhas da região, movendo o conteúdo.
    // Começamos da primeira linha que será visível após o scroll.
    for (j = y; j < y + altura - linhas; j++) {
        for (i = x; i < x + largura; i++) {
            // Calculamos o offset da origem (onde o carácter está agora)
            offset_origem = 2 * (LARGURA_LOCAL * (j + linhas) + i);
            // Calculamos o offset do destino (para onde o carácter vai ser movido)
            offset_destino = 2 * (LARGURA_LOCAL * j + i);

            // Lemos o carácter e os atributos da posição de origem.
            char ch = _farpeekb(_dos_ds, ENDERECO_VIDEO_LOCAL + offset_origem);
            char attr = _farpeekb(_dos_ds, ENDERECO_VIDEO_LOCAL + offset_origem + 1);

            // Escrevemos o carácter e os atributos na posição de destino.
            _farpokeb(_dos_ds, ENDERECO_VIDEO_LOCAL + offset_destino, ch);
            _farpokeb(_dos_ds, ENDERECO_VIDEO_LOCAL + offset_destino + 1, attr);
        }
    }

    // Preenchemos as últimas 'linhas' que ficaram vazias com espaços e os atributos indicados.
    for (j = y + altura - linhas; j < y + altura; j++) {
        for (i = x; i < x + largura; i++) {
            if (printCharAt(' ', i, j, atributos) == FALSO) {
                return FALSO; // Se falhar a limpar, falha tudo.
            }
        }
    }

    return VERDADE; // Operação de scroll concluída com sucesso.
}

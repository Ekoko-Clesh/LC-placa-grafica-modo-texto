#ifndef _LC_VIDEO_TEXT_H_
#define _LC_VIDEO_TEXT_H_

#include "utypes.h" // Inclui o tipo Bool e outros tipos definidos pelo utilizador

/** #defgroup LC_VIDEO_TEXT LC_VIDEO_TEXT
 * @{
 *
 * Definições para manipulação de vídeo em modo texto
*/

/** @name Definições de ecrã e memória de vídeo em modo texto */
/*@{*/
#define ENDERECO_VIDEO 0xB8000 ///< Endereço base da memória de vídeo em modo texto
#define LARGURA 80            ///< Largura do ecrã em modo texto
#define ALTURA 25             ///< Altura do ecrã em modo texto
/*@}*/

/** @name Significado dos bits no byte de atributo
*/
/*@{*/
#define AZUL_FRENTE (1 << 0)   ///< Bit 0: Azul para primeiro plano
#define VERDE_FRENTE (1 << 1)  ///< Bit 1: Verde para primeiro plano
#define VERMELHO_FRENTE (1 << 2) ///< Bit 2: Vermelho para primeiro plano

#define INTENSO (1 << 3) ///< Bit 3: Intensidade do primeiro plano (1 = intenso, 0 = normal)

#define AZUL_FUNDO (1 << 4)    ///< Bit 4: Azul para fundo
#define VERDE_FUNDO (1 << 5)   ///< Bit 5: Verde para fundo
#define VERMELHO_FUNDO (1 << 6) ///< Bit 6: Vermelho para fundo

#define NORMAL (VERMELHO_FRENTE | VERDE_FRENTE | AZUL_FRENTE) ///< Atributo normal (verde para primeiro plano, verde para fundo)
/*@{*/

/** 
* @brief Imprime um caractere na posição (x, y) com atributos específicos.
* @param ch Caractere a ser impresso.
* @param x Posição horizontal (coluna) onde o caractere será impresso.
* @param y Posição vertical (linha) onde o caractere será impresso.
* @param atributos Atributos do caractere (cor, intensidade, etc.).
* @return VERDADE se a impressão for bem-sucedida, falso caso contrário.
*/

Bool printCharAt(char ch, int x, int y, char atributos);

/**
 * @brief Imprimie uma cadeia de caracteres na posição especificada do ecrã com atributos específicos.
* @param str Cadeia de caracteres a ser impressa.
* @param x Posição horizontal (coluna) onde a cadeia será impressa.
* @param y Posição vertical (linha) onde a cadeia será impressa.
* @param atributos Atributos dos caracteres (cor, intensidade, etc.).
* @return VERDADE se a impressão for bem-sucedida, falso caso contrário.
 */
 Bool printStringAt(const char *str, int x, int y, char atributos);

/**
    * @brief Desenha um quadro rectangular no ecrã com atributos específicos.
    * @param x Posição horizontal (coluna) do canto superior esquerdo do quadro.
    * @param y Posição vertical (linha) do canto superior esquerdo do quadro.
    * @param largura Largura do quadro.
    * @param altura Altura do quadro.
    * @param atributos Atributos do quadro (cor, intensidade, etc.).
    * @param titulo Título do quadro (opcional, pode ser NULL).
    * @return VERDADE se o quadro for desenhado com sucesso, falso caso contrário.
*/

Bool drwaFrame(const char *titulo, char atributos, int x, int y, int largura, int altura);

/**
    * @brief Imprime o mesmo caracter repetidamente numa linha
    * @param ch Caractere a ser impresso.
    * @param contagem O número de vezes que o caractere deve ser impresso.
    * @param x Posição horizontal (coluna) onde o caractere será impresso.
    * @param y Posição vertical (linha) onde o caractere será impresso.
    * @param atributos Atributos do caractere (cor, intensidade, etc.).
    * @return VERDADE se a impressão for bem-sucedida, falso caso contrário.
 */
 Bool printCharRepeated(char ch, int count, int x, int y, char atributos);

 /**
    * @brief Limpa uma região rectangula do ecrã com um atributo específico
    * @param x Posição horizontal (coluna) do canto superior esquerdo da região a ser limpa.
    * @param y Posição vertical (linha) do canto superior esquerdo da região a ser limpa.
    * @param largura Largura da região a ser limpa.
    * @param altura Altura da região a ser limpa.
    * @param atributos Atributos do caractere (cor, intensidade, etc.) a ser usado para limpar a região.
    * @return VERDADE se a região for limpa com sucesso, falso caso contrário.
*/
Bool clearScreen(int x, int y, int largura, int altura, char atributos);

/**
    * @brief Desloca o conteúdo do ecrã para cima ou para baixo.
    *@param x A posição horizontal (coluna) do canto superior esquerdo da região a ser deslocada.
    * @param y A posição vertical (linha) do canto superior esquerdo da região a ser deslocada.
    * @param largura A largura da região a ser deslocada.
    * @param altura A altura da região a ser deslocada.
    * @param linhas Número de linhas para deslocar (positivo para baixo, negativo para cima).
    * @param atributos Atributos do caractere (cor, intensidade, etc.) a ser usado para preencher as linhas vazias após o deslocamento.
    * @return VERDADE se o deslocamento for bem-sucedido, falso caso contrário.
 */
 Bool scrollRegion(int x, int y, int largura, int altura, int linhas, char atributos);
 /*@}*/
 /**@} Fim do grupo LC_VIDEO_TEXT */
#endif // LC_VIDEO_TEXT_H_

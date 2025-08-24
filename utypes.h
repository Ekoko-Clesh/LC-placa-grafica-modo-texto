#ifndef _UTYPES_H_
#define _UTYPES_H_

/** @defgroup UserTypes UserTypes
 * @{
 * 
 * Definições de tipos para Programador
 */

typedef unsigned char uchar; ///< uchar é mais breve/curto que unsigned char
typedef unsigned short ushort; ///< ushort é um inteiro curto sem sinal
typedef unsigned int uint; ///< uint é um inteiro sem sinal
typedef unsigned long ulong; ///< ulong é um inteiro longo sem sinal

typedef unsigned char Byte; ///< conjunto de 8 bits para máquinas i386
typedef unsigned short Word; ///< conjunto de 16 bits para máquinas i386

/** Definição de Tipo booleano
* <pre>
* Exemplo de uso:
* Bool feito = falso;
* enquanto (feito == falso){...}
* </pre>
*/

typedef enum {
    falso = 0, ///< Valor Falso
    verdade = 1   ///< Valor Verdadeiro
} Bool; ///< Tipo booleano definido pelo utilizador
/**@} Fim dos tipos de utilizador*/
#endif


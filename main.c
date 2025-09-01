#include <stdio.h>
#include <stdlib.h> 
#include "LC_VID.h" 
#include "utypes.h" 

/**
 * @mainpage Documentação do Projecto Trabalho 1 em Grupo
 *
 * @section intro_sec Introdução
 *
 * Este é o documento gerado automaticamente para o projecto Trabalho 1 em Grupo.
 * Ele descreve a estrutura do código, funções, tipos de dados e mais.
 *
 * @section author_sec Autores
 *
 * Este projecto foi desenvolvido por:
 * - António Frazão
 * - Ekoko Clesh
 *
 * @version 1.0
 * @date 2025-09-01
 *
  * <hr>
 *
 * @image html img1.png "Figura 1: Execução 1."
 * @image latex img1.png "Figura 1: Execução 1" width=16cm
 *
 * <hr>
 *
 * @image html img2.png "Figura 2: Execução 2"
 * @image latex img2.png "Figura 2: Execuçao 2" width=16cm
 *
 * <hr>
 *
 * @image html img3.png "Figura 3: Execução 3"
 * @image latex img3.png "Figura 3: Execução 3" width=16cm
 *
 * <hr>
 *
 * @image html img4.png "Figura 4: Execução 4"
 * @image latex img4.png "Figura 4: Execução 4" width=16cm

  * @image html img5.png "Figura 4: Execução 5"
 * @image latex img5.png "Figura 4: Execução 5" width=16cm
/**
 * @section dificuldades_sec Dificuldades Encontradas Durante o Desenvolvimento
 *
 * A execução deste projecto, levou-nos a enfrentar alguns obstáculos técnicos que exigiram uma análise
 * cuidada e soluções específicas da nossa parte. Estes desafios, embora
 * tivessem atrasado momentaneamente o progresso, acabaram por se revelar
 * oportunidades de aprendizagem valiosas sobre as ferramentas que tínhamos
 * à nossa disposição.
 *
 *
 * @subsection desafio_dosbox Incompatibilidade de Nomes de Ficheiro no Ambiente DOSBox
 *
 * O primeiro grande desafio com que nos deparámos surgiu durante a compilação
 * do código-fonte. O projecto recorreu ao emulador DOSBox para garantir a
 * compatibilidade com compiladores mais antigos, mas esta decisão trouxe
 * consigo uma limitação inesperada. O processo de compilação, automatizado
 * através de um `Makefile`, falhava consistentemente sempre que os ficheiros
 * de código tinham nomes mais longos, como `LC_video_text.c`.
 *
 * A nossa análise do problema revelou que a causa era a estrita convenção de
 * nomes de ficheiro **8.3** (oito caracteres para o nome, três para a extensão),
 * imposta pelo sistema de ficheiros FAT16 que o DOSBox emula. O emulador
 * renomeava automaticamente os ficheiros longos para um formato abreviado
 * (ex: `LC_VID~1.C`), mas o `Makefile` que tínhamos construído continuava a
 * referenciar o nome original. Esta discrepância resultava em erros de
 * "Ficheiro não encontrado", bloqueando a compilação.
 *
 * A solução que encontrámos passou por uma refactorização: todos
 * os nomes de ficheiro do projecto foram por nós encurtados para se conformarem
 * ao padrão 8.3, como por exemplo `LC_vid.c`. Esta adaptação, embora simples,
 * foi crucial para assegurarmos a estabilidade do ambiente de compilação e
 * demonstrou na prática como sistemas legados podem impor restrições ao
 * desenvolvimento moderno.
 *
 *
 * @subsection desafio_doxygen Configuração da Geração de Documentação em PDF
 *
 * Um segundo obstáculo, não menos complexo, surgiu na fase final, quando
 * tentámos gerar a documentação do projecto em formato PDF. A cadeia de
 * ferramentas, composta pelo Doxygen e pelo sistema de composição de texto
 * MiKTeX (LaTeX), apresentou-nos uma série de problemas de configuração.
 *
 * O processo falhava durante a compilação dos ficheiros `.tex` intermediários,
 * com erros que indicavam a falta de "pacotes" LaTeX necessários para
 * processar os comandos específicos do Doxygen. Além disso, as definições de
 * segurança do sistema operativo Windows impediam que o MiKTeX descarregasse
 * e instalasse automaticamente estes pacotes em falta, e bloqueavam a
 * execução do compilador `pdflatex` quando este era invocado a partir de um
 * terminal com privilégios de administrador.
 *
 * A resolução deste impasse exigiu da nossa equipa uma intervenção a dois
 * níveis. Primeiro, foi necessário configurar manualmente o MiKTeX (em modo
 * de administrador) para que este passasse a instalar as dependências de
 * forma automática. Segundo, tivemos de garantir que todo o processo de
 * compilação da documentação fosse executado a partir de um terminal com
 * permissões de utilizador padrão. Este processo reforçou a importância de
 * compreendermos não só as ferramentas em si, mas também a forma como estas
 * interagem com o sistema operativo.
 
  */


/**
 * @brief Verifica se um caracter é um dígito numérico.
 * 
 * Esta função é uma versão simplificada de isdigit() da biblioteca padrão,
 * feita à mão para cumprir as restrições do trabalho.
 * 
 * @param ch O caracter a verificar.
 * @return 1 (verdadeiro) se o carácter for um dígito (
'0' a '9'), 0 (falso) caso contrário.
 */
int eDigito(char ch)
{
    return (ch >= '0' && ch <= '9');
}

/**
 * @brief Calcula o comprimento de uma cadeia de caracteres.
 * 
 * Esta função é a nossa versão de strlen(), contando o número de caracteres
 * até encontrar o terminador nulo ('\0').
 * 
 * @param str A cadeia de caracteres (string) a medir.
 * @return O número de caracteres na cadeia, sem incluir o terminador nulo.
 */
int comprimentoCadeia(const char *str)
{
    int comprimento = 0;
    // Percorremos a cadeia até encontrar o terminador nulo.
    while (str[comprimento] != '\0')
    {
        comprimento++;
    }
    return comprimento;
}

/**
 * @brief Verifica se uma cadeia de caracteres representa um número inteiro.
 * 
 * Esta função analisa uma cadeia para determinar se ela contém apenas dígitos,
 * opcionalmente precedidos por um sinal de menos para números negativos.
 * É a nossa versão de uma verificação de número.
 * 
 * @param str A cadeia de caracteres a verificar.
 * @return 1 (verdadeiro) se a cadeia for um número válido, 0 (falso) caso contrário.
 */
int eNumero(const char *str)
{
    int i = 0;

    // Se o primeiro carácter for um sinal de menos, avançamos.
    if (str[0] == '-')
    {
        i++;
    }

    // Percorremos o resto da cadeia, verificando se todos são dígitos.
    for (; str[i] != '\0'; i++)
    {
        if (!eDigito(str[i]))
        {
            return 0; // Se encontrarmos algo que não seja um dígito, não é um número.
        }
    }

    // Deve haver pelo menos um dígito (além de um possível sinal).
    return (i > 0); 
}

/**
 * @brief Converte uma cadeia de caracteres para um número inteiro.
 * 
 * Esta função transforma uma representação textual de um número inteiro
 * na sua forma numérica. É a nossa versão de atoi().
 * 
 * @param str A cadeia de caracteres que contém o número.
 * @return O valor inteiro correspondente à cadeia.
 */
int cadeiaParaInteiro(const char *str)
{
    int resultado = 0;
    int sinal = 1;
    int i = 0;

    // Verificamos se o número é negativo.
    if (str[0] == '-')
    {
        sinal = -1;
        i++; // Saltamos o sinal.
    }

    // Convertemos cada dígito da cadeia para o seu valor numérico.
    for (; str[i] != '\0'; i++)
    {
        resultado = resultado * 10 + (str[i] - '0');
    }

    return sinal * resultado;
}


int main()
{
    int linha, coluna; 
    char entrada[100];
    int escolhaCor;
    char atributosTexto;
    char atributosQuadro = VERDE_FRENTE; 
    int larguraQuadro = LARGURA; 
    int alturaQuadro = ALTURA;

    int inicioX = (LARGURA - larguraQuadro) / 2;   // Centrar horizontalmente
    int inicioY = (ALTURA - alturaQuadro) / 2; // Centrar verticalmente

    printf("\nIndique a linha (0 a %d) para o texto: ", ALTURA - 2);
    scanf("%d", &linha);
    // Verifica se a linha está dentro dos limites aceitáveis.
    if (linha < 0 || linha >= ALTURA - 1)
    {
        printf("\nErro: A linha indicada estah fora dos limites do quadro.\n");
        return 1;
    }
    printf("Indique a coluna (0 a %d) para o texto: ", LARGURA - 2);
    scanf("%d", &coluna);
   
    if (coluna < 0 || coluna >= LARGURA - 1)
    {
        printf("\nErro: A coluna indicada estah fora dos limites do quadro.\n");
        return 1; 
    }

    printf("\nEscreva o que deseja imprimir : ");
    scanf(" %[^\n]", entrada);

    printf("\nEscolha a cor do texto (1 = Verde, 2 = Azul, 3 = Vermelho): ");
    scanf("%d", &escolhaCor);
    switch (escolhaCor)
    {
        case 1:
            atributosTexto = VERDE_FRENTE;
            break;
        case 2:
            atributosTexto = AZUL_FRENTE;
            break;
        case 3:
            atributosTexto = VERMELHO_FRENTE;
            break;
        default:
            printf("\nCor invalida! Aplicando cor verde predefinição.\n");
            atributosTexto = VERDE_FRENTE; 
            break;
    }

    printf("\nLimpando o ecra...\n");
    clearScreen(0, 0, LARGURA, ALTURA, AZUL_FUNDO);
    drawFrame("TRABALHO PRATICO LC", atributosQuadro, inicioX, inicioY, larguraQuadro, alturaQuadro);

    if (comprimentoCadeia(entrada) == 1)
    {
        // Se a entrada for um único carácter.
        // printf("\nImprimindo um carácter...\n");
        printCharAt(entrada[0], inicioX + coluna, inicioY + linha, atributosTexto);
    }
    else if (eNumero(entrada))
    {
        // Se a entrada for um número, convertemos e imprimimos.
        // printf("\nImprimindo um número...\n");
        int num = cadeiaParaInteiro(entrada);
        char bufferNum[12]; // Suficiente para um int
        sprintf(bufferNum, "%d", num); // sprintf para converter int para string
        printStringAt(bufferNum, inicioX + coluna, inicioY + linha, atributosTexto);
    }
    else
    {
        // printf("\nImprimindo uma cadeia de caracteres...\n");
        printStringAt(entrada, inicioX + coluna, inicioY + linha, atributosTexto);
    }

    // printf("\nDemonstrando printCharRepeatedAt (linha de asteriscos)...\n");
    // printCharRepeatedAt('*', 30, inicioX + 5, inicioY + 5, VERMELHO_FRENTE | INTENSO);

    // // Demonstração de scrollRegion
    // printf("\nDemonstrando scrollRegion (rolagem de texto)...\n");
    // // Preenchemos uma área para depois fazer scroll
    // printStringAt("Esta eh a linha um.", inicioX + 2, inicioY + 10, NORMAL);
    // printStringAt("Esta eh a linha dois.", inicioX + 2, inicioY + 11, NORMAL);
    // printStringAt("Esta eh a linha três.", inicioX + 2, inicioY + 12, NORMAL);
    // printStringAt("Esta eh a linha quatro.", inicioX + 2, inicioY + 13, NORMAL);

    // printf("\nFazendo scroll de 1 linha para cima...\n");
    // scrollRegion(inicioX + 2, inicioY + 10, 30, 4, 1, NORMAL); // Scroll de 1 linha
    // getchar(); // Esperar por tecla

    // printf("\nFazendo scroll de 2 linhas para cima...\n");
    // scrollRegion(inicioX + 2, inicioY + 10, 30, 4, 2, NORMAL); // Scroll de 2 linhas
    // getchar(); // Esperar por tecla

    // printf("\nFazendo scroll de 4 linhas para cima (limpa a região)...\n");
    // scrollRegion(inicioX + 2, inicioY + 10, 30, 4, 4, NORMAL); // Scroll de 4 linhas (limpa)
    // getchar(); // Esperar por tecla

    // printf("\nFim da demonstração. Pressione qualquer tecla para sair...\n");
    // getchar(); // Esperar por tecla final.

    return 0; // Saída bem-sucedida.
}

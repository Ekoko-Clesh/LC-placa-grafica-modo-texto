# Makefile
# Trabalho 1

# Regra principal: constrói o executável final.
all: Trabalho1.exe

# Como construir o executável 'Trabalho1.exe'.
# Depende dos ficheiros objeto 'main.o' e 'LC_video_text.o'.
Trabalho1.exe: main.o LC_VID.o
	gcc -Wall main.o LC_VID.o -o Trabalho1.exe

# Regra para compilar o ficheiro 'LC_video_text.c' para 'LC_video_text.o'.
# Depende do seu próprio código-fonte e do ficheiro de cabeçalho 'LC_video_text.h'.
LC_VIDEO_TEXT.o: LC_VID.c LC_VID.h
	gcc -c -Wall LC_VID.c

# Regra para compilar o ficheiro 'main.c' para 'main.o'.
# Depende do seu próprio código-fonte.
main.o: main.c
	gcc -c -Wall main.c

# Limpar os ficheiros gerados pela compilação (.o e .exe).

clean:
	-rm -f *.o *.exe
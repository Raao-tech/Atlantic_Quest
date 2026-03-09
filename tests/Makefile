CC = gcc
# Busca todos los .c en el directorio actual
SRCS = $(wildcard *.c)
# Convierte la lista de .c en .o
OBJS = $(SRCS:.c=.o)

FLAGS = -g -Wall -O0 -Wextra -I ./headers -Wpedantic -DDEBUG 
PREFLAG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

set_tests:
	
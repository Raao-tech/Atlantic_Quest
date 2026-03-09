CC = gcc
FLAGS = -g -Wall -O0 -Wextra -I../headers -Wpedantic -DDEBUG
PREFLAG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

# Archivos necesarios para el test
# (Asegúrate de que los nombres coincidan exactamente con tus archivos)
SRCS = ../set.c  test_set.c
OBJS = $(SRCS:.c=.o)





# Regla principal para generar el ejecutable del test
test_set: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

# Regla genérica para convertir cualquier .c en .o
%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@




# Ejecutar el test con Valgrind para verificar fugas de memoria en el realloc
runv_set: test_set
	@read -p "Would you like to show data on the terminal? (s/n): " answ; \
	if [ "$$answ" = "n" ]; then \
		mkdir -p Outputs; \
		$(PREFLAG) ./test_set > Outputs/out_set.txt 2>&1; \
		echo "Results saved in Outputs/out_set.txt"; \
	else \
		$(PREFLAG) ./test_set; \
	fi
	
	make clean

# Limpiar archivos basura
clean:
	@rm -f *.o test_set

.PHONY: clean runv_set
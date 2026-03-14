# COMPILER AND FLAGS
CC = gcc
FLAGS = -g -Wall -O0 -Wextra -I../headers -Wpedantic -DDEBUG
PREFLAG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

# TARGETS
SET_BIN = set_test
ENT_BIN = entity_test
SPC_BIN = space_test
PLY_BIN = player_test

all: $(SET_BIN) $(ENT_BIN) $(SPC_BIN) $(PLY_BIN)

# COMPILATION RULES

# Set test
$(SET_BIN): set_test.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

# Entity test
$(ENT_BIN): entity_test.o ../entity.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

# Space test: space depends on set (for Set* inside Space)
$(SPC_BIN): space_test.o ../space.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

# Player test: There are two unused functions. Don't worry (8"D)  Be Happy... please
$(PLY_BIN): player_test.o ../player.o ../entity.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

# Local test objects
%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

# Parent directory objects
../%.o: ../%.c
	$(CC) -c $(FLAGS) $< -o $@

# RUN WITH VALGRIND
vset: $(SET_BIN)
	$(PREFLAG) ./$(SET_BIN)

vply: $(PLY_BIN)
	$(PREFLAG) ./$(PLY_BIN)

vent: $(ENT_BIN)
	$(PREFLAG) ./$(ENT_BIN)

vspc: $(SPC_BIN)
	$(PREFLAG) ./$(SPC_BIN)

# Run a single test: make run_set T=5
run_set: $(SET_BIN)
	./$(SET_BIN) $(T)

run_ply: $(PLY_BIN)
	./$(PLY_BIN) $(T)

run_ent: $(ENT_BIN)
	./$(ENT_BIN) $(T)

run_spc: $(SPC_BIN)
	./$(SPC_BIN) $(T)

# CLEANUP
#######################################
clean:
	@rm -f *.o ../*.o $(SET_BIN) $(ENT_BIN) $(SPC_BIN)

.PHONY: clean all vset vent vspc run_set run_ent run_spc

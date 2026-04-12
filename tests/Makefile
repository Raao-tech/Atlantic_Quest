# COMPILER AND FLAGS
CC = gcc
FLAGS = -g -Wall -O0 -Wextra -I../headers -Wpedantic -DDEBUG
PREFLAG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

# TARGETS
SET_BIN = set_test
ENT_BIN = entity_test
SPC_BIN = space_test
PLY_BIN = player_test
CHR_BIN = character_test
GAM_BIN = game_test
CMD_BIN = command_test
LNK_BIN = links_test
OBJ_BIN = object_test

all: $(SET_BIN) $(ENT_BIN) $(SPC_BIN) $(PLY_BIN) $(CHR_BIN) $(GAM_BIN) $(CMD_BIN) $(LNK_BIN) $(OBJ_BIN)

# COMPILATION RULES

$(SET_BIN): set_test.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

$(ENT_BIN): entity_test.o ../entity.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

$(SPC_BIN): space_test.o ../space.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

$(PLY_BIN): player_test.o ../player.o ../entity.o ../inventory.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

$(CHR_BIN): character_test.o ../character.o ../entity.o ../set.o
	$(CC) $(FLAGS) $^ -o $@

$(GAM_BIN): game_test.o ../game.o ../player.o ../character.o ../object.o ../space.o ../entity.o ../inventory.o ../set.o ../command.o ../links.o

$(CMD_BIN): command_test.o ../command.o
	$(CC) $(FLAGS) $^ -o $@

$(LNK_BIN): links_test.o ../links.o
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_BIN): object_test.o ../object.o
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

../%.o: ../src/%.c
	$(CC) -c $(FLAGS) $< -o $@

# RUN WITH VALGRIND
vset: $(SET_BIN)
	$(PREFLAG) ./$(SET_BIN)
vent: $(ENT_BIN)
	$(PREFLAG) ./$(ENT_BIN)
vspc: $(SPC_BIN)
	$(PREFLAG) ./$(SPC_BIN)
vply: $(PLY_BIN)
	$(PREFLAG) ./$(PLY_BIN)
vchr: $(CHR_BIN)
	$(PREFLAG) ./$(CHR_BIN)
vgam: $(GAM_BIN)
	$(PREFLAG) ./$(GAM_BIN)
vcmd: $(CMD_BIN)
	$(PREFLAG) ./$(CMD_BIN)
vlnk: $(LNK_BIN)
	$(PREFLAG) ./$(LNK_BIN)
vobj: $(OBJ_BIN)
	$(PREFLAG) ./$(OBJ_BIN)

# RUN SINGLE TEST
run_set: $(SET_BIN)
	./$(SET_BIN) $(T)
run_ent: $(ENT_BIN)
	./$(ENT_BIN) $(T)
run_spc: $(SPC_BIN)
	./$(SPC_BIN) $(T)
run_ply: $(PLY_BIN)
	./$(PLY_BIN) $(T)
run_chr: $(CHR_BIN)
	./$(CHR_BIN) $(T)
run_gam: $(GAM_BIN)
	./$(GAM_BIN) $(T)
run_cmd: $(CMD_BIN)
	./$(CMD_BIN) $(T)
run_lnk: $(LNK_BIN)
	./$(LNK_BIN) $(T)
run_obj: $(OBJ_BIN)
	./$(OBJ_BIN) $(T)

# CLEANUP
clean:
	@rm -f *.o ../*.o $(SET_BIN) $(ENT_BIN) $(SPC_BIN) $(PLY_BIN) $(CHR_BIN) $(GAM_BIN) $(CMD_BIN) $(LNK_BIN) $(OBJ_BIN)

.PHONY: clean all vset vent vspc vply vchr vgam vcmd vlnk vobj

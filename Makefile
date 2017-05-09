#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
#

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TEST_DIR=./testes
MOCKS_DIR=./testes/mocks
MOCKS_BIN_DIR=./testes/mocks/bin

all: regra1 regra2 regran

regra1: #dependências para a regra1
	$(CC) -o $(BIN_DIR)regra1 $(SRC_DIR)regra1.c -Wall

regra2: #dependências para a regra2
	$(CC) -o $(BIN_DIR)regra2 $(SRC_DIR)regra2.c -Wall

regran: #dependências para a regran
	$(CC) -o $(BIN_DIR)regran $(SRC_DIR)regran.c -Wall

short_scheduler: #dependências para a regran
	$(CC) $(SRC_DIR)/short_scheduler.c -c -o $(BIN_DIR)/short_scheduler -Wall

ready_queue_mock:
	$(CC) $(MOCKS_DIR)/ready_queue.c -c -o $(MOCKS_BIN_DIR)/ready_queue  -Wall

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~

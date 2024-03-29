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

CC=gcc -m32
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TEST_DIR=./testes
TEST_BIN_DIR=./testes/bin
MOCKS_DIR=./testes/mocks
MOCKS_BIN_DIR=./testes/mocks/bin

all: interface short_scheduler execution_queue semaphore ready_queue medium_scheduler blocking_queue long_scheduler
	ar crs $(BIN_DIR)/libcthreads.a $(BIN_DIR)/interface.o $(BIN_DIR)/short_scheduler $(BIN_DIR)/execution_queue $(BIN_DIR)/semaphore $(BIN_DIR)/medium_scheduler $(BIN_DIR)/ready_queue $(BIN_DIR)/long_scheduler $(BIN_DIR)/blocking_queue $(BIN_DIR)/support.o

interface:
	$(CC) $(SRC_DIR)/interface.c  -c -o $(BIN_DIR)/interface.o

short_scheduler:
	$(CC) $(SRC_DIR)/short_scheduler.c -c -o $(BIN_DIR)/short_scheduler -Wall

long_scheduler:
	$(CC) $(SRC_DIR)/long_scheduler.c  -c -o $(BIN_DIR)/long_scheduler -Wall

execution_queue:
	$(CC) $(SRC_DIR)/execution_queue.c -c -o $(BIN_DIR)/execution_queue -Wall

semaphore:
	$(CC) $(SRC_DIR)/semaphore.c -c -o $(BIN_DIR)/semaphore -Wall

ready_queue:
	$(CC) $(SRC_DIR)/ready_queue.c -c -o $(BIN_DIR)/ready_queue -Wall

medium_scheduler:
	$(CC) $(SRC_DIR)/medium_scheduler.c  -c -o $(BIN_DIR)/medium_scheduler -Wall

blocking_queue:
	$(CC) $(SRC_DIR)/blocking_queue.c  -c -o $(BIN_DIR)/blocking_queue -Wall

#------------------------_TESTES_---------------------------

short_scheduler_test: ready_queue_mock short_scheduler execution_queue_mock thread_mock
	$(CC) $(TEST_DIR)/short_scheduler_test.c $(BIN_DIR)/short_scheduler $(MOCKS_BIN_DIR)/execution_queue $(MOCKS_BIN_DIR)/ready_queue $(MOCKS_BIN_DIR)/thread -o $(TEST_BIN_DIR)/short_scheduler_test -Wall

semaphore_test: short_scheduler thread_mock ready_queue_mock medium_scheduler_mock execution_queue_mock
	$(CC) $(TEST_DIR)/semaphore_test.c $(BIN_DIR)/short_scheduler $(MOCKS_BIN_DIR)/execution_queue $(MOCKS_BIN_DIR)/ready_queue $(MOCKS_BIN_DIR)/medium_scheduler $(BIN_DIR)/support.o $(SRC_DIR)/semaphore.c $(MOCKS_BIN_DIR)/thread -o $(TEST_BIN_DIR)/semaphore_test -Wall

full_test:
	$(CC) $(TEST_DIR)/full_test.c $(BIN_DIR)/libcthreads.a -o $(TEST_DIR)/full

#------------------------_MOCKS_-------------------------------

ready_queue_mock: thread_mock
	$(CC) $(MOCKS_DIR)/ready_queue.c -c -o $(MOCKS_BIN_DIR)/ready_queue -Wall

execution_queue_mock: thread_mock
	$(CC) $(MOCKS_DIR)/execution_queue.c -c -o $(MOCKS_BIN_DIR)/execution_queue -Wall

medium_scheduler_mock: thread_mock
	$(CC) $(MOCKS_DIR)/medium_scheduler.c -c -o $(MOCKS_BIN_DIR)/medium_scheduler -Wall

thread_mock:
	$(CC) $(MOCKS_DIR)/thread.c -c -o $(MOCKS_BIN_DIR)/thread -Wall
#-------------------------_clean_--------------------------------
clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*  $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ & cp ./support.o $(BIN_DIR)/support.o

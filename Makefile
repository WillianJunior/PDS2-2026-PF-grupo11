CXX        := g++
CXX_FLAGS  := -Wall -Wextra -std=c++17 -ggdb

BIN        := build
SRC        := src
INCLUDE    := include 
LIB        := lib
TESTS      := tests

LIBRARIES  :=
EXECUTABLE := main

# Detecta se está no Windows para aplicar a extensão .exe correta
ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
    FIX_PATH = $(subst /,\,$1)
else
    EXE_EXT :=
    FIX_PATH = $1
endif

TEST_EXEC  := test_runner$(EXE_EXT)
MAIN_EXEC  := $(EXECUTABLE)$(EXE_EXT)

SRC_FILES  := $(filter-out $(SRC)/main.cpp, $(wildcard $(SRC)/*.cpp))
TEST_FILES := $(wildcard $(TESTS)/*.cpp)

MAIN_OBJS        := $(patsubst $(SRC)/%.cpp, $(BIN)/%.o, $(wildcard $(SRC)/*.cpp))
TEST_SRC_OBJS    := $(patsubst $(SRC)/%.cpp, $(BIN)/%_test.o, $(SRC_FILES))
TEST_RUNNER_OBJS := $(patsubst $(TESTS)/%.cpp, $(BIN)/%_test.o, $(TEST_FILES))

all: $(BIN)/$(MAIN_EXEC)

run: all
	./$(BIN)/$(MAIN_EXEC)

$(BIN)/$(MAIN_EXEC): $(MAIN_OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) $^ -o $@ -L$(LIB) $(LIBRARIES)

$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

# Força a execução sem travar e especifica o gcov correto para evitar o mismatch de versão
test: $(BIN)/$(TEST_EXEC)
	-rm -f $(BIN)/*.gcda
	-./$(BIN)/$(TEST_EXEC) -s
	gcovr -r . --gcov-executable gcov --exclude "$(TESTS)/.*" --exclude "$(SRC)/main.cpp" --exclude "src/InterfaceTerminal.cpp" --exclude "include/doctest.h"

$(BIN)/$(TEST_EXEC): $(TEST_SRC_OBJS) $(TEST_RUNNER_OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) --coverage $^ -o $@ -L$(LIB) $(LIBRARIES)

$(BIN)/%_test.o: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) --coverage -I$(INCLUDE) -c $< -o $@

$(BIN)/%_test.o: $(TESTS)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) --coverage -I$(INCLUDE) -c $< -o $@

# Limpa apenas o programa principal, mantendo os testes intactos
clean:
	-rm -f $(MAIN_OBJS) $(BIN)/$(MAIN_EXEC)

# Limpa absolutamente tudo (use apenas quando quiser resetar o projeto)
clean_all:
	-rm -rf $(BIN)/*
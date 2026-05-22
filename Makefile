CXX        := g++
CXX_FLAGS  := -Wall -Wextra -std=c++17 -ggdb

BIN        := build
SRC        := src
INCLUDE    := include 
LIB        := lib
TESTS      := tests

LIBRARIES  :=
EXECUTABLE := main
TEST_EXEC  := test_runner

SRC_FILES  := $(filter-out $(SRC)/main.cpp, $(wildcard $(SRC)/*.cpp))
TEST_FILES := $(wildcard $(TESTS)/*.cpp)

MAIN_OBJS        := $(patsubst $(SRC)/%.cpp, $(BIN)/%.o, $(wildcard $(SRC)/*.cpp))
TEST_SRC_OBJS    := $(patsubst $(SRC)/%.cpp, $(BIN)/%_test.o, $(SRC_FILES))
TEST_RUNNER_OBJS := $(patsubst $(TESTS)/%.cpp, $(BIN)/%_test.o, $(TEST_FILES))

all: $(BIN)/$(EXECUTABLE)

run: all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(MAIN_OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) $^ -o $@ -L$(LIB) $(LIBRARIES)

$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

test: $(BIN)/$(TEST_EXEC)
	-rm -f $(BIN)/*.gcda
	-./$(BIN)/$(TEST_EXEC) -s
	gcovr -r . --exclude "$(TESTS)/.*" --exclude "$(SRC)/main.cpp" --exclude "include/doctest.h"

$(BIN)/$(TEST_EXEC): $(TEST_SRC_OBJS) $(TEST_RUNNER_OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) --coverage $^ -o $@ -L$(LIB) $(LIBRARIES)

$(BIN)/%_test.o: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) --coverage -I$(INCLUDE) -c $< -o $@

$(BIN)/%_test.o: $(TESTS)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) --coverage -I$(INCLUDE) -c $< -o $@

clean:
	-rm -rf $(BIN)/*
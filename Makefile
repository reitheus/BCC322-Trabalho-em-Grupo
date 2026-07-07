CXX = g++

SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

FUNC_TEST_DIR = test/functional
UNIT_TEST_DIR = test/unit

CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INCLUDE_DIR)

$(shell mkdir -p $(BIN_DIR))

TARGET = $(BIN_DIR)/prog
FUNC_TARGET = $(BIN_DIR)/progTestFuncional
UNIT_TARGET = $(BIN_DIR)/progTestUnit

SRC_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
LIB_SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(LIB_SRCS))

FUNC_TEST_SRCS = $(wildcard $(FUNC_TEST_DIR)/*.cpp)
FUNC_TEST_OBJS = $(patsubst $(FUNC_TEST_DIR)/%.cpp, $(BIN_DIR)/%.func.o, $(wildcard $(FUNC_TEST_DIR)/*.cpp))

UNIT_TEST_SRCS = $(wildcard $(UNIT_TEST_DIR)/*.cpp)
UNIT_MAIN = $(UNIT_TEST_DIR)/main.cpp
UNIT_LIB_SRCS = $(filter-out $(UNIT_MAIN),$(UNIT_TEST_SRCS))
UNIT_TEST_OBJS = $(patsubst $(UNIT_TEST_DIR)/%.cpp,$(BIN_DIR)/%.unit.o,$(UNIT_LIB_SRCS))
UNIT_MAIN_OBJ = $(BIN_DIR)/main.unit.o

.PHONY: all clean functional_tests unit_tests run

all: $(TARGET) $(FUNC_TARGET) $(UNIT_TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.func.o: $(FUNC_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.unit.o: $(UNIT_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(SRC_DIR)/main.cpp $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(FUNC_TARGET): $(LIB_OBJS) $(FUNC_TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(UNIT_MAIN_OBJ): $(UNIT_MAIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UNIT_TARGET): $(LIB_OBJS) $(UNIT_TEST_OBJS) $(UNIT_MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

functional_tests: $(FUNC_TARGET)
	./$(FUNC_TARGET)

unit_tests: $(UNIT_TARGET)
	./$(UNIT_TARGET)

run: functional_tests unit_tests

clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.func.o
	rm -f $(BIN_DIR)/*.unit.o
	rm -f $(TARGET)
	rm -f $(FUNC_TARGET)
	rm -f $(UNIT_TARGET)

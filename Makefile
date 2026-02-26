BUILD_DIR = build
SRC_DIR = src

ATNLR4_DIR = antlr4
ATNLR4_INCLUDE = $(ATNLR4_DIR)/include 
ATNLR4_LIB = $(ATNLR4_DIR)/lib 

CXX_FLAGS = --std=c++17 -Wall -Wextra -I$(ATNLR4_INCLUDE) -I.

CXX_ANTLR4_DYNAMIC_LIB = -lantlr4-runtime
CXX_ANTLR4_STATIC_LIB = -lantlr4-runtime-static

GRAMMAR_NAME = TryCatchGrammar

ANTLR4_GENERATED = generated

.PHONY: grammar src link

all: grammar $(BUILD_DIR) src link

grammar: $(BUILD_DIR)/grammar

$(BUILD_DIR)/grammar: $(GRAMMAR_NAME).g4
	antlr4 -Dlanguage=Cpp $(GRAMMAR_NAME).g4 -o $(ANTLR4_GENERATED)
	touch $(BUILD_DIR)/grammar


src: $(BUILD_DIR)/AST.o $(BUILD_DIR)/listener.o $(BUILD_DIR)/interpret.o $(BUILD_DIR)/main.o

$(BUILD_DIR)/AST.o: $(SRC_DIR)/AST.cpp $(SRC_DIR)/AST.h
	g++ $(CXX_FLAGS) -c $(SRC_DIR)/AST.cpp -o $(BUILD_DIR)/AST.o 
$(BUILD_DIR)/listener.o: $(SRC_DIR)/listener.cpp $(SRC_DIR)/listener.h
	g++ $(CXX_FLAGS) -c $(SRC_DIR)/listener.cpp -o $(BUILD_DIR)/listener.o 
$(BUILD_DIR)/interpret.o: $(SRC_DIR)/interpret.cpp $(SRC_DIR)/interpreter.h
	g++ $(CXX_FLAGS) -c $(SRC_DIR)/interpret.cpp -o $(BUILD_DIR)/interpret.o 
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	g++ $(CXX_FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o 

generate: grammar $(BUILD_DIR)/TryCatchGrammarBaseListener.o $(BUILD_DIR)/TryCatchGrammarListener.o $(BUILD_DIR)/TryCatchGrammarLexer.o $(BUILD_DIR)/TryCatchGrammarParser.o

$(BUILD_DIR)/TryCatchGrammarBaseListener.o: $(ANTLR4_GENERATED)/TryCatchGrammarBaseListener.cpp
	g++ -c $(CXX_FLAGS) $(ANTLR4_GENERATED)/TryCatchGrammarBaseListener.cpp -o $(BUILD_DIR)/TryCatchGrammarBaseListener.o
$(BUILD_DIR)/TryCatchGrammarLexer.o: $(ANTLR4_GENERATED)/TryCatchGrammarLexer.cpp
	g++ -c $(CXX_FLAGS) $(ANTLR4_GENERATED)/TryCatchGrammarLexer.cpp -o $(BUILD_DIR)/TryCatchGrammarLexer.o
$(BUILD_DIR)/TryCatchGrammarParser.o: $(ANTLR4_GENERATED)/TryCatchGrammarParser.cpp
	g++ -c $(CXX_FLAGS) $(ANTLR4_GENERATED)/TryCatchGrammarParser.cpp -o $(BUILD_DIR)/TryCatchGrammarParser.o
$(BUILD_DIR)/TryCatchGrammarListener.o: $(ANTLR4_GENERATED)/TryCatchGrammarListener.cpp
	g++ -c $(CXX_FLAGS) $(ANTLR4_GENERATED)/TryCatchGrammarListener.cpp -o $(BUILD_DIR)/TryCatchGrammarListener.o

link: main.exe

main.exe: src generate
	g++ $(BUILD_DIR)/*.o -L$(ATNLR4_LIB) $(CXX_ANTLR4_DYNAMIC_LIB) -o main.exe

clear:
	rm $(BUILD_DIR)/*
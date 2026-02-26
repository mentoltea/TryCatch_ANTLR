#include "AST.h"
#include "listener.h"
#include "interpreter.h"

#include "generated/TryCatchGrammarLexer.h"
#include "generated/TryCatchGrammarParser.h"
#include "generated/TryCatchGrammarListener.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Filepath is expected" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];
    std::ifstream fd(filepath);

    std::string input;
    std::string line;
    while (std::getline(fd, line)) {
        input += line + "\n";
    }

    antlr4::ANTLRInputStream stream(input);
    
    TryCatchGrammarLexer lexer(&stream);    
    antlr4::CommonTokenStream tokens(&lexer);
    
    TryCatchGrammarParser parser(&tokens);    
    antlr4::tree::ParseTree* tree = parser.prog();
    
    MyListener listener;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    auto *ast = listener.ast;

    bool int_success = Interpreter::interpret(ast);
    if (int_success == false) {
        std::cerr << "INTERPRETING ERROR" << std::endl;
        return 1;
    }
    std::cout << "Successfully interpreted" << std::endl;

    return 0;
}
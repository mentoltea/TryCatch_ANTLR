#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "AST.h"

class Interpreter {
    struct State {
        bool active_exception;
        struct ExceptionDescription {
            std::string type;
            std::string var;
            AST::Expression* value;

            bool operator==(const ExceptionDescription& other) const;
        };
        std::vector<ExceptionDescription> scope;
    };
    
    static bool int_statement(AST::Statement *ptr, State &state);
    static bool int_block(AST::Block *ptr, State &state);
    static bool int_tryblock(AST::TryBlock *ptr, State &state);
    static bool int_catchblock(AST::CatchBlock *ptr, State &state);
    static bool int_trycatchblock(AST::TryCatchBlock *ptr, State &state);
    
    public:
    static bool interpret(AST::TryCatchBlock *root);
};

#endif // INTERPRETER_H
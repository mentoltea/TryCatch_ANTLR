#include "interpreter.h"
#include <iostream>
#include <algorithm>

using namespace AST;

bool Interpreter::State::ExceptionDescription::operator==(const ExceptionDescription& other) const {
    if (this == &other) return true;
    return (type == other.type) && (value == other.value);
}


bool Interpreter::int_statement(Statement *ptr, State &state) {
    // std::cout << "int_statement" << std::endl;
    bool result = true;
    switch (ptr->type) {
        case Statement::PRINT : {
            PrintStatement *ps = (PrintStatement *)ptr;
            if (ps->argument->type == Expression::INT) 
                std::cout << ps->argument->intlit << std::endl;
            else if (ps->argument->type == Expression::STR) {
                std::cout << ps->argument->strlit << std::endl;
            }
        } break;

        case Statement::TRYCATCH : {
            TryCatchStatement *tcs = (TryCatchStatement *)ptr;
            result = int_trycatchblock(tcs->tcblock, state);
        } break;

        case Statement::THROW : {
            ThrowStatement *ts = (ThrowStatement *)ptr;
            Exception *exc = ts->exception;
            if (exc->type == Exception::NEW) {
                NewException *nexc = (NewException*) exc;
                State::ExceptionDescription descr;
                descr.type = nexc->exception_type;
                descr.value = nexc->exception_argument;

                state.active_exception = true;
                state.scope.push_back(descr);
            }
            else if (exc->type == Exception::VAR) {
                VarException *vexc = (VarException*) exc;
                size_t index = 0;
                for (; index < state.scope.size(); index++) {
                    if (state.scope[index].var == vexc->exception_var) {
                        break;
                    }
                }
                if (index >= state.scope.size()) {
                    std::cout << "Unknown exception variable `" 
                        << vexc->exception_var << "`" << std::endl;
                        result = false;
                    break;
                }
                State::ExceptionDescription descr = state.scope[index];
                
                state.active_exception = true;
                state.scope.push_back(descr);
            }
        } break;
    }
    // std::cout << "int_statement end " << result << std::endl;
    return result;
}

bool Interpreter::int_block(Block *ptr, State &state) {
    // std::cout << "int_block" << std::endl;
    bool result;
    for (Statement *st: ptr->statements) {
        result = int_statement(st, state);
        if (result == false) return false;
        if (state.active_exception) return true;
    }
    return true;
}

bool Interpreter::int_tryblock(TryBlock *ptr, State &state) {
    // std::cout << "int_tryblock" << std::endl;
    Block* b = ptr->block;
    bool result = int_block(b, state);
    return result;
}

bool Interpreter::int_catchblock(CatchBlock *ptr, State &state) {
    // std::cout << "int_catchblock" << std::endl;
    Block* b = ptr->block;
    bool result = int_block(b, state);
    return result;
}

bool Interpreter::int_trycatchblock(TryCatchBlock *ptr, State &state) {
    // std::cout << "int_trycatchblock" << std::endl;
    bool result = int_tryblock(ptr->try_block, state);
    if (result == false) return false;
    if (state.active_exception) {
        size_t index = 0;
        auto &exc = state.scope.back();
        while (index < ptr->catch_blocks.size()) {
            CatchBlock *cb = ptr->catch_blocks[index];
            if (cb->exception_type == exc.type) {
                break;
            }
            index++;
        } 
        if (index >= ptr->catch_blocks.size()) return true;
        
        CatchBlock *cb = ptr->catch_blocks[index];
        
        state.active_exception = false;
        for (size_t i=0; i<state.scope.size(); i++) {
            if (state.scope[i].var == cb->exception_var) {
                std::cout << "Conflicting exception variable name: `" 
                    << cb->exception_var << "`" << std::endl;
                std::cout << "Name is already in scope" << std::endl;
                return false;
            }
        }
        exc.var = cb->exception_var; 

        result = int_catchblock(cb, state);
        if (result == false) return false;
        
        state.scope.erase(std::find(state.scope.begin(), state.scope.end(), exc));        
    }
    return true;
}

bool Interpreter::interpret(TryCatchBlock *root) {
    State state;
    state.active_exception = false;

    bool result = int_trycatchblock(root, state);
    if (result) {
        if (state.active_exception) {
            auto exc = state.scope.back();
            std::cout << "Unhandled exception: " << exc.type << " ( ";

            if (exc.value->type == Expression::STR)
                std::cout << '"' << exc.value->strlit << '"' << " )" << std::endl;
            else if (exc.value->type == Expression::INT)
                std::cout << exc.value->intlit << " )" << std::endl;
            else {
                std::cerr << exc.type << std::endl;
            }

        }
    }
    return result;
}
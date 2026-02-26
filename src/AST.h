#ifndef AST_H
#define AST_H

#include <vector>
#include <string>
#include <fstream>

namespace AST {
    
struct Node {
    virtual ~Node() = default;
    virtual void print(std::ostream &os, int tabs = 0) const = 0;
};

struct TryCatchBlock;

struct Expression: public Node {
    std::string strlit;
    int intlit;
    enum {
        STR,
        INT
    } type;

    ~Expression() override;
    void print(std::ostream &os, int tabs = 0) const override;
};



struct Exception: public Node {
    enum {
        VAR,
        NEW,
    } type;
};

struct VarException: public Exception {
    std::string exception_var;

    ~VarException() override;
    void print(std::ostream &os, int tabs = 0) const override;
};

struct NewException: public Exception {
    std::string exception_type;
    Expression* exception_argument;

    ~NewException() override;
    void print(std::ostream &os, int tabs = 0) const override;
};



struct Statement: public Node {
    enum {
        PRINT,
        THROW,
        TRYCATCH,
    } type;

    ~Statement() = default;
};

struct PrintStatement: public Statement {
    Expression* argument;
    ~PrintStatement() override;
    void print(std::ostream &os, int tabs = 0) const override;
};

struct ThrowStatement: public Statement {
    Exception* exception;
    ~ThrowStatement() override;
    void print(std::ostream &os, int tabs = 0) const override;
};

struct TryCatchStatement: public Statement {
    TryCatchBlock* tcblock;
    ~TryCatchStatement() override;
    void print(std::ostream &os, int tabs = 0) const override;
};




struct Block: public Node {
    std::vector< Statement* > statements;
    ~Block() override;
    void print(std::ostream &os, int tabs = 0) const override;
};

struct TryBlock: public Node {
    Block* block;
    ~TryBlock() override;
    void print(std::ostream &os, int tabs = 0) const override;
};

struct CatchBlock: public Node {
    std::string exception_type;
    std::string exception_var;
    Block* block;
    ~CatchBlock() override;
    void print(std::ostream &os, int tabs = 0) const override;
};

struct TryCatchBlock: public Node {
    TryBlock* try_block;
    std::vector< CatchBlock* > catch_blocks;
    ~TryCatchBlock() override;
    void print(std::ostream &os, int tabs = 0) const override;
};

};

#endif
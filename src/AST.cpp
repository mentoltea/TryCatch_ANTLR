#include "AST.h"
using namespace AST;


Expression::~Expression() {}
void Expression::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    if (type == STR) {
        os << "STR( " << strlit << " )";
    } else if (type == INT) {
        os << "INT( " << intlit << " )";
    }
}

VarException::~VarException() {}
void VarException::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Exception{ var = " << this->exception_var << " }";
}

NewException::~NewException() {
    if (exception_argument) delete exception_argument;
}
void NewException::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Exception{ " 
        << "type = " << this->exception_type
        << ", arg = "; this->exception_argument->print(os, tabs+1); 
    os << " }";
}


PrintStatement::~PrintStatement() {
    if (argument) delete argument;
}
void PrintStatement::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Print{ " 
        << "arg = "; this->argument->print(os, tabs+1); 
    os << " }";
}


ThrowStatement::~ThrowStatement() {
    if (exception) delete exception;
}
void ThrowStatement::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Throw{ " 
        << "arg = "; this->exception->print(os, tabs+1); 
    os << " }";
}


TryCatchStatement::~TryCatchStatement() {
    if (tcblock) delete tcblock;
}
void TryCatchStatement::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Throw{ " << std::endl;
        for (int t=0; t<tabs+1; t++) os << '\t'; 
        this->tcblock->print(os, tabs+1);
        for (int t=0; t<tabs; t++) os << '\t'; 
    os << " }";
}

Block::~Block() {
    for (auto ptr: statements) {
        if (ptr) delete ptr;
    }
}
void Block::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Block{" << std::endl;
    for (auto ptr: statements) {
        for (int t=0; t<tabs+1; t++) os << '\t';
        ptr->print(os, tabs+1);
        os << ';' << std::endl;
    }
    for (int t=0; t<tabs; t++) os << '\t';
    os << "}" << std::endl;
}


TryBlock::~TryBlock() {
    if (block) delete block;
}
void TryBlock::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Try {" << std::endl;
        for (int t=0; t<tabs+1; t++) os << '\t';
        block->print(os, tabs+1);
        for (int t=0; t<tabs; t++) os << '\t';
    os << "} ";
}

CatchBlock::~CatchBlock() {
    if (block) delete block;
}
void CatchBlock::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "Catch { type = " << exception_type << ", var = " << exception_var  << std::endl;
        for (int t=0; t<tabs+1; t++) os << '\t';
        block->print(os, tabs+1);
        for (int t=0; t<tabs; t++) os << '\t';
        os << "} ";
    }
    
TryCatchBlock::~TryCatchBlock() {
    if (try_block) delete try_block;
    for (auto ptr: catch_blocks) {
        if (ptr) delete ptr;
    }
}
void TryCatchBlock::print(std::ostream &os, int tabs) const {
    (void)(tabs);
    os << "TryCatchBlock { " << std::endl;
        for (int t=0; t<tabs+1; t++) os << '\t';
        try_block->print(os, tabs+1);
        for (auto ptr: catch_blocks) {
            ptr->print(os, tabs+1);
        }
        os << std::endl;
        for (int t=0; t<tabs; t++) os << '\t';
    os << "} ";
}
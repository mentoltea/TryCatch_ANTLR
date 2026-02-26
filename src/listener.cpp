#include "listener.h"


void MyListener::enterProg(TryCatchGrammarParser::ProgContext *ctx) {
}

void MyListener::exitProg(TryCatchGrammarParser::ProgContext *ctx) {
    this->ast = (AST::TryCatchBlock*) state.stack.top();
    state.stack.pop();
    assert(state.stack.size() == 0);
}

void MyListener::enterTryCatchBlock(TryCatchGrammarParser::TryCatchBlockContext *ctx) {
}

void MyListener::exitTryCatchBlock(TryCatchGrammarParser::TryCatchBlockContext *ctx) {
    AST::TryCatchBlock *tcb = new AST::TryCatchBlock;

    std::stack< AST::CatchBlock* > reversed;

    size_t catch_count = ctx->catchBlock().size();
    for (size_t i=0; i<catch_count; i++) {
        AST::CatchBlock *cb = (AST::CatchBlock*) state.stack.top();
        state.stack.pop();
        reversed.push(cb);
    }

    tcb->try_block = (AST::TryBlock*) state.stack.top();
    state.stack.pop();

    for (size_t i=0; i<catch_count; i++) {
        AST::CatchBlock *cb = reversed.top();
        reversed.pop();
        tcb->catch_blocks.push_back(cb);
    }

    state.stack.push(tcb);
}

void MyListener::enterTryBlock(TryCatchGrammarParser::TryBlockContext *ctx) {
}

void MyListener::exitTryBlock(TryCatchGrammarParser::TryBlockContext *ctx) {
    AST::TryBlock *tb = new AST::TryBlock;
    
    tb->block = (AST::Block*) state.stack.top();
    state.stack.pop();

    state.stack.push(tb);
}

void MyListener::enterCatchBlock(TryCatchGrammarParser::CatchBlockContext *ctx) {
}

void MyListener::exitCatchBlock(TryCatchGrammarParser::CatchBlockContext *ctx) {
    AST::CatchBlock *cb = new AST::CatchBlock;
    
    cb->exception_type = ctx->ID(0)->getText();
    cb->exception_var = ctx->ID(1)->getText();
    cb->block = (AST::Block*) state.stack.top();
    state.stack.pop();

    state.stack.push(cb);
}

void MyListener::enterBlock(TryCatchGrammarParser::BlockContext *ctx) {
}

void MyListener::exitBlock(TryCatchGrammarParser::BlockContext *ctx) {
    AST::Block *block = new AST::Block;
    std::stack< AST::Statement* > reversed;

    size_t count = ctx->statement().size();

    for (size_t i=0; i < count; i++) {
        AST::Statement *st = (AST::Statement*) state.stack.top();
        state.stack.pop();
        reversed.push(st);
    }
    for (size_t i=0; i < count; i++) {
        AST::Statement *st = reversed.top();
        reversed.pop();
        block->statements.push_back(st);
    }

    state.stack.push(block);
}

void MyListener::enterStatement(TryCatchGrammarParser::StatementContext *ctx) {
}

void MyListener::exitStatement(TryCatchGrammarParser::StatementContext *ctx) {
}

void MyListener::enterTryCatchBlockStatement(TryCatchGrammarParser::TryCatchBlockStatementContext *ctx) {
}

void MyListener::exitTryCatchBlockStatement(TryCatchGrammarParser::TryCatchBlockStatementContext *ctx) {
    AST::TryCatchStatement *st = new AST::TryCatchStatement;
    st->type = AST::Statement::TRYCATCH;
    st->tcblock = (AST::TryCatchBlock*) state.stack.top();
    state.stack.pop();
    state.stack.push(st);
}

void MyListener::enterThrowStatement(TryCatchGrammarParser::ThrowStatementContext *ctx) {
}

void MyListener::exitThrowStatement(TryCatchGrammarParser::ThrowStatementContext *ctx) {
    AST::ThrowStatement *st = new AST::ThrowStatement;
    st->type = AST::Statement::THROW;
    st->exception = (AST::Exception*) state.stack.top();
    state.stack.pop();
    state.stack.push(st);
}

void MyListener::enterException_(TryCatchGrammarParser::Exception_Context *ctx) {
}

void MyListener::exitException_(TryCatchGrammarParser::Exception_Context *ctx) {
    AST::Exception* exc = nullptr;

    if (ctx->NEW()) { // NEW
        AST::Expression* expr = (AST::Expression*) state.stack.top(); state.stack.pop();
        
        AST::NewException *ne = new AST::NewException;
        ne->type = AST::Exception::NEW;
        ne->exception_type = ctx->ID()->getText();
        ne->exception_argument = expr;
        
        exc = ne;
    } else  { // VAR
        AST::VarException *ve = new AST::VarException;
        ve->type = AST::Exception::VAR;
        ve->exception_var = ctx->ID()->getText();
        exc = ve;
    }

    state.stack.push(exc);
}

void MyListener::enterPrintStatement(TryCatchGrammarParser::PrintStatementContext *ctx) {
}
void MyListener::exitPrintStatement(TryCatchGrammarParser::PrintStatementContext *ctx) {
    auto *st = new AST::PrintStatement;
    st->type = AST::Statement::PRINT;

    AST::Expression* expr = (AST::Expression*)state.stack.top(); 
    state.stack.pop();
    
    st->argument = expr;

    state.stack.push(st);
}

void MyListener::enterExpression(TryCatchGrammarParser::ExpressionContext *ctx) {
}

void MyListener::exitExpression(TryCatchGrammarParser::ExpressionContext *ctx) {
    AST::Expression *expr = new AST::Expression;
    
    auto node = ctx->INT_LITERAL();
    if (node) {
        expr->type = AST::Expression::INT;
        expr->intlit = std::stoi(node->getText());
    } else {
        node = ctx->STRING_LITERAL();
    
        expr->type = AST::Expression::STR;
        expr->strlit = node->getText();
    }
    
    state.stack.push(expr);
}



#ifndef LISTENER_H
#define LISTENER_H

#include "AST.h"
#include "generated/TryCatchGrammarBaseListener.h"

#include <stack>

class MyListener : public TryCatchGrammarBaseListener {
public:
    struct State {
        std::stack< AST::Node* > stack;
        bool exception_flag = false;
        std::string exception;
    } state;
    AST::TryCatchBlock *ast;

    virtual void enterProg(TryCatchGrammarParser::ProgContext *ctx) override;
    virtual void exitProg(TryCatchGrammarParser::ProgContext *ctx) override;

    virtual void enterTryCatchBlock(TryCatchGrammarParser::TryCatchBlockContext *ctx) override;
    virtual void exitTryCatchBlock(TryCatchGrammarParser::TryCatchBlockContext *ctx) override;

    virtual void enterTryBlock(TryCatchGrammarParser::TryBlockContext *ctx) override;
    virtual void exitTryBlock(TryCatchGrammarParser::TryBlockContext *ctx) override;

    virtual void enterCatchBlock(TryCatchGrammarParser::CatchBlockContext *ctx) override;
    virtual void exitCatchBlock(TryCatchGrammarParser::CatchBlockContext *ctx) override;

    virtual void enterBlock(TryCatchGrammarParser::BlockContext *ctx) override;
    virtual void exitBlock(TryCatchGrammarParser::BlockContext *ctx) override;

    virtual void enterStatement(TryCatchGrammarParser::StatementContext *ctx) override;
    virtual void exitStatement(TryCatchGrammarParser::StatementContext *ctx) override;

    virtual void enterTryCatchBlockStatement(TryCatchGrammarParser::TryCatchBlockStatementContext *ctx) override;
    virtual void exitTryCatchBlockStatement(TryCatchGrammarParser::TryCatchBlockStatementContext *ctx) override;

    virtual void enterThrowStatement(TryCatchGrammarParser::ThrowStatementContext *ctx) override;
    virtual void exitThrowStatement(TryCatchGrammarParser::ThrowStatementContext *ctx) override;

    virtual void enterException_(TryCatchGrammarParser::Exception_Context *ctx) override;
    virtual void exitException_(TryCatchGrammarParser::Exception_Context *ctx) override;

    virtual void enterPrintStatement(TryCatchGrammarParser::PrintStatementContext *ctx) override;
    virtual void exitPrintStatement(TryCatchGrammarParser::PrintStatementContext *ctx) override;

    virtual void enterExpression(TryCatchGrammarParser::ExpressionContext *ctx) override;
    virtual void exitExpression(TryCatchGrammarParser::ExpressionContext *ctx) override;
};


#endif // LISTENER_H
/*

ТОКЕНЫ:

Строки (StringLiteral)
"..."

Целые числа (IntLiteral)
1234
-23
-0  (=0)

ID'шники (ID)
Терминалы, состоящие из букв английского алфавита Aa-Zz и (опционально) цифр 0-9,
такие что в начале терминала должна стоять буква
(Проще говоря, как название любой функции или переменной в С)

*/

<TryCatchBlock> ::= <TryBlock><CatchBlock> | <TryCatchBlock><CatchBlock>

<TryBlock> ::= try <Block>
<CatchBlock> ::= catch (ID ID) <Block>

<Block> ::= {<StatementList>}

<StatementList> ::= ^ | <NonEmptyStatementList>

<NonEmptyStatementList> ::= <Statement> | <NonEmptyStatementList><Statement>

<Statement> ::= <TryCatchBlockStatement> | <ThrowStatement> | <PrintStatement>

<TryCatchBlockStatement> ::= <TryCatchBlock>;

<ThrowStatement> ::= throw <Exception>;
<Exception> ::= new ID(<Expression>) | ID

<PrintStatement> ::= print(<Expression>);

<Expression> ::= StringLiteral | IntLiteral

/* 
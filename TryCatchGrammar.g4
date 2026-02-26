grammar TryCatchGrammar;

// Точка входа - программа состоит из одного или нескольких блоков try-catch
prog: tryCatchBlock EOF;

// Правила для try-catch блоков
tryCatchBlock: tryBlock catchBlock+;

tryBlock: TRY block;

catchBlock: CATCH '(' ID ID ')' block;

// Блок кода
block: '{' (statement)* '}';

statement: tryCatchBlockStatement
         | throwStatement
         | printStatement
         ;

tryCatchBlockStatement: tryCatchBlock ';';

throwStatement: THROW exception_ ';';

exception_: NEW ID '(' expression ')'   
         | ID                           
         ;

printStatement: PRINT '(' expression ')' ';';


expression: STRING_LITERAL
          | INT_LITERAL
          ;

// Ключевые слова
TRY: 'try';
CATCH: 'catch';
THROW: 'throw';
NEW: 'new';
PRINT: 'print';

// Терминалы
ID: [a-zA-Z_][a-zA-Z0-9_]*;

STRING_LITERAL: '"' (~["\r\n])* '"';

INT_LITERAL: [0-9]+;

// Пропускаем пробельные символы
WS: [ \t\r\n]+ -> skip;

// Комментарии (опционально)
LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
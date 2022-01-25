%{
#include "Grammar.yy.hpp"
#include <iostream>

%}

%option nounput
%option noinput

%%

optimize        { return T_OPTIMIZE; }
[_a-zA-Z]+      { yylval.word = strdup(yytext); return T_WORD; }
":"             { return T_COLON; }
";"             { return T_SEMICOLON; }
"("             { return T_OPEN_BRACKET; }
")"             { return T_CLOSE_BRACKET; }
[0-9]+          {
                    double number = std::stod(yytext);
                    yylval.number = number;
                    return T_NUMBER;
                }

[\t\v\r\f ]+    { ; }
#[^\n]+[\n]     { return T_SEPARATOR; }
[\n]            { return T_SEPARATOR; }
#               { return T_SEPARATOR; }
.               { throw std::runtime_error("LEX EXCEPTION: lexeme \"" + std::string(yytext) + "\" doesn't correct"); }

%%

int yywrap (void) {
    return 1;
}
%{
#include "Grammar.yy.hpp"
#include <iostream>

%}

%option nounput
%option noinput

%%

optimize        { std::cout << "OPT: " << yytext << std::endl; return T_OPTIMIZE; }
[_a-zA-Z]+      { std::cout << "WORD" << std::endl; yylval.word = strdup(yytext); return T_WORD; }
":"             { return T_COLON; }
";"             { std::cout << "SEMIC" << std::endl; return T_SEMICOLON; }
"("             { return T_OPEN_BRACKET; }
")"             { return T_CLOSE_BRACKET; }
[0-9]+          {
                    long number = std::stol(yytext);
                    if (number < 0) {
                       throw std::runtime_error("LEX EXCEPTION: negative number \"" + std::string(yytext) + "\"");
                    }
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
%{
#include <iostream>
#include "Grammar.yy.hpp"

extern int yychar;
extern int yylex();

void yyerror(Graph* graph, const char *msg) {
    (void)graph;
    throw std::runtime_error("YACC EXCEPTION: " + std::string(msg) + ", lookahead token number " + std::to_string(yychar));
}

%}

%union              {
                    char* word;
                    size_t number;
                    }
                    
%parse-param        {Graph* graph}

%token              T_SEPARATOR
%token              T_COMMENT
%token              T_OPEN_BRACKET
%token              T_CLOSE_BRACKET
%token              T_COLON
%token              T_SEMICOLON
%token              T_OPTIMIZE
%token<number>      T_NUMBER
%token<word>        T_WORD


%left               T_SEPARATOR
%left               T_COLON

%%

LINES:
                    LINE
                    | LINE SEPARATORS LINES

LINE:
                    | RESOURCE
                    | PROCESS
                    | OPTIMIZE

SEPARATORS:
                    T_SEPARATOR
                    | T_SEPARATOR SEPARATORS

RESOURCE:
                    T_WORD T_COLON T_NUMBER {
                        if (graph->GetResourceByName($1) != nullptr) {
                            throw std::runtime_error("Multiple initializations of the same resource");
                        }
                        graph->AddResource(Resource($1, $3));
                    }

PROCESS:
                    T_WORD T_COLON PROCESS_REQUIRED T_COLON PROCESS_PRODUCED T_COLON T_NUMBER {
                        std::cout << "process \"" << $1 << "\"" << std::endl;
                    }

PROCESS_REQUIRED:
                    T_OPEN_BRACKET REQUIRED_RESOURCES T_CLOSE_BRACKET {
                        std::cout << "PROCESS_REQUIRED" << std::endl;
                    }

REQUIRED_RESOURCES:
                    REQUIRED_RESOURCE
                    | T_SEMICOLON REQUIRED_RESOURCES {
                        std::cout << "REQUIRED_RESOURCES" << std::endl;
                    }

REQUIRED_RESOURCE:
                    T_WORD T_COLON T_NUMBER {
                        std::cout << "REQUIRED_RESOURCE: " << $1 << " " << $3 << std::endl;
                    }

PROCESS_PRODUCED:
                    T_OPEN_BRACKET PRODUCED_RESOURCES T_CLOSE_BRACKET {
                        std::cout << "PROCESS_PRODUCED" << std::endl;
                    }

PRODUCED_RESOURCES:
                    PRODUCED_RESOURCE
                    | T_SEMICOLON PRODUCED_RESOURCES {
                        std::cout << "PRODUCED_RESOURCES" << std::endl;
                    }

PRODUCED_RESOURCE:
                    T_WORD T_COLON T_NUMBER {
                        std::cout << "PRODUCED_RESOURCE: " << $1 << " " << $3 << std::endl;
                    }

OPTIMIZE:
                    T_OPTIMIZE T_COLON T_OPEN_BRACKET OPTIMIZE_RESOURCES T_CLOSE_BRACKET {
                        std::cout << "AA OPTIMIZE" << std::endl;
                    }

OPTIMIZE_RESOURCES:
                    OPTIMIZE_RESOURCE T_SEMICOLON OPTIMIZE_RESOURCES
                    | OPTIMIZE_RESOURCE {
                        std::cout << "AAA" << std::endl;
                    }

OPTIMIZE_RESOURCE:
                    T_WORD {
                        std::cout << $1 << std::endl;
                    }

%%

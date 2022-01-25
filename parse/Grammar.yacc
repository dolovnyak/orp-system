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
                    double number;
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
                            throw std::runtime_error("Multiple initializations of the same resource \"" + std::string($1) + "\"");
                        }
                        graph->AddResource(Resource($1, $3));
                    }

PROCESS:
                    T_WORD T_COLON PROCESS_REQUIRED T_COLON PROCESS_PRODUCED T_COLON T_NUMBER {
                        if (graph->GetProcessByName($1) != nullptr) {
                            throw std::runtime_error("Multiple initializations of the same process \"" + std::string($1) + "\"");
                        }
                        Process process($1, $7,
                                        std::move(ParseProcess::GetRequiredResources()),
                                        std::move(ParseProcess::GetProducedResources()));
                        graph->AddProcess(process);
                        ParseProcess::CleanUp();
                    }

PROCESS_REQUIRED:
                    T_OPEN_BRACKET REQUIRED_RESOURCES T_CLOSE_BRACKET

REQUIRED_RESOURCES:
                    REQUIRED_RESOURCE T_SEMICOLON REQUIRED_RESOURCES
                    | REQUIRED_RESOURCE

REQUIRED_RESOURCE:
                    T_WORD T_COLON T_NUMBER {
                        ParseProcess::AddRequiredResource($1, $3, graph);
                    }

PROCESS_PRODUCED:
                    T_OPEN_BRACKET PRODUCED_RESOURCES T_CLOSE_BRACKET

PRODUCED_RESOURCES:
                    PRODUCED_RESOURCE T_SEMICOLON PRODUCED_RESOURCES
                    | PRODUCED_RESOURCE

PRODUCED_RESOURCE:
                    T_WORD T_COLON T_NUMBER {
                        ParseProcess::AddProducedResource($1, $3, graph);
                    }

OPTIMIZE:
                    T_OPTIMIZE T_COLON T_OPEN_BRACKET OPTIMIZE_RESOURCES T_CLOSE_BRACKET

OPTIMIZE_RESOURCES:
                    OPTIMIZE_RESOURCE T_SEMICOLON OPTIMIZE_RESOURCES
                    | OPTIMIZE_RESOURCE

OPTIMIZE_RESOURCE:
                    T_WORD {
                        if (strcmp($1, "time") == 0) {
                            graph->AddOptimizeByTime();
                        }
                        else {
                            Resource* resource = graph->GetResourceByName($1);
                             if (resource == nullptr) {
                                throw std::runtime_error("Try optimize not existed resource");
                            }
                            graph->AddResourceToOptimize(resource);
                        }
                   }

%%

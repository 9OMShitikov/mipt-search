%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include "ast.h"

    using namespace sql;

    class Scanner;
    class Driver;
}

// %param { std::shared_ptr<Ast>& result }

%define parse.trace
%define parse.error verbose

%code {
    #include "location.hh"
    #include "driver.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0       "end of file"

    // help
    LPAREN      "("
    RPAREN      ")"
    ENDLINE     ";"
    COMMA       ","
    STAR        "*"
    SELECT      "select"
    FROM        "from"
    MATCH       "match"
    WHERE       "where"
    LIMIT       "limit"
;

%token <int> NUMBER "number"
%token <std::string> NAME
%token <std::string> QUOTED

// Uncomment this after complete
// %nterm <std::shared_ptr<Ast>> query
// %nterm <std::shared_ptr<Ast>> select_query
// %nterm <std::shared_ptr<Ast>> insert_query
// %nterm <std::shared_ptr<Ast>> index_name
// %nterm <std::shared_ptr<Where>> where_clause
// %nterm <std::optional<std::string>> match_expr
// %nterm <std::shared_ptr<List>> namelist
// %nterm <int> limit

// %printer { yyo << $$; } <*>;

// HINT: Use $$->SetLocation(@$);

%%
%start query;

// query:
//    select_query { driver.parsed = $1; }
//    | insert_query { driver.parsed = $1; }
// ;

// Your code goes here...
// Write rules for queries

%left "+" "-";
%left "*" "/" "%";

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

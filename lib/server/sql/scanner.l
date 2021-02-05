%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "parser.hh"
    #include "driver.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );

  yy::parser::symbol_type make_QUOTED(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

// Your code goes here...
// Add utf-8 support

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]
quoted_string \"{uname}*\"

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"("        return yy::parser::make_LPAREN   (loc);
")"        return yy::parser::make_RPAREN   (loc);
";"        return yy::parser::make_ENDLINE  (loc);
","        return yy::parser::make_COMMA    (loc);
"*"        return yy::parser::make_STAR     (loc);

// Your code goes here...

{id}       return yy::parser::make_NAME     (yytext, loc);
{quoted_string} return make_QUOTED (yytext, loc);

{int}      return make_NUMBER (yytext, loc);

.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  // Your code goes here...
  return yy::parser::make_NUMBER((int) 0, loc);
}

yy::parser::symbol_type make_QUOTED(
const std::string &s,
const yy::parser::location_type& loc
) {
    return yy::parser::make_QUOTED(s.substr(1, s.length() - 2).c_str(), loc);
}

%{
  #include "y.tab.h"
%}

%%

[ \t]+
[a-zA-Z]                                { yylval.id = yytext[0]; return ID; }
"||"                                    { return OR; }
"&&"                                    { return AND; }
">="|">"|"<="|"<"|"=="                  { strcpy(yylval.str,yytext); return RELOP; }
\n                                      { return '\n'; }
.                                       { return yytext[0]; }

%%

int yywrap(){
  return 1;
}
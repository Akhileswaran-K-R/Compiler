%{
  #include "y.tab.h"
%}

DIGIT                     [0-9]
FLOAT                     {DIGIT}+("."{DIGIT}+)?

%%

[\t ]+
\n                        { return '\n'; }
{FLOAT}                   { yylval.id = atof(yytext); return NUM; }
[-+*/]                    { return yytext[0]; }
.                         { return yytext[0]; }

%%

int yywrap(){
  return 1;
}
%{
#include "y.tab.h"
%}

%%

[0-9]+     { yylval = atoi(yytext); return NUM; }
[ \t]+ 
\n         return 0;
[-+*/()]   return yytext[0];
.          return yytext[0];

%%

int yywrap(){
  return 1;
}
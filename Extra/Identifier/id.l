%{
  #include "y.tab.h"
%}

%%

[A-Za-z_]               { return LETTER; }
[0-9]                   { return DIGIT; }
\n                      { return '\n'; }
.                       { return yytext[0]; }

%%

int yywrap(){
  return 1;
}
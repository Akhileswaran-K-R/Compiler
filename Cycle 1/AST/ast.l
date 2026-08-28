%{
  #include "ast.h"
  #include "y.tab.h"
%}

%%

[a-zA-Z]      { yylval.id = yytext[0]; return ID; }
[ \t]+        
\n            return '\n';
[-+*/()]      return yytext[0];
.             return yytext[0];

%%

int yywrap()
{
    return 1;
}
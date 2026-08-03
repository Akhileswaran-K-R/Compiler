%{
#include<stdio.h>
#include<stdlib.h>

void yyerror(char *s){
  printf("Invalid arithmetic expression\n");
}

int yylex(void);
%}

%token NUM

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

S : E '\n'                { printf("Result: %d\n",$1); return 0; }

E : E '+' E               { $$ = $1 + $3; }
  | E '-' E               { $$ = $1 - $3; }
  | E '*' E               { $$ = $1 * $3; }
  | E '/' E               { $$ = $1 / $3; }
  | '(' E ')'             { $$ = $2; }
  | '-' E %prec UMINUS    { $$ = -$2; }
  | NUM                   { $$ = $1; }

%%

void main(){
  printf("Enter an arithmetic expression:\n");
  yyparse();
}
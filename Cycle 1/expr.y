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

S : 
  | S E '\n'                 { printf("Valid arithmetic expression\n"); }
  | S error '\n'             { yyerrok; }

E : E '+' E 
  | E '-' E 
  | E '*' E 
  | E '/' E 
  | '(' E ')' 
  | '-' E %prec UMINUS 
  | NUM

%%

void main(){
  printf("Enter an arithmetic expression:\n");
  yyparse();
}
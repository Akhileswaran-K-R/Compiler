%{
  #include<stdio.h>
  #include<string.h>

  void yyerror(char *s){
    printf("Inavlid string\n");
  }

  int yylex(void);
%}

%union{
  float id;
}

%token <id> NUM
%type <id> E

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

S : 
  | S E '\n'                      { printf("Result: %.2f\n",$2); }
  | S error '\n'                  { yyerrok; }

E : E '+' E                       { $$ = $1 + $3; }
  | E '-' E                       { $$ = $1 - $3; }
  | E '*' E                       { $$ = $1 * $3; }
  | E '/' E                       { $$ = $1 / $3; } 
  | '(' E ')'                     { $$ = $2; }
  | '-' E %prec UMINUS            { $$ = -$2; }
  | NUM                           { $$ = $1; }

%%

void main(){
  printf("Enter an expression\n\n");
  yyparse();
}
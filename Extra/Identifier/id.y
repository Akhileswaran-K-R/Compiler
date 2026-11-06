%{
  #include<stdio.h>

  void yyerror(char *s){
    printf("Invalid identifier\n");
    return;
  }

  int yylex(void);
%}

%token LETTER DIGIT

%%

S : 
  | S LETTER A '\n'         { printf("Valid identifier\n"); }
  | S error '\n'            { yyerrok; }

A : 
  | LETTER A
  | DIGIT A

%%

void main(){
  printf("Enter an identifier\n");
  yyparse();
}
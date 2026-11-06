%{
  #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>

  void yyerror(char *s){
    printf("Invalid expression\n\n");
  }

  int yylex(void);

  void display(char res[],char arg1[],char op[],char arg2[]){
    printf("\n%s = %s %s %s",res,arg1,op,arg2);
  }

  int temp = 0;
%}

%union{
  char str[20];
  char id;
}

%token OR AND
%token <id> ID 
%token <str> RELOP
%type <str> E

%left OR
%left AND
%left RELOP

%%

S :
  | S E '\n'              { printf("\nResult: %s\n\n",$2); temp = 0; }
  | S error '\n'          { yyerrok; }

E : E OR E                { sprintf($$,"t%d",temp++); display($$,$1,"||",$3); }
  | E AND E               { sprintf($$,"t%d",temp++); display($$,$1,"&&",$3); }
  | E RELOP E             { sprintf($$,"t%d",temp++); display($$,$1,$2,$3); }
  | '(' E ')'             { strcpy($$,$2); }
  | ID                    { sprintf($$, "%c", $1); }

%%

void main(){
  printf("Enter an expression\n\n");
  yyparse();
}
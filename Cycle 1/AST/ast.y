%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"

  Node *newNode(char data, Node *left, Node *right){
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = left;
    newNode->right = right;

    return newNode;
  }

  void preorder(Node *root){
    if(root != NULL){
      printf("%c ", root->data);
      preorder(root->left);
      preorder(root->right);
    }
  }

  void yyerror(char *s){
    printf("Invalid arithmetic expression\n\n");
  }

  int yylex(void);
%}

%union{
  Node *ptr;
  char id;
}

%token <id> ID
%type <ptr> E

%left '+' '-'
%left '*' '/'

%%

S : 
  | S E '\n'      {
                    printf("Preorder Traversal of AST: ");
                    preorder($2);
                    printf("\n\n");
                  }
  | S error '\n'  { yyerrok; }

E : E '+' E       { $$ = newNode('+',$1,$3); }
  | E '-' E       { $$ = newNode('-',$1,$3); }
  | E '*' E       { $$ = newNode('*',$1,$3); }
  | E '/' E       { $$ = newNode('/',$1,$3); }
  | '(' E ')'     { $$ = $2; }
  | ID            { $$ = newNode($1,NULL,NULL); }

%%

void main(){
  printf("Enter Expression:\n\n");
  yyparse();
}
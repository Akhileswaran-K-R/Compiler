%{
  #include <stdio.h>
  #include <stdlib.h>

  typedef struct Node{
    char data;
    struct Node *left;
    struct Node *right;
  }Node;

  Node *createNode(char data, Node *left, Node *right){
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = left;
    newNode->right = right;

    return newNode;
  }

  void levelOrder(Node *root){
    Node *queue[100];
    int front = 0,rear = 0;
    queue[rear++] = root;

    while(front < rear){
      int nodesInLevel = rear - front;

      while(nodesInLevel > 0){
        Node *current = queue[front++];
        printf("%c ",current->data);

        if(current->left != NULL){
          queue[rear++] = current->left;
        }

        if(current->right != NULL){
          queue[rear++] = current->right;
        }
        nodesInLevel--; 
      }
      printf("\n");
    }
  }

  void yyerror(char *s){
    printf("Invalid arithmetic expression\n\n");
  }

  int yylex(void);
%}

%union{
  struct Node *ptr;
  char id;
}

%token <id> ID
%type <ptr> E

%left '+' '-'
%left '*' '/'

%%

S : 
  | S E '\n'      {
                    printf("\n");
                    levelOrder($2);
                    printf("\n\n");
                  }
  | S error '\n'  { yyerrok; }

E : E '+' E       { $$ = createNode('+',$1,$3); }
  | E '-' E       { $$ = createNode('-',$1,$3); }
  | E '*' E       { $$ = createNode('*',$1,$3); }
  | E '/' E       { $$ = createNode('/',$1,$3); }
  | '(' E ')'     { $$ = $2; }
  | ID            { $$ = createNode($1,NULL,NULL); }

%%

void main(){
  printf("Enter Expression:\n\n");
  yyparse();
}
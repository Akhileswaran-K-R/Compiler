#ifndef AST_H
#define AST_H

typedef struct Node{
  char data;
  struct Node *left;
  struct Node *right;
}Node;

#endif
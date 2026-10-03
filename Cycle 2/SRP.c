#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXPROD 20
#define MAXSIZE 100

typedef struct{
  char st[MAXSIZE];
  int top;
}stack;

typedef struct{
  char stack[MAXSIZE][MAXSIZE];
  int pos[MAXSIZE];
  char action[MAXSIZE][40];
  int steps;
}table;

int accept(int m,char prods[][MAXSIZE]){
  char temp[MAXSIZE];
  int n=0;
  for(int i=0;i<m;i++){
    scanf(" %[^\n]",temp);
    char lhs = temp[0];

    int j;
    for(j=1;j<strlen(temp);j++){
      if(strchr(" ->=",temp[j]) == NULL){
        break;
      }
    }

    char *str = strtok(temp+j,"| ");
    while(str != NULL){
      prods[n][0] = lhs;
      prods[n][1] = '=';
      strcpy(prods[n] + 2,str);
      n++;
      str = strtok(NULL,"| ");
    }
  }
  return n;
}

void record(int pos,char action[],stack *s, table *t){
  int len = s->top + 1;
  strncpy(t->stack[t->steps],s->st,len);
  t->stack[t->steps][len] = '\0';
  t->pos[t->steps] = pos;
  strcpy(t->action[t->steps],action);
  t->steps++;
}

void display(char input[],table *t){
  strcat(input,"$");
  printf("\n%-20s%-20s%-20s\n","STACK","INPUT","ACTION");
  printf("%-20s%-20s%-20s\n","$",input,"START");

  for(int i=0;i<t->steps;i++){
    printf("$%-19s%-20s%-20s\n",t->stack[i],input + t->pos[i],t->action[i]);
  }
}

int srp(int n,char prods[][MAXSIZE],char input[],int pos,stack *s,table *t){
  if(input[pos] == '\0' && s->top == 0 && s->st[0] == prods[0][0]){
    display(input,t);
    return 1;
  }

  for(int i=0;i<n;i++){
    int rhsLen = strlen(prods[i]) - 2;
    int stackLen = s->top + 1;

    if(stackLen >= rhsLen && strncmp(s->st + stackLen - rhsLen,prods[i] + 2,rhsLen) == 0){
      s->top -= rhsLen;
      s->st[++s->top] = prods[i][0];

      char action[40];
      snprintf(action,sizeof(action),"REDUCE %c -> %s",prods[i][0],prods[i] + 2);
      record(pos,action,s,t);

      if(srp(n,prods,input,pos,s,t)){
        return 1;
      }

      strncpy(s->st + s->top,prods[i] + 2,rhsLen);
      s->top += rhsLen - 1;
      t->steps--;
    }
  }

  if(input[pos] != '\0'){
    s->st[++s->top] = input[pos];
    record(pos+1,"SHIFT",s,t);

    if(srp(n,prods,input,pos + 1,s,t)){
      return 1;
    }

    s->top--;
    t->steps--;
  }
  return 0;
}

void main(){
  int m;
  printf("Enter the no: of production statements\n");
  scanf("%d",&m);

  char prods[MAXPROD][MAXSIZE],input[MAXSIZE];
  printf("\nEnter the productions\n");
  int n = accept(m,prods);

  printf("\nEnter the input string: ");
  scanf("%s",input);

  stack s;
  table t;
  s.top = -1;
  t.steps = 0;
  
  if(srp(n,prods,input,0,&s,&t)){
    printf("\nString accepted\n");
  }else{
    printf("\nString rejected\n");
  }
}
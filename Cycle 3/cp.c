#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 100
#define MIN 20

typedef struct{
  char lhs[MIN];
  char id1[MIN];
  char op;
  char id2[MIN];
}TAC;

typedef struct{
  char var[MIN];
  int val;
  int isConst;
}Symbol;

void trim(char str[]){
  int i = 0,j = 0;
  while(str[i] != '\0'){
    if(str[i] != ' '){
      str[j++] = str[i];
    }
    i++;
  }
  str[j] = '\0';
}

int compute(int v1,char op,int v2){
  switch(op){
    case '+': return v1 + v2;
    case '-': return v1 - v2;
    case '*': return v1 * v2;
    case '/': return v1 / v2;
  }
}

int isNumber(char str[]){
  int start = 0;
  if(str[0] == '-' || str[0] == '+'){
    start = 1;
  }

  for(int i=start;str[i]!='\0';i++){
    if(!isdigit(str[i])){
      return 0;
    }
  }
  return 1;
}

int getConstVal(Symbol table[],int n,char var[],int *val){
  for(int i=0;i<n;i++){
    if(strcmp(table[i].var,var) == 0 && table[i].isConst){
      *val = table[i].val;
      return 1;
    }
  }
  return 0;
}

int setVarConst(Symbol table[],int n,char var[],int val,int isConst){
  for(int i=0;i<n;i++){
    if(strcmp(table[i].var,var) == 0){
      table[i].val = val;
      table[i].isConst = isConst;
      return n;
    }
  }

  strcpy(table[n].var,var);
  table[n].val = val;
  table[n].isConst = isConst;
  return ++n;
}

void cp(TAC code[],int n1,Symbol table[],int n2){
  for(int i=0;i<n1;i++){
    int v1,v2;

    if(!isNumber(code[i].id1) && getConstVal(table,n2,code[i].id1,&v1)){
      sprintf(code[i].id1,"%d",v1);
    }

    if(code[i].op != '\0' && !isNumber(code[i].id2) && getConstVal(table,n2,code[i].id2,&v2)){
      sprintf(code[i].id2,"%d",v2);
    }

    if(code[i].op != '\0'){
      if(isNumber(code[i].id1) && isNumber(code[i].id2)){
        int res = compute(atoi(code[i].id1),code[i].op,atoi(code[i].id2));
        sprintf(code[i].id1,"%d",res);
        code[i].op = '\0';
        code[i].id2[0] = '\0';
        n2 = setVarConst(table,n2,code[i].lhs,res,1);
      }else{
        n2 = setVarConst(table,n2,code[i].lhs,0,0);
      }
    }else{
      if(isNumber(code[i].id1)){
        n2 = setVarConst(table,n2,code[i].lhs,atoi(code[i].id1),1);
      }else{
        n2 = setVarConst(table,n2,code[i].lhs,0,0);
      }
    }
  }
}

int parse(char line[],int n,TAC code[]){
  char lhs[MIN],id1[MIN],op,id2[MIN];

  if(sscanf(line,"%[^=]=%[^+-*/]%c%s",lhs,id1,&op,id2) == 4){
    strcpy(code[n].lhs,lhs);
    strcpy(code[n].id1,id1);
    code[n].op = op;
    strcpy(code[n].id2,id2);
  }else if(sscanf(line,"%[^=]=%s",lhs,id1) == 2){
    strcpy(code[n].lhs,lhs);
    strcpy(code[n].id1,id1);
    code[n].op = '\0';
    code[n].id2[0] = '\0';
  }
  return ++n;
}

void main(){
  int n,n1 = 0,n2 = 0;
  char line[MAX];
  TAC code[MAX];
  Symbol table[MAX];

  printf("Enter the no: of statements\n");
  scanf("%d",&n);
  getchar();

  printf("\nEnter the TAC statements\n");
  for(int i=0;i<n;i++){
    fgets(line,sizeof(line),stdin);
    line[strcspn(line,"\n")] = '\0';
    trim(line);
    n1 = parse(line,n1,code);
  }

  cp(code,n1,table,n2);
  printf("\nOptimized code after Constant Propogation\n\n");
  for(int i=0;i<n1;i++){
    if(code[i].op != '\0'){
      printf("%s = %s %c %s\n",code[i].lhs,code[i].id1,code[i].op,code[i].id2);
    }else{
      printf("%s = %s\n", code[i].lhs, code[i].id1);
    }
  }
}
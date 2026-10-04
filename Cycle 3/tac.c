#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 100 
#define MIN 20

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

void E(char input[],int *pos,int *t,char res[]);

void F(char input[],int *pos,int *t,char res[]){
  if(input[*pos] == '-'){
    (*pos)++;
    char val[MIN],temp[MIN];
    F(input,pos,t,val);

    sprintf(temp,"t%d",(*t)++);
    printf("%s = minus %s\n",temp,val);
    strcpy(res,temp);
    return;
  }

  if(input[*pos] == '('){
    (*pos)++;
    E(input,pos,t,res);
    if(input[*pos] == ')'){
      (*pos)++;
    }
    return;
  }

  int i = 0;
  while(isalnum(input[*pos]) || input[*pos] == '_'){
    res[i++] = input[(*pos)++];
  }
  res[i] = '\0';
}

void Tprime(char input[],int *pos,int *t,char left[],char res[]){
  if(input[*pos] == '*' || input[*pos] == '/'){
    char op = input[(*pos)++];
    char right[MIN],temp[MIN];

    F(input,pos,t,right);
    sprintf(temp,"t%d",(*t)++);
    printf("%s = %s %c %s\n",temp,left,op,right);
    Tprime(input,pos,t,temp,res);
  }else{
    strcpy(res,left);
  }
}

void T(char input[],int *pos,int *t,char res[]){
  char val[MIN];
  F(input,pos,t,val);
  Tprime(input,pos,t,val,res);
}

void Eprime(char input[],int *pos,int *t,char left[],char res[]){
  if(input[*pos] == '+' || input[*pos] == '-'){
    char op = input[(*pos)++];
    char right[MIN],temp[MIN];

    T(input,pos,t,right);
    sprintf(temp,"t%d",(*t)++);
    printf("%s = %s %c %s\n",temp,left,op,right);
    Eprime(input,pos,t,temp,res);
  }else{
    strcpy(res,left);
  }
}

void E(char input[],int *pos,int *t,char res[]){
  char val[MIN];
  T(input,pos,t,val);
  Eprime(input,pos,t,val,res);
}

void main(){
  char lhs[MIN] = "",res[MIN],input[MAX],*p;
  int t = 1,pos = 0;

  printf("Enter an expression\n");
  fgets(input,sizeof(input),stdin);
  input[strcspn(input,"\n")] = '\0';
  trim(input);

  if((p = strchr(input,'='))){
    *p = '\0';
    strcpy(lhs,input);
    strcpy(input,p + 1);
  }

  printf("\nGenerated TAC\n\n");
  E(input,&pos,&t,res);

  if(strlen(lhs) > 0){
    printf("%s = %s\n",lhs,res);
  }
}
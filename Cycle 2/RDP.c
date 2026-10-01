#include<stdio.h>
#include<string.h>
#include<ctype.h>

int E(char input[],int pos);

int F(char input[],int pos){
  if(input[pos] == '('){
    pos++;
    pos = E(input,pos);
    
    if(input[pos] == ')'){
      pos++;
    }else{
      return -1;
    }
  }else if(isalpha(input[pos])){
    pos++;
  }else{
    return -1;
  }
  return pos;
}

int Tprime(char input[],int pos){
  if(pos == -1){
    return pos;
  }

  if(input[pos] == '&'){
    pos++;
    pos = F(input,pos);
    pos = Tprime(input,pos);
  }
  return pos;
}

int T(char input[],int pos){
  pos = F(input,pos);
  pos = Tprime(input,pos);
  return pos;
}

int Eprime(char input[],int pos){
  if(pos == -1){
    return pos;
  }

  if(input[pos] == '|'){
    pos++;
    pos = T(input,pos);
    pos = Eprime(input,pos);
  }
  return pos;
}

int E(char input[],int pos){
  pos = T(input,pos);
  pos = Eprime(input,pos);
  return pos;
}

void main(){
  char input[100];

  printf("Type exit to stop\n");
  while(1){
    printf("\nEnter a string: ");
    scanf("%s",input);

    if(strcmp(input,"exit") == 0){
      break;
    }

    int pos = 0;
    pos = E(input,pos);
    if(pos != -1 && input[pos] == '\0'){
      printf("String is accepted\n");
    }else{
      printf("String is not accepted\n");
    }
  }
}
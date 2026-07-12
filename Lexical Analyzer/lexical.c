#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isKeyword(char token[]){
  char *keywords[] = {
    "int","float","double","char",
    "printf","scanf",
    "if","else",
    "for","while","do",
    "switch","case","break","default",
    "continue","return"
  };

  int n = sizeof(keywords) / sizeof(keywords[0]);
  for(int i=0;i<n;i++){
    if(strcmp(keywords[i],token) == 0){
      return 1;
    }
  }

  return 0;
}

int isInteger(char token[]){
  if(token[0] == '\0'){
    return 0;
  }

  for(int i=0;i<strlen(token);i++){
    if(token[i] < 48 || token[i] > 57){
      return 0;
    }
  }

  return 1;
}

int isFloat(char token[]){
  int dotCount = 0;
  int digitCount = 0;

  if(token[0] == '\0'){
    return 0;
  }

  for(int i=0;i<strlen(token);i++){
    if(token[i] == '.'){
      dotCount++;
    }else if(token[i] >= '0' && token[i] <= '9'){
      digitCount++;
    }else{
      return 0;
    }
  }

  if(dotCount == 1 && digitCount > 0){
    return 1;
  }

  return 0;
}

int isOperator(char ch, char type[]){
  if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'){
    strcpy(type,"Arithmetic");
    return 1;
  }if(ch == '='){
    strcpy(type,"Assignment");
    return 1;
  }if(ch == '>' || ch == '<'){
    strcpy(type,"Relational");
    return 1;
  }

  return 0;
}

int isParenthesis(char ch){
  if(ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')'){
    return 1;
  }

  return 0;
}

int isDelimiter(char ch){
  char type[20];
  if(ch == ' ' || ch == ';' || isOperator(ch,type) || isParenthesis(ch)){
    return 1;
  }

  return 0;
}

void printToken(char str[],int fp,int bp){
  char token[50];
  strncpy(token, str + bp, fp - bp);
  token[fp - bp] = '\0';

  if(isKeyword(token)){
    printf("%s\tKeyword\n",token);
  }else if(isInteger(token)){
    printf("%s\tInteger\n",token);
  }else if(isFloat(token)){
    printf("%s\tFloat\n",token);
  }else{
    printf("%s\tIdentifier\n",token);
  }
}

void lexicalAnalyzer(char str[]){
  int fp = 0,bp = 0;
  int n = strlen(str);
  char type[20];

  while(fp < n && bp < n){
    char ch = str[fp];

    if(isDelimiter(ch)){
      if(bp != fp){
        printToken(str,fp,bp);
      }

      bp = fp + 1;
      if(ch == ' '){
        fp++; 
        continue;
      }else if((ch == '>' || ch == '<' || ch == '=' || ch == '!') && str[bp] == '='){
        printf("%c=\tRelational Operator\n",ch);
        bp++;
        fp = bp;
      }else if(isOperator(ch,type)){
        printf("%c\t%s Operator\n",ch,type);
      }else if(isParenthesis(ch)){
        printf("%c\tParenthesis\n",ch);
      }else{
        printf("%c\tPunctuator\n",ch);
      }
    }

    fp++;
  }

  if(bp < n){
    printToken(str,fp,bp);
  }
}

void main(){
  FILE *fp = fopen("input.txt","r");
  char line[100];

  while(fgets(line, sizeof(line), fp)){
    line[strcspn(line, "\n")] = '\0';
    lexicalAnalyzer(line);
  }

  fclose(fp);
}
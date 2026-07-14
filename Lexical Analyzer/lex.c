#include<stdio.h>
#include<string.h>

int isKeyword(char token[]){
  char *keywords[] = {
    "int","float","double","char",
    "printf","scanf","main",
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

  int n = strlen(token);
  for(int i=0;i<n;i++){
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

  int n = strlen(token);
  for(int i=0;i<n;i++){
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
    strcpy(type,"Arithmetic Operator");
    return 1;
  }else if(ch == '='){
    strcpy(type,"Assignment Operator");
    return 1;
  }else if(ch == '>' || ch == '<' || ch == '!'){
    strcpy(type,"Relational Operator");
    return 1;
  }

  return 0;
}

int isParenthesis(char ch, char type[]){
  if(ch == '{' || ch == '}' || ch == '(' || ch == ')'){
    strcpy(type,"Paranthesis");
    return 1;
  }

  return 0;
}

int isPunctuator(char ch,char type[]){
  if(ch == ';' || ch == ',' || ch == ':'){
    strcpy(type,"Punctuator");
    return 1;
  }

  return 0;
}

int isDelimiter(char ch,char type[]){
  if(ch == ' ' || ch == '\'' || ch == '\"' || isOperator(ch,type) || isParenthesis(ch,type) || isPunctuator(ch,type)){
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
  char token[50],type[20];

  while(fp < n && bp < n){
    char ch = str[fp];

    if(isDelimiter(ch,type)){
      if(bp != fp){
        printToken(str,fp,bp);
      }

      bp = fp + 1;
      if(ch == ' '){
        fp++; 
        continue;
      }else if(ch == '/' && (str[bp] == '/' || str[bp] == '*')){
        return;
      }else if(ch == '\''){
        printf("\'%c\'\tCharacter\n",str[bp]);
        bp += 2;
        fp += 2;
      }else if(ch == '\"'){
        while(str[++fp] != '\"');
        strncpy(token, str + bp, fp - bp);
        token[fp - bp] = '\0';
        printf("\"%s\"\tString\n",token);
        bp = fp + 1;
      }else if((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') && str[bp] == '='){
        printf("%c=\tAssignment Operator\n",ch);
        bp++;
        fp = bp - 1;
      }else if((ch == '>' || ch == '<' || ch == '=' || ch == '!') && str[bp] == '='){
        printf("%c=\tRelational Operator\n",ch);
        bp++;
        fp = bp - 1;
      }else{
        printf("%c\t%s\n",ch,type);
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
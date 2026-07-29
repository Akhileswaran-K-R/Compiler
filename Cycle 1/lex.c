#include<stdio.h>
#include<string.h>
#include<ctype.h>

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

int isNumber(char token[],char type[]){
  int dotCount = 0,before = 0,after = 0,Ecount = 0,n = strlen(token);

  for(int i=0;i<n;i++){
    if(token[i] == '.'){
      dotCount++;
      if(dotCount > 1 || Ecount > 1){
        return 0;
      }
    }else if(isdigit(token[i])){
      if(dotCount == 0){
        before++;
      }else{
        after++;
      }
    }else if(token[i] == 'E'){
      Ecount++;
      if(Ecount  > 1){
        return 0;
      }
    }else{
      return 0;
    }
  }

  if(dotCount == 0 && Ecount == 0){
    strcpy(type,"Integer");
    return 1;
  }else if((before > 0 && after > 0) || Ecount == 1){
    strcpy(type,"Float");
    return 1;
  }else{
    return 0;
  }
}

int isIdentifier(char token[]){
  if(!(isalpha(token[0]) || token[0] == '_')){
    return 0;
  }

  int n = strlen(token);
  for(int i=1;i<n;i++){
    if(!(isalnum(token[i]) || token[i] == '_')){
      return 0;
    }
  }

  return 1;
}

int isOperator(char ch, char type[]){
  if(strchr("+-*/%",ch)){
    strcpy(type,"Arithmetic Operator");
    return 1;
  }else if(ch == '='){
    strcpy(type,"Assignment Operator");
    return 1;
  }else if(strchr("><!",ch)){
    strcpy(type,"Relational Operator");
    return 1;
  }

  return 0;
}

int isParenthesis(char ch, char type[]){
  if(strchr("{}()[]",ch)){
    strcpy(type,"Parenthesis");
    return 1;
  }

  return 0;
}

int isPunctuator(char ch,char type[]){
  if(strchr(";,:",ch)){
    strcpy(type,"Punctuator");
    return 1;
  }

  return 0;
}

int isDelimiter(char ch,char type[]){
  if(strchr(" \t'\"",ch) || isOperator(ch,type) || isParenthesis(ch,type) || isPunctuator(ch,type)){
    return 1;
  }

  return 0;
}

void printToken(char str[],int fp,int bp){
  char token[1024],type[20];
  strncpy(token, str + bp, fp - bp);
  token[fp - bp] = '\0';

  if(isKeyword(token)){
    printf("%s\tKeyword\n",token);
  }else if(isNumber(token,type)){
    printf("%s\t%s\n",token,type);
  }else if(isIdentifier(token)){
    printf("%s\tIdentifier\n",token);
  }else{
    printf("%s\tUnknown\n",token);
  }
}

void skipComments(char str[],int *fp,int *bp,int *comment,int n){
  while(*fp < n - 1){
    if(str[*fp] == '*' && str[*fp + 1] == '/'){
      *comment = 0;
      *fp += 2;
      *bp = *fp;
      return;
    }
    (*fp)++;
  }
  *bp = n;
}

void lexicalAnalyzer(char str[],int *comment){
  int fp = 0,bp = 0;
  int n = strlen(str);
  char token[50],type[20];

  if(*comment){
    skipComments(str,&fp,&bp,comment,n);
  }

  while(fp < n && bp < n){
    char ch = str[fp];

    if(isDelimiter(ch,type)){
      if(bp != fp){
        printToken(str,fp,bp); 
      }

      bp = fp + 1;
      if(strchr(" \t",ch)){
        fp++; 
        continue;
      }else if(ch == '/'){
        if(str[bp] == '/'){
          return;
        }else if(str[bp] == '*'){
          *comment = 1;
          skipComments(str,&fp,&bp,comment,n);
          continue;
        }
      }else if(ch == '\'' || ch == '"'){
        fp++;
        while(str[fp] != ch){
          if(str[fp] == '\\'){
            fp += 2;
          }else{
            fp++;
          }
        }
        strncpy(token, str + bp, fp - bp);
        token[fp - bp] = '\0';
        printf("%c%s%c\t%s\n",ch,token,ch,(ch == '\'') ? "Character" : "String");
        bp = fp + 1;
      }else if(strchr("+-*/%",ch) && str[bp] == '='){
        printf("%c=\tAssignment Operator\n",ch);
        bp++;
        fp++;
      }else if(strchr("><=!",ch) && str[bp] == '='){
        printf("%c=\tRelational Operator\n",ch);
        bp++;
        fp++;
      }else if(strchr("+-",ch) && str[bp] == ch){
        printf("%c%c\t%s Operator\n",ch,ch,(ch == '+') ? "Increment" : "Decrement");
        bp++;
        fp++;
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
  char line[1024];
  int comment = 0;

  while(fgets(line, sizeof(line), fp)){
    line[strcspn(line, "\n")] = '\0';
    lexicalAnalyzer(line,&comment);
  }

  fclose(fp);
}
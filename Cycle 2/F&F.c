#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXSIZE 100

void add(char symbol,char result[]){
  if(strchr(result,symbol) == NULL){
    int len = strlen(result);
    result[len] = symbol;
    result[len + 1] = '\0';
  }
}

int findFirst(char symbol,char result[],int n,char prods[][MAXSIZE],int level){
  if(symbol == '#'){
    return 1;
  }

  if(!isupper(symbol)){
    add(symbol,result);
    return 0;
  }

  int allEpsilon = 0;
  for(int i=0;i<n;i++){
    if(prods[i][0] != symbol){
      continue;
    }

    int j = 2,epsilon = 1;
    while(prods[i][j] != '\0' && epsilon != 0){
      char x = prods[i][j];
      epsilon = findFirst(x,result,n,prods,level+1);
      j++;
    }

    if(epsilon == 1){
      allEpsilon = 1;
      if(level == 0){
        add('#',result);
      }
    }
  }
  return allEpsilon;
}

void findFollow(char symbol,char result[],int n,char prods[][MAXSIZE],char first[][MAXSIZE],int visited[]){
  if(visited[symbol - 'A']){
    return;
  }
  visited[symbol - 'A'] = 1;
  
  if(symbol == prods[0][0]){
    add('$',result);
  }

  for(int i=0;i<n;i++){
    int len = strlen(prods[i]);
    for(int j=2;j<len;j++){
      if(prods[i][j] != symbol){
        continue;
      }

      int index = prods[i][j+1] - 'A';
      if(j + 1 == len && prods[i][0] != symbol){
        findFollow(prods[i][0],result,n,prods,first,visited);
      }else if(!isupper(prods[i][j+1])){
        add(prods[i][j+1],result);
      }else if(strchr(first[index],'#')){
        for(int k=0;k<strlen(first[index]);k++){
          if(first[index][k] != '#')
          add(first[index][k],result);
        }

        if(prods[i][0] != symbol){
          findFollow(prods[i][0],result,n,prods,first,visited);
        }
      }else{
        strcat(result,first[index]);
      }
    }
  }
}

void display(int n,char prods[][MAXSIZE],char first[][MAXSIZE],char title[]){
  printf("\n\n%s\n",title);
  for(int i=0;i<n;i++){
    char symbol = prods[i][0];
    int alreadyPrinted = 0;

    for(int j=0;j<i;j++){
      if(prods[j][0] == symbol){
        alreadyPrinted = 1;
        break;
      }
    }

    if(!alreadyPrinted){
      printf("%s(%c) = { ",title,symbol);
      for(int j=0;j<strlen(first[symbol - 'A']);j++){
        printf("%c ",first[symbol - 'A'][j]);
      }
      printf("}\n");
    }
  }
}

void main(){
  int n;
  printf("Enter the no: of productions\n");
  scanf("%d",&n);

  char prods[n][MAXSIZE];
  printf("\nEnter the productions\n");
  for(int i=0;i<n;i++){
    scanf("%s",prods[i]);
  }

  char first[26][MAXSIZE] = {0};
  char follow[26][MAXSIZE] = {0};

  for(int i=0;i<n;i++){
    char symbol = prods[i][0];
    if(first[symbol - 'A'][0] == '\0'){
      findFirst(symbol,first[symbol - 'A'],n,prods,0);
    }
  }

  for(int i=0;i<n;i++){
    char symbol = prods[i][0];
    if(follow[symbol - 'A'][0] == '\0'){
      int visited[26] = {0};
      findFollow(symbol,follow[symbol - 'A'],n,prods,first,visited);
    }
  }

  display(n,prods,first,"FIRST");
  display(n,prods,follow,"FOLLOW");
}
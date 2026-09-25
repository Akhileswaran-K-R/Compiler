#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXPROD 20
#define MAXSIZE 100

int accept(int m,char prods[][MAXSIZE]){
  char temp[MAXSIZE];
  int n=0;
  for(int i=0;i<m;i++){
    fgets(temp, sizeof(temp), stdin); 
    temp[strcspn(temp, "\n")] = '\0';
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
      strcat(prods[n],str);
      n++;
      str = strtok(NULL,"| ");
    }
  }
  return n;
}

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

  int isNullable = 0;
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
      isNullable = 1;
      if(level == 0){
        add('#',result);
      }
    }
  }
  return isNullable;
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

      int isNullable = 1,k;
      for(k=j+1;k<len && isNullable;k++){
        char nxt = prods[i][k];
        if(!isupper(nxt)){
          add(nxt,result);
          isNullable = 0;
        }else{
          isNullable = 0;
          for(int l=0;l<strlen(first[nxt - 'A']);l++){
            if(first[nxt - 'A'][l] == '#'){
              isNullable = 1;
            }else{
              add(first[nxt - 'A'][l],result);
            }
          }
        }
      }

      if(k == len && isNullable && prods[i][0] != symbol){
        findFollow(prods[i][0],result,n,prods,first,visited);
      }
    }
  }
}

void display(int n,char prods[][MAXSIZE],char result[][MAXSIZE],char title[]){
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
      for(int j=0;j<strlen(result[symbol - 'A']);j++){
        printf("%c ",result[symbol - 'A'][j]);
      }
      printf("}\n");
    }
  }
}

void main(){
  int m;
  printf("Enter the no: of production statements\n");
  scanf("%d",&m);
  getchar();

  char prods[MAXPROD][MAXSIZE];
  printf("\nEnter the productions(# for epsilon)\n");
  int n = accept(m,prods);

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
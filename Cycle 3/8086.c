#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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

int conditional(char line[],char result[][MAX],int m){
  char cond[MAX],label[MIN],id1[MIN],id2[MIN],jmp[4];
  char *p,*g;
  int len,i,isFalse = 0;

  if(strncmp(line,"ifFalse",7) == 0){
    p = line + 7;
    isFalse = 1;
  }else if(strncmp(line,"if",2) == 0){
    p = line + 2;
  }

  g = strstr(p, "goto");
  strcpy(label, g + 4);

  len = g - p;
  strncpy(cond,p,len);
  cond[len] = '\0';

  char *ops[] = {"<=",">=","==","!=","<",">"};
  char *jmps[] = {"JLE","JGE","JE","JNE","JL","JG"};
  for(i=0;i<6;i++){
    char *q = strstr(cond,ops[i]);
    if(q != NULL){
      strcpy(jmp,jmps[i]);
      len = q - cond;
      strncpy(id1,cond,len);
      id1[len] = '\0';
      strcpy(id2,q + strlen(ops[i]));
      break;
    }
  }

  if(i == 6){
    sprintf(result[m++],"MOV AX,%s",cond);
    strcpy(result[m++],"CMP AX,0");
    sprintf(result[m++],"%s %s\n",isFalse ? "JE" : "JNE",label);
  }else{
    sprintf(result[m++], "MOV AX,%s", id1);
    sprintf(result[m++], "CMP AX,%s", id2);
    sprintf(result[m++],"%s %s\n",jmp,label);
  }
  return m;
}

int unconditional(char line[],char result[][MAX],int m){
  char label[MIN];
  if(sscanf(line,"goto%s",label) == 1){
    sprintf(result[m++],"JMP %s\n",label);
  }
  return m;
}

int expr(char line[],char result[][MAX],int m){
  char lhs[MIN],id1[MIN],op,id2[MIN];
  
  if(sscanf(line,"%[^=]=%[^+-*/]%c%s",lhs,id1,&op,id2) == 4){
    sprintf(result[m++],"MOV AX,%s",id1);
    if(op == '+'){
      sprintf(result[m++],"ADD AX,%s",id2);
    }else if(op == '-'){
      sprintf(result[m++],"SUB AX,%s",id2);
    }else if(op == '*'){
      sprintf(result[m++],"MOV BX,%s",id2);
      strcpy(result[m++],"MUL BX");
    }else if(op == '/'){
      sprintf(result[m++],"MOV BX,%s",id2);
      strcpy(result[m++],"MOV DX,0");
      strcpy(result[m++],"DIV BX");
    }
  }else if(sscanf(line,"%[^=]=minus%s",lhs,id1) == 2){
    sprintf(result[m++], "MOV AX,%s",id1);
    strcpy(result[m++], "NEG AX");
  }else if(sscanf(line,"%[^=]=%s",lhs,id1) == 2){
    sprintf(result[m++], "MOV AX,%s",id1);
  }
  sprintf(result[m++],"MOV %s,AX\n",lhs);
  return m;
}

void display(char result[][MAX],int m){
  printf("\nGenerated 8086 instructions:\n\n");
  for(int i=0;i<m;i++){
    printf("%s\n",result[i]);
  }
}

void main(){
  char line[MAX],result[MAX][MAX],label[MIN],rest[MAX];
  int n,m = 0;

  printf("Enter the no: of TAC statements:\n");
  scanf("%d",&n);
  getchar();

  printf("\nEnter the TAC statements\n");
  for(int i=0;i<n;i++){
    fgets(line,sizeof(line),stdin);
    line[strcspn(line,"\n")] = '\0';
    trim(line);

    if(strchr(line,':')){
      if(sscanf(line,"%[^:]:%s",label,rest) == 2){
        sprintf(result[m++],"%s:",label);
        strcpy(line,rest);
      }else if(sscanf(line,"%[^:]:",label) == 1){
        sprintf(result[m++],"%s:",label);
        continue;
      }
    }

    if(strstr(line,"if")){
      m = conditional(line,result,m);
    }else if(strstr(line,"goto")){
      m = unconditional(line,result,m);
    }else{
      m = expr(line,result,m);
    }
  }
  display(result,m);
}
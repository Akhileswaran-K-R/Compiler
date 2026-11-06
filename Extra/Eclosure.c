// Write a program to find ε – closure of all states of any given NFA with ε transition.

#include<stdio.h>
#define MIN 20

typedef struct{
  int states[MIN];
  int count;
}FA;

void acceptNFA(int states,int inputs,FA nfa[][inputs+1]){
  printf("\nEnter transition table\n");
  for(int i=0;i<states;i++){
    printf("\n");
    for(int j=0;j<inputs;j++){
      printf("No: of states for q%d on input %d: ",i,j);
      scanf("%d",&nfa[i][j].count);

      printf("%s",(nfa[i][j].count > 0)?"Desitination States: " : "");
      for(int k=0;k<nfa[i][j].count;k++){
        scanf("%d",&nfa[i][j].states[k]);
      }
    }

    printf("No: of states for q%d on input #: ",i);
    scanf("%d",&nfa[i][inputs].count);
    printf("%s",(nfa[i][inputs].count > 0)?"Desitination States: " : "");
    for(int k=0;k<nfa[i][inputs].count;k++){
      scanf("%d",&nfa[i][inputs].states[k]);
    }
  }
}

void add(int closure[],int *n,int state){
  for(int i=0;i<*n;i++){
    if(closure[i] == state){
      return;
    }
  }
  closure[(*n)++] = state;
}

void findEclosure(int inputs,int state,FA nfa[][inputs + 1],int closure[],int *n){
  add(closure,n,state);

  for(int i=0;i<nfa[state][inputs].count;i++){
    int ns = nfa[state][inputs].states[i];
    findEclosure(inputs,ns,nfa,closure,n);
  }
}

void main(){
  int states,inputs;
  printf("Enter the no: of sates: ");
  scanf("%d",&states);
  printf("Enter the no: of inputs excluding #: ");
  scanf("%d",&inputs);

  FA nfa[states][inputs+1];
  acceptNFA(states,inputs,nfa);
  printf("\n");
  for(int i=0;i<states;i++){
    int closure[MIN] = {0},n = 0;
    findEclosure(inputs,i,nfa,closure,&n);

    printf("E-closure(q%d) -> { ",i);
    for(int j=0;j<n;j++){
      printf("q%d ",closure[j]);
    }
    printf("}\n");
  }
}
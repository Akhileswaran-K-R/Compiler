//Write a program to convert NFA with ε transition to NFA without ε transition.

#include<stdio.h>
#define MIN 20

typedef struct{
  int states[MIN];
  int count;
}FA;
 
void acceptNFA(int states,int inputs,FA nfa[][inputs + 1]){
  printf("\nEnter the transition table\n");
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

void add(FA *res,int state){
  for(int i=0;i<res->count;i++){
    if(res->states[i] == state){
      return;
    }
  }
  res->states[res->count++] = state;
}

void findEclosure(int inputs,int state,FA nfa[][inputs + 1],FA *closure){
  add(closure,state);

  for(int i=0;i<nfa[state][inputs].count;i++){
    int ns = nfa[state][inputs].states[i];
    findEclosure(inputs,ns,nfa,closure);
  }
}

void convert(int states,int inputs,FA nfa[][inputs + 1],FA closure[]){
  for(int i=0;i<states;i++){
    printf("\nState q%d:\n",i);
    for(int j=0;j<inputs;j++){
      FA next;
      next.count = 0;
      for(int k=0;k<closure[i].count;k++){
        int current = closure[i].states[k];
        for(int l=0;l<nfa[current][j].count;l++){
          int dest = nfa[current][j].states[l];
          for(int m=0;m<closure[dest].count;m++){
            add(&next,closure[dest].states[m]);
          }
        }
      }

      printf("  On input %d -> { ",j);
      for(int k=0;k<next.count;k++){
        printf("q%d ",next.states[k]);
      }
      printf("}\n");
    }
  }
}

void main(){
  int states,inputs;
  printf("Enter the no: of states: ");
  scanf("%d",&states);
  printf("Enter the no: of inputs excluding #: ");
  scanf("%d",&inputs);

  FA nfa[states][inputs + 1];
  acceptNFA(states,inputs,nfa);

  FA closure[states];
  for(int i=0;i<states;i++){
    closure[i].count = 0;
    findEclosure(inputs,i,nfa,&closure[i]);
  }
  convert(states,inputs,nfa,closure);
}
#include<stdio.h>
#include<stdlib.h>
#define MAXSTATES 5

typedef struct{
  int states[MAXSTATES];
  int count;
}FA;

void sortState(FA *s){
  for(int i=0;i<s->count-1;i++){
    for(int j=0;j<s->count-i-1;j++){
      if(s->states[j] > s->states[j+1]){
        int temp = s->states[j];
        s->states[j] = s->states[j+1];
        s->states[j+1] = temp;
      }
    }
  }
}

int alreadyIn(FA a,int b){
  for(int i=0;i<a.count;i++){
    if(a.states[i] == b){
      return 1;
    }
  }
  return 0;
}

int compareStates(FA a, FA b){
  if(a.count != b.count){
    return 0;
  }

  for(int i=0;i<a.count;i++){
    if(a.states[i] != b.states[i]){
      return 0;
    }
  }
  return 1;
}

int findDFAState(FA dfa[],FA s,int dfaCount){
  for(int i=0;i<dfaCount;i++){
    if(compareStates(dfa[i],s)){
      return i;
    }
  }
  return -1;
}

void acceptNFA(int states,int inputs,FA nfa[][inputs]){
  printf("\nEnter transitions:\n");

  for(int i=0;i<states;i++){
    printf("\n");
    for(int j=0;j<inputs;j++){
      printf("Number of transitions from q%d on input %d: ", i, j);
      scanf("%d", &nfa[i][j].count);

      if(nfa[i][j].count > 0){
        printf("Destination states: ");
      }
      for(int k=0;k<nfa[i][j].count;k++){
        scanf("%d", &nfa[i][j].states[k]);
      }
    }
  }
}

void conversion(int states,int inputs,FA nfa[][inputs],FA dfa[],int dfaCount){
  printf("\nDFA Transition Table:\n");

  for(int i=0;i<dfaCount;i++){
    printf("\nState [ ");
    for(int j=0;j<dfa[i].count;j++){
      printf("q%d ", dfa[i].states[j]);
    }
    printf("]\n");

    for(int j=0;j<inputs;j++){
      FA next;
      next.count = 0;

      for(int k=0;k<dfa[i].count;k++){
        int current = dfa[i].states[k];

        for(int l=0;l<nfa[current][j].count;l++){
          int ns = nfa[current][j].states[l];

          if(!alreadyIn(next,ns)){
            next.states[next.count++] = ns;
          }
        }
      }
      sortState(&next);

      int index = findDFAState(dfa,next,dfaCount);
      if(index == -1 && next.count > 0){
        dfa[dfaCount++] = next;
      }

      printf("  On input %d -> [ ", j);
      for(int k=0;k<next.count;k++){
        printf("q%d ", next.states[k]);
      }
      printf("]\n");
    }
  }
}

void main(){
  int states,inputs,dfaCount = 0;
  printf("Enter the no: of states: ");
  scanf("%d",&states);
  printf("Enter the no: of input symbols: ");
  scanf("%d",&inputs);

  FA nfa[states][inputs],dfa[1 << states];
  acceptNFA(states,inputs,nfa);

  dfa[dfaCount].count = 1;
  dfa[dfaCount++].states[0] = 0;
  conversion(states,inputs,nfa,dfa,dfaCount);
}
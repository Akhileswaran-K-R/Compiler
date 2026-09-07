#include<stdio.h>
#include<stdlib.h>
#define MAXSTATES 5

typedef struct{
  int states[MAXSTATES];
  int count;
}DFA;

void sortState(DFA *s){
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

int alreadyIn(DFA a,int b){
  for(int i=0;i<a.count;i++){
    if(a.states[i] == b){
      return 1;
    }
  }
  return 0;
}

int compareStates(DFA a, DFA b){
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

int findDFAState(DFA dfa[],DFA s,int dfaCount){
  for(int i=0;i<dfaCount;i++){
    if(compareStates(dfa[i],s)){
      return i;
    }
  }
  return -1;
}


void main(){
  int states,inputs;
  printf("Enter the no: of states: ");
  scanf("%d",&states);
  printf("Enter the no: of input symbols: ");
  scanf("%d",&inputs);

  int nfa[states][inputs][states];
  int nfaCount[states][inputs];

  printf("\nEnter transitions:\n");

  for(int i=0;i<states;i++){
    printf("\n");
    for(int j=0;j<inputs;j++){
      printf("Number of transitions from q%d on input %d: ", i, j);
      scanf("%d", &nfaCount[i][j]);

      for(int k=0;k<nfaCount[i][j];k++){
        scanf("%d", &nfa[i][j][k]);
      }
    }
  }

  DFA dfa[1 << states],start;
  int dfaCount = 0;

  start.count = 1;
  start.states[0] = 0;
  dfa[dfaCount++] = start;
  
  printf("\nDFA Transition Table:\n");

  for(int i=0;i<dfaCount;i++){
    printf("\nState { ");
    for(int j=0;j<dfa[i].count;j++){
      printf("q%d ", dfa[i].states[j]);
    }
    printf("}\n");

    for(int j=0;j<inputs;j++){
      DFA next;
      next.count = 0;

      for(int k=0;k<dfa[i].count;k++){
        int current = dfa[i].states[k];

        for(int l=0;l<nfaCount[current][j];l++){
          int ns = nfa[current][j][l];

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

      printf("  On symbol %d -> { ", j);
      for(int k=0;k<next.count;k++){
        printf("q%d ", next.states[k]);
      }
      printf("}\n");
    }
  }
}
#include<stdio.h>
#include<string.h>

void acceptDFA(int states,int inputs,int delta[][inputs]){
  for(int i=0;i<states;i++){
    printf("\n");
    for(int j=0;j<inputs;j++){
      printf("Transition(q%d,%d): q",i,j);
      scanf("%d",&delta[i][j]);
    }
  }
}

int findRep(int states,int currgrp,int group[]){
  for(int i=0;i<states;i++){
    if(group[i] == currgrp){
      return i;
    }
  }
  return -1;
}

int minimize(int states,int inputs,int delta[][inputs],int group[]){
  int split,changed,count,temp[states],newgrp = 2;
  do{
    changed = 0;

    for(int currgrp=0;currgrp<newgrp;currgrp++){
      count = 0,split = 0;

      int rep = findRep(states,currgrp,group);
      if(rep == -1){
        continue;
      }

      for(int i=rep+1;i<states;i++){
        if(group[i] != currgrp){
          continue;
        }

        for(int j=0;j<inputs;j++){
          if(group[delta[rep][j]] != group[delta[i][j]]){
            temp[count++] = i;
            split = 1;
            break;
          }
        }
      }

      for(int i=0;i<count;i++){
        group[temp[i]] = newgrp;
      }

      if(split){
        newgrp++;
        changed = 1;
      }
    }
  }while(changed);

  return newgrp;
}

void display(int totalgrp,int states,int group[]){
  printf("\nMinimized DFA\n\n");
  for(int i=0;i<totalgrp;i++){
    printf("Group %c: [ ",i+65);
    for(int j=0;j<states;j++){
      if(i == group[j]){
        printf("q%d ",j);
      }
    }
    printf("]\n");
  }
}

void main(){
  int states,inputs,temp,f,totalgrp;
  printf("Enter the no: of states: ");
  scanf("%d",&states);
  printf("Enter the no: of inputs: ");
  scanf("%d",&inputs);

  int delta[states][inputs],group[states];
  printf("\n");
  acceptDFA(states,inputs,delta);

  printf("\nEnter no: of final states: ");
  scanf("%d",&f);

  memset(group,0,sizeof(group));
  printf("Enter final states: ");
  for(int i=0;i<f;i++){
    scanf("%d",&temp);
    group[temp] = 1;
  }

  totalgrp = minimize(states,inputs,delta,group);
  display(totalgrp,states,group);
}
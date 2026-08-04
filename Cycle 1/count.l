%{
  #include<stdio.h>

  int line = 0;
  int word = 0;
  int charac = 0;
%}

%%

\n          { line++; }
[^\t\n ]+   { word++; charac += yyleng; }
.

%%

void main(){
  printf("Enter your text\n");
  yylex();
  
  printf("\n--- Results ---\n");
  printf("Lines: %d\n", line);
  printf("Words: %d\n", word);
  printf("Characters: %d\n", charac);
}

int yywrap() {
  return 1;
}
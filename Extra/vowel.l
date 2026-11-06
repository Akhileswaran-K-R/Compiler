/* Write a lex program to find out total number of vowels and consonants from the given input string. */

%{
  #include<stdio.h>

  int v = 0;
  int c = 0;
%}

%%

[aeiouAEIOU]                { v++; }
[a-zA-Z]                    { c++; }
\n                          {
                              printf("Vowels: %d\n", v);
                              printf("Constants: %d\n\n", c);
                              v = 0;
                              c = 0;
                            }
.

%%

void main(){
  printf("Enter a string\n\n");
  yylex();
}

int yywrap(){
  return 1;
}
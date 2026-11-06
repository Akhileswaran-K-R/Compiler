/*Write a LEX Program to convert the substring abc to ABC from the given input string.*/

%{
  #include<stdio.h>
%}

%%

"abc"                   { printf("ABC"); }
\n                      { printf("\n\n"); }
.                       { printf("%c",yytext[0]); }

%%

void main(){
  printf("Enter a string\n\n");
  yylex();
}

int yywrap(){
  return 1;
}
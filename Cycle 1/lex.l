%{
#include <stdio.h>
#include <string.h>

char *keywords[] = {
  "int","float","double","char",
  "printf","scanf","main",
  "if","else",
  "for","while","do",
  "switch","case","break","default",
  "continue","return"
};

int isKeyword(char *str)
{
  int n = sizeof(keywords) / sizeof(keywords[0]);
  for(int i=0;i<n;i++)
    if(strcmp(str,keywords[i])==0)
      return 1;
  return 0;
}
%}

LETTER      [a-zA-Z_]
DIGIT       [0-9]

ID          {LETTER}({LETTER}|{DIGIT})*
INT         {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+([Ee][+-]?{DIGIT}+)?
STRING      \"([^\\\n]|(\\.))*\"
CHAR        \'([^\\\n]|(\\.))\'

%%

[ \t\n]+                      ;

"//".*                        ;

"/*"([^*]|\*+[^*/])*\*+"/"    ;

"++"                          { printf("++\tIncrement Operator\n"); }
"--"                          { printf("--\tDecrement Operator\n"); }

"+="|"-="|"*="|"/="|"%="      { printf("%s\tAssignment Operator\n",yytext); }

"=="|"!="|"<="|">="           { printf("%s\tRelational Operator\n",yytext); }

">"|"<"|"!"                   { printf("%s\tRelational Operator\n",yytext); }

"="                           { printf("=\tAssignment Operator\n"); }

"+"|"-"|"*"|"/"|"%"           { printf("%s\tArithmetic Operator\n",yytext); }

"("|")"|"{"|"}"|"["|"]"       { printf("%s\tParenthesis\n",yytext); }

";"|","|":"                   { printf("%s\tPunctuator\n",yytext); }

{FLOAT}                       { printf("%s\tFloat\n",yytext); }

{INT}                         { printf("%s\tInteger\n",yytext); }

{STRING}                      { printf("%s\tString\n",yytext); }

{CHAR}                        { printf("%s\tCharacter\n",yytext); }

{ID}                          {
                                if(isKeyword(yytext))
                                    printf("%s\tKeyword\n",yytext);
                                else
                                    printf("%s\tIdentifier\n",yytext);
                              }

.                             { printf("%s\tUnknown\n",yytext); }

%%

int yywrap()
{
  return 1;
}

void main()
{
  yyin = fopen("input.txt","r");
  yylex();
  fclose(yyin);
}
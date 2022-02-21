%{
#include<stdio.h>
%}
{Tag} \<[^>]*\>
eol \n
%%
{Tag} {
            printf("%s\n",yytext);
        }
{eol} {

}
. {

}
%%


int main(int argc,char *argv[])
{
    yylex();
    return 0;
}
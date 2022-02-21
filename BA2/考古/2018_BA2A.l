%{
#include<stdio.h>
unsigned int tabCount=0;
%}
SN  ^[+|-]?[0-9].[0-9]*E[+|-]?[0-9]*
eol \n
%%
{SN}    {
    printf("%s",yytext);
}
. {

}
%%
int main(int argc, char *argv[]) {
	yylex();
	return(0);
}

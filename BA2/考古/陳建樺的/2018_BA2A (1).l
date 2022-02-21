%{
#include<stdio.h>
unsigned int tabCount=0;
%}
SN  ^[+|-]?[1-9](\.[0-9]*)?E[+|-]?[0-9]+[\n\r]
eol \n
%%
{SN}    {
    printf("%s\n",yytext);
}
{eol} {

}
. {

}
%%
int main(int argc, char *argv[]) {
	yylex();
	return(0);
}

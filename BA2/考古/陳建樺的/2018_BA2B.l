%{
#include<stdio.h>
%}
WORD ^[A-Z][A-Za-z]*[\n\r]
IP ^(([0-9][0-9]?|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.){3}([0-9][0-9]?|1[0-9][0-9]|2[0-4][0-9]|25[0-5])[\n\r]
EMAIL [A-Za-z0-9]+@([A-Za-z0-9]+\.)+[A-Za-z0-9]+
eol \n
%%
{WORD} {
    char *tmp=yytext;
    tmp[yyleng-1]='\0';
    printf("%s is a word\n",tmp);
}
{IP} {
    char *tmp=yytext;
    tmp[yyleng-1]='\0';
    printf("%s is an IP address\n",tmp);
}
{EMAIL} {
    printf("%s is an email address\n",yytext);
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

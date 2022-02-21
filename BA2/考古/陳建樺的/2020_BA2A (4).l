%{
#include<stdio.h>
%}
ATM $([0-9]{0,5}[^0-9]|100000)
Day \+([0-9]|[1-9][0-9]|[12][0-9][0-9]|3[0-5][0-9]|36[0-5])[^0-9]
Time ([01][0-9]|2[0-4]):([0-9]|[1-5][0-9]|60)
Place [A-Z]([a-z]|\.|-)*[A-Z]
eol \n
%%
{ATM} {
    char *tmp=yytext;
    tmp[yyleng-1]='\0';
    printf("transfer %s\n",tmp);
}
{Day}    {
    char *tmp=yytext;
    tmp[yyleng-1]='\0';
    printf("after %s day\n",tmp);
}
{Time} {
    printf("at %s\n",yytext);
}
{Place} {
    printf("at %s\n",yytext);
}
. {

}
%%
int main(int argc, char *argv[]) {
	yylex();
	return(0);
}

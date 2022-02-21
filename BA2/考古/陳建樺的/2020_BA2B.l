%{
#include<stdio.h>
%}
name [A-Za-z_][a-zA-Z_0-9]*
para ([A-Za-z0-9]*)
function ^{name}\(({para}(," "))*{para}?\)
eol \n
%%
{function} {
    printf("%s",yytext);
}
. {

}
%%
int main(int argc, char *argv[]) {
	yylex();
    printf("\n");
	return(0);
}

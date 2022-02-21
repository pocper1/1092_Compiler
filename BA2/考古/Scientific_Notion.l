%{

%}

normalized_significand ^[+|-]{0,1}?[1-9].[0-9]*{0,1}E[+|-]{0,1}[0-9]+

eol \n
%%
{normalized_significand} {
    printf("%s\n",yytext);
}
{eol} {

}
. {

}
%%
int main(int argc, int argv[]){
    yylex();
    return(0);
}
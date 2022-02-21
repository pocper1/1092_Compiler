%{

%}
point .
eol \n


bound ^([0-9]*[\.]{1}[0-9]+|[0-9]+[\.]{1}[0-9]*)[\r\n]

normalized_significand ^([0-9]*[\.]{1}[0-9]+|[0-9]+[\.]{1}[0-9]*|[0-9]+[\.]?)[E|e]{1}[+|-]?[0-9]+[\r\n]

%%
{bound} {
    char *tmp=yytext;
    tmp[yyleng-1]='\0';
    printf("%s\n",tmp);
}
{normalized_significand} {
    char *tmp=yytext;
    tmp[yyleng-1]='\0';
    printf("%s\n",tmp);
}
{eol} {

}
. {

}
%%
int main(int argc, char*argv[]){
    yylex();
    return(0);
    // 第二題 E多個正負號
    // lim_n ^[^+|^-][0-9]*.[0-9]*
    // normalized_significand ^[+|-]{0,1}?[1-9].[0-9]*{0,1}E[+|-]{0,1}[0-9]+
    // bounded ^([^+-][0-9]*)?[.]([^+-][0-9]*)?[\n\r]
    //bounded ^([^+-][0-9]*)?([.]){1}([^+-][0-9]*)?[\n\r]
    //bound ^(([^+-][0-9]+\.)|(\.[^+-][0-9]+))[\n\r]
}

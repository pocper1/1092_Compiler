%{

%}
Word ^[A-Z][A-Za-z]*

ip_int   ([0-9]|[1-9][0-9]|1[0-9][0-9]|2([0-4][0-9]|5[0-5]))
IP       {ip_int}\.{ip_int}\.{ip_int}\.{ip_int}[^0-9]
Email ([a-z0-9_\.-]+)@([\da-z\.-]+)\.([a-z\.]{2,6})
eol \n
%%
{Word} {
        printf("%s is a word\n",yytext);
    }

{IP} {
        char *tmp=yytext;
        tmp[yyleng-1]='\0';
        printf("%s is an IP address\n",tmp);
       
    }
{Email} {
        printf("%s is an email address\n",yytext);
       
    }
{eol} {
   
}
.   {
    }
%%

int main(int argc, int argv[]){
    yylex();
    return(0);
}
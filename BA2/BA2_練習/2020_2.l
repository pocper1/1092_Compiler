%{

%}
functioncall [A-Za-z_][A-Za-z0-9_]*\(     ([A-Za-z0-9_]*[,])*[A-Za-z0-9_]+     \)
begining [A-Za-z_]
content [\w]+
excep   [%$#@!$*&]+
eol \n
%%
{functioncall} {
            printf("%s\n",yytext);
        }
{eol}   {
            
        }
.       {

        }
%%
int main(int argc, char*argv[]){
    yylex();
    return(0);
}

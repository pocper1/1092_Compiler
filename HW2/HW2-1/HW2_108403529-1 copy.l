
%{
unsigned int tab_count=0;
%}
lp  [{]
rp  [}]
eol [\n]
content [\w]+

%%

{lp}    {
            printf("{");    
            tab_count++;
        }
{rp}    {
            printf("}");
            tab_count--;
        }
{eol}   {
    
            if(tab_count == 1)
                printf("\n%s","\t");
            else if(tab_count == 2)
                printf("\n%s","\t\t");
            else if(tab_count == 3)
                printf("\n%s","\t\t\t");
            else
                printf("\n");

        }
{content} {
            printf("%s",yytext);
        }
%%
int main(int argc, char *argv[]){
  yylex();
  return(0);
}
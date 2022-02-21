%{
unsigned int tab_count=0,tmp_count=0;
%}
lp  [{]
rp  [}]
eol [\n]
content [a-zA-Z0-9]*

%%

{lp}    {
            if(tab_count == 1)
                printf("%s","\t");
            else if(tab_count == 2)
                printf("%s","\t\t");
            else if(tab_count == 3)
                printf("%s","\t\t\t");
            
            printf("{");
            tab_count++; 
        }
{rp}    {
            tab_count--;
            if(tab_count != 0){
                tmp_count = tab_count;
                
                if(tab_count == 1)
                    printf("%s","\t");
                else if(tab_count == 2)
                    printf("%s","\t\t");
                else if(tab_count == 3)
                    printf("%s","\t\t\t");
                tab_count = 0;
            }
            printf("}");
        }
{eol}   {
        printf("\n");
        if(tmp_count != 0){
            tab_count += tmp_count;
            tmp_count = 0;
        }
}

{content} {
            if(tab_count != 0){
                tmp_count = tab_count;
                
                if(tab_count == 1)
                    printf("%s","\t");
                else if(tab_count == 2)
                    printf("%s","\t\t");
                else if(tab_count == 3)
                    printf("%s","\t\t\t");

                tab_count = 0;
            }

            printf("%s",yytext);
        }

%%
int main(int argc, char *argv[]){
  yylex();
  return(0);
}
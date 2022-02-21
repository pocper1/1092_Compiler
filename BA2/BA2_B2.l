%{
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
char dest[200];
char tmp_line[200];
char quote_str[200];
char tmp[200];
int i=0,k=0,tmp_start=0,flag=0,tmp_i=0,title_count=0,list_counter=0,quote_counter=0,pos=0;
void mysubstr (const char* input, int start, int end, char* dest){ 
    memset(dest, '\0', 200); 
    if (start > end || end > strlen(input) ) 
        return; 
    strncpy (dest, input + start, end - start + 1);
}

void iterator_quote(const char* input){
    for(i=2;i<yyleng;i++){
        if(yytext[i] == '*' && yytext[i+1] == '*'){

            if(flag == 0){
                printf("<strong>");
                flag =1;
            }
            else if(flag == 1){
                printf("</strong>");
                flag =0;
            }

            i++;
        }
        else{
            printf("%c",yytext[i]);

        }
        
    }
    printf("\n");
}

%}

TEXT [A-Za-z0-9 ]{1,200}
SPECIAL [\/\?\:\.\&\(\)\=\"\'\,\-\_]
TAG #
eol \n
TITLE [ ]{TEXT}
HR ---
IMAGE ^!\[{TEXT}\][\(]({TEXT}|{SPECIAL})+[\)]
MULTICHOICE ^[-][ ](\[X\]|\[x\]|\[[ ]\])[ ]{TEXT}
LIST ^[\*][ ]{TEXT}
ATTR ^\[{TEXT}\][\(]({TEXT}|{SPECIAL})+[\)]
QUOTE ^[\>][ ].*

%%
{TAG} {
    title_count++; 
}
{TITLE} {
    char res[200];
    if(title_count >= 7 | title_count == 0){
        title_count =0;
    }else{
        mysubstr(yytext, 1, yyleng, res);
        printf("<h%d>%s</h%d>\n",title_count,res,title_count);
        title_count =0;
    }
    
}
{HR} {
    if(list_counter != 0){
        printf("</ul>\n");
        list_counter =0;
    }
    if(quote_counter != 0){
        printf("</blockquote>\n");
        quote_counter =0;
    }
    printf("<hr />\n");
   
    
}

{IMAGE} {
    char *pch,*pch1,*pch2,*pch3;
    int first=0,second=0;
    char alt[200];
    char src[200];
    
    pch = strchr(yytext, '[');
    first = pch-yytext;

    pch1 = strchr(yytext, ']');
    second = pch1-yytext;
    
    mysubstr(yytext, first+1, second-1, alt);

    pch2 = strchr(yytext, '(');
    first = pch2-yytext;

    pch3 = strchr(yytext, ')');
    second = pch3-yytext;

    mysubstr(yytext, first+1, second-1, src);

    
    printf("<img alt=\"%s\" src=\"%s\">\n",alt,src);

}
{ATTR} {
    char *pch,*pch1,*pch2,*pch3;
    int first=0,second=0;
    char alt[200];
    char src[200];
    
    pch = strchr(yytext, '[');
    first = pch-yytext;

    pch1 = strchr(yytext, ']');
    second = pch1-yytext;
    
    mysubstr(yytext, first+1, second-1, alt);

    pch2 = strchr(yytext, '(');
    first = pch2-yytext;

    pch3 = strchr(yytext, ')');
    second = pch3-yytext;

    mysubstr(yytext, first+1, second-1, src);

    
    printf("<a href=\"%s\">\n",src);
    printf("\t<span>%s</span>\n",alt);
    printf("</a>\n");

}

{MULTICHOICE} {
    char *pch,*pch1,*pch2;
    int first=0,second=0;
    char src[200];

    pch = strchr(yytext, '[');
    pch1 = strchr(yytext, 'X');
    pch2 = strchr(yytext, ']');

    first = pch - yytext;
    second = pch2 - yytext;
    
    mysubstr(yytext, second+2, yyleng, src);
    if(*(pch+1) == 'X' | *(pch+1) == 'x'){
      
        printf("<p>\n\t<input checked=\"checked\" type=\"checkbox\" /> %s\n</p>\n",src);
    }else{

        printf("<p>\n\t<input type=\"checkbox\" /> %s\n</p>\n",src);
    }
    first = 0;
    second = 0;
   
}
{LIST} {
    char lis[200];
    if(list_counter == 0){
        printf("<ul>\n");
    }
    list_counter++;
    mysubstr(yytext, 2, yyleng, lis);
    
    printf("\t<li>%s</li>\n",lis);

}
{QUOTE} {
    if(quote_counter == 0){
        printf("<blockquote>\n");
    }
    quote_counter++;
   
    // mysubstr(yytext, 2, yyleng, quote_str);
    iterator_quote(yytext);
   
}

. {

}
{eol} {

}
%%
int main(int argc, char*argv[]){
    yylex();
    return(0);
}

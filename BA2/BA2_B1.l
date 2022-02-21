%{
int title_count=0;

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
char dest[200];

void mysubstr (const char* input, int start, int end, char* dest){ 
    memset(dest, '\0', 200); 
    if (start > end || end > strlen(input) ) 
        return; 
    strncpy (dest, input + start, end - start + 1); // + 1 是比較直觀一些 
}

%}

TEXT [A-Za-z0-9 ]{1,200}
SPECIAL [\/\?\:\.\&\(\)\=\"\'\,\-\_]

eol \n
TAG #
TITLE [ ]{TEXT}
HR ---[\r\n]
IMAGE ^!\[{TEXT}\][\(]({TEXT}|{SPECIAL})+[\)][\r\n]
MULTICHOICE ^[-][ ](\[X\]|\[x\]|\[[ ]\])[ ]{TEXT}[\r\n]
%%
{TAG} {
    title_count++; 
}
{TITLE} {
    char res[200];
    if(title_count >= 7 | title_count == 0){
        title_count =0;
    }else{
        mysubstr(yytext, 1, yyleng-1, res);
        printf("<h%d>%s</h%d>\n",title_count,res,title_count);
        title_count =0;
    }

}
{HR} {
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

{MULTICHOICE} {
    char *pch,*pch1,*pch2;
    int first=0,second=0;
    char src[200];

    pch = strchr(yytext, '[');
    pch1 = strchr(yytext, 'X');
    pch2 = strchr(yytext, ']');

    first = pch - yytext;
    second = pch2 - yytext;
    
    mysubstr(yytext, second+2, yyleng-1, src);
    if(*(pch+1) == 'X' | *(pch+1) == 'x'){
        // checked
        printf("<p>\n\t<input checked=\"checked\" type=\"checkbox\" /> %s\n</p>\n",src);
    }else{
        // not check
        printf("<p>\n\t<input type=\"checkbox\" /> %s\n</p>\n",src);
    }
    first = 0;
    second = 0;
}
{eol} {

}
. {

}
%%
int main(int argc, char*argv[]){
    yylex();
    return(0);
}

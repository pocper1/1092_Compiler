%{
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <string.h>
    #include<stddef.h>
    char dest[200];
    char dest2[200];
    char output[200];
    int pos=0;
    void mysubstr (const char* input, int start, int end, char* dest){ 
        memset(dest, '\0', 200); 
        if (start > end || end > strlen(input) ) 
            return;
        strncpy (dest, input + start, end - start +1); 
    }
    void mysubstr2 (const char* input, int start, int end, char* dest){ 
        memset(dest2, '\0', 200); 
        if (start > end || end > strlen(input) ) 
            return;
        strncpy (dest2, input + start, end - start +1); 
    }
    ptrdiff_t index_of(const char *string, char search) {
    const char *moved_string = strchr(string, search);
        /* If not null, return the difference. */
        if (moved_string) {
            return moved_string - string;
        }
        /* Character not found. */
        return -1;
    }
    int getCheck(const char* input){
        if(input[3]=='X'||input[3]=='x')
            return 1;
        else
            return 0;
    }
    int i;
    void title(const char* input){
		int count = 0;
		for(i=0;i<yyleng;i++){
			if(yytext[i] == '#' ){
				count++;
			}	
		}
		mysubstr(yytext, count+1, yyleng, dest);
		printf("<h%d>%s</h%d>\n", count, dest, count);
    }
    void img(const char* input){
        int midquotel;
        int midquoter;
        int quotel;
        int quoter;
		for(i=0;i<yyleng;i++){
			if(yytext[i] == '[' ){
                midquotel = i;
			}	
            if(yytext[i] == ']'){
                midquoter = i;
            }
            if(yytext[i] == '('){ 
                quotel = i;
            }
            if(yytext[i] == ')'){
                quoter = i;
            }
		}
        char name[200], url[200];
		mysubstr(yytext, midquotel+1, midquoter-1, name);
		mysubstr(yytext, quotel+1, quoter-1, url);
        printf("<img alt=\"%s\" src=\"%s\">\n",name,url);
    }
%}

text [a-zA-Z0-9 ]+
title #{1,6}[ ]{text}
hr \-\-\-
img \!\[{text}\]\(.+\)
checkbox -[ ]\[[Xx ]\][ ]{text}

%%
{title} {
    title(yytext);
}
{hr} {
    printf("<hr />\n");
}
{img} {
    img(yytext);
}
{checkbox} {
    mysubstr(yytext,6,yyleng,dest);
    if(getCheck(yytext)==1){
        printf("<p>\n\t<input checked=\"checked\" type=\"checkbox\" /> %s\n</p>\n",dest);
    }else{
        printf("<p>\n\t<input type=\"checkbox\" /> %s\n</p>\n",dest);
    }
}
\n {

}
. {

}
%%
int main(int argc, char *argv[]) {
	yylex();
    printf("\n");
	return(0);
}

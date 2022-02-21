%{
char tagID[100] = "";
char nextID[100] = "";
char nextLine[5] = "\\n";
char doubleSpace[3] = "  ";
char empty[2] = "";
int error = 0;
char answer[] = "";
%}
tagId    [a-z|A-Z|_]+
errortagId  [^ a-z|^ A-Z|^ _]+
lefttag   <
righttag  >
ID   ({lefttag}{tagId}{righttag})
%%
{ID}  { strcpy( nextID , yytext); 
        if( strcmp( tagID , empty )==0 ){
            strcat( answer , yytext );
            strcat( answer , nextLine );
            strcpy( tagID , yytext);
        }
        else if( strcmp( tagID , nextID )==0 ){
            strcat( answer , yytext );
            strcat( answer , nextLine );
            strcpy( tagID , yytext);
        }
        else if( strcmp( tagID , nextID )!=0 ){
            strcat( answer , doubleSpace );
            strcat( answer , yytext );
            strcat( answer , nextLine );
            strcpy( tagID , yytext);
        }
      }
{errortagId}  {error++;}
\n  {;}
.  {;}
%%
int main(int argc, char *argv[]) {
    yylex();
    if( error!=0 ){
        printf("please don't eat me");
    }
    else{
        printf("%s", answer);	
    }
    return(0);
}
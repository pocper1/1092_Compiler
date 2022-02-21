%{
#include "BA3-2.tab.h"

%}

%%

[0-9]+	{  
            yylval.ival = atoi(yytext);
            return(DIGITS); 
        }
"+"     {
            return ADDITION;
        } 
"*"     {
            return MULTIPLY;
        }
"["     {
            return LBRACKET;
        }
"]"     {
           
            return RBRACKET;
        }
","     {
            return COMMA;
        }


[\n]    { 
            return(0); /* EOF */ 
        }
[ ]+ 	{ 
            /* do nothing */ 
        }
[\t]+	{ 
            /* do nothing */ 
        }
.	    { 
            return(yytext[0]); 
        }

%%

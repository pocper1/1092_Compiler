%{
#include "postorder.tab.h"
%}

Num [0-9]+|[0-9]+[.][0-9]+
%%

{Num}	{  
            yylval.ival = atof(yytext);
            return(INUMBER); 
        }

"+"     {
            return ADD;
        }
"-"     {
            return SUB;
        }
"*"     {
            return MUL;
        }
"/"     {
            return DIV;
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

%{
#include "BA3-1.tab.h"
%}

%%

[0-9]+	{  
            yylval.ival = atoi(yytext);
            return(INUMBER); 
        }

"push"     {
            return PUSH;
        }
"inverse"     {
            return INVERSE;
        }
"inc"     {
            return INC;
        }
"dec"     {
            return DEC;
        }

"$"    { 
            return(0); /* EOF */ 
        }
[\n]    { 
             /* EOF */ 
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

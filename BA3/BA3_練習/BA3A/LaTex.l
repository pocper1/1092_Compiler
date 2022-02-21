%{
#include "LaTex.tab.h"
%}

%%

[0-9]+	{  
            yylval.ival = atof(yytext);
            return(INUMBER); 
        }
"^"     {
            return UPPER;
        } 
"+"     {
            return ADD;
        }
"-"     {
            return SUB;
        }
"\\frac" {
            return FRAC;
        }
"{" {
            return L_par;
        }
"}" {
            return R_par;
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

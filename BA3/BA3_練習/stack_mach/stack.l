%{
#include "stack.tab.h"
%}
%%

[0-9]+	{  
            yylval.ival = atoi(yytext);
            return(INUMBER); 
        }
"load"  {
            return LOAD;
        }
"add"   {
            return ADD;
        }
"sub"   {
            return SUB;
        }
"mul"   {
            return MUL;
        }
"div"   {
            return DIV;
        }
"mod"   {
            return MOD;
        }
"inc"   {
            return INC;
        }
"dec"   {
            return DEC;
        }
"copy"  {
            return COPY;
        }
"delete" {
            return DELETE;
        }
"switch" {
            return SWITCH;
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

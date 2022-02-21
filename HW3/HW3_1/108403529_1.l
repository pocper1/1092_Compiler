%{
#include "108403529_1.tab.h"
%}

numbers [0-9]+
load load
add add
sub sub
mod mod
mul mul
inc inc
dec dec
%%
{numbers} { 
            yylval.ival = atoi(yytext);
            return(INUMBER); 
        }
{load}  {
            return LOAD; 
        }
{add}   {
            return ADD; 
        }
{sub}   {
            return SUB; 
        }
{mod}   {
            return MOD; 
        }
{mul}   {
            return MUL; 
        }
{inc}   {
            return INC; 
        }
{dec}   {
            return DEC; 
        }
[\n]	{ /* do nothing */ }
[ \t]+	{ /* do nothing */ }
.	    { 
            return(yytext[0]); 
        }


%%

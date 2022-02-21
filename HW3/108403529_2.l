%{
#include "108403529_2.tab.h"
int exec_to_where = 0;
%}

eol \n
numbers [0-9]+

addition "+"
subtraction "-"
multiplication "*"
transpose "^T"

Left_par "("
Right_par ")"
Left_brac "["
Right_brac "]"
Com ","

%%

{numbers}	{ 
                exec_to_where++;
                yylval.ival = atoi(yytext);
                return(INUMBER); 
            }
{addition}  {
                exec_to_where+= 1;
                yylval.ival = exec_to_where;
                return ADDITION;
            }
{subtraction}   {
                exec_to_where+= 1;
                yylval.ival = exec_to_where;
                return SUBTRACTION;
            }
{multiplication} {
                exec_to_where+= 1;
                yylval.ival = exec_to_where;
                return MULTIPLICATION;
            }
{transpose} {
                exec_to_where+= 2;
                return TRANSPOSE;
            }
{Left_par} {
                exec_to_where+= 1;
                return LEFT_PAR;
            }
{Right_par} {
                exec_to_where+= 1;
                return RIGHT_PAR;
            }
{Left_brac} {
                exec_to_where+= 1;
                return LEFT_BRAC;
            }
{Right_brac} {
                exec_to_where+= 1;
                return RIGHT_BRAC;
            }
{Com} {
                exec_to_where+= 1;
                return COM;
            }
{eol}	    { 
                return (0);
            }
[ ]+	    { 
                exec_to_where+= yyleng;
            }
[\t]+	    { 
                exec_to_where+= yyleng;
            }
.	        { 
                return(yytext[0]); 
            }

%%

%{
#include "matrix.tab.h"
int pos=0;
%}

%%

[0-9]+	{  
            pos+=1;
            yylval.ival = atoi(yytext);
            return(INUMBER); 
        }
"["     {

            pos+=1;
            yylval.ival = pos;
            return L_a;
        } 
"]"     {
            pos+=1;
            yylval.ival = pos;
            return R_a;
        }
"("     {
            pos+=1;
            yylval.ival = pos;
            return L_par;
        }
")"     {
            pos+=1;
            yylval.ival = pos;
            return R_par;
        }
","    {
            pos+=1;
            yylval.ival = pos;
            return COM;
        }
"^T"    {
            pos+=2;
            yylval.ival = pos;
            return Trans;
        }
"+"     {
            pos+=1;
            yylval.ival = pos;
            return ADD;
        }
"*"     {
            pos+=1;
            yylval.ival = pos;
            return MUL;
        }


[\n]    { 
            return(0); /* EOF */ 
        }
[ ]+ 	{ 
            pos+=yyleng;
            
            /* do nothing */ 
        }
[\t]+	{ 
            pos+=yyleng;
            
            /* do nothing */ 
        }
.	    { 
            return(yytext[0]); 
        }

%%

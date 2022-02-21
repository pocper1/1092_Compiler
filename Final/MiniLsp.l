%{
#include "MiniLsp.tab.h"

%}
separator [\t\r ]+
letter [a-z]
digit [0-9]

numbers 0|[1-9]{digit}*|-[1-9]{digit}*
ID {letter}({letter}|{digit}|'-')*

Bool_val #f|#t 
%%

"("         {
                return L_par;
            }
")"         {
                return R_par;
            }

"+"         {
                return plu;
            }
"-"         {
                return min;
            }

"*"         {
                return mul;
            }

"/"         {
                return Div;
            }

"mod"         {
                return mod;
            }

"="         {
                return eql;
            }

">"         {
                return gre;
            }

"<"         {
                return sml;
            }


            
"and"         { 
                return and;
            }
"or"         { 
                return or;
            }
"not"         { 
                return Not;
            }

"define"      { 
                return define;
            }
"if"          { 
                return IF;
            }
"print-num"   {
                return PrintOfNum;
            }
"print-bool"  {
                return PrintOfBool;
            }

{numbers}	{  
                yylval.intval = atoi(yytext);
                return(number); 
            }
{Bool_val}  {
                if(!strcmp(yytext,"#t")){
                    yylval.intval = 1;
                }else if(!strcmp(yytext,"#f")){
                    yylval.intval = 0;
                }else{
                     yylval.intval = -1;
                }
                return (bool_val);
            }
{ID}	    {  
                yylval.String = strdup(yytext);
                return (ID);
            }


{separator} {
                ;
            }
\n          {
                ;
            }
.	        { 
                return(yytext[0]); 
            }

%%

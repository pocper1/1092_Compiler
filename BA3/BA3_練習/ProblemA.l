%{
#include "ProblemB.tab.h"
#include <stdio.h>
%}
and          "& "
or           "| "
xor          "^ "
not          "~ "
L_shift      "<< "
R_shift      ">> "
number       ([0-9]|[1-9][0-9]+)
%%
{and}        { yylval.intVal = 1; return OPERATORS; }
{or}         { yylval.intVal = 2; return OPERATORS; }
{xor}        { yylval.intVal = 3; return OPERATORS; }
{not}        { yylval.intVal = 4; return OPERATORS; }
{L_shift}    { yylval.intVal = 5; return OPERATORS; }
{R_shift}    { yylval.intVal = 6; return OPERATORS; }
{number}     { yylval.intVal = atoi(yytext); return(NUMBER); }

\n      {;}
[ \t]+  {;}
.       { return(yytext[0]); }
%%

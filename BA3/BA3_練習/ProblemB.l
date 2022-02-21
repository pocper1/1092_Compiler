%{
#include "ProblemB.tab.h"
#include <stdio.h>
int depth = 0;
%}
left_arrow   "<"
right_arrow  ">"
slash        "/"
and          "and"
or           "or"
not          "not"
true         "true"
false        "false"
blank        [ \t]*
tag_and      ({left_arrow}{and}{right_arrow})
tag_or       ({left_arrow}{or}({blank}?){right_arrow})
tag_not      ({left_arrow}{not}({blank}?){right_arrow})
Endtag_and   ({left_arrow}{slash}{and}{right_arrow})
Endtag_or    ({left_arrow}{slash}({blank}?){or}({blank}?){right_arrow})
Endtag_not   ({left_arrow}{slash}({blank}?){not}({blank}?){right_arrow})
tag_true     ({left_arrow}{true}{slash}{right_arrow})
tag_false    ({left_arrow}{false}{slash}{right_arrow})    
%%
{tag_and}    { depth++; yylval.intVal = depth*10 + 1; return Start_Tag; }
{tag_or}     { depth++; yylval.intVal = depth*10 + 2; return Start_Tag; }
{tag_not}    { depth++; yylval.intVal = depth*10 + 3; return Start_Tag; }
{Endtag_and} { return End_Tag; }
{Endtag_or}  { return End_Tag; }
{Endtag_not} { return End_Tag; }
{tag_false}  { yylval.intVal = 1; return SC_Tag; }
{tag_true}   { yylval.intVal = 2; return SC_Tag; }

\n      {;}
[ \t]+  {;}
.       { return(yytext[0]); }
%%

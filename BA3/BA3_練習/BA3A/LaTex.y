%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void yyerror(const char *message);

double  cal[100];
int cal_pointer=0;

%}
%union {
float ival;
}


%token UPPER ADD SUB FRAC L_par R_par
%token <ival> INUMBER
%type <ival> expr

%left ADD SUB
%right UPPER

%%
line    : expr line             {
                                    printf("%.3lf\n",$1);
                                }             
        |
        ;

expr    : INUMBER               {
                                    
                                    $$ = $1;
                                }
        | expr UPPER expr       {
                                    $$ = pow($1, $3);
                                }
        
        | L_par expr R_par      {
                                    
                                    $$ = $2;
                                }
       
        | expr ADD expr   { 
                                    $$ = $1 + $3;
                                }
        
        | expr SUB expr   { 
                                    $$ = $1 - $3;
                                }
        | FRAC L_par expr R_par L_par expr R_par {
                                    $$ = $3 / $6;
                                }
        ;
%%
void yyerror (const char *message)
{
        fprintf (stderr, "%s\n",message);
}

int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}

%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool flag = true;
void yyerror(const char *message);

int mat_row=0;
int mat_col=0;
int mat1_row=0;
int mat1_col=0;
int mat2_row=0;
int mat2_col=0;

void Sem_error(const int pos){
        printf("Semantic error on col %d\n",pos);
}

%}
%union {
int ival;
}
 
%token LEFT_PAR RIGHT_PAR LEFT_BRAC RIGHT_BRAC COM ADDITION SUBTRACTION MULTIPLICATION TRANSPOSE INUMBER
%type <ival> ADDITION
%type <ival> SUBTRACTION
%type <ival> MULTIPLICATION
%type <ival> INUMBER
%type <ival> expr

%left ADDITION SUBTRACTION
%left MULTIPLICATION
%%

SingleLine      : expr        
                ;

expr            : expr ADDITION expr            {
                                                       if($1 == $3){
                                                               $$ = $3;
                                                       }else{
                                                               flag = false;
                                                               Sem_error($2);
                                                               return 0;
                                                       }
                                                }
                | expr SUBTRACTION expr         {
                                                        if($1 == $3){
                                                                $$ = $3;
                                                        }else{
                                                                flag = false;
                                                                Sem_error($2);
                                                                return 0;
                                                        }
                                                }
                | expr MULTIPLICATION expr      {
                                                        mat1_row = $1 / 10;
                                                        mat1_col = $1 % 10;
                                                        mat2_row = $3 / 10;
                                                        mat2_col = $3 % 10;
                                                        if(mat1_col == mat2_row){
                                                                $$ = (mat1_row * 10) + (mat2_col);
                                                        }else{
                                                                flag = false;
                                                                Sem_error($2);
                                                                return 0;
                                                        }
                                                }
                | LEFT_PAR expr RIGHT_PAR       {
                                                        $$ = $2;
                                                }
                | expr TRANSPOSE                {
                                                        mat_row = $1 / 10; 
                                                        mat_col = $1 % 10; 
                                                        $$ = (mat_col * 10) + (mat_row);
                                                }
                | LEFT_BRAC INUMBER COM INUMBER RIGHT_BRAC {
                                                        $$ = ($2 * 10) + $4;
                                                }
                ;
%%
void yyerror (const char *message)
{
        fprintf (stderr, "%s\n",message);
}


int main(int argc, char *argv[]) {
        yyparse();
        if(flag == true){
                printf("Accepted\n");
        }
        return(0);
}

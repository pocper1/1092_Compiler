%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void yyerror(const char *message);

int cal[100];
int cal_pointer=0;

bool flag = true;
bool Syn_flag = true;
bool has_print = false;

void error_message(int n){
    flag = false;
    if(Syn_flag == true && flag == false){
        printf("Semantic error on col %d\n", n);

    }
}
void syntax_message(){
    if(Syn_flag == false && has_print == false)
        printf("Syntax Error\n");
        has_print= true;
}
%}
%union {
int ival;
}

%token <ival> L_a R_a L_par R_par Trans ADD MUL COM
%token <ival> INUMBER
%type <ival> expr

%left ADD MUL
%right Trans
%%
line    : expr line             {
                                    if(flag == true){
                                        int tmp,tmp1;
                                        tmp = $1 / 10;
                                        tmp1 = $1 % 10;
                                        printf("%d %d\n",tmp,tmp1);
                                    }
                                }       
        |
        ;

expr    : L_a INUMBER COM INUMBER R_a { 
                                    if($2 == 0 || $4 == 0){
                                        Syn_flag = false;
                                        syntax_message();

                                    }else{
                                        $$ = $2 * 10 + $4;
                                    }

                                }
        | expr Trans            { 
                                    int tmp,tmp1;
                                    tmp = $1 / 10;
                                    tmp1 = $1 % 10;
                                    $$ = tmp1 * 10 + tmp;
                                }
        | expr ADD expr         { 
                                    int tmp,tmp1, tmp2, tmp3;
                                    tmp = $1 / 10;
                                    tmp1 = $1 % 10;
                                   
                                    tmp2 = $3 / 10;
                                    tmp3 = $3 % 10;

                                    if(tmp == tmp2 && tmp1 == tmp3){
                                        $$ = (tmp + tmp2) * 10 + (tmp1+tmp3);
                                    }else{
                                       error_message($2); 
                                    }
                                }
        | expr MUL expr         { 
                                    int tmp,tmp1, tmp2, tmp3;
                                    tmp = $1 / 10;
                                    tmp1 = $1 % 10;

                                    tmp2 = $3 / 10;
                                    tmp3 = $3 % 10;
                                    if(tmp1 == tmp2){
                                        $$ = tmp * 10 + tmp3;
                                    }else{
                                       error_message($2); 
                                    }
                                }
        | L_par expr R_par      { 
                                    $$ = $2;
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

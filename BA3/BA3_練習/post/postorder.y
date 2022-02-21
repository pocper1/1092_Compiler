%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void yyerror(const char *message);

float cal[100];
int cal_pointer=0;
bool flag = true;

void error_message(){
    flag = false;
    printf("Wrong Formula\n");
}
%}
%union {
float ival;
}
 
%token ADD SUB MUL DIV

%token <ival> INUMBER

%type <ival> expr
%%
line    : expr line
        |
        ;
expr    : INUMBER               {
                                    cal[cal_pointer] = $1;
                                    cal_pointer++;
                                }
        | ADD                   {
                                    if(cal_pointer >= 2){
                                        float tmp = cal[cal_pointer-2];
                                        cal[cal_pointer-2] = cal[cal_pointer-1]+ tmp;
                                        cal[cal_pointer-1] = 0;
                                        cal_pointer--;
                                    }else{
                                        error_message();
                                    }
                                    

                                }
        | SUB                   {
                                    if(cal_pointer>= 2){
                                        float tmp = cal[cal_pointer-2];
                                        cal[cal_pointer-2] = cal[cal_pointer-1] - tmp;
                                        cal[cal_pointer-1] = 0;
                                        cal_pointer--;
                                    }else{
                                        error_message();
                                    }
                                    

                                }
        | MUL                   {
                                    if(cal_pointer >= 2){
                                        float tmp = cal[cal_pointer-2];
                                        cal[cal_pointer-2] = cal[cal_pointer-1] * tmp;
                                        cal[cal_pointer-1] = 0;
                                        cal_pointer--;
                                    }else{
                                        error_message();
                                    }
                                    
                                }
        | DIV                   {
                                    if(cal_pointer >= 2){
                                        float tmp = cal[cal_pointer-2];
                                        
                                        cal[cal_pointer-2] = tmp / cal[cal_pointer-1];
                                        cal[cal_pointer-1] = 0;
                                        cal_pointer--;
                                    }else{
                                        error_message();
                                    }
                                   
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
            printf("%.1f\n", cal[0]);
        }
        return(0);
}

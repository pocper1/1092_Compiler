%{
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    void yyerror(const char *message);
    int cal[100];
    int cal_pointer = 0;
    bool flag = true;
%}
%union {
    int ival;
}

%token ADD
%token SUB
%token MUL
%token MOD
%token LOAD
%token INC
%token DEC
%token <ival> INUMBER
%type <ival> expr
%%

SingleLine : expr SingleLine
        | 
        ;

expr    : LOAD INUMBER  {
                            cal[cal_pointer] = $2;
                            // printf("load pointer: %d %d\n",cal_pointer,cal[cal_pointer]);
                            cal_pointer++;
                        }
        | ADD           {
                            if(cal_pointer >= 2){
                                int tmp = cal[cal_pointer-2];
                                cal[cal_pointer-2] = cal[cal_pointer-1] + tmp;
                                cal[cal_pointer-1] = 0;
                                cal_pointer--;
                                // printf("add pointer: %d %d\n",cal_pointer,cal[cal_pointer]);
                            }
                            else{
                                flag = false;
                            }
                        }
        | SUB           {
                            if(cal_pointer >= 2){
                                int tmp = cal[cal_pointer-2];
                                cal[cal_pointer-2] = cal[cal_pointer-1] - tmp;
                                cal[cal_pointer-1] = 0;
                                cal_pointer--;
                                // printf("sub pointer: %d %d\n",cal_pointer,cal[cal_pointer]);
                            }else{
                                flag = false;
                            }
                        }
        | MUL           {
                            if(cal_pointer >= 2){
                                int tmp = cal[cal_pointer-2];
                                cal[cal_pointer-2] = cal[cal_pointer-1] * tmp;
                                cal[cal_pointer-1] = 0;
                                cal_pointer--;
                            }else{
                                flag = false;
                            }
                        }
        | MOD           {
                            if(cal_pointer >= 2){
                                int tmp = cal[cal_pointer-2];
                                cal[cal_pointer-2] = cal[cal_pointer-1] % tmp;
                                cal[cal_pointer-1] = 0;
                                cal_pointer--;
                            }else{
                                flag = false;
                            }
                        }
        | INC           {
                            if(cal_pointer >= 1){
                                cal[cal_pointer-1]++;
                            }else{
                                flag = false;
                            }
                        }
        | DEC           {
                            if(cal_pointer >= 1){
                                cal[cal_pointer-1]--;
                            }else{
                                flag = false;
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

    if(cal_pointer == 1 && flag == true) {
        printf("%d\n", cal[cal_pointer-1]);
    }
    else{
        printf("Invalid format\n");
    }

    return(0);
}

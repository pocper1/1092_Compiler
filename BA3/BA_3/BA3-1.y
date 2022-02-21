%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void yyerror(const char *message);

int cal[100];
int cal_pointer=0;


void print_func(){
    printf("%d\n",cal[cal_pointer-1]);
}

%}
%union {
int ival;
}
 
%token PUSH INVERSE INC DEC

%token <ival> INUMBER

%type <ival> expr
%%
line    : expr line
        |
        ;
expr    : PUSH INUMBER          {
                                    cal[cal_pointer] = $2;
                                    cal_pointer++;
                                }
        | INVERSE               {
                                    int tmp, tmp1;
                                    tmp = cal[cal_pointer -1];
                                    tmp1 = cal[cal_pointer - 2];
                                    // printf("tmp: %d tmp1:%d",tmp,tmp1);
                                    cal[cal_pointer-1] = tmp1;
                                    cal[cal_pointer - 2] = tmp;
                                }
        | INC                   {
                                    cal[cal_pointer-1]++; 
                                }
        | DEC                   {
                                    cal[cal_pointer-1]--; 
                                }
        ;
%%
void yyerror (const char *message)
{
        fprintf (stderr, "%s\n",message);
}

int main(int argc, char *argv[]) {
        yyparse();
        print_func();
        
        return(0);
}

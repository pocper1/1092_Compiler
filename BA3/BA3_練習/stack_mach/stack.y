%{
#include <stdio.h>
#include <string.h>
void yyerror(const char *message);
int cal[100];
int cal_pointer = 0;
int flag = 1;
%}
%union {
int ival;
}
 
%token ADD SUB MUL DIV MOD INC DEC LOAD COPY DELETE SWITCH

%token <ival> INUMBER
%type <ival> expr
%%
line    : expr line
        |
        ;
expr    : LOAD INUMBER          {
                                    
                                    cal[cal_pointer] = $2;
                                    cal_pointer++;

                                }
        | ADD                   {
                                    int tmp = cal[cal_pointer-2];
                                    cal[cal_pointer-2] = cal[cal_pointer-1]+ tmp;
                                    cal[cal_pointer-1] = 0;
                                    cal_pointer--;

                                }
        | SUB                   {
                                    int tmp = cal[cal_pointer-2];
                                    cal[cal_pointer-2] = cal[cal_pointer-1] - tmp;
                                    cal[cal_pointer-1] = 0;
                                    cal_pointer--;

                                }
        | DIV                   {
                                    int tmp = cal[cal_pointer-2];
                                    if(tmp == 0){
                                        printf("Divide by zero\n");
                                        flag = 0;
                                    }else{
                                        cal[cal_pointer-2] = cal[cal_pointer-1] / tmp;
                                        cal[cal_pointer-1] = 0;
                                        cal_pointer--;
                                    }
                                }
        | MUL                   {

                                    int tmp = cal[cal_pointer-2];
                                   
                                    cal[cal_pointer-2] = cal[cal_pointer-1] * tmp;
                                    cal[cal_pointer-1] = 0;
                                    cal_pointer--;
                                    
                                    

                                }
        | MOD                   {

                                    int tmp = cal[cal_pointer-2];
                                    cal[cal_pointer-2] = cal[cal_pointer-1] % tmp;
                                    cal[cal_pointer-1] = 0;
                                    cal_pointer--;
                                    
                                    

                                }
        | DEC                   {
                                    printf("cal_pointer: %d",cal[cal_pointer-1]);
                               

                                    cal[cal_pointer-1]--;
                                    
                                }
        | INC                   {
                                
                                     cal[cal_pointer-1]++;

                                }
        | DELETE                   {
                                
                                     cal[cal_pointer-1] = 0;
                                    cal_pointer--;

                                }
        | COPY                  {
                                    int tmp = cal[cal_pointer-1];
                                   cal[cal_pointer] = tmp;
                                   cal_pointer++;
                                   
                                   

                                }
        | SWITCH                {
                                    if(cal_pointer >= 3 ){
                                        int tmp = cal[cal_pointer-1];
                                        int tmp1 = cal[cal_pointer-2];
                                        cal[cal_pointer-2 ] = tmp1;
                                        cal[cal_pointer-1] = tmp;
                                    }else{
                                        flag = 0;
                                        printf("Invalid format\n");
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
        if(flag == 1){
            printf("cal_pointer:%d\n", cal_pointer);
            printf("%d\n", cal[0]);

        }
        return(0);
}

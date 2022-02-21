%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void yyerror(const char *message);

int cal[100];
int tmp[100];
int cal_pointer=0;
int tmp_pointer=0;
int mul_d = 1;
%}
%union {
int ival;
}

%token ADDITION MULTIPLY LBRACKET RBRACKET COMMA

%token <ival> DIGITS

%%
S : Sum                                         
Sum : Term ADDITION Sum                 {
                                                // printf("via add\n");
                                                // printf("b tmp_pointer: %d\n",tmp_pointer);
                                                int i=0;
                                                for(i=0;i<tmp_pointer;i++){
                                                        tmp[i] =0;
                                                }
                                                
                                                tmp_pointer=0;
                                                // printf("a tmp_pointer: %d\n",tmp_pointer);
                                        
                                        }                       
        | Term                          {
                                                
                                        }

Term : List MULTIPLY MulDigit           {
                                                
                                                // 次數
                                                int i=0,j=0;
                                                // printf("3mul_d %d\n",mul_d);
                                                // printf("1tmp_pointer %d\n",tmp_pointer);
                                                
                                                
                                                for(j=0;j<mul_d-1;j++){
                                                        for(i=0;i<tmp_pointer;i++){
                                                                cal[cal_pointer] = tmp[i];
                                                                cal_pointer++;
                                                        }
                                                }

                                                for(i=0;i<tmp_pointer;i++){
                                                        tmp[i] =0;
                                                }
                                                tmp_pointer=0;

                                                mul_d = 1;
                                                
                                        
                                        }
        | MulDigit MULTIPLY List        {
                                                // 次數
                                                int i=0,j=0;
                                                // printf("3mul_d %d\n",mul_d);
                                                // printf("2tmp_pointer %d\n",tmp_pointer);
                                                
                                                for(j=0;j<mul_d-1;j++){
                                                        for(i=0;i<tmp_pointer;i++){
                                                                cal[cal_pointer] = tmp[i];
                                                                cal_pointer++;
                                                        }
                                                }

                                                for(i=0;i<tmp_pointer;i++){
                                                        tmp[i] =0;
                                                }
                                                tmp_pointer=0;

                                                mul_d = 1;
                                        }
        | MulDigit MULTIPLY List MULTIPLY MulDigit {
                                                
                                                // 次數
                                                int i=0,j=0;
                                                // printf("3mul_d %d\n",mul_d);
                                                // printf("3tmp_pointer %d\n",tmp_pointer);
                                                for (j=0;j<mul_d-1;j++){
                                                        for(i=0;i<tmp_pointer;i++){
                                                                cal[cal_pointer] = tmp[i];
                                                                cal_pointer++;
                                                        }
                                                }

                                                for(i=0;i<tmp_pointer;i++){
                                                        tmp[i] =0;
                                                }
                                                tmp_pointer=0;

                                                mul_d = 1;
                                                
                                        }
        | List                          {
                                                int i=0;
                                                for(i=0;i<tmp_pointer;i++){
                                                        tmp[i] =0;
                                                }
                                        tmp_pointer=0;  
                                        }                    

MulDigit : MulDigit MULTIPLY DIGITS
        | DIGITS                        {
                                                // printf("mul_d: %d\n",$1);
                                                mul_d *= $1;
                                        }

List : LBRACKET ListItem RBRACKET       {
                                                
                                                // printf("af tmp_pointer: %d\n",tmp_pointer);
                                                int i=0;
                                                for(i=0;i<tmp_pointer/2;i++){
                                                       int tmp1,tmp2;
                                                       tmp1 = tmp[tmp_pointer - i -1];
                                                       tmp2 = tmp[i];
                                                       tmp[i] = tmp1;
                                                       tmp[tmp_pointer - i - 1] = tmp2;
                                                }

                                                
                                                for(i=0;i<tmp_pointer;i++){
                                                        cal[cal_pointer] = tmp[i];
                                                        cal_pointer++;
                                                }
                                               
                                                // tmp_pointer=0;
                                        }

ListItem : DIGITS COMMA ListItem        {
                                                tmp[tmp_pointer] = $1;
                                                tmp_pointer++;
                                        }
        | DIGITS                        {
                                                
                                                tmp[tmp_pointer] = $1;
                                                tmp_pointer++;
                                                
                                                
                                        }

%%
void yyerror (const char *message)
{
        fprintf (stderr, "%s\n",message);
}

int main(int argc, char *argv[]) {
        yyparse();
        int i=0;
        printf("[");
        for(i=0;i<cal_pointer;i++){
                if(i != cal_pointer-1){
                        printf("%d, ",cal[i]);
                }else{
                        printf("%d",cal[i]);
                }
        }               
        printf("]\n");
                                        
        return(0);
}

%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void yyerror(const char *message);

char variable[100][100];        //存變數
int variable_ind = 0;

int variable_val[100];          // 存值
int val_poi = 0;
int LEquR = 1;                  //判斷左 = 右

void boolFunc(int v){

        if(v == 1){
                printf("#t\n");
        } else{
                printf("#f\n");
        }
}

void store_var(char* n, int n_val){
        strcpy(variable[variable_ind],n); 
        variable_val[variable_ind] = n_val; 
        variable_ind++; 
        // printf("this is def stmt n:%s\n",n);
        // printf("this is def stmt n_v:%d\n",n_v);
}
int selectVariable(char* var){
        int i=0,tmp_val=-1;
        for(i=0;i<variable_ind; i++){
                if(!strcmp(variable[i], var)){
                        tmp_val = variable_val[i]; 
                        break;
                }
        }
        return tmp_val;
}
%}

%union {
int intval;
char* String;
}

%type <intval> EXP 
%type <intval> NUM_OP PLUS MINUS MULTIPLY DIVIDE MODULUS
%type <intval> PLUS_EXPS MULTIPLY_EXPS
%type <intval> LOGICAL_OP AND_OP AND_EXPS OR_OP OR_EXPS NOT_OP
%type <intval> GREATER SMALLER EQUAL EQUAL_EXPS
%type <intval> IF_EXP TEST_EXP THEN_EXP ELSE_EXP
%type <intval> bool_val number

%type <String> ID VARIABLE 

%token plu min mul Div mod
%token gre sml eql 

%token and or Not IF
%token define
%token L_par R_par
%token PrintOfNum PrintOfBool
%token number ID bool_val
%%

PROGRAM         : STMTS
                ;

STMTS           : STMT STMTS
                | STMT
                ;

STMT            : EXP
                | DEF_STMT
                | PRINT_STMT
                ;


PRINT_STMT      : L_par PrintOfNum EXP R_par {printf("%d\n",$3);}
                | L_par PrintOfBool EXP R_par { boolFunc($3);}
                ;
EXP             : number        {$$ = $1;}
                | bool_val
                | VARIABLE      { $$ = selectVariable($1); }

                | NUM_OP        {$$ = $1;}   
                | LOGICAL_OP    {$$ = $1;}
                // | FUN_EXP
                // | FUN_CALL
                | IF_EXP        {$$ = $1;}
                ;
NUM_OP          : PLUS          {$$ = $1;}
                | MINUS         {$$ = $1;}
                | MULTIPLY      {$$ = $1;}
                | DIVIDE        {$$ = $1;}
                | MODULUS       {$$ = $1;}
                | GREATER       {$$ = $1;}
                | SMALLER       {$$ = $1;}
                | EQUAL         {$$ = $1;}
                ;

// numbers operator
PLUS            : L_par plu EXP PLUS_EXPS R_par { $$ = $3 + $4; }
                ;

PLUS_EXPS       : EXP PLUS_EXPS {$$ = $1 + $2; }
                | EXP   {$$ = $1; }
                ;

MINUS           : L_par min EXP EXP R_par { $$ = $3 - $4; }
                ;

MULTIPLY        : L_par mul EXP MULTIPLY_EXPS R_par { $$ = $3 * $4; }
                ;

MULTIPLY_EXPS   : EXP MULTIPLY_EXPS     {$$ = $1 * $2; }
                | EXP   {$$ = $1;}
                ;

DIVIDE          : L_par Div EXP EXP R_par { $$ = $3 / $4; }
                ;

MODULUS         : L_par mod EXP EXP R_par { $$ = $3 % $4; }
                ;


GREATER         : L_par gre EXP EXP R_par {if($3 > $4){$$ = 1;}else{$$ = 0;}}
                ;


SMALLER         : L_par sml EXP EXP R_par {if($3 < $4){$$ = 1;}else{$$ = 0;}}
                ;

EQUAL           : L_par eql EXP EQUAL_EXPS R_par {if($3 == $4){$$ = 1;}else{$$ = 0;} if(LEquR == 0){$$ = 0;}}
                ;

EQUAL_EXPS      : EXP EQUAL_EXPS {if($1 != $2){LEquR = 0;}$$ = $1;}
                | EXP {$$ = $1;}
                ;
// numbers operator end

// logical operator start
LOGICAL_OP      : AND_OP  {$$ = $1;}
                | OR_OP {$$ = $1;}
                | NOT_OP {$$ = $1;}
                ;
AND_OP          : L_par and EXP AND_EXPS R_par {$$ = $3 * $4;}
                ;
AND_EXPS        : EXP AND_EXPS {$$ = $1 * $2;}
                | EXP {$$ = $1;}
                ;

OR_OP           : L_par or EXP OR_EXPS R_par { int flag = 0;if($3 == 1 || $4 == 1){flag = 1;} $$ = flag;}
                ;

OR_EXPS         : EXP OR_EXPS {int flag = 0;if($1 == 1 || $2 == 1){flag = 1;} $$ = flag;}
                | EXP {$$ = $1;}
                ;

NOT_OP          : L_par Not EXP R_par {$$ = !$3;}
                ;
DEF_STMT        : L_par define VARIABLE EXP R_par { store_var($3,$4); }
                ;
VARIABLE        : ID {strcpy($$,$1);}
                ;
// logical operator end

// functions start
// FUN_EXP         : L_par FUN_IDS FUN_BODY R_par {printf("fun_exp\n");}
//                 ;
// FUN_IDS         : L_par ID IDS R_par
//                 ;

// IDS             : ID IDS
//                 | ID
//                 ;
        
// FUN_BODY        : EXP

// FUN_CALL        : L_par FUN_EXP PARAM R_par 
//                 | L_par FUN_NAME PARAM R_par
//                 ;
       
// PARAM           : EXP PARAM
//                 | EXP
//                 | ;

// LAST_EXP        : EXP
//                 ;
// FUN_NAME        : ID
//                 ;
// functions start end

// if test then else start
IF_EXP          : L_par IF TEST_EXP THEN_EXP ELSE_EXP R_par {if($3 == 1){$$ = $4;} else{$$ = $5;}}
                ;
TEST_EXP        : EXP {$$ = $1;}
                ;
THEN_EXP        : EXP {$$ = $1;}
                ;
ELSE_EXP        : EXP {$$ = $1;}
                ;

// if test then else end
%%
void yyerror (const char *message)
{
        fprintf (stderr, "%s\n",message);
}

int main(int argc, char *argv[]) {
        yyparse();                                        
        return(0);
}

%{
#include <stdio.h>
#include <string.h>
#include <math.h>
int yylex();
int a[5] = {0};
int b[5] = {0};
int c[5] = {0};
void yyerror(const char* message) {
    printf("Invaild format\n");
};
int Xor(int A, int B);
%}

%union {
    int intVal;
}

%token OPERATORS NUMBER
%type <intVal> OPERATORS NUMBER
%type <intVal> expression

%%
line
    : expression    { printf("%d",$1);}
    ;

expression
    : OPERATORS expression NUMBER {
          if( $1==3 ){  // xor
	          $$ = Xor($2,$3);
			  for( int i=4 ; i>=0 ; i-- ){
	             a[i] = 0;
		         b[i] = 0;
	          }
	      }
    }
	| OPERATORS NUMBER NUMBER {
	      if( $1==3 ){  // xor
	          $$ = Xor($2,$3);
			  for( int i=4 ; i>=0 ; i-- ){
	             a[i] = 0;
		         b[i] = 0;
	          }
	      }
	
	}
    ;
%%
int Xor(int A, int B){
    for( int i=4 ; i>=0 ; i-- ){
	    a[i] = A%2;
		A = A/2;
	}
	for( int i=4 ; i>=0 ; i-- ){
	    b[i] = B%2;
		B = B/2;
	}
	for( int i=4 ; i>=0 ; i-- ){
	    if(a[i]!=b[i])
		    c[i] = 1;
		else 
		    c[i] = 0;
	
	int temp;
	for( int i=4 ; i>=0 ; i-- ){
	    if(c[i]==1){
		    temp = temp + pow(2,4-i);
		}
	}
	return temp;
}
int main(int argc, char *argv[]) {
    yyparse();
    return(0);
}

#compile bison
bison -d -o LaTex.tab.c LaTex.y	
gcc -c -g -I.. LaTex.tab.c
#compile flex
flex -o lex.yy.c LaTex.l
gcc -c -g -I.. lex.yy.c
#compile and link bison and flex
gcc -o LaTex LaTex.tab.o lex.yy.o -ll -lm

./LaTex < ../test2.txt

#compile bison
bison -d -o matrix.tab.c matrix.y	
gcc -c -g -I.. matrix.tab.c
#compile flex
flex -o lex.yy.c matrix.l
gcc -c -g -I.. lex.yy.c
#compile and link bison and flex
gcc -o matrix matrix.tab.o lex.yy.o -ll -lm

./matrix < ../test2.txt

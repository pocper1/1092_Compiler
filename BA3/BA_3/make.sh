#compile bison
bison -d -o BA3-2.tab.c BA3-2.y	
gcc -c -g -I.. -std=c99 BA3-2.tab.c
#compile flex
flex -o lex.yy.c BA3-2.l
gcc -c -g -I.. lex.yy.c
#compile and link bison and flex
gcc -o  BA3-2 BA3-2.tab.o lex.yy.o -ll

./BA3-2 < ./test2.txt


#compile bison
bison -d -o 108403529_2.tab.c 108403529_2.y	
gcc -c -g -I.. 108403529_2.tab.c
#compile flex
flex -o lex.yy.c 108403529_2.l
gcc -c -g -I.. lex.yy.c
#compile and link bison and flex
gcc -o 108403529_2 108403529_2.tab.o lex.yy.o -ll

./108403529_2 < ./test2.txt

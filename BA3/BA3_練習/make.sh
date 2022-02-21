#compile bison
bison -d -o postorder.tab.c postorder.y	
gcc -c -g -I.. postorder.tab.c
#compile flex
flex -o lex.yy.c postorder.l
gcc -c -g -I.. lex.yy.c
#compile and link bison and flex
gcc -o postorder postorder.tab.o lex.yy.o -ll

./postorder < ./test2.txt

#compile bison
bison -d -o MiniLsp.tab.c MiniLsp.y	
gcc -c -g -I.. MiniLsp.tab.c
#compile flex
flex -o lex.yy.c MiniLsp.l
gcc -c -g -I.. lex.yy.c
#compile and link bison and flex
gcc -o  MiniLsp MiniLsp.tab.o lex.yy.o -ll

./MiniLsp < ./testcase/0110/06_2_hidden.lsp
# ./MiniLsp < ./testcase/test_data/test.txt


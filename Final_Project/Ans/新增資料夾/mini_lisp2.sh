bison -d -o mini_lisp2.tab.c mini_lisp2.y
g++ -c -g -I.. mini_lisp2.tab.c
flex -o lex.yy.c mini_lisp2.l
g++ -c -g -I.. lex.yy.c
g++ -o mini_lisp2 mini_lisp2.tab.o lex.yy.o -ll


# ./a.out < mini_lisp2.in

for file in ./test_data/*
do
    # ./smli < "$file"
    # echo -e "\n<!-------- ${file##*/} --------!>\n"
    echo -e "\n--------------\n"
    cat "$file"
    echo -e "\noutput =>\n"
    ./mini_lisp2 < "$file"
done

echo ""

rm mini_lisp2.tab.c
rm mini_lisp2.tab.h
rm mini_lisp2.tab.o
rm lex.yy.c
rm lex.yy.o
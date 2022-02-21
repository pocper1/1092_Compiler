bison -d Minilsp.y
gcc -c -g -I.. Minilsp.tab.c
flex Minilsp.l
gcc -c -g -I.. lex.yy.c
gcc -o Minilsp Minilsp.tab.o lex.yy.o -ll

# ./a.out < Final-MiniLisp.in

for file in ./test_data/*
do
    # ./smli < "$file"
    # echo -e "\n<!-------- ${file##*/} --------!>\n"
    echo -e "\n--------------\n"
    cat "$file"
    echo -e "\noutput =>\n"
    ./Minilsp < "$file"
done

echo ""

rm Minilsp.tab.c
rm Minilsp.tab.h
rm Minilsp.tab.o
rm lex.yy.c
rm lex.yy.o
rm Minilsp
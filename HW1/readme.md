### HW1_1 ParserTest
> Description
> Please write a program to read a program source from stdin following the token definition and grammar rule at right.
> If Yes, print each token’s type and the string of token seperated by a whitespace “ ” and end with a newline.
> If No, print only “invalid input” with a newline. (don’t output any token!)
> Your program has to check the source whether it follows the token and grammar rules or not.

> Required-> Recursive-Decent-Parsing
####  Productions
> 1. program → stmts
> 2. stmts → stmt stmts
> 3. stmts → λ
> 4. stmt → primary
> 5. stmt → STRLIT
> 6. stmt → λ
> 7. primary → ID primary_tail
> 8. primary_tail → DOT ID primary_tail
> 9. primary_tail → LBR stmt RBR primary_tail
> 10. primary_tai → λ


### HW1_2 ScannerTest
> Description
> 在 編譯器中， token 是組成程式的最小單位，需要由 Scanner 先把 input text 按照規則轉為 Token ，才能讓 Parser 進行處理。請依照題目規則，試著寫一個 Scanner 來取得 Tokens 並印出。
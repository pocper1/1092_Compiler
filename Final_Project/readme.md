### 編譯器期末作業
```
撰寫語言：yacc、lex
```

### 邏輯
- 輸入的字串會先丟到lex做解析，解析一個一個token，解析完之後放到yacc

---
### 完成：
1. Syntax Validation
2. Print
3. Numerical Operations
4. Logical Operations
5. if Expression
6. Variable Definition

---
程式邏輯：放進去yacc，會先遇到program
- 拆解STMTS
- 然後STMT再去做EXP運算，或者PRINT_STMT，等等動作
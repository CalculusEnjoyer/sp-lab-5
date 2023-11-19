syntax: calculator.y
	bison -H calculator.y

lexer: calculator.l
	lex calculator.l

calculator: syntax lexer helpers.c helpers.h tree.c tree.h
	gcc lex.yy.c calculator.tab.c helpers.c tree.c -ocalculator -lm

clean:
	rm calculator lex.yy.c calculator.tab.c calculator.tab.h
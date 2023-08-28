wordlang: wordlang.y wordlang.l
	bison -d wordlang.y
	flex wordlang.l
	gcc -o wordlang lex.yy.c wordlang.tab.c utils.c

clean: 
	rm -f wordlang wordlang.exe wordlang.tab.* lex.yy.*

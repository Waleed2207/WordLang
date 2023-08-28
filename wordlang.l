 
 /* Modern versions of flex let you say %option noyywrap at the top of your scanner to tell it not to call yywrap. */
%option noyywrap

%{
#define YYSTYPE void*		// defines YYSTYPE to be void*, so all of the symbol values are pointers (strings or structures). Used only when necessary.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordlang.tab.h"

void terminate(const char* message, int exitCode) {
    fprintf(stderr, "Error: %s\n", message);
    exit(exitCode);
}
%}

%x COMMENTS
%{

char* copyWithoutSeparators(const char *strOrg);
%}

 /* Definition of names. */

white       [ \n\t\r]+
integer     [0-9]+
id          [a-zA-Z_][a-zA-Z0-9]{0,31}

character   [^ \"\'\^]
word        {character}+
sentence    {word}(" "{word})*

%%

 /* Definition of patterns. */

<INITIAL>"//"        { BEGIN(COMMENTS); }
<COMMENTS>(.)        { /* Nothing to do */ }
<COMMENTS><<EOF>>    { yyterminate(); }
<COMMENTS>"\n"       { BEGIN(INITIAL); }

"char"      { return TOK_CHAR; }
"int"       { return TOK_INT; }
"sentence"  { return TOK_SENT; }
"word"      { return TOK_WORD; }

"else"     { return TOK_ELSE; }
"if"       { return TOK_IF; }
"input"    { return TOK_INPUT; }
"loop"     { return TOK_LOOP; }
"output"   { return TOK_OUTPUT; }
"while"    { return TOK_WHILE; }

{white}     { /*Nothing*/ }

"("    { return TOK_LPAR; }
")"    { return TOK_RPAR; }
"{"    { return TOK_LCBRACK; }
"}"    { return TOK_RCBRACK; }
"+"    { return TOK_PLUS; }
"-"    { return TOK_MINUS; }
"#"    { return TOK_CONCAT; }
":"    { return TOK_INDEX; }
";"    { return TOK_SEMI; }
","    { return TOK_COMMA; }
"!"    { return TOK_NEG; }
"="    { return TOK_ASSIGN; }
"<"    { return TOK_LT; }
">"    { return TOK_GT; }
"=="   { return TOK_EQ; }
"!="   { return TOK_NQ; }
"<="   { return TOK_LE; }
">="   { return TOK_GE; }

{integer}    { yylval = (char*)malloc(yyleng + 1); strcpy(yylval, yytext); return TOK_NUMINT; }

{id} {
    if (yyleng > 32) {
        terminate("Error, variable can't be more than 32 characters", 1);
    }
    yylval = (char*)malloc(yyleng + 1);
    strcpy(yylval, yytext);
    return TOK_ID;
}

\'{character}?\'    { yylval = copyWithoutSeparators(yytext); return TOK_STRCHAR; }
\"{word}?\"         { yylval = copyWithoutSeparators(yytext); return TOK_STRWORD; }
\^{sentence}?\^     { yylval = copyWithoutSeparators(yytext); return TOK_STRSENT; }

.      { return TOK_ERROR; }		/* Rest of the characters that do not match the previous patterns */

%%

char* copyWithoutSeparators(const char *strOrg)
{
    char *strDst;
    int size = 1;

    if(strlen(strOrg) > 2) {
        size = (strlen(strOrg) - 2) + 1;
    }

    strDst = (char *) malloc(size * sizeof(char));

    if(strDst != NULL) {
        if(size > 1) {
            strncpy(strDst, strOrg+1, size-1);
        }
        strDst[size-1] = '\0';

        //free(strDst);
    }

    return strDst;
}

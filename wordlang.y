
%{
#define YYSTYPE void*		// defines YYSTYPE to be void*, so all of the symbol values are pointers (strings or structures). Used only when necessary.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yylex(void);
void yyerror(const char *s);

 /* Declaration of variables used for error handling and for validation during analysis. */

void showResult(StTreeNode *tree);
void showError();
%}

/* declare tokens */
%token TOK_NUMINT TOK_STRCHAR TOK_STRWORD TOK_STRSENT
%token TOK_LPAR TOK_RPAR TOK_LCBRACK TOK_RCBRACK TOK_CHAR TOK_INT TOK_SENT TOK_WORD
%token TOK_PLUS TOK_MINUS TOK_CONCAT TOK_INDEX TOK_NEG TOK_SEMI TOK_COMMA
%token TOK_ASSIGN TOK_LT TOK_GT TOK_EQ TOK_NQ TOK_LE TOK_GE
%token TOK_ELSE TOK_IF TOK_INPUT TOK_LOOP TOK_OUTPUT TOK_WHILE
%token TOK_ID
%token TOK_ERROR


%right  TOK_ASSIGN
%left   TOK_CONCAT TOK_PLUS TOK_MINUS
%left   TOK_INDEX
%left   TOK_LPAR TOK_RPAR

%nonassoc   TOK_LOWER_THAN_ELSE
%nonassoc   TOK_ELSE

%start Input

%%

Input : /* Empty */
      | Program { showResult((StTreeNode*)$1); }
      | error { showError(); }
;

Program : StatementList { $$ = $1; }
;

Block : TOK_LCBRACK StatementList TOK_RCBRACK { $$ = $2; }
      | Statement { $$ = $1; }
;

StatementList : StatementList Statement { $$ = joinNode($1, $2); }
              | Statement { $$ = $1; }
;

Statement : Declarator TOK_SEMI { $$ = $1; }
          | TOK_ID TOK_ASSIGN Expression TOK_SEMI { $$ = newNodeKind(AssignK, (char*)$1, (StTreeNode*)$3, NULL, NULL); }
          | Conditional { $$ = $1; }
          | Loop { $$ = $1; }
          | TOK_INPUT Expression TOK_ID TOK_SEMI { $$ = newNodeKind(InputK, (char*)$3, (StTreeNode*)$2, NULL, NULL); }
          | TOK_OUTPUT Expression TOK_SEMI { $$ = newNodeKind(OutputK, NULL, (StTreeNode*)$2, NULL, NULL); }
;

Declarator : TOK_INT VariableList { $$ = newNodeKind(DeclK, "int", (StTreeNode*)$2, NULL, NULL); }
           | TOK_CHAR VariableList { $$ = newNodeKind(DeclK, "char", (StTreeNode*)$2, NULL, NULL); }
           | TOK_WORD VariableList { $$ = newNodeKind(DeclK, "word", (StTreeNode*)$2, NULL, NULL); }
           | TOK_SENT VariableList { $$ = newNodeKind(DeclK, "sentence", (StTreeNode*)$2, NULL, NULL); }
;

Conditional : TOK_IF Condition Block %prec TOK_LOWER_THAN_ELSE { $$ = newNodeKind(IfK, NULL, (StTreeNode*)$2, (StTreeNode*)$3, NULL); }
            | TOK_IF Condition Block TOK_ELSE Block { $$ = newNodeKind(IfK, NULL, (StTreeNode*)$2, (StTreeNode*)$3, (StTreeNode*)$5); }
;

Loop : TOK_WHILE Condition Block { $$ = newNodeKind(WhileK, NULL, (StTreeNode*)$2, (StTreeNode*)$3, NULL); }
     | TOK_LOOP TOK_LPAR Expression TOK_RPAR Block { $$ = newNodeKind(LoopK, NULL, (StTreeNode*)$3, (StTreeNode*)$5, NULL); }
;

VariableList : VariableList TOK_COMMA Identif { $$ = joinNode($1, $3); }
             | Identif { $$ = $1; }
;

Expression : Expression TOK_INDEX Expression { $$ = newNodeKind(IndexK, NULL, (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
           | Expression TOK_PLUS Expression { $$ = newNodeKind(OperK, "+", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
           | Expression TOK_MINUS Expression { $$ = newNodeKind(OperK, "-", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
           | Expression TOK_CONCAT Expression { $$ = newNodeKind(ConcatK, NULL, (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
           | Primary { $$ = $1; }
;

Condition : TOK_LPAR Cond TOK_RPAR { $$ = $2; }
;

Cond : Expression TOK_LT Expression { $$ = newNodeKind(OperRelK, "<", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
     | Expression TOK_GT Expression { $$ = newNodeKind(OperRelK, ">", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
     | Expression TOK_EQ Expression { $$ = newNodeKind(OperRelK, "==", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
     | Expression TOK_NQ Expression { $$ = newNodeKind(OperRelK, "!=", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
     | Expression TOK_LE Expression { $$ = newNodeKind(OperRelK, "<=", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
     | Expression TOK_GE Expression { $$ = newNodeKind(OperRelK, ">=", (StTreeNode*)$1, (StTreeNode*)$3, NULL); }
     | TOK_NEG Expression { $$ = newNodeKind(OperRelK, "!", (StTreeNode*)$2, NULL, NULL); }
     | Expression { $$ = newNodeKind(OperRelK, "eval", (StTreeNode*)$1, NULL, NULL); }
;

Primary : TOK_LPAR Expression TOK_RPAR { $$ = $2; }
        | TOK_ID { $$ = newNodeKind(IdK, (char*)$1, NULL, NULL, NULL); }
        | TOK_MINUS TOK_NUMINT { $$ = newNodeKind(ConstIntK, (char*)strJoin("-", (char*)$2), NULL, NULL, NULL); }
        | TOK_NUMINT { $$ = newNodeKind(ConstIntK, (char*)$1, NULL, NULL, NULL); }
        | TOK_STRCHAR { $$ = newNodeKind(ConstCharK, (char*)$1, NULL, NULL, NULL); }
        | TOK_STRWORD { $$ = newNodeKind(ConstWordK, (char*)$1, NULL, NULL, NULL); }
        | TOK_STRSENT { $$ = newNodeKind(ConstSenteK, (char*)$1, NULL, NULL, NULL); }
;

Identif : TOK_ID { $$ = newNodeKind(IdK, (char*)$1, NULL, NULL, NULL); }
;

%%

void showResult(StTreeNode *tree)
{
	generateCFile(yyout, tree);
}

void showError(StTreeNode *tree)
{
	printf("Syntax error\n");
	exit(0);
}

void yyerror(const char *s){
	/* Commented out because we use our own error handler. */
	
	//printf("Error in: %s\n", s);
}

int main(int argc, char *argv[]) {
	char nameOut[50];

	if (argc >= 2) {
		yyin = fopen(argv[1], "r");
		if (yyin == NULL) {
			yyin = stdin;
			printf("Error: Could not open file %s\n", argv[1]);
		} else {
			strcpy(nameOut, "a.c");
			if (argc >= 3) {
				strcpy(nameOut, argv[2]);
			}

			yyout = fopen(nameOut, "w");
			if (yyout == NULL) {
				yyout = stdout;
				printf("Error: Could not open file %s\n", nameOut);
			} else {
				yyparse();
		  
				if (yyin != NULL) {
					fclose(yyin);
				}

				if (yyout != NULL) {
					fclose(yyout);
				}
			}
		}		
	} else {
		printf("Error - Should execute like this: wordlang <<input_file.wl>> <<output_file.c>>\n");
	}
  
	return 0;
}


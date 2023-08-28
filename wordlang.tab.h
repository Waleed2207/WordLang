
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_NUMINT = 258,
     TOK_STRCHAR = 259,
     TOK_STRWORD = 260,
     TOK_STRSENT = 261,
     TOK_LPAR = 262,
     TOK_RPAR = 263,
     TOK_LCBRACK = 264,
     TOK_RCBRACK = 265,
     TOK_CHAR = 266,
     TOK_INT = 267,
     TOK_SENT = 268,
     TOK_WORD = 269,
     TOK_PLUS = 270,
     TOK_MINUS = 271,
     TOK_CONCAT = 272,
     TOK_INDEX = 273,
     TOK_NEG = 274,
     TOK_SEMI = 275,
     TOK_COMMA = 276,
     TOK_ASSIGN = 277,
     TOK_LT = 278,
     TOK_GT = 279,
     TOK_EQ = 280,
     TOK_NQ = 281,
     TOK_LE = 282,
     TOK_GE = 283,
     TOK_ELSE = 284,
     TOK_IF = 285,
     TOK_INPUT = 286,
     TOK_LOOP = 287,
     TOK_OUTPUT = 288,
     TOK_WHILE = 289,
     TOK_ID = 290,
     TOK_ERROR = 291,
     TOK_LOWER_THAN_ELSE = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



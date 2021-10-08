/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     PROGRAM = 258,
     VARS = 259,
     IF = 260,
     ELSE = 261,
     PRINT = 262,
     CHAR = 263,
     MAIN = 264,
     FUNCTION = 265,
     COMMA = 266,
     RETURN = 267,
     READ = 268,
     WRITE = 269,
     WHILE = 270,
     GREATEREQUAL = 271,
     INT = 272,
     FLOAT = 273,
     ID = 274,
     SEMICOLON = 275,
     PLUS = 276,
     MINUS = 277,
     DIVIDE = 278,
     MULTIPLY = 279,
     EQUALS = 280,
     QUOTATIONMARK = 281,
     FOR = 282,
     LESSEQUAL = 283,
     OPENPARENTHESES = 284,
     CLOSEPARENTHESES = 285,
     DOT = 286,
     TWODOTS = 287,
     OPENBRACKET = 288,
     CLOSEBRACKET = 289,
     DO = 290,
     AND = 291,
     OPENBRACE = 292,
     CLOSEBRACE = 293,
     DIFFERENT = 294,
     GREATER = 295,
     LESS = 296,
     CTEF = 297,
     CTEI = 298,
     CTESTRING = 299,
     THEN = 300,
     TO = 301,
     OR = 302,
     EQUALS_BOOLEAN = 303
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define VARS 259
#define IF 260
#define ELSE 261
#define PRINT 262
#define CHAR 263
#define MAIN 264
#define FUNCTION 265
#define COMMA 266
#define RETURN 267
#define READ 268
#define WRITE 269
#define WHILE 270
#define GREATEREQUAL 271
#define INT 272
#define FLOAT 273
#define ID 274
#define SEMICOLON 275
#define PLUS 276
#define MINUS 277
#define DIVIDE 278
#define MULTIPLY 279
#define EQUALS 280
#define QUOTATIONMARK 281
#define FOR 282
#define LESSEQUAL 283
#define OPENPARENTHESES 284
#define CLOSEPARENTHESES 285
#define DOT 286
#define TWODOTS 287
#define OPENBRACKET 288
#define CLOSEBRACKET 289
#define DO 290
#define AND 291
#define OPENBRACE 292
#define CLOSEBRACE 293
#define DIFFERENT 294
#define GREATER 295
#define LESS 296
#define CTEF 297
#define CTEI 298
#define CTESTRING 299
#define THEN 300
#define TO 301
#define OR 302
#define EQUALS_BOOLEAN 303




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "parser.y"
{                  /* SEMANTIC RECORD            */
char    *id;              /* For returning identifiers  */
}
/* Line 1529 of yacc.c.  */
#line 149 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


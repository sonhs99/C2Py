/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    IDENT = 259,
    INT = 260,
    FLOAT = 261,
    ASS = 262,
    EQUAL = 263,
    NOTEQU = 264,
    GREATER = 265,
    EQUGRE = 266,
    LESS = 267,
    EQULESS = 268,
    IN = 269,
    ADD = 270,
    SUB = 271,
    MUL = 272,
    DIV = 273,
    UMINUS = 274,
    UPLUS = 275,
    NOT = 276,
    LPAREN = 277,
    RPAREN = 278,
    LBRACKET = 279,
    RBRACKET = 280,
    DOT = 281,
    MAINPROG = 282,
    FUNCTION = 283,
    PROCEDURE = 284,
    BEG = 285,
    END = 286,
    IF = 287,
    ELIF = 288,
    ELSE = 289,
    NOP = 290,
    WHILE = 291,
    RETURN = 292,
    COMMA = 293,
    SEMICOLON = 294,
    COLON = 295,
    FOR = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 7 "yacc.y" /* yacc.c:1909  */

    char * data;
	struct TreeNode * node;

#line 101 "yacc.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (struct TreeNode ** pt);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

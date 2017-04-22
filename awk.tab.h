/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AWKBEGIN = 258,
     AWKEND = 259,
     REGMATCH = 260,
     COMMENT = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     EXIT = 265,
     EQ = 266,
     LE = 267,
     GE = 268,
     NE = 269,
     BOOLAND = 270,
     BOOLOR = 271,
     REGEX = 272,
     STRING = 273,
     NUM = 274,
     ID = 275
   };
#endif
#define AWKBEGIN 258
#define AWKEND 259
#define REGMATCH 260
#define COMMENT 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define EXIT 265
#define EQ 266
#define LE 267
#define GE 268
#define NE 269
#define BOOLAND 270
#define BOOLOR 271
#define REGEX 272
#define STRING 273
#define NUM 274
#define ID 275




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;




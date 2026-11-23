/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

/******************************************************************************
  Copyright (c) 1992, 1995, 1996 Xerox Corporation.  All rights reserved.
  Portions of this code were written by Stephen White, aka ghond.
  Use and copying of this software and preparation of derivative works based
  upon this software are permitted.  Any distribution of this software or
  derivative works must comply with all applicable United States export
  control laws.  This software is made available AS IS, and Xerox Corporation
  makes no warranty about the software, its performance or its conformity to
  any specification.  Any person obtaining a copy of this software is requested
  to send their name and post office or electronic mail address to:
    Pavel Curtis
    Xerox PARC
    3333 Coyote Hill Rd.
    Palo Alto, CA 94304
    Pavel@Xerox.Com
 *****************************************************************************/

/*************************************************************************/
/* NOTE: If you add an #include here, make sure you properly update the  */
/*       parser.o dependency line in the Makefile.			 */
/*************************************************************************/

#include "parser.h"

#include "my-ctype.h"
#include "my-math.h"
#include "my-stdlib.h"
#include "my-string.h"

#include "ast.h"
#include "code_gen.h"
#include "exceptions.h"
#include "functions.h"
#include "keywords.h"
#include "list.h"
#include "log.h"
#include "numbers.h"
#include "opcode.h"
#include "program.h"
#include "storage.h"
#include "streams.h"
#include "structures.h"
#include "sym_table.h"
#include "utils.h"
#include "utf.h"
#include "utf-ctype.h"
#include "version.h"

static Stmt    	       *prog_start;
static int		dollars_ok;
static DB_Version	language_version;

static void	error(const char *, const char *);
static void	warning(const char *, const char *);
static int	find_id(char *name);
static void	yyerror(const char *s);
static int32_t	yylex(void);
static Scatter *scatter_from_arglist(Arg_List *);
static Scatter *add_scatter_item(Scatter *, Scatter *);
static void	vet_scatter(Scatter *);
static void	push_loop_name(const char *);
static void	pop_loop_name(void);
static void	suspend_loop_scope(void);
static void	resume_loop_scope(void);

enum loop_exit_kind { LOOP_BREAK, LOOP_CONTINUE };

static void	check_loop_name(const char *, enum loop_exit_kind);

#line 142 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tCHR = 258,                    /* tCHR  */
    tINTEGER = 259,                /* tINTEGER  */
    tOBJECT = 260,                 /* tOBJECT  */
    tFLOAT = 261,                  /* tFLOAT  */
    tSTRING = 262,                 /* tSTRING  */
    tID = 263,                     /* tID  */
    tERROR = 264,                  /* tERROR  */
    tIF = 265,                     /* tIF  */
    tELSE = 266,                   /* tELSE  */
    tELSEIF = 267,                 /* tELSEIF  */
    tENDIF = 268,                  /* tENDIF  */
    tFOR = 269,                    /* tFOR  */
    tIN = 270,                     /* tIN  */
    tENDFOR = 271,                 /* tENDFOR  */
    tRETURN = 272,                 /* tRETURN  */
    tFORK = 273,                   /* tFORK  */
    tENDFORK = 274,                /* tENDFORK  */
    tWHILE = 275,                  /* tWHILE  */
    tENDWHILE = 276,               /* tENDWHILE  */
    tTRY = 277,                    /* tTRY  */
    tENDTRY = 278,                 /* tENDTRY  */
    tEXCEPT = 279,                 /* tEXCEPT  */
    tFINALLY = 280,                /* tFINALLY  */
    tANY = 281,                    /* tANY  */
    tBREAK = 282,                  /* tBREAK  */
    tCONTINUE = 283,               /* tCONTINUE  */
    tTO = 284,                     /* tTO  */
    tARROW = 285,                  /* tARROW  */
    tOR = 286,                     /* tOR  */
    tAND = 287,                    /* tAND  */
    tEQ = 288,                     /* tEQ  */
    tNE = 289,                     /* tNE  */
    tLE = 290,                     /* tLE  */
    tGE = 291,                     /* tGE  */
    tBITOR = 292,                  /* tBITOR  */
    tBITXOR = 293,                 /* tBITXOR  */
    tBITAND = 294,                 /* tBITAND  */
    tSHL = 295,                    /* tSHL  */
    tSHR = 296,                    /* tSHR  */
    tLSHR = 297,                   /* tLSHR  */
    tUNARYMINUS = 298              /* tUNARYMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tCHR 258
#define tINTEGER 259
#define tOBJECT 260
#define tFLOAT 261
#define tSTRING 262
#define tID 263
#define tERROR 264
#define tIF 265
#define tELSE 266
#define tELSEIF 267
#define tENDIF 268
#define tFOR 269
#define tIN 270
#define tENDFOR 271
#define tRETURN 272
#define tFORK 273
#define tENDFORK 274
#define tWHILE 275
#define tENDWHILE 276
#define tTRY 277
#define tENDTRY 278
#define tEXCEPT 279
#define tFINALLY 280
#define tANY 281
#define tBREAK 282
#define tCONTINUE 283
#define tTO 284
#define tARROW 285
#define tOR 286
#define tAND 287
#define tEQ 288
#define tNE 289
#define tLE 290
#define tGE 291
#define tBITOR 292
#define tBITXOR 293
#define tBITAND 294
#define tSHL 295
#define tSHR 296
#define tLSHR 297
#define tUNARYMINUS 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "parser.y"

  Stmt	       *stmt;
  Expr	       *expr;
  int32_t	chr;		/* Used to carry non-ASCII characters */
  Num		integer;
  Objid		object;
  FlBox         real;
  char	       *string;
  enum error	error;
  Arg_List     *args;
  Cond_Arm     *arm;
  Except_Arm   *except;
  Scatter      *scatter;

#line 296 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tCHR = 3,                       /* tCHR  */
  YYSYMBOL_tINTEGER = 4,                   /* tINTEGER  */
  YYSYMBOL_tOBJECT = 5,                    /* tOBJECT  */
  YYSYMBOL_tFLOAT = 6,                     /* tFLOAT  */
  YYSYMBOL_tSTRING = 7,                    /* tSTRING  */
  YYSYMBOL_tID = 8,                        /* tID  */
  YYSYMBOL_tERROR = 9,                     /* tERROR  */
  YYSYMBOL_tIF = 10,                       /* tIF  */
  YYSYMBOL_tELSE = 11,                     /* tELSE  */
  YYSYMBOL_tELSEIF = 12,                   /* tELSEIF  */
  YYSYMBOL_tENDIF = 13,                    /* tENDIF  */
  YYSYMBOL_tFOR = 14,                      /* tFOR  */
  YYSYMBOL_tIN = 15,                       /* tIN  */
  YYSYMBOL_tENDFOR = 16,                   /* tENDFOR  */
  YYSYMBOL_tRETURN = 17,                   /* tRETURN  */
  YYSYMBOL_tFORK = 18,                     /* tFORK  */
  YYSYMBOL_tENDFORK = 19,                  /* tENDFORK  */
  YYSYMBOL_tWHILE = 20,                    /* tWHILE  */
  YYSYMBOL_tENDWHILE = 21,                 /* tENDWHILE  */
  YYSYMBOL_tTRY = 22,                      /* tTRY  */
  YYSYMBOL_tENDTRY = 23,                   /* tENDTRY  */
  YYSYMBOL_tEXCEPT = 24,                   /* tEXCEPT  */
  YYSYMBOL_tFINALLY = 25,                  /* tFINALLY  */
  YYSYMBOL_tANY = 26,                      /* tANY  */
  YYSYMBOL_tBREAK = 27,                    /* tBREAK  */
  YYSYMBOL_tCONTINUE = 28,                 /* tCONTINUE  */
  YYSYMBOL_tTO = 29,                       /* tTO  */
  YYSYMBOL_tARROW = 30,                    /* tARROW  */
  YYSYMBOL_31_ = 31,                       /* '='  */
  YYSYMBOL_32_ = 32,                       /* '?'  */
  YYSYMBOL_33_ = 33,                       /* '|'  */
  YYSYMBOL_tOR = 34,                       /* tOR  */
  YYSYMBOL_tAND = 35,                      /* tAND  */
  YYSYMBOL_tEQ = 36,                       /* tEQ  */
  YYSYMBOL_tNE = 37,                       /* tNE  */
  YYSYMBOL_38_ = 38,                       /* '<'  */
  YYSYMBOL_tLE = 39,                       /* tLE  */
  YYSYMBOL_40_ = 40,                       /* '>'  */
  YYSYMBOL_tGE = 41,                       /* tGE  */
  YYSYMBOL_tBITOR = 42,                    /* tBITOR  */
  YYSYMBOL_tBITXOR = 43,                   /* tBITXOR  */
  YYSYMBOL_tBITAND = 44,                   /* tBITAND  */
  YYSYMBOL_tSHL = 45,                      /* tSHL  */
  YYSYMBOL_tSHR = 46,                      /* tSHR  */
  YYSYMBOL_tLSHR = 47,                     /* tLSHR  */
  YYSYMBOL_48_ = 48,                       /* '+'  */
  YYSYMBOL_49_ = 49,                       /* '-'  */
  YYSYMBOL_50_ = 50,                       /* '*'  */
  YYSYMBOL_51_ = 51,                       /* '/'  */
  YYSYMBOL_52_ = 52,                       /* '%'  */
  YYSYMBOL_53_ = 53,                       /* '^'  */
  YYSYMBOL_54_ = 54,                       /* '!'  */
  YYSYMBOL_55_ = 55,                       /* '~'  */
  YYSYMBOL_tUNARYMINUS = 56,               /* tUNARYMINUS  */
  YYSYMBOL_57_ = 57,                       /* '.'  */
  YYSYMBOL_58_ = 58,                       /* ':'  */
  YYSYMBOL_59_ = 59,                       /* '['  */
  YYSYMBOL_60_ = 60,                       /* '$'  */
  YYSYMBOL_61_ = 61,                       /* '('  */
  YYSYMBOL_62_ = 62,                       /* ')'  */
  YYSYMBOL_63_ = 63,                       /* ']'  */
  YYSYMBOL_64_ = 64,                       /* ';'  */
  YYSYMBOL_65_ = 65,                       /* '{'  */
  YYSYMBOL_66_ = 66,                       /* '}'  */
  YYSYMBOL_67_ = 67,                       /* '`'  */
  YYSYMBOL_68_ = 68,                       /* '\''  */
  YYSYMBOL_69_ = 69,                       /* '@'  */
  YYSYMBOL_70_ = 70,                       /* ','  */
  YYSYMBOL_YYACCEPT = 71,                  /* $accept  */
  YYSYMBOL_program = 72,                   /* program  */
  YYSYMBOL_statements = 73,                /* statements  */
  YYSYMBOL_statement = 74,                 /* statement  */
  YYSYMBOL_75_1 = 75,                      /* $@1  */
  YYSYMBOL_76_2 = 76,                      /* $@2  */
  YYSYMBOL_77_3 = 77,                      /* $@3  */
  YYSYMBOL_78_4 = 78,                      /* $@4  */
  YYSYMBOL_79_5 = 79,                      /* $@5  */
  YYSYMBOL_80_6 = 80,                      /* $@6  */
  YYSYMBOL_elseifs = 81,                   /* elseifs  */
  YYSYMBOL_elsepart = 82,                  /* elsepart  */
  YYSYMBOL_excepts = 83,                   /* excepts  */
  YYSYMBOL_84_7 = 84,                      /* $@7  */
  YYSYMBOL_except = 85,                    /* except  */
  YYSYMBOL_opt_id = 86,                    /* opt_id  */
  YYSYMBOL_expr = 87,                      /* expr  */
  YYSYMBOL_dollars_up = 88,                /* dollars_up  */
  YYSYMBOL_codes = 89,                     /* codes  */
  YYSYMBOL_default = 90,                   /* default  */
  YYSYMBOL_arglist = 91,                   /* arglist  */
  YYSYMBOL_ne_arglist = 92,                /* ne_arglist  */
  YYSYMBOL_scatter = 93,                   /* scatter  */
  YYSYMBOL_scatter_item = 94               /* scatter_item  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1621

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  230

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,     2,    60,    52,     2,    68,
      61,    62,    50,    48,    70,    49,    57,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    64,
      38,    31,    40,    32,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    63,    53,     2,    67,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,    33,    66,    55,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    34,    35,    36,    37,
      39,    41,    42,    43,    44,    45,    46,    47,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   122,   122,   128,   129,   144,   153,   152,   165,   164,
     178,   177,   190,   189,   202,   201,   214,   213,   225,   230,
     236,   242,   248,   254,   259,   264,   266,   272,   282,   283,
     301,   302,   307,   310,   309,   336,   342,   343,   348,   353,
     358,   363,   368,   373,   378,   387,   394,   398,   405,   414,
     418,   423,   431,   437,   459,   467,   488,   492,   496,   500,
     504,   508,   512,   516,   520,   524,   528,   532,   536,   540,
     544,   548,   552,   556,   560,   564,   568,   572,   593,   598,
     603,   605,   610,   617,   628,   632,   634,   640,   641,   647,
     648,   653,   655,   657,   671,   688,   697,   701,   706,   711,
     716,   720
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "tCHR", "tINTEGER",
  "tOBJECT", "tFLOAT", "tSTRING", "tID", "tERROR", "tIF", "tELSE",
  "tELSEIF", "tENDIF", "tFOR", "tIN", "tENDFOR", "tRETURN", "tFORK",
  "tENDFORK", "tWHILE", "tENDWHILE", "tTRY", "tENDTRY", "tEXCEPT",
  "tFINALLY", "tANY", "tBREAK", "tCONTINUE", "tTO", "tARROW", "'='", "'?'",
  "'|'", "tOR", "tAND", "tEQ", "tNE", "'<'", "tLE", "'>'", "tGE", "tBITOR",
  "tBITXOR", "tBITAND", "tSHL", "tSHR", "tLSHR", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'^'", "'!'", "'~'", "tUNARYMINUS", "'.'", "':'", "'['",
  "'$'", "'('", "')'", "']'", "';'", "'{'", "'}'", "'`'", "'\\''", "'@'",
  "','", "$accept", "program", "statements", "statement", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "elseifs", "elsepart", "excepts", "$@7",
  "except", "opt_id", "expr", "dollars_up", "codes", "default", "arglist",
  "ne_arglist", "scatter", "scatter_item", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -52,     4,   715,   -52,   -52,   -52,   -52,   -52,   -37,   -52,
     -33,    24,    38,    17,    18,   -52,     8,    12,   690,   690,
     690,    28,   690,   -52,   103,   690,   -52,   752,   276,   690,
      25,   -52,   791,    30,   690,    34,   690,   359,    21,   -52,
      32,   -52,   -24,   -24,   -24,    39,   947,    78,   690,  1455,
      35,    36,   -47,   -52,  1337,   690,   690,   690,   690,   690,
     690,   690,   690,   690,   690,   690,   690,   690,   690,   690,
     690,   690,   690,   690,   690,   690,   690,   690,    22,    23,
     -52,   -52,    42,    43,   986,   -22,   -52,   690,  1025,   690,
    1064,   106,   -52,   -14,   -52,   -52,   276,   -52,    84,  1455,
     -52,   193,    85,     6,   210,   261,  1455,  1377,  1533,  1533,
     261,   261,   261,   261,   261,   261,  1550,   182,  1509,  1562,
    1562,  1562,    81,    81,   -51,   -51,   -51,   -51,   -52,   690,
      56,   690,   690,   -52,   293,   -52,   690,   690,  1103,   -52,
    1142,   -52,   -52,   -52,    57,   384,   -52,   -52,    59,   690,
     690,  1455,   -52,   690,   -52,   111,   -52,   -52,    93,    43,
     690,  1181,   276,  1220,   830,   715,  1416,  1259,   -52,   -52,
     -52,   -52,   210,   -52,   106,   -52,  1455,  1455,  1455,   -52,
     690,    58,  1494,   -52,    66,    75,   690,   -52,    62,   690,
     -52,   -52,   448,   -52,   473,    79,   -52,  1455,   -52,   -52,
     276,   869,   -52,    83,   132,   908,   -52,   537,   -52,   562,
     -52,   -52,    86,   -52,   715,   690,   -52,   -52,   626,   -52,
     -52,   715,   -52,  1298,   -52,   -52,   -52,   651,   715,   -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    38,    41,    39,    40,    43,    42,
       0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
       0,    52,     0,    25,    89,     0,     4,     0,    89,     0,
       0,    24,     0,     0,     0,     0,     0,     0,     0,    19,
       0,    21,    77,    79,    78,    44,     0,     0,     0,    91,
       0,    90,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      84,    18,     0,    90,     0,     0,    23,     0,     0,     0,
       0,    36,     3,     0,    20,    22,    89,    80,   100,    92,
      81,     0,     0,     0,     0,    73,    53,     0,    63,    62,
      67,    68,    69,    70,    71,    72,    64,    65,    66,    74,
      75,    76,    56,    57,    58,    59,    60,    61,    45,     0,
       0,     0,     0,    55,     0,     3,     0,     0,     0,    14,
       0,    10,    37,    32,     0,     0,    26,    33,     0,     0,
       0,    93,    95,     0,    97,     0,    96,    85,    87,    86,
       0,     0,    89,     0,     0,    28,     0,     0,    16,     3,
      12,     3,     0,    27,    36,    48,   101,    94,    54,    98,
       0,     0,    82,    46,     0,     0,     0,    50,    30,     0,
       6,     3,     0,     3,     0,     0,    34,    88,    83,    47,
      89,     0,     3,     0,     0,     0,     3,     0,    15,     0,
      11,     3,     0,    51,    31,     0,     5,     8,     0,    17,
      13,    35,    49,     0,     3,     7,     3,     0,    29,     9
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,   -15,   -52,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   -52,   -27,   -52,    -7,   -52,   -21,   -52,
     -25,   -23,   -52,   -13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    26,   206,   224,   171,   193,   169,   191,
     188,   204,    93,   174,   143,   144,    27,   132,   158,   181,
      50,    83,    52,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,    51,    77,    82,     3,    32,    78,    79,    80,   146,
     147,    42,    43,    44,   154,    46,    38,    49,    54,   102,
      40,    49,    84,   103,    28,    33,    35,    88,    29,    90,
     128,   130,    30,    78,    79,    80,    45,   136,    47,   137,
      85,    99,     4,     5,     6,     7,     8,     9,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   148,    39,   202,   203,   155,    41,   145,    34,    36,
     138,   159,   140,   129,   131,    94,    98,    18,   152,    49,
     156,    87,    19,    20,   151,    89,    95,    49,    21,    22,
      96,   100,    31,    24,   133,    25,   101,     4,     5,     6,
       7,     8,     9,   134,   142,   149,   153,   162,   172,   179,
     165,   175,   161,   180,   163,   164,   198,   151,   199,   166,
     167,    74,    75,    76,    77,    47,   200,   184,    78,    79,
      80,   211,   176,   177,   215,   216,   178,   196,   222,   159,
       0,   195,    18,   182,   192,    49,   194,    19,    20,     0,
       0,     0,     0,    21,    22,    49,     0,     0,    24,     0,
      25,     0,    48,   197,     0,   212,   207,     0,   209,   201,
       0,     0,   205,     0,     0,     0,     0,   214,     0,     0,
       0,   218,     0,    49,     0,     0,   221,     4,     5,     6,
       7,     8,     9,     0,     0,     0,     0,     0,   223,   227,
       0,   228,     0,     0,     4,     5,     6,     7,     8,     9,
       0,     0,     0,     0,     0,    47,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,   157,     0,     0,    78,
      79,    80,    18,     0,     0,     0,     0,    19,    20,     0,
       0,     0,     0,    21,    22,     0,     0,     0,    24,    18,
      25,     0,   150,     0,    19,    20,     0,     0,     0,     0,
      21,    22,     0,     0,     0,    24,     0,    25,     0,    48,
       4,     5,     6,     7,     8,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,     0,     0,     0,    78,    79,
      80,     0,     0,     0,     0,    18,     0,     0,     0,     0,
      19,    20,     0,     0,     0,     0,    21,    22,     0,     0,
       0,    24,    18,    25,     0,    48,     0,    19,    20,     0,
       0,     0,     0,    21,    22,     0,     0,     0,    24,     0,
      25,     0,   150,     4,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,     0,     0,    12,    13,     0,    14,
       0,    15,     0,    91,    92,     0,    16,    17,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,    11,     0,
       0,    12,    13,     0,    14,     0,    15,   173,    18,     0,
       0,    16,    17,    19,    20,     0,     0,     0,     0,    21,
      22,     0,     0,    23,    24,     0,    25,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,     0,    19,    20,
       0,     0,     0,     0,    21,    22,     0,     0,    23,    24,
       0,    25,     4,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,     0,     0,    12,    13,   208,    14,     0,
      15,     0,     0,     0,     0,    16,    17,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    11,     0,     0,
      12,    13,     0,    14,   210,    15,     0,    18,     0,     0,
      16,    17,    19,    20,     0,     0,     0,     0,    21,    22,
       0,     0,    23,    24,     0,    25,     0,     0,     0,     0,
       0,     0,    18,     0,     0,     0,     0,    19,    20,     0,
       0,     0,     0,    21,    22,     0,     0,    23,    24,     0,
      25,     4,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    11,     0,     0,    12,    13,   219,    14,     0,    15,
       0,     0,     0,     0,    16,    17,     4,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,     0,     0,    12,
      13,     0,    14,   220,    15,     0,    18,     0,     0,    16,
      17,    19,    20,     0,     0,     0,     0,    21,    22,     0,
       0,    23,    24,     0,    25,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    19,    20,     0,     0,
       0,     0,    21,    22,     0,     0,    23,    24,     0,    25,
       4,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,     0,   225,    12,    13,     0,    14,     0,    15,     0,
       0,     0,     0,    16,    17,     4,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,     0,   229,    12,    13,
       0,    14,     0,    15,     0,    18,     0,     0,    16,    17,
      19,    20,     0,     0,     0,     0,    21,    22,     0,     0,
      23,    24,     0,    25,     4,     5,     6,     7,     8,     9,
      18,     0,     0,     0,     0,    19,    20,     0,     0,     0,
       0,    21,    22,     0,     0,    23,    24,     0,    25,     4,
       5,     6,     7,     8,     9,    10,     0,     0,     0,    11,
       0,     0,    12,    13,     0,    14,     0,    15,     0,    18,
       0,     0,    16,    17,    19,    20,     0,     0,     0,     0,
      21,    22,     0,     0,     0,    24,     0,    25,     0,     0,
       0,     0,     0,     0,    18,     0,     0,    55,     0,    19,
      20,     0,     0,     0,     0,    21,    22,     0,     0,    23,
      24,     0,    25,    56,    57,     0,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    55,     0,     0,    78,
      79,    80,     0,     0,     0,     0,    81,     0,     0,     0,
       0,     0,    56,    57,     0,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    55,     0,     0,    78,    79,
      80,     0,     0,     0,     0,    86,     0,     0,     0,   186,
       0,    56,    57,     0,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    55,     0,     0,    78,    79,    80,
       0,     0,     0,   187,     0,     0,     0,     0,     0,     0,
      56,    57,     0,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    55,     0,     0,    78,    79,    80,     0,
       0,     0,   213,     0,     0,     0,     0,     0,     0,    56,
      57,     0,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    55,     0,     0,    78,    79,    80,     0,     0,
       0,   217,     0,     0,     0,     0,     0,     0,    56,    57,
       0,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    55,     0,     0,    78,    79,    80,     0,     0,    97,
       0,     0,     0,     0,     0,     0,     0,    56,    57,     0,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      55,     0,     0,    78,    79,    80,     0,     0,   135,     0,
       0,     0,     0,     0,     0,     0,    56,    57,     0,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    55,
       0,     0,    78,    79,    80,     0,     0,   139,     0,     0,
       0,     0,     0,     0,     0,    56,    57,     0,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    55,     0,
       0,    78,    79,    80,     0,     0,   141,     0,     0,     0,
       0,     0,     0,     0,    56,    57,     0,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    55,     0,     0,
      78,    79,    80,     0,     0,   168,     0,     0,     0,     0,
       0,     0,     0,    56,    57,     0,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    55,     0,     0,    78,
      79,    80,     0,     0,   170,     0,     0,     0,     0,     0,
       0,     0,    56,    57,     0,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    55,     0,     0,    78,    79,
      80,     0,     0,   183,     0,     0,     0,     0,     0,     0,
       0,    56,    57,     0,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    55,     0,     0,    78,    79,    80,
       0,     0,   185,     0,     0,     0,     0,     0,     0,     0,
      56,    57,     0,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    55,     0,     0,    78,    79,    80,     0,
       0,   190,     0,     0,     0,     0,     0,     0,     0,    56,
      57,     0,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    55,     0,     0,    78,    79,    80,     0,     0,
     226,     0,     0,     0,     0,     0,     0,     0,    56,    57,
       0,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,   104,    55,     0,    78,    79,    80,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    57,
     160,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    55,     0,     0,    78,    79,    80,     0,     0,     0,
       0,     0,     0,     0,     0,   189,     0,    56,    57,     0,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      55,     0,     0,    78,    79,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,     0,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    55,
       0,     0,    78,    79,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -1,     0,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    55,     0,
       0,    78,    79,    80,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     0,     0,     0,    78,    79,    80,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,     0,     0,     0,
      78,    79,    80,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,     0,     0,     0,    78,    79,    80,
      72,    73,    74,    75,    76,    77,     0,     0,     0,    78,
      79,    80
};

static const yytype_int16 yycheck[] =
{
      15,    24,    53,    28,     0,    12,    57,    58,    59,    23,
      24,    18,    19,    20,     8,    22,     8,    24,    25,    66,
       8,    28,    29,    70,    61,     8,     8,    34,    61,    36,
       8,     8,     8,    57,    58,    59,     8,    59,    32,    61,
      15,    48,     4,     5,     6,     7,     8,     9,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    96,    64,    11,    12,    69,    64,    92,    61,    61,
      87,   104,    89,    61,    61,    64,     8,    49,   101,    96,
     103,    61,    54,    55,   101,    61,    64,   104,    60,    61,
      61,    66,    64,    65,    62,    67,    70,     4,     5,     6,
       7,     8,     9,    70,     8,    31,    31,    61,    61,     8,
     135,    62,   129,    30,   131,   132,    68,   134,    62,   136,
     137,    50,    51,    52,    53,    32,    61,   162,    57,    58,
      59,    62,   149,   150,    61,    13,   153,   174,    62,   172,
      -1,   172,    49,   160,   169,   162,   171,    54,    55,    -1,
      -1,    -1,    -1,    60,    61,   172,    -1,    -1,    65,    -1,
      67,    -1,    69,   180,    -1,   200,   191,    -1,   193,   186,
      -1,    -1,   189,    -1,    -1,    -1,    -1,   202,    -1,    -1,
      -1,   206,    -1,   200,    -1,    -1,   211,     4,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    -1,    -1,   215,   224,
      -1,   226,    -1,    -1,     4,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    -1,    32,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    26,    -1,    -1,    57,
      58,    59,    49,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    65,    49,
      67,    -1,    69,    -1,    54,    55,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    65,    -1,    67,    -1,    69,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    57,    58,
      59,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      54,    55,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    65,    49,    67,    -1,    69,    -1,    54,    55,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    65,    -1,
      67,    -1,    69,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    14,    -1,    -1,    17,    18,    -1,    20,
      -1,    22,    -1,    24,    25,    -1,    27,    28,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    14,    -1,
      -1,    17,    18,    -1,    20,    -1,    22,    23,    49,    -1,
      -1,    27,    28,    54,    55,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    64,    65,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    54,    55,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    64,    65,
      -1,    67,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    14,    -1,    -1,    17,    18,    19,    20,    -1,
      22,    -1,    -1,    -1,    -1,    27,    28,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    14,    -1,    -1,
      17,    18,    -1,    20,    21,    22,    -1,    49,    -1,    -1,
      27,    28,    54,    55,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    64,    65,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    64,    65,    -1,
      67,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    14,    -1,    -1,    17,    18,    19,    20,    -1,    22,
      -1,    -1,    -1,    -1,    27,    28,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    14,    -1,    -1,    17,
      18,    -1,    20,    21,    22,    -1,    49,    -1,    -1,    27,
      28,    54,    55,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    64,    65,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    64,    65,    -1,    67,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      14,    -1,    16,    17,    18,    -1,    20,    -1,    22,    -1,
      -1,    -1,    -1,    27,    28,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    14,    -1,    16,    17,    18,
      -1,    20,    -1,    22,    -1,    49,    -1,    -1,    27,    28,
      54,    55,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      64,    65,    -1,    67,     4,     5,     6,     7,     8,     9,
      49,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    64,    65,    -1,    67,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    14,
      -1,    -1,    17,    18,    -1,    20,    -1,    22,    -1,    49,
      -1,    -1,    27,    28,    54,    55,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    65,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    15,    -1,    54,
      55,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    64,
      65,    -1,    67,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    15,    -1,    -1,    57,
      58,    59,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    15,    -1,    -1,    57,    58,
      59,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    29,
      -1,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    15,    -1,    -1,    57,    58,    59,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    15,    -1,    -1,    57,    58,    59,    -1,
      -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    15,    -1,    -1,    57,    58,    59,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    15,    -1,    -1,    57,    58,    59,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      15,    -1,    -1,    57,    58,    59,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    15,
      -1,    -1,    57,    58,    59,    -1,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    15,    -1,
      -1,    57,    58,    59,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    15,    -1,    -1,
      57,    58,    59,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    15,    -1,    -1,    57,
      58,    59,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    15,    -1,    -1,    57,    58,
      59,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    15,    -1,    -1,    57,    58,    59,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    15,    -1,    -1,    57,    58,    59,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    15,    -1,    -1,    57,    58,    59,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    15,    -1,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    15,    -1,    -1,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      15,    -1,    -1,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    15,
      -1,    -1,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    15,    -1,
      -1,    57,    58,    59,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    59,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    59,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    59,
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    57,
      58,    59
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    72,    73,     0,     4,     5,     6,     7,     8,     9,
      10,    14,    17,    18,    20,    22,    27,    28,    49,    54,
      55,    60,    61,    64,    65,    67,    74,    87,    61,    61,
       8,    64,    87,     8,    61,     8,    61,    73,     8,    64,
       8,    64,    87,    87,    87,     8,    87,    32,    69,    87,
      91,    92,    93,    94,    87,    15,    31,    32,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    57,    58,
      59,    64,    91,    92,    87,    15,    64,    61,    87,    61,
      87,    24,    25,    83,    64,    64,    61,    62,     8,    87,
      66,    70,    66,    70,    54,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,     8,    61,
       8,    61,    88,    62,    70,    62,    59,    61,    87,    62,
      87,    62,     8,    85,    86,    73,    23,    24,    91,    31,
      69,    87,    94,    31,     8,    69,    94,    26,    89,    92,
      33,    87,    61,    87,    87,    73,    87,    87,    62,    79,
      62,    77,    61,    23,    84,    62,    87,    87,    87,     8,
      30,    90,    87,    62,    91,    62,    29,    63,    81,    29,
      62,    80,    73,    78,    73,    89,    85,    87,    68,    62,
      61,    87,    11,    12,    82,    87,    75,    73,    19,    73,
      21,    62,    91,    63,    73,    61,    13,    63,    73,    19,
      21,    73,    62,    87,    76,    16,    62,    73,    73,    16
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    71,    72,    73,    73,    74,    75,    74,    76,    74,
      77,    74,    78,    74,    79,    74,    80,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    81,    81,
      82,    82,    83,    84,    83,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    89,    89,    90,    90,    91,
      91,    92,    92,    92,    92,    93,    93,    93,    93,    93,
      94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     8,     0,     9,     0,    11,
       0,     7,     0,     8,     0,     7,     0,     8,     2,     2,
       3,     2,     3,     3,     2,     1,     4,     5,     0,     6,
       0,     2,     2,     0,     4,     5,     0,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     5,     6,     5,     8,
       5,     7,     1,     3,     5,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     3,     5,     6,     0,     1,     1,     0,     2,     0,
       1,     1,     2,     3,     4,     3,     3,     3,     4,     1,
       2,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statements  */
#line 123 "parser.y"
                { prog_start = (yyvsp[0].stmt); }
#line 1794 "y.tab.c"
    break;

  case 3: /* statements: %empty  */
#line 128 "parser.y"
                { (yyval.stmt) = 0; }
#line 1800 "y.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 130 "parser.y"
                {
		    if ((yyvsp[-1].stmt)) {
			Stmt *tmp = (yyvsp[-1].stmt);

			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = (yyvsp[0].stmt);
			(yyval.stmt) = (yyvsp[-1].stmt);
		    } else
			(yyval.stmt) = (yyvsp[0].stmt);
		}
#line 1816 "y.tab.c"
    break;

  case 5: /* statement: tIF '(' expr ')' statements elseifs elsepart tENDIF  */
#line 145 "parser.y"
                {

		    (yyval.stmt) = alloc_stmt(STMT_COND);
		    (yyval.stmt)->s.cond.arms = alloc_cond_arm((yyvsp[-5].expr), (yyvsp[-3].stmt));
		    (yyval.stmt)->s.cond.arms->next = (yyvsp[-2].arm);
		    (yyval.stmt)->s.cond.otherwise = (yyvsp[-1].stmt);
		}
#line 1828 "y.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 153 "parser.y"
                {
		    push_loop_name((yyvsp[-4].string));
		}
#line 1836 "y.tab.c"
    break;

  case 7: /* statement: tFOR tID tIN '(' expr ')' $@1 statements tENDFOR  */
#line 157 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_LIST);
		    (yyval.stmt)->s.list.id = find_id((yyvsp[-7].string));
		    (yyval.stmt)->s.list.expr = (yyvsp[-4].expr);
		    (yyval.stmt)->s.list.body = (yyvsp[-1].stmt);
		    pop_loop_name();
		}
#line 1848 "y.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 165 "parser.y"
                {
		    push_loop_name((yyvsp[-6].string));
		}
#line 1856 "y.tab.c"
    break;

  case 9: /* statement: tFOR tID tIN '[' expr tTO expr ']' $@2 statements tENDFOR  */
#line 169 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_RANGE);
		    (yyval.stmt)->s.range.id = find_id((yyvsp[-9].string));
		    (yyval.stmt)->s.range.from = (yyvsp[-6].expr);
		    (yyval.stmt)->s.range.to = (yyvsp[-4].expr);
		    (yyval.stmt)->s.range.body = (yyvsp[-1].stmt);
		    pop_loop_name();
		}
#line 1869 "y.tab.c"
    break;

  case 10: /* $@3: %empty  */
#line 178 "parser.y"
                {
		    push_loop_name(0);
		}
#line 1877 "y.tab.c"
    break;

  case 11: /* statement: tWHILE '(' expr ')' $@3 statements tENDWHILE  */
#line 182 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_WHILE);
		    (yyval.stmt)->s.loop.id = -1;
		    (yyval.stmt)->s.loop.condition = (yyvsp[-4].expr);
		    (yyval.stmt)->s.loop.body = (yyvsp[-1].stmt);
		    pop_loop_name();
		}
#line 1889 "y.tab.c"
    break;

  case 12: /* $@4: %empty  */
#line 190 "parser.y"
                {
		    push_loop_name((yyvsp[-3].string));
		}
#line 1897 "y.tab.c"
    break;

  case 13: /* statement: tWHILE tID '(' expr ')' $@4 statements tENDWHILE  */
#line 194 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_WHILE);
		    (yyval.stmt)->s.loop.id = find_id((yyvsp[-6].string));
		    (yyval.stmt)->s.loop.condition = (yyvsp[-4].expr);
		    (yyval.stmt)->s.loop.body = (yyvsp[-1].stmt);
		    pop_loop_name();
		}
#line 1909 "y.tab.c"
    break;

  case 14: /* $@5: %empty  */
#line 202 "parser.y"
                {
		    suspend_loop_scope();
		}
#line 1917 "y.tab.c"
    break;

  case 15: /* statement: tFORK '(' expr ')' $@5 statements tENDFORK  */
#line 206 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_FORK);
		    (yyval.stmt)->s.fork.id = -1;
		    (yyval.stmt)->s.fork.time = (yyvsp[-4].expr);
		    (yyval.stmt)->s.fork.body = (yyvsp[-1].stmt);
		    resume_loop_scope();
		}
#line 1929 "y.tab.c"
    break;

  case 16: /* $@6: %empty  */
#line 214 "parser.y"
                {
		    suspend_loop_scope();
		}
#line 1937 "y.tab.c"
    break;

  case 17: /* statement: tFORK tID '(' expr ')' $@6 statements tENDFORK  */
#line 218 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_FORK);
		    (yyval.stmt)->s.fork.id = find_id((yyvsp[-6].string));
		    (yyval.stmt)->s.fork.time = (yyvsp[-4].expr);
		    (yyval.stmt)->s.fork.body = (yyvsp[-1].stmt);
		    resume_loop_scope();
		}
#line 1949 "y.tab.c"
    break;

  case 18: /* statement: expr ';'  */
#line 226 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_EXPR);
		    (yyval.stmt)->s.expr = (yyvsp[-1].expr);
		}
#line 1958 "y.tab.c"
    break;

  case 19: /* statement: tBREAK ';'  */
#line 231 "parser.y"
                {
		    check_loop_name(0, LOOP_BREAK);
		    (yyval.stmt) = alloc_stmt(STMT_BREAK);
		    (yyval.stmt)->s.exit = -1;
		}
#line 1968 "y.tab.c"
    break;

  case 20: /* statement: tBREAK tID ';'  */
#line 237 "parser.y"
                {
		    check_loop_name((yyvsp[-1].string), LOOP_BREAK);
		    (yyval.stmt) = alloc_stmt(STMT_BREAK);
		    (yyval.stmt)->s.exit = find_id((yyvsp[-1].string));
		}
#line 1978 "y.tab.c"
    break;

  case 21: /* statement: tCONTINUE ';'  */
#line 243 "parser.y"
                {
		    check_loop_name(0, LOOP_CONTINUE);
		    (yyval.stmt) = alloc_stmt(STMT_CONTINUE);
		    (yyval.stmt)->s.exit = -1;
		}
#line 1988 "y.tab.c"
    break;

  case 22: /* statement: tCONTINUE tID ';'  */
#line 249 "parser.y"
                {
		    check_loop_name((yyvsp[-1].string), LOOP_CONTINUE);
		    (yyval.stmt) = alloc_stmt(STMT_CONTINUE);
		    (yyval.stmt)->s.exit = find_id((yyvsp[-1].string));
		}
#line 1998 "y.tab.c"
    break;

  case 23: /* statement: tRETURN expr ';'  */
#line 255 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_RETURN);
		    (yyval.stmt)->s.expr = (yyvsp[-1].expr);
		}
#line 2007 "y.tab.c"
    break;

  case 24: /* statement: tRETURN ';'  */
#line 260 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_RETURN);
		    (yyval.stmt)->s.expr = 0;
		}
#line 2016 "y.tab.c"
    break;

  case 25: /* statement: ';'  */
#line 265 "parser.y"
                { (yyval.stmt) = 0; }
#line 2022 "y.tab.c"
    break;

  case 26: /* statement: tTRY statements excepts tENDTRY  */
#line 267 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_TRY_EXCEPT);
		    (yyval.stmt)->s.catch.body = (yyvsp[-2].stmt);
		    (yyval.stmt)->s.catch.excepts = (yyvsp[-1].except);
		}
#line 2032 "y.tab.c"
    break;

  case 27: /* statement: tTRY statements tFINALLY statements tENDTRY  */
#line 273 "parser.y"
                {
		    (yyval.stmt) = alloc_stmt(STMT_TRY_FINALLY);
		    (yyval.stmt)->s.finally.body = (yyvsp[-3].stmt);
		    (yyval.stmt)->s.finally.handler = (yyvsp[-1].stmt);
		}
#line 2042 "y.tab.c"
    break;

  case 28: /* elseifs: %empty  */
#line 282 "parser.y"
                { (yyval.arm) = 0; }
#line 2048 "y.tab.c"
    break;

  case 29: /* elseifs: elseifs tELSEIF '(' expr ')' statements  */
#line 284 "parser.y"
                {
		    Cond_Arm *this_arm = alloc_cond_arm((yyvsp[-2].expr), (yyvsp[0].stmt));

		    if ((yyvsp[-5].arm)) {
		        Cond_Arm *tmp = (yyvsp[-5].arm);

			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = this_arm;
			(yyval.arm) = (yyvsp[-5].arm);
		    } else
			(yyval.arm) = this_arm;
		}
#line 2066 "y.tab.c"
    break;

  case 30: /* elsepart: %empty  */
#line 301 "parser.y"
                { (yyval.stmt) = 0; }
#line 2072 "y.tab.c"
    break;

  case 31: /* elsepart: tELSE statements  */
#line 303 "parser.y"
                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2078 "y.tab.c"
    break;

  case 32: /* excepts: tEXCEPT except  */
#line 308 "parser.y"
                { (yyval.except) = (yyvsp[0].except); }
#line 2084 "y.tab.c"
    break;

  case 33: /* $@7: %empty  */
#line 310 "parser.y"
                {
		    Except_Arm *tmp = (yyvsp[-1].except);
		    int		count = 1;

		    while (tmp->next) {
			tmp = tmp->next;
			count++;
		    }
		    if (!tmp->codes)
			yyerror("Unreachable EXCEPT clause");
		    else if (count > 255)
			yyerror("Too many EXCEPT clauses (max. 255)");
		}
#line 2102 "y.tab.c"
    break;

  case 34: /* excepts: excepts tEXCEPT $@7 except  */
#line 324 "parser.y"
                {
		    Except_Arm *tmp = (yyvsp[-3].except);

		    while (tmp->next)
			tmp = tmp->next;

		    tmp->next = (yyvsp[0].except);
		    (yyval.except) = (yyvsp[-3].except);
		}
#line 2116 "y.tab.c"
    break;

  case 35: /* except: opt_id '(' codes ')' statements  */
#line 337 "parser.y"
                { (yyval.except) = alloc_except((yyvsp[-4].string) ? find_id((yyvsp[-4].string)) : -1, (yyvsp[-2].args), (yyvsp[0].stmt)); }
#line 2122 "y.tab.c"
    break;

  case 36: /* opt_id: %empty  */
#line 342 "parser.y"
                { (yyval.string) = 0; }
#line 2128 "y.tab.c"
    break;

  case 37: /* opt_id: tID  */
#line 344 "parser.y"
                { (yyval.string) = (yyvsp[0].string); }
#line 2134 "y.tab.c"
    break;

  case 38: /* expr: tINTEGER  */
#line 349 "parser.y"
                {
		    (yyval.expr) = alloc_var(TYPE_INT);
		    (yyval.expr)->e.var.v.num = (yyvsp[0].integer);
		}
#line 2143 "y.tab.c"
    break;

  case 39: /* expr: tFLOAT  */
#line 354 "parser.y"
                {
		    (yyval.expr) = alloc_var(TYPE_FLOAT);
		    (yyval.expr)->e.var.v.fnum = (yyvsp[0].real);
		}
#line 2152 "y.tab.c"
    break;

  case 40: /* expr: tSTRING  */
#line 359 "parser.y"
                {
		    (yyval.expr) = alloc_var(TYPE_STR);
		    (yyval.expr)->e.var.v.str = (yyvsp[0].string);
		}
#line 2161 "y.tab.c"
    break;

  case 41: /* expr: tOBJECT  */
#line 364 "parser.y"
                {
		    (yyval.expr) = alloc_var(TYPE_OBJ);
		    (yyval.expr)->e.var.v.obj = (yyvsp[0].object);
		}
#line 2170 "y.tab.c"
    break;

  case 42: /* expr: tERROR  */
#line 369 "parser.y"
                {
		    (yyval.expr) = alloc_var(TYPE_ERR);
		    (yyval.expr)->e.var.v.err = (yyvsp[0].error);
		}
#line 2179 "y.tab.c"
    break;

  case 43: /* expr: tID  */
#line 374 "parser.y"
                {
		    (yyval.expr) = alloc_expr(EXPR_ID);
		    (yyval.expr)->e.id = find_id((yyvsp[0].string));
		}
#line 2188 "y.tab.c"
    break;

  case 44: /* expr: '$' tID  */
#line 379 "parser.y"
                {
		    /* Treat $foo like #0.("foo") */
		    Expr *obj = alloc_var(TYPE_OBJ);
		    Expr *prop = alloc_var(TYPE_STR);
		    obj->e.var.v.obj = 0;
		    prop->e.var.v.str = (yyvsp[0].string);
		    (yyval.expr) = alloc_binary(EXPR_PROP, obj, prop);
		}
#line 2201 "y.tab.c"
    break;

  case 45: /* expr: expr '.' tID  */
#line 388 "parser.y"
                {
		    /* Treat foo.bar like foo.("bar") for simplicity */
		    Expr *prop = alloc_var(TYPE_STR);
		    prop->e.var.v.str = (yyvsp[0].string);
		    (yyval.expr) = alloc_binary(EXPR_PROP, (yyvsp[-2].expr), prop);
		}
#line 2212 "y.tab.c"
    break;

  case 46: /* expr: expr '.' '(' expr ')'  */
#line 395 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_PROP, (yyvsp[-4].expr), (yyvsp[-1].expr));
		}
#line 2220 "y.tab.c"
    break;

  case 47: /* expr: expr ':' tID '(' arglist ')'  */
#line 399 "parser.y"
                {
		    /* treat foo:bar(args) like foo:("bar")(args) */
		    Expr *verb = alloc_var(TYPE_STR);
		    verb->e.var.v.str = (yyvsp[-3].string);
		    (yyval.expr) = alloc_verb((yyvsp[-5].expr), verb, (yyvsp[-1].args));
		}
#line 2231 "y.tab.c"
    break;

  case 48: /* expr: '$' tID '(' arglist ')'  */
#line 406 "parser.y"
                {
		    /* treat $bar(args) like #0:("bar")(args) */
		    Expr *obj = alloc_var(TYPE_OBJ);
		    Expr *verb = alloc_var(TYPE_STR);
		    obj->e.var.v.obj = 0;
		    verb->e.var.v.str = (yyvsp[-3].string);
		    (yyval.expr) = alloc_verb(obj, verb, (yyvsp[-1].args));
		}
#line 2244 "y.tab.c"
    break;

  case 49: /* expr: expr ':' '(' expr ')' '(' arglist ')'  */
#line 415 "parser.y"
                {
		    (yyval.expr) = alloc_verb((yyvsp[-7].expr), (yyvsp[-4].expr), (yyvsp[-1].args));
		}
#line 2252 "y.tab.c"
    break;

  case 50: /* expr: expr '[' dollars_up expr ']'  */
#line 419 "parser.y"
                {
		    dollars_ok--;
		    (yyval.expr) = alloc_binary(EXPR_INDEX, (yyvsp[-4].expr), (yyvsp[-1].expr));
		}
#line 2261 "y.tab.c"
    break;

  case 51: /* expr: expr '[' dollars_up expr tTO expr ']'  */
#line 424 "parser.y"
                {
		    dollars_ok--;
		    (yyval.expr) = alloc_expr(EXPR_RANGE);
		    (yyval.expr)->e.range.base = (yyvsp[-6].expr);
		    (yyval.expr)->e.range.from = (yyvsp[-3].expr);
		    (yyval.expr)->e.range.to = (yyvsp[-1].expr);
		}
#line 2273 "y.tab.c"
    break;

  case 52: /* expr: '$'  */
#line 432 "parser.y"
                {
		    if (!dollars_ok)
			yyerror("Illegal context for `$' expression.");
		    (yyval.expr) = alloc_expr(EXPR_LENGTH);
		}
#line 2283 "y.tab.c"
    break;

  case 53: /* expr: expr '=' expr  */
#line 438 "parser.y"
                {
		    Expr *e = (yyvsp[-2].expr);

		    if (e->kind == EXPR_LIST) {
			e->kind = EXPR_SCATTER;
			if (e->e.list) {
			    e->e.scatter = scatter_from_arglist(e->e.list);
			    vet_scatter(e->e.scatter);
			} else
			    yyerror("Empty list in scattering assignment.");
		    } else {
			if (e->kind == EXPR_RANGE)
			    e = e->e.range.base;
			while (e->kind == EXPR_INDEX)
			    e = e->e.bin.lhs;
			if (e->kind != EXPR_ID  &&  e->kind != EXPR_PROP)
			    yyerror("Illegal expression on left side of"
				    " assignment.");
		    }
		    (yyval.expr) = alloc_binary(EXPR_ASGN, (yyvsp[-2].expr), (yyvsp[0].expr));
	        }
#line 2309 "y.tab.c"
    break;

  case 54: /* expr: '{' scatter '}' '=' expr  */
#line 460 "parser.y"
                {
		    Expr       *e = alloc_expr(EXPR_SCATTER);

		    e->e.scatter = (yyvsp[-3].scatter);
		    vet_scatter((yyvsp[-3].scatter));
		    (yyval.expr) = alloc_binary(EXPR_ASGN, e, (yyvsp[0].expr));
		}
#line 2321 "y.tab.c"
    break;

  case 55: /* expr: tID '(' arglist ')'  */
#line 468 "parser.y"
                {
		    unsigned f_no;

		    (yyval.expr) = alloc_expr(EXPR_CALL);
		    if ((f_no = number_func_by_name((yyvsp[-3].string))) == FUNC_NOT_FOUND) {
			/* Replace with call_function("$1", @args) */
			Expr	       *fname = alloc_var(TYPE_STR);
			Arg_List       *a = alloc_arg_list(ARG_NORMAL, fname);

			fname->e.var.v.str = (yyvsp[-3].string);
			a->next = (yyvsp[-1].args);
			warning("Unknown built-in function: ", (yyvsp[-3].string));
			(yyval.expr)->e.call.func = number_func_by_name("call_function");
			(yyval.expr)->e.call.args = a;
		    } else {
			(yyval.expr)->e.call.func = f_no;
			(yyval.expr)->e.call.args = (yyvsp[-1].args);
			dealloc_string((yyvsp[-3].string));
		    }
		}
#line 2346 "y.tab.c"
    break;

  case 56: /* expr: expr '+' expr  */
#line 489 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_PLUS, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2354 "y.tab.c"
    break;

  case 57: /* expr: expr '-' expr  */
#line 493 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_MINUS, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2362 "y.tab.c"
    break;

  case 58: /* expr: expr '*' expr  */
#line 497 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_TIMES, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2370 "y.tab.c"
    break;

  case 59: /* expr: expr '/' expr  */
#line 501 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_DIVIDE, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2378 "y.tab.c"
    break;

  case 60: /* expr: expr '%' expr  */
#line 505 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_MOD, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2386 "y.tab.c"
    break;

  case 61: /* expr: expr '^' expr  */
#line 509 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_EXP, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2394 "y.tab.c"
    break;

  case 62: /* expr: expr tAND expr  */
#line 513 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2402 "y.tab.c"
    break;

  case 63: /* expr: expr tOR expr  */
#line 517 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2410 "y.tab.c"
    break;

  case 64: /* expr: expr tBITOR expr  */
#line 521 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_BITOR, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2418 "y.tab.c"
    break;

  case 65: /* expr: expr tBITXOR expr  */
#line 525 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_BITXOR, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2426 "y.tab.c"
    break;

  case 66: /* expr: expr tBITAND expr  */
#line 529 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_BITAND, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2434 "y.tab.c"
    break;

  case 67: /* expr: expr tEQ expr  */
#line 533 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_EQ, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2442 "y.tab.c"
    break;

  case 68: /* expr: expr tNE expr  */
#line 537 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_NE, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2450 "y.tab.c"
    break;

  case 69: /* expr: expr '<' expr  */
#line 541 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_LT, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2458 "y.tab.c"
    break;

  case 70: /* expr: expr tLE expr  */
#line 545 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_LE, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2466 "y.tab.c"
    break;

  case 71: /* expr: expr '>' expr  */
#line 549 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_GT, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2474 "y.tab.c"
    break;

  case 72: /* expr: expr tGE expr  */
#line 553 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_GE, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2482 "y.tab.c"
    break;

  case 73: /* expr: expr tIN expr  */
#line 557 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_IN, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2490 "y.tab.c"
    break;

  case 74: /* expr: expr tSHL expr  */
#line 561 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_SHL, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2498 "y.tab.c"
    break;

  case 75: /* expr: expr tSHR expr  */
#line 565 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_SHR, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2506 "y.tab.c"
    break;

  case 76: /* expr: expr tLSHR expr  */
#line 569 "parser.y"
                {
		    (yyval.expr) = alloc_binary(EXPR_LSHR, (yyvsp[-2].expr), (yyvsp[0].expr));
		}
#line 2514 "y.tab.c"
    break;

  case 77: /* expr: '-' expr  */
#line 573 "parser.y"
                {
		    if ((yyvsp[0].expr)->kind == EXPR_VAR
			&& ((yyvsp[0].expr)->e.var.type == TYPE_INT
			    || (yyvsp[0].expr)->e.var.type == TYPE_FLOAT)) {
			switch ((yyvsp[0].expr)->e.var.type) {
			  case TYPE_INT:
			    (yyvsp[0].expr)->e.var.v.num = -(yyvsp[0].expr)->e.var.v.num;
			    break;
			  case TYPE_FLOAT:
			    flbox_negate_in_place(&((yyvsp[0].expr)->e.var.v.fnum));
			    break;
			  default:
			    break;
			}
			(yyval.expr) = (yyvsp[0].expr);
		    } else {
			(yyval.expr) = alloc_expr(EXPR_NEGATE);
			(yyval.expr)->e.expr = (yyvsp[0].expr);
		    }
		}
#line 2539 "y.tab.c"
    break;

  case 78: /* expr: '~' expr  */
#line 594 "parser.y"
                {
		    (yyval.expr) = alloc_expr(EXPR_COMPLEMENT);
		    (yyval.expr)->e.expr = (yyvsp[0].expr);
		}
#line 2548 "y.tab.c"
    break;

  case 79: /* expr: '!' expr  */
#line 599 "parser.y"
                {
		    (yyval.expr) = alloc_expr(EXPR_NOT);
		    (yyval.expr)->e.expr = (yyvsp[0].expr);
		}
#line 2557 "y.tab.c"
    break;

  case 80: /* expr: '(' expr ')'  */
#line 604 "parser.y"
                { (yyval.expr) = (yyvsp[-1].expr); }
#line 2563 "y.tab.c"
    break;

  case 81: /* expr: '{' arglist '}'  */
#line 606 "parser.y"
                {
		    (yyval.expr) = alloc_expr(EXPR_LIST);
		    (yyval.expr)->e.list = (yyvsp[-1].args);
		}
#line 2572 "y.tab.c"
    break;

  case 82: /* expr: expr '?' expr '|' expr  */
#line 611 "parser.y"
                {
		    (yyval.expr) = alloc_expr(EXPR_COND);
		    (yyval.expr)->e.cond.condition = (yyvsp[-4].expr);
		    (yyval.expr)->e.cond.consequent = (yyvsp[-2].expr);
		    (yyval.expr)->e.cond.alternate = (yyvsp[0].expr);
		}
#line 2583 "y.tab.c"
    break;

  case 83: /* expr: '`' expr '!' codes default '\''  */
#line 618 "parser.y"
                {
		    (yyval.expr) = alloc_expr(EXPR_CATCH);
		    (yyval.expr)->e.catch.try = (yyvsp[-4].expr);
		    (yyval.expr)->e.catch.codes = (yyvsp[-2].args);
		    (yyval.expr)->e.catch.except = (yyvsp[-1].expr);
		}
#line 2594 "y.tab.c"
    break;

  case 84: /* dollars_up: %empty  */
#line 628 "parser.y"
                { dollars_ok++; }
#line 2600 "y.tab.c"
    break;

  case 85: /* codes: tANY  */
#line 633 "parser.y"
                { (yyval.args) = 0; }
#line 2606 "y.tab.c"
    break;

  case 86: /* codes: ne_arglist  */
#line 635 "parser.y"
                { (yyval.args) = (yyvsp[0].args); }
#line 2612 "y.tab.c"
    break;

  case 87: /* default: %empty  */
#line 640 "parser.y"
                { (yyval.expr) = 0; }
#line 2618 "y.tab.c"
    break;

  case 88: /* default: tARROW expr  */
#line 642 "parser.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 2624 "y.tab.c"
    break;

  case 89: /* arglist: %empty  */
#line 647 "parser.y"
                { (yyval.args) = 0; }
#line 2630 "y.tab.c"
    break;

  case 90: /* arglist: ne_arglist  */
#line 649 "parser.y"
                { (yyval.args) = (yyvsp[0].args); }
#line 2636 "y.tab.c"
    break;

  case 91: /* ne_arglist: expr  */
#line 654 "parser.y"
                { (yyval.args) = alloc_arg_list(ARG_NORMAL, (yyvsp[0].expr)); }
#line 2642 "y.tab.c"
    break;

  case 92: /* ne_arglist: '@' expr  */
#line 656 "parser.y"
                { (yyval.args) = alloc_arg_list(ARG_SPLICE, (yyvsp[0].expr)); }
#line 2648 "y.tab.c"
    break;

  case 93: /* ne_arglist: ne_arglist ',' expr  */
#line 658 "parser.y"
                {
		    Arg_List *this_arg = alloc_arg_list(ARG_NORMAL, (yyvsp[0].expr));

		    if ((yyvsp[-2].args)) {
			Arg_List *tmp = (yyvsp[-2].args);

			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = this_arg;
			(yyval.args) = (yyvsp[-2].args);
		    } else
			(yyval.args) = this_arg;
		}
#line 2666 "y.tab.c"
    break;

  case 94: /* ne_arglist: ne_arglist ',' '@' expr  */
#line 672 "parser.y"
                {
		    Arg_List *this_arg = alloc_arg_list(ARG_SPLICE, (yyvsp[0].expr));

		    if ((yyvsp[-3].args)) {
			Arg_List *tmp = (yyvsp[-3].args);

			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = this_arg;
			(yyval.args) = (yyvsp[-3].args);
		    } else
			(yyval.args) = this_arg;
		}
#line 2684 "y.tab.c"
    break;

  case 95: /* scatter: ne_arglist ',' scatter_item  */
#line 689 "parser.y"
                {
		    Scatter    *sc = scatter_from_arglist((yyvsp[-2].args));

		    if (sc)
			(yyval.scatter) = add_scatter_item(sc, (yyvsp[0].scatter));
		    else
			(yyval.scatter) = (yyvsp[0].scatter);
		}
#line 2697 "y.tab.c"
    break;

  case 96: /* scatter: scatter ',' scatter_item  */
#line 698 "parser.y"
                {
		    (yyval.scatter) = add_scatter_item((yyvsp[-2].scatter), (yyvsp[0].scatter));
		}
#line 2705 "y.tab.c"
    break;

  case 97: /* scatter: scatter ',' tID  */
#line 702 "parser.y"
                {
		    (yyval.scatter) = add_scatter_item((yyvsp[-2].scatter), alloc_scatter(SCAT_REQUIRED,
							    find_id((yyvsp[0].string)), 0));
		}
#line 2714 "y.tab.c"
    break;

  case 98: /* scatter: scatter ',' '@' tID  */
#line 707 "parser.y"
                {
		    (yyval.scatter) = add_scatter_item((yyvsp[-3].scatter), alloc_scatter(SCAT_REST,
							    find_id((yyvsp[0].string)), 0));
		}
#line 2723 "y.tab.c"
    break;

  case 99: /* scatter: scatter_item  */
#line 712 "parser.y"
                {   (yyval.scatter) = (yyvsp[0].scatter);  }
#line 2729 "y.tab.c"
    break;

  case 100: /* scatter_item: '?' tID  */
#line 717 "parser.y"
                {
		    (yyval.scatter) = alloc_scatter(SCAT_OPTIONAL, find_id((yyvsp[0].string)), 0);
		}
#line 2737 "y.tab.c"
    break;

  case 101: /* scatter_item: '?' tID '=' expr  */
#line 721 "parser.y"
                {
		    (yyval.scatter) = alloc_scatter(SCAT_OPTIONAL, find_id((yyvsp[-2].string)), (yyvsp[0].expr));
		}
#line 2745 "y.tab.c"
    break;


#line 2749 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 726 "parser.y"


static int		lineno, nerrors, must_rename_keywords;
static Parser_Client	client;
static void	       *client_data;
static Names	       *local_names;

static int
find_id(char *name)
{
    int slot = find_or_add_name(&local_names, name);

    dealloc_string(name);
    return slot;
}

static void
yyerror(const char *s)
{
    error(s, 0);
}

static const char *
fmt_error(const char *s, const char *t)
{
    static Stream      *str = 0;

    if (str == 0)
	str = new_stream(100);
    if (t)
	stream_printf(str, "Line %d:  %s%s", lineno, s, t);
    else
	stream_printf(str, "Line %d:  %s", lineno, s);
    return reset_stream(str);
}

static void
error(const char *s, const char *t)
{
    nerrors++;
    (*(client.error))(client_data, fmt_error(s, t));
}

static void
warning(const char *s, const char *t)
{
    if (client.warning)
	(*(client.warning))(client_data, fmt_error(s, t));
    else
	error(s, t);
}

static int32_t unget_buffer[5], unget_count;
#if UNICODE_STRINGS
static int32_t getc_state;
#endif

static int32_t
lex_getc(void)
{
    if (unget_count > 0)
	return unget_buffer[--unget_count];
    else
#if !UNICODE_STRINGS
	return (*(client.getch))(client_data);
#else
	return get_utf_call(client.getch, client_data, &getc_state);
#endif
}

static void
lex_ungetc(int32_t c)
{
    unget_buffer[unget_count++] = c;
}

static int32_t
follow(int32_t expect, int32_t ifyes, int32_t ifno)     /* look ahead for >=, etc. */
{
    int32_t c = lex_getc();

    if (c == expect)
        return ifyes;
    lex_ungetc(c);
    return ifno;
}

#if !BITWISE_OPERATORS
static inline int checkbitwise(void) { return 0; }

#else /* BITWISE_OPERATORS */

/* look ahead for bit-wise operators */
static int
checkbitwise(void)
{
    int c1 = lex_getc();

    if (EOF != c1) {
	int c2 = lex_getc();
	if (c2 == '.')
	    switch (c1) {
	    default:
		break;
	    case '&':
		return tBITAND;
	    case '|':
		return tBITOR;
	    case '^':
		return tBITXOR;
	    }
	lex_ungetc(c2);
    }
    lex_ungetc(c1);
    return 0;
}

static int
checkrightshift(int iftwo, int ifone, int ifnone)
{
    int c;

    if ('>' != (c = lex_getc())) {
	lex_ungetc(c);
	return ifnone;
    }
    if ('>' != (c = lex_getc())) {
	lex_ungetc(c);
	return ifone;
    }
    return iftwo;
}

#endif /* BITWISE_OPERATORS */

static Stream  *token_stream = 0;

static int32_t
yylex(void)
{
    int32_t c;

    reset_stream(token_stream);

start_over:

    do {
	c = lex_getc();
	if (c == '\n') lineno++;
    } while (c != EOF && my_isspace(c));

    if (c == EOF)
        return c;

    if (c == '/') {
	c = lex_getc();
	if (c == '*') {
	    for (;;) {
		c = lex_getc();
		if (c == '*') {
		    c = lex_getc();
		    if (c == '/')
			goto start_over;
		}
		if (c == EOF) {
		    yyerror("End of program while in a comment");
		    return c;
		}
	    }
	} else {
	    lex_ungetc(c);
	    return '/';
	}
    }

    if (c == '#') {
	Var pn = parse_number(0, lex_getc(), lex_getc, lex_ungetc);
	if (pn.type == TYPE_INT) {
	    yylval.object = pn.v.num;
	    return tOBJECT;
	}
	else if (pn.type != TYPE_ERR)
	    panic("parse_number(#...) returned unexpected type");
	else if (pn.v.err == E_RANGE)
	    yyerror("Object number outside of allowed range");
	else
	    yyerror("Malformed object number literal");
	return 0;
    }

    if (my_isdigit(c) ||
	(c == '.'  &&  language_version >= DBV_Float)) {

	Var pn = parse_number(
	     PN_NONNEG|(PN_FLOAT_OK*(language_version >= DBV_Float)),
	     c, lex_getc, lex_ungetc);

	if (pn.type == TYPE_INT) {
	    yylval.integer = pn.v.num;
	    return tINTEGER;
	}
	else if (pn.type == TYPE_FLOAT) {
	    yylval.real = astpool_recv_float(pn.v.fnum);
	    return tFLOAT;
	}
	else if (pn.type != TYPE_ERR)
	    panic("parse_number returned unexpected type");
	else if (pn.v.err == E_NONE) {
	    c = lex_getc();
	    if (c == '.') goto normal_dot;
	    else panic("parse_number ungot unexpected char.");
	}
	else if (pn.v.err == E_RANGE)
	    yyerror("INT literal outside of allowed range");
	else if (pn.v.err == E_FLOAT)
	    yyerror("FLOAT literal outside of allowed range");
	else if (pn.v.err == E_INVARG)
	    yyerror("Malformed numeric literal");
	else
	    panic("parse_number returned weird error code.");
	return 0;
    }

    if (my_is_xid_start(c) || c == '_') {
	Keyword	       *k;

	stream_add_utf(token_stream, c);
	while (my_is_xid_cont(c = lex_getc()) || c == '_')
	    stream_add_utf(token_stream, c);
	lex_ungetc(c);

	k = find_keyword(stream_contents(token_stream),
			 stream_length(token_stream));
	if (k) {
	    if (k->version <= language_version) {
		int	t = k->token;

		if (t == tERROR)
		    yylval.error = k->error;
		return t;
	    } else {		/* New keyword being used as an identifier */
		if (!must_rename_keywords)
		    warning("Renaming old use of new keyword: ", k->name);
		must_rename_keywords = 1;
	    }
	}

	yylval.string = alloc_string(reset_stream(token_stream));
	return tID;
    }

    if (c == '"') {
	while(1) {
	    c = lex_getc();
	    if (c == '"')
		break;
	    if (c == '\\')
		c = lex_getc();
	    if (c == '\n' || c == EOF) {
		yyerror("Missing quote");
		break;
	    }
	    stream_add_utf(token_stream, c);
	}
	yylval.string = alloc_string(reset_stream(token_stream));
	return tSTRING;
    }

    switch(c) {

#if BITWISE_OPERATORS
    case '>':
	return ((c = follow('=', tGE, 0))
		? c
		: checkrightshift(tLSHR, tSHR, '>'));
    case '<':
	return ((c = follow('=', tLE, 0))
		? c
		: follow('<', tSHL, '<'));

#else /* !BITWISE_OPERATORS */
    case '>':
	return follow('=', tGE, '>');
    case '<':
	return follow('=', tLE, '<');

#endif	 /* !BITWISE_OPERATORS */

    case '=':
	return ((c = follow('=', tEQ, 0))
		? c
		: follow('>', tARROW, '='));
    case '!':
	return follow('=', tNE, '!');
    case '|':
	return follow('|', tOR, '|');
    case '&':
	return follow('&', tAND, '&');
    normal_dot:
    case '.':
	return ((c = checkbitwise())
		? c
		: follow('.', tTO, '.'));

#if !BITWISE_OPERATORS
	/* Hide attempted bitwise complement */
    case '~':
	yylval.chr = c;
	return tCHR;
#endif

    default:
	if (c < 127) {
	    return c;
	} else {
	    /* Don't confuse yacc with large Unicode values */
	    yylval.chr = c;
	    return tCHR;
	}
    }
}

static Scatter *
add_scatter_item(Scatter *first, Scatter *last)
{
    Scatter    *tmp = first;

    while (tmp->next)
	tmp = tmp->next;
    tmp->next = last;

    return first;
}

static Scatter *
scatter_from_arglist(Arg_List *a)
{
    Scatter    *sc = 0, **scp;
    Arg_List   *anext;

    for (scp = &sc; a; a = anext, scp = &((*scp)->next)) {
	if (a->expr->kind == EXPR_ID) {
	    *scp = alloc_scatter(a->kind == ARG_NORMAL ? SCAT_REQUIRED
						       : SCAT_REST,
				 a->expr->e.id, 0);
	    anext = a->next;
	    dealloc_node(a->expr);
	    dealloc_node(a);
	} else {
	    yyerror("Scattering assignment targets must be simple variables.");
	    return 0;
	}
    }

    return sc;
}

static void
vet_scatter(Scatter *sc)
{
    int	seen_rest = 0, count = 0;

    for (; sc; sc = sc->next) {
	if (sc->kind == SCAT_REST) {
	    if (seen_rest)
		yyerror("More than one `@' target in scattering assignment.");
	    else
		seen_rest = 1;
	}
	count++;
    }

    if (count > 255)
	yyerror("Too many targets in scattering assignment.");
}

struct loop_entry {
    struct loop_entry  *next;
    const char	       *name;
    int			is_barrier;
};

static struct loop_entry *loop_stack;

static void
push_loop_name(const char *name)
{
    struct loop_entry  *entry = mymalloc(sizeof(struct loop_entry), M_AST);

    entry->next = loop_stack;
    entry->name = (name ? str_dup(name) : 0);
    entry->is_barrier = 0;
    loop_stack = entry;
}

static void
pop_loop_name(void)
{
    if (!loop_stack)
	errlog("PARSER: Empty loop stack in POP_LOOP_NAME!\n");
    else if (loop_stack->is_barrier)
	errlog("PARSER: Tried to pop loop-scope barrier!\n");
    else {
	struct loop_entry      *entry = loop_stack;

	loop_stack = loop_stack->next;
	if (entry->name)
	    free_str(entry->name);
	myfree(entry, M_AST);
    }
}

static void
suspend_loop_scope(void)
{
    struct loop_entry  *entry = mymalloc(sizeof(struct loop_entry), M_AST);

    entry->next = loop_stack;
    entry->name = 0;
    entry->is_barrier = 1;
    loop_stack = entry;
}

static void
resume_loop_scope(void)
{
    if (!loop_stack)
	errlog("PARSER: Empty loop stack in RESUME_LOOP_SCOPE!\n");
    else if (!loop_stack->is_barrier)
	errlog("PARSER: Tried to resume non-loop-scope barrier!\n");
    else {
	struct loop_entry      *entry = loop_stack;

	loop_stack = loop_stack->next;
	myfree(entry, M_AST);
    }
}

static void
check_loop_name(const char *name, enum loop_exit_kind kind)
{
    struct loop_entry  *entry;

    if (!name) {
	if (!loop_stack  ||  loop_stack->is_barrier) {
	    if (kind == LOOP_BREAK)
		yyerror("No enclosing loop for `break' statement");
	    else
		yyerror("No enclosing loop for `continue' statement");
	}
	return;
    }

    for (entry = loop_stack; entry && !entry->is_barrier; entry = entry->next)
	if (entry->name  &&  mystrcasecmp(entry->name, name) == 0)
	    return;

    if (kind == LOOP_BREAK)
	error("Invalid loop name in `break' statement: ", name);
    else
	error("Invalid loop name in `continue' statement: ", name);
}

extern int yyparse(void);

Program *
parse_program(DB_Version version, Parser_Client c, void *data)
{
    Program    *prog;

    if (token_stream == 0)
	token_stream = new_stream(1024);
    unget_count = 0;
#if UNICODE_STRINGS
    getc_state = -1;
#endif
    nerrors = 0;
    must_rename_keywords = 0;
    lineno = 1;
    client = c;
    client_data = data;
    local_names = new_builtin_names(version);
    dollars_ok = 0;
    loop_stack = 0;
    language_version = version;

    begin_code_allocation();
    yyparse();
    end_code_allocation(nerrors > 0);
    if (loop_stack) {
	if (nerrors == 0)
	    errlog("PARSER: Non-empty loop-scope stack!\n");
	while (loop_stack) {
	    struct loop_entry *entry = loop_stack;

	    loop_stack = loop_stack->next;
	    if (entry->name)
		free_str(entry->name);
	    myfree(entry, M_AST);
	}
    }

    if (nerrors == 0) {
	if (must_rename_keywords) {
	    /* One or more new keywords were used as identifiers in this code,
	     * possibly as local variable names (but maybe only as property or
	     * verb names).  Such local variables must be renamed to avoid a
	     * conflict in the new world.  We just add underscores to the end
	     * until it stops conflicting with any other local variable.
	     */
	    unsigned i;

	    /* yyparse() and hence yylex() have been called by now,
	     * so token_stream could have garbage in it.
	     */
	    (void)reset_stream(token_stream);

	    for (i = first_user_slot(version); i < local_names->size; i++) {
		const char	*name = local_names->names[i];

		if (find_keyword(name, strlen(name))) { /* Got one... */
		    stream_add_string(token_stream, name);
		    do {
			stream_add_utf(token_stream, '_');
		    } while (find_name(local_names,
				       stream_contents(token_stream)) >= 0);
		    free_str(name);
		    local_names->names[i] =
			str_dup(reset_stream(token_stream));
		}
	    }
	}

	prog = generate_code(prog_start, version);
	prog->num_var_names = local_names->size;
	prog->var_names = local_names->names;

	myfree(local_names, M_NAMES);
	free_stmt(prog_start);

	return prog;
    } else {
	free_names(local_names);
	return 0;
    }
}

struct parser_state {
    Var		code;		/* a list of strings */
    int		cur_string;	/* which string? */
    int		cur_char;	/* which character in that string? */
    Var		errors;		/* a list of strings */
};

static void
my_error(void *data, const char *msg)
{
    struct parser_state	*state = (struct parser_state *) data;
    Var			v;

    v.type = TYPE_STR;
    v.v.str = str_dup(msg);
    state->errors = listappend(state->errors, v);
}

static int32_t
my_getc(void *data)
{
    struct parser_state	*state = (struct parser_state *) data;
    Var      code;
    uint8_t  c;

    code = state->code;
    if (task_timed_out_now() || state->cur_string > code.v.list[0].v.num)
	return EOF;
    else if (!(c = code.v.list[state->cur_string].v.str[state->cur_char])) {
	state->cur_string++;
	state->cur_char = 0;
	return '\n';
    } else {
	state->cur_char++;
	return c;
    }
}

static Parser_Client list_parser_client = { my_error, 0, my_getc };

Program *
parse_list_as_program(Var code, Var *errors)
{
    struct parser_state	state;
    Program	       *program;

    state.code = code;
    state.cur_string = 1;
    state.cur_char = 0;
    state.errors = new_list(0);
    program = parse_program(current_db_version, list_parser_client, &state);
    *errors = state.errors;

    return program;
}


/*
 * $Log$
 * Revision 2.11  1996/05/12  21:28:37  pavel
 * Removed non-backward-compatible parse error for negating a non-numeric
 * literal.  Made certain aspects of floating-point literal parsing be
 * language-version-dependent, to maintain backward compatibility with DBs
 * written by pre-float servers.  Release 1.8.0p5.
 *
 * Revision 2.10  1996/04/19  01:26:38  pavel
 * Fixed potential memory smash when `$' expression occurs in an illegal
 * context.  Release 1.8.0p4.
 *
 * Revision 2.9  1996/03/10  01:08:01  pavel
 * Removed bogus `call_function("foo", ...)' --> `foo(...)' conversion.
 * Fixed line numbers of renamed-variable warnings.  Release 1.8.0.
 *
 * Revision 2.8  1996/02/18  23:14:54  pavel
 * Liberalized parsing of floating-point numbers to accept `3.' and `3.e1'.
 * Changed parsing to replace call_function("foo", @args) with foo(@args) if
 * foo is a known function.  Release 1.8.0beta3.
 *
 * Revision 2.7  1996/02/11  00:46:01  pavel
 * Liberalized parsing of floating-point literals to accept `.02' and the
 * like.  Fixed a bug where `1E6' and the like would be parsed as an integer.
 * Release 1.8.0beta2.
 *
 * Revision 2.6  1996/02/08  06:32:48  pavel
 * Added support for floating-point literals, exponentiation expression, named
 * WHILE loops, and BREAK and CONTINUE statements.  Generalized support for
 * version-dependent compilation.  Renamed TYPE_NUM to TYPE_INT.  Removed use
 * of ungetch() method on Parser_Client.  Updated copyright notice for 1996.
 * Release 1.8.0beta1.
 *
 * Revision 2.5  1996/01/16  07:17:05  pavel
 * Add support for scattering assignment.  Release 1.8.0alpha6.
 *
 * Revision 2.4  1996/01/11  07:50:49  pavel
 * Added missing #include "my-string.h".  Release 1.8.0alpha5.
 *
 * Revision 2.3  1995/12/31  00:09:40  pavel
 * Removed unused tokens tRAISE and tFORLIST (huh?).  Added `$' expression.
 * Release 1.8.0alpha4.
 *
 * Revision 2.2  1995/12/28  00:43:25  pavel
 * Added some support for MOO-compilation warnings.  Changed `unknown built-in
 * function' error into a warning with recovery.  Changed identifier-renaming
 * log message into a warning.  Release 1.8.0alpha3.
 *
 * Revision 2.1  1995/12/11  08:01:26  pavel
 * Added support for `$foo(...)' syntax.  Release 1.8.0alpha2.
 *
 * Revision 2.0  1995/11/30  04:48:11  pavel
 * New baseline version, corresponding to release 1.8.0alpha1.
 *
 * Revision 1.13  1992/10/23  23:03:47  pavel
 * Added copyright notice.
 *
 * Revision 1.12  1992/10/23  22:21:43  pavel
 * Eliminated all uses of the useless macro NULL.
 *
 * Revision 1.11  1992/10/21  03:02:35  pavel
 * Converted to use new automatic configuration system.
 *
 * Revision 1.10  1992/08/31  22:25:51  pjames
 * Changed some `char *'s to `const char *'
 *
 * Revision 1.9  1992/08/28  23:18:38  pjames
 * Added ASGN_RANGE parsing code.  Fixed tiny memory leak.
 *
 * Revision 1.8  1992/08/28  16:16:52  pjames
 * Changed `ak_dealloc_string()' to `free_str()'.
 *
 * Revision 1.7  1992/08/12  01:49:58  pjames
 * Negative literals are now accepted (instead of negated positive literals).
 *
 * Revision 1.6  1992/08/10  16:55:59  pjames
 * Updated #includes.
 *
 * Revision 1.5  1992/07/30  21:22:08  pjames
 * Removed max_stack calculations (moved to vector.c).
 *
 * Revision 1.4  1992/07/29  18:05:12  pjames
 * $$ no longer = NULL when there is an illegal left hand side of an
 * expression.
 *
 * Revision 1.3  1992/07/27  18:12:41  pjames
 * Changed name of ct_env to var_names and const_env to literals.
 * Modified call to vectorize to use new argument format.
 * Assignment statements now check left hand side properly for allowable
 * expressions, and now frees memory from reused expressions.
 *
 * Revision 1.2  1992/07/21  00:05:16  pavel
 * Added rcsid_<filename-root> declaration to hold the RCS ident. string.
 *
 * Revision 1.1  1992/07/20  23:23:12  pavel
 * Initial RCS-controlled version.
 */

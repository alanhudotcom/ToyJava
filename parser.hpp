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
     TIDENTIFIER = 258,
     TINTEGER = 259,
     TDOUBLE = 260,
     TSTRING = 261,
     TCEQ = 262,
     TCNE = 263,
     TCLT = 264,
     TCLE = 265,
     TCGT = 266,
     TCGE = 267,
     TEQUAL = 268,
     TLPAREN = 269,
     TRPAREN = 270,
     TLBRACE = 271,
     TRBRACE = 272,
     TCOMMA = 273,
     TDOT = 274,
     TPLUS = 275,
     TMINUS = 276,
     TMUL = 277,
     TDIV = 278,
     TRETURN = 279,
     TEXTERN = 280,
     TEND = 281,
     TPUBLIC = 282,
     TPROTECTED = 283,
     TPRIVATE = 284,
     TSTATIC = 285,
     TINTERFACE = 286,
     TCLASS = 287,
     TFOR = 288,
     TDO = 289,
     TWHILE = 290,
     TNEW = 291,
     TIF = 292
   };
#endif
/* Tokens.  */
#define TIDENTIFIER 258
#define TINTEGER 259
#define TDOUBLE 260
#define TSTRING 261
#define TCEQ 262
#define TCNE 263
#define TCLT 264
#define TCLE 265
#define TCGT 266
#define TCGE 267
#define TEQUAL 268
#define TLPAREN 269
#define TRPAREN 270
#define TLBRACE 271
#define TRBRACE 272
#define TCOMMA 273
#define TDOT 274
#define TPLUS 275
#define TMINUS 276
#define TMUL 277
#define TDIV 278
#define TRETURN 279
#define TEXTERN 280
#define TEND 281
#define TPUBLIC 282
#define TPROTECTED 283
#define TPRIVATE 284
#define TSTATIC 285
#define TINTERFACE 286
#define TCLASS 287
#define TFOR 288
#define TDO 289
#define TWHILE 290
#define TNEW 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "parser.y"
{

	ASTree *node;
	ASTLeaf *leaf;
	ASTFork *fork;
	NodeList *nodeList;
	SentenceList *sentenceList;
	VariableList *variableList;
	ValueLeaf    *valueNode;
	IdentifierASTLeaf *identifierNode;
	ReturnSentenceASTFork *returnNode;
	AssignmentASTFork   *assignNode;
	CastTypeASTFork     *castNode;
	BinaryASTFork       *binaryNode;
	ThreeASTFork        *threeNode;
	FragmentASTree      *fragmentNode;
	IfASTFork           *ifNode;
	ForASTFork          *forNode;
	PreWhileASTFork     *preWhileNode;
	BackWhileASTFork    *backWhileNode;
	VariableDeclarationASTFork *varDeclNode;
	InterfaceMethodASTFork     *interfaceMethodNode;
	StaticMethodASTFork        *staticMethodNode;
	NormalMethodASTFork        *normalMethodNode;
	InterfaceDefineASTFork     *interfaceNode;
	ClassDefineASTFork         *classNode;
	ClassDeclBodyASTFork       *classBodyNode;
	CallAttributionASTFork     *callAttrNode;
	CallMethodASTFork          *callMethodNode;
	NewObjectASTFork           *newObjNode;

	std::string *string;
	int token;
}
/* Line 1529 of yacc.c.  */
#line 156 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


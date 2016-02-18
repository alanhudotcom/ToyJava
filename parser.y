%{
	#include "JavaASTree.h"
    #include <cstdio>
    #include <cstdlib>
    #include "parser.hpp"
	ASTree *programBlock; /* the top level root node of our final AST */

    int yylex(void);
	void yyerror(const char *s) { std::printf("Error: %s\n", s);std::exit(1); }
%}

/* Represents the many different ways we can access our data */
%union {

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

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> TIDENTIFIER TINTEGER TDOUBLE TSTRING
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT
%token <token> TPLUS TMINUS TMUL TDIV
%token <token> TRETURN TEXTERN TEND

%token <token> TPUBLIC TPROTECTED TPRIVATE TSTATIC TINTERFACE TCLASS
%token <token> TFOR TDO TWHILE TNEW TIF

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <node> expr sentence
%type <token> comparison
%type <nodeList> call_args
%type <variableList> func_decl_args
%type <identifierNode> ident
%type <valueNode> primary
%type <varDeclNode> var_decl
%type <normalMethodNode> func_decl
/*
    %type <varDeclNode>
    %type <returnNode>
    %type <assignNode>
    %type <castNode>
    %type <binaryNode>
    %type <threeNode>
*/
%type <fragmentNode> stmts fragment
/*
    %type <ifNode>
    %type <forNode>
    %type <preWhileNode>
    %type <backWhileNode>
    %type <interfaceMethodNode>
    %type <staticMethodNode>
*/
/*
    %type <interfaceNode>
*/
%type <classNode> class
%type <classBodyNode> class_decl
/*
    %type <callAttrNode>
    %type <callMethodNode>
    %type <newObjNode>
*/


/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start fragment

%%


class : TCLASS ident TLBRACE class_decl TRBRACE
        {
        $$ = new ClassDefineASTFork(*$2,*$4);
        programBlock = $$;
        return 0;
        };

class_decl :func_decl {$$ = new ClassDeclBodyASTFork(); $$->methodList.push_back($1);}
            |var_decl TEND  {$$ = new ClassDeclBodyASTFork(); $$->variableList.push_back($1);}
            |class_decl func_decl {$1->methodList.push_back($2); $$=$1;}
            |class_decl  var_decl TEND {$1->variableList.push_back($2); $$=$1;};



fragment : TLBRACE stmts TRBRACE { $$ = $2; programBlock = $$; return 0;  }
           	  | TLBRACE TRBRACE { $$ =  new FragmentASTree();  };

stmts : sentence { $$ = new FragmentASTree(); $$->sentenceList.push_back((ASTree *)$1);}
        | stmts sentence { $1->sentenceList.push_back((ASTree *)$2); $$ = $1; };

sentence : expr TEND {$$ = $1;} | var_decl {$$ = (ASTree *) $1;} TEND
            | TRETURN expr TEND { $$ = new ReturnSentenceASTFork(*$2);} ;

var_decl :
            ident ident { $$ = new VariableDeclarationASTFork(*$1,*$2); }
            ;



func_decl : ident ident TLPAREN func_decl_args TRPAREN fragment
			{ $$ = new NormalMethodASTFork(*$2, *$1, *$4, *$6); delete $4; }
		  ;

func_decl_args : /*blank*/  { $$ = new VariableList(); }
		  | ident ident { VariableDeclarationASTFork * vd = new VariableDeclarationASTFork(*$1,*$2); $$ = new VariableList(); $$->push_back(vd); }
		  | func_decl_args TCOMMA ident ident { VariableDeclarationASTFork * vd = new VariableDeclarationASTFork(*$3,*$4); $1->push_back(vd); $$ = $1;}
		  ;


expr :primary {$$ = $1;} | ident TEQUAL expr { $$ = new AssignmentASTFork(*$1, $3); }
	 | ident TLPAREN call_args TRPAREN {$$ = new CallMethodASTFork(*$1, *$3); delete $3; }
	 | ident { $$ = $1; }
         | expr TMUL expr { $$ = new BinaryASTFork($1, $2, $3); }
         | expr TDIV expr { $$ = new BinaryASTFork($1, $2, $3); }
         | expr TPLUS expr { $$ = new BinaryASTFork($1, $2, $3); }
         | expr TMINUS expr { $$ = new BinaryASTFork($1, $2, $3); }
 	 | expr comparison expr { $$ = new BinaryASTFork($1, $2, $3); }
     | TLPAREN expr TRPAREN { $$ = $2; }
	 ;

call_args : /*blank*/  { $$ = new NodeList(); }
          | expr { $$ = new NodeList(); $$->push_back($1); }
          | call_args TCOMMA expr  { $1->push_back($3); }
          ;


primary : TINTEGER {$$ = new ValueLeaf(); $$->ptrLeafValue = dynamic_pointer_cast<BaseObject>(make_shared<BaseInteger>(std::atoi( $1->c_str() ))); }
            | TDOUBLE {$$ = new ValueLeaf(); $$->ptrLeafValue = dynamic_pointer_cast<BaseObject>(make_shared<BaseDouble>(std::atof( $1->c_str()))); }
            | TSTRING {$$ = new ValueLeaf(); $$->ptrLeafValue = dynamic_pointer_cast<BaseObject>(make_shared<BaseString>(*$1)); } ;

ident : TIDENTIFIER { $$ = new IdentifierASTLeaf(*$1); }


comparison : TCEQ  | TCNE  | TCLT  | TCLE  | TCGT  | TCGE ;

%%

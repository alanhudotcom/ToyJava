%{

#include <string>
#include "JavaASTree.h"
#include "parser.hpp"

#define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)    (yylval.token = t)

%}



%%

[ \t\n]					        ;
"extern"                        return TOKEN(TEXTERN);
"return"				        return TOKEN(TRETURN);

"public"                        return TOKEN(TPUBLIC);
"protected"                     return TOKEN(TPROTECTED);
"private"                       return TOKEN(TPRIVATE);
"static"                        return TOKEN(TSTATIC);
"interface"                     return TOKEN(TINTERFACE);
"class"                         return TOKEN(TCLASS);
"for"                           return TOKEN(TFOR);
"if"                            return TOKEN(TIF);
"do"                            return TOKEN(TDO);
"while"                         return TOKEN(TWHILE);
"new"                           return TOKEN(TNEW);
";"                             return TOKEN(TEND);

"\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\""   SAVE_TOKEN;return TOKEN(TSTRING);

[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]* 			    SAVE_TOKEN; return TDOUBLE;
[0-9]+					        SAVE_TOKEN; return TINTEGER;

"="						        return TOKEN(TEQUAL);
"=="				          	return TOKEN(TCEQ);
"!="			          		return TOKEN(TCNE);
"<"				          		return TOKEN(TCLT);
"<="	          				return TOKEN(TCLE);
">"				          		return TOKEN(TCGT);
">="					        return TOKEN(TCGE);

"("	          					return TOKEN(TLPAREN);
")"					          	return TOKEN(TRPAREN);
"{"         					return TOKEN(TLBRACE);
"}"					          	return TOKEN(TRBRACE);

"."         					return TOKEN(TDOT);
","				          		return TOKEN(TCOMMA);


"+"				          		return TOKEN(TPLUS);
"-"		          				return TOKEN(TMINUS);
"*"		          				return TOKEN(TMUL);
"/"				          		return TOKEN(TDIV);

.                               printf("Unknown token!\n"); yyterminate();

%%

int yywrap()
{
  return 0;
}
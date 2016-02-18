#include <iostream>
#include <stdio.h>
#include "JavaASTree.h"
#include "parser.hpp"

using namespace std;

extern int yyparse();



extern ASTree* programBlock;
extern FILE * yyin;

int main() {

    yyin = fopen("/Users/flb/ClionProjects/ToyJava/samplecode","r");

    if(yyin == NULL){
        cout << "open file fail " << endl;
    }

    yyparse();

    cout << "    ---- start execute ---- " << endl;

    CodeExecuteContext context;
    programBlock->executeCode(context);

    return 0;
}
//
// Created by fulongbin on 16/1/25.
//



#include "CodeExecute.h"
#include "JavaBaseType.h"
#include "JavaASTree.h"
#include "parser.hpp"



PtrValue ValueLeaf::executeCode(CodeExecuteContext &context) {
    return ptrLeafValue;
}

PtrValue IdentifierASTLeaf::executeCode(CodeExecuteContext &context) {
    
    map<string,PtrValue>::iterator  it ;
    for (it = context.varIdentPool.begin() ; it!=context.varIdentPool.end();it++) {
        BaseInteger * baseInteger = (BaseInteger *) it->second.get();
        cout << "[key : " << it->first << ", value : " <<  baseInteger->value << " ]" << endl;
    }
    
    PtrValue varValue = context.varIdentPool.at(idName);
    if(varValue==NULL || varValue.get()==NULL){
        if(context.outerContext != NULL){
            varValue = context.outerContext->varIdentPool[idName];
        }
    }
    BaseInteger *base = (BaseInteger *) varValue.get();
    cout << "VariableASTLeaf  map[ " << idName << " ] = " << base->value << endl;

    return varValue;
}

PtrValue ReturnSentenceASTFork::executeCode(CodeExecuteContext &context) {
    cout << "ReturnSentenceASTFork::executeCode" << endl;
    return returnNode.executeCode(context);
}

PtrValue AssignmentASTFork::executeCode(CodeExecuteContext &context) {
    PtrValue pValue = rightNode->executeCode(context);
//    context.varIdentPool.insert(make_pair(leftNode.idName,pValue));

    context.varIdentPool[leftNode.idName] = pValue;

    BaseInteger * baseInteger = (BaseInteger *) pValue.get();
    cout << "==AssignmentASTFork==  insert [ " << leftNode.idName << " , " << baseInteger->value << " ]" <<endl;

    map<string,PtrValue>::iterator it;
    for (it = context.varIdentPool.begin() ; it!=context.varIdentPool.end();it++) {
        BaseInteger * baseInteger = (BaseInteger *) it->second.get();
        cout << "[key : " << it->first << ", value : " << baseInteger->value << endl;
    }
    return pValue;
}

PtrValue CastTypeASTFork::executeCode(CodeExecuteContext &context) {
    cout << "CastTypeASTFork::executeCode" << endl;

    PtrValue pValue = rightNode.executeCode(context);
    return NULL;
}

PtrValue BinaryASTFork::executeCode(CodeExecuteContext &context) {


    PtrValue leftValue = leftNode->executeCode(context);
    PtrValue rightValue = rightNode->executeCode(context);

    BaseInteger * baseInteger = new BaseInteger(0);

    BaseInteger * left = (BaseInteger *)leftValue.get();
    BaseInteger * right = (BaseInteger *)rightValue.get();

    switch (operatorType){
        case TPLUS:
            baseInteger->value = left->value + right->value;
            break;
        case TMINUS:
            baseInteger->value = left->value - right->value;
            break;
        case TMUL:
            baseInteger->value = left->value * right->value;
            break;
        case TDIV:
            baseInteger->value = left->value / right->value;
            break;

    }

    cout << "BinaryASTFork::executeCode value " << baseInteger->value << endl;

    PtrValue ptrResult(baseInteger);

    return ptrResult;
}

PtrValue ThreeASTFork::executeCode(CodeExecuteContext &context) {
    cout << "ThreeASTFork::executeCode" << endl;

    BaseBoolean * pBool = (BaseBoolean *) judgeNode.executeCode(context).get();

    if(pBool){
        thenNode.executeCode(context);
    } else{
        elseNode.executeCode(context);
    }

    return NULL;
}

PtrValue FragmentASTree::executeCode(CodeExecuteContext &context) {
    cout << "FragmentASTree::executeCode" << endl;

    PtrExecuteContext ptrExecuteContext(&context);
    fragmentContext.outerContext = ptrExecuteContext;
    for (int i = 0; i < sentenceList.size() ; ++i) {
        sentenceList[i]->executeCode(fragmentContext);
    }
    return NULL;
}

PtrValue IfASTFork::executeCode(CodeExecuteContext &context) {
    cout << "IfASTFork::executeCode" << endl;

    if(((BaseBoolean *) judgeNode.executeCode(context).get())->value){

    } else{

    }
    return  NULL;
}

PtrValue ForASTFork::executeCode(CodeExecuteContext &context) {
    cout << "ForASTFork::executeCode" << endl;

    CodeExecuteContext forContext = repeatNode.fragmentContext;

    firstSentence.executeCode(forContext);

    while (((BaseBoolean *) secondSentence.executeCode(forContext).get())->value) {
        repeatNode.executeCode(forContext);
        thirdSentence.executeCode(forContext);
    }

    return NULL;
}

PtrValue PreWhileASTFork::executeCode(CodeExecuteContext &context) {
    cout << "PreWhileASTFork::executeCode" << endl;

    CodeExecuteContext whileContext = repeatNode.fragmentContext;

    while ( ((BaseBoolean *) judgeNode.executeCode(whileContext).get())->value ){
        repeatNode.executeCode(whileContext);
    }

    return NULL;
}

PtrValue BackWhileASTFork::executeCode(CodeExecuteContext &context) {
    cout << "BackWhileASTFork::executeCode" << endl;

    CodeExecuteContext whileContext = repeatNode.fragmentContext;
    do{
        repeatNode.executeCode(whileContext);
    }while ( ((BaseBoolean *) judgeNode.executeCode(whileContext).get())->value );

    return NULL;
}

PtrValue VariableDeclarationASTFork::executeCode(CodeExecuteContext &context) {
    cout << "VariableDeclarationASTFork::executeCode" << endl;


    if(identifierASTLeaf.idName == "int"){
        BaseInteger * baseInteger = new BaseInteger(0);
        PtrValue ptr((BaseObject *)baseInteger);
        context.varIdentPool.insert(map<string,PtrValue>::value_type(variableName.idName,ptr));
    } else
    if(identifierASTLeaf.idName == "double"){
        shared_ptr<BaseDouble> ptrValue = make_shared<BaseDouble>(0.0);
        PtrValue ptr((BaseObject *)ptrValue.get());
        context.varIdentPool.insert(map<string,PtrValue>::value_type(variableName.idName,ptr));
    } else
    if(identifierASTLeaf.idName == "boolean"){
        shared_ptr<BaseBoolean> ptrValue = make_shared<BaseBoolean>(false);
        PtrValue ptr((BaseObject *)ptrValue.get());
        context.varIdentPool.insert(map<string,PtrValue>::value_type(variableName.idName,ptr));
    }

    return NULL;
}


PtrValue ClassDefineASTFork::executeCode(CodeExecuteContext &context) {

    cout << "ClassDefineASTFork ---> executeCode" << endl;

    return NULL;
}
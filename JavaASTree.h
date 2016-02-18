//
// Created by fulongbin on 16/1/23.
//

#ifndef TOYJAVA_JAVAASTREE_H
#define TOYJAVA_JAVAASTREE_H

#include <iostream>
#include <vector>
#include "JavaBaseType.h"
#include "CodeExecute.h"


using namespace std;

class ASTLeaf;
class ASTFork;
class ASTree;
class VariableDeclarationASTFork;
class MethodDeclarationASTFork;

typedef  vector<ASTLeaf*> LeafList;
typedef  vector<ASTFork*> ForkList;
typedef  vector<ASTree*>  NodeList;
typedef  vector<ASTree*>  SentenceList;
typedef  vector<VariableDeclarationASTFork*> VariableList;
typedef  vector<MethodDeclarationASTFork*> NormalMethodList;

class ASTree{
public:
    virtual shared_ptr<BaseObject> executeCode(CodeExecuteContext & context) {return NULL;};
};

class ASTLeaf : public ASTree{

};

class ValueLeaf : public ASTLeaf{
public:
    shared_ptr<BaseObject> ptrLeafValue;
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
    ValueLeaf(){
        cout << "ValueLeaf" << endl;
    };
};
//关键字
class IdentifierASTLeaf : public ASTLeaf{
public:
    string idName;
    IdentifierASTLeaf(string & name):idName(name){
        cout << "IdentifierASTLeaf -->" << name << endl;
    }
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};


class ASTFork : public ASTree{
};


//赋值语句
class AssignmentASTFork : public ASTFork{
public:
    //被赋值
    IdentifierASTLeaf leftNode;
    //赋值
    ASTree * rightNode;
    AssignmentASTFork(IdentifierASTLeaf & assigned,ASTree * node):leftNode(assigned),rightNode(node){
        cout << "AssignmentASTFork --> " << assigned.idName << endl;
    };

    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//返回语句
class ReturnSentenceASTFork : public ASTFork{
public:
    ASTree returnNode;
    ReturnSentenceASTFork(ASTree & node):returnNode(node){};
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

// 强转类型
class CastTypeASTFork : public ASTFork{
public:
    IdentifierASTLeaf castType;
    ASTree rightNode;
    CastTypeASTFork(ASTFork & node,string & typeName):rightNode(node),castType(typeName){}

    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//两目运算
class BinaryASTFork : public ASTFork{
protected:
    int operatorType;
    ASTree * leftNode;
    ASTree * rightNode;
public:
    BinaryASTFork(ASTree * lfNode,int opType,ASTree * rtNode)
            :operatorType(opType),
             leftNode(lfNode),
             rightNode(rtNode){
        cout << "BinaryASTFork  " <<endl;
    }
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};
//三目运算
class ThreeASTFork : public ASTFork{
protected:
    ASTree judgeNode;
    ASTree thenNode;
    ASTree elseNode;
public:
    ThreeASTFork(ASTree & judge,ASTree & then,ASTree & else_):
            judgeNode(judge),thenNode(then),elseNode(else_){

    }
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//语句块
class FragmentASTree : public ASTFork{
public:
    NodeList sentenceList;
    CodeExecuteContext fragmentContext;
    FragmentASTree(){}
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//if判断句
class IfASTFork :public ASTFork{
protected:
    ASTree judgeNode;
    ASTree thenNode;
    ASTree elseNode;
public:
    IfASTFork(ASTree & judge,ASTree & then,ASTree & else_):
    judgeNode(judge),thenNode(then),elseNode(else_){

    }
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//for 运算
class ForASTFork : public  ASTFork{
    ASTree firstSentence;
    ASTree secondSentence;
    ASTree thirdSentence;

    FragmentASTree  repeatNode;

    ForASTFork(ASTFork & first,ASTFork & second,ASTFork & third,FragmentASTree & repeat)
            :firstSentence(first),
             secondSentence(second),
             thirdSentence(third),
             repeatNode(repeat){}
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//while(){} 语句
class PreWhileASTFork : public  ASTFork{
protected:
    ASTree judgeNode;
    FragmentASTree repeatNode;
public:
    PreWhileASTFork(ASTree & judge,FragmentASTree & repeat):judgeNode(judge),repeatNode(repeat){

    }
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};
//do{}while()语句
class BackWhileASTFork : public  ASTFork{
protected:
    ASTree judgeNode;
    FragmentASTree repeatNode;
public:
    BackWhileASTFork(ASTree & judge,FragmentASTree & repeat):judgeNode(judge),repeatNode(repeat){

    }
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};
//变量定义
class VariableDeclarationASTFork : public  ASTFork{

public:
    //变量类型
    IdentifierASTLeaf identifierASTLeaf;
    //变量名
    IdentifierASTLeaf variableName;
    VariableDeclarationASTFork(IdentifierASTLeaf & idLeaf,IdentifierASTLeaf & varLeaf):
            identifierASTLeaf(idLeaf),
            variableName(varLeaf){}
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//接口方法
class InterfaceMethodASTFork : public ASTFork{
public:
    //变量名
    IdentifierASTLeaf methodIdentifier;
    //参数列表
    VariableList parameterList;
    //
    IdentifierASTLeaf returnIdentifier;
    InterfaceMethodASTFork(IdentifierASTLeaf & methodName,IdentifierASTLeaf & returnType,VariableList & varList)
            :methodIdentifier(methodName),returnIdentifier(returnType),parameterList(varList){};
};


class MethodDeclarationASTFork : public InterfaceMethodASTFork{
public:
    FragmentASTree fragmentASTree;
    MethodDeclarationASTFork(IdentifierASTLeaf & methodName,IdentifierASTLeaf & returnType,VariableList & varList,FragmentASTree & fragment)
            :InterfaceMethodASTFork(methodName,returnType,varList),fragmentASTree(fragment){};
};

//静态方法
class StaticMethodASTFork : public MethodDeclarationASTFork{
    StaticMethodASTFork(IdentifierASTLeaf & methodName,IdentifierASTLeaf & returnType,VariableList & varList,FragmentASTree & fragment):MethodDeclarationASTFork(methodName,returnType,varList,fragment){};
};

//类方法
class NormalMethodASTFork : public MethodDeclarationASTFork{
public:
    NormalMethodASTFork(IdentifierASTLeaf & methodName,IdentifierASTLeaf & returnType,VariableList & varList,FragmentASTree & fragment):MethodDeclarationASTFork(methodName,returnType,varList,fragment){};
};

//接口
class InterfaceDefineASTFork : public ASTFork{
public:
    IdentifierASTLeaf interfaceIdentifier;
    InterfaceDefineASTFork(string & interfaceName):interfaceIdentifier(interfaceName){};
};

class ClassDeclBodyASTFork : public ASTFork{
public:
    VariableList staticVariableList;
    NormalMethodList   staticMethodList;
    VariableList variableList;
    NormalMethodList   methodList;
    ClassDeclBodyASTFork(){
        cout << "ClassDeclBodyASTFork" << endl;
    }
};

//类定义
class ClassDefineASTFork : public ASTFork{
public:
    IdentifierASTLeaf classIdentifier;
    ClassDeclBodyASTFork classBody;
    ClassDefineASTFork(IdentifierASTLeaf & identifierASTLeaf,ClassDeclBodyASTFork & body)
            :classIdentifier(identifierASTLeaf),classBody(body){
        cout << "ClassDefineASTFork" << endl;
    }
//    ClassDefineASTFork(IdentifierASTLeaf & identifierASTLeaf,IdentifierASTLeaf & super,ClassDeclBodyASTFork body)
//            :classIdentifier(identifierASTLeaf),superIdentifier(super),classBody(body){}
    shared_ptr<BaseObject> executeCode(CodeExecuteContext & context);
};

//调用类成员
class CallClassMemberASTFork : public ASTFork{
public:
    IdentifierASTLeaf callobject;
    IdentifierASTLeaf interfaceIdentifier;
    CallClassMemberASTFork(IdentifierASTLeaf & memberName,IdentifierASTLeaf & varLeaf):interfaceIdentifier(memberName),callobject(varLeaf){};
    CallClassMemberASTFork(IdentifierASTLeaf & memberName,string varName):interfaceIdentifier(memberName),callobject(varName){};
};
//调用属性
class CallAttributionASTFork : public CallClassMemberASTFork{
public:
    IdentifierASTLeaf attributionNode;
    CallAttributionASTFork(IdentifierASTLeaf & attribution,IdentifierASTLeaf & attributionName,IdentifierASTLeaf & varLeaf)
            :CallClassMemberASTFork(attributionName,varLeaf),
             attributionNode(attribution){};
};

//调用类方法

class CallMethodASTFork : public CallClassMemberASTFork{
public:
    NodeList   argsList;
    CallMethodASTFork(IdentifierASTLeaf & methodNode,NodeList & nodeList,IdentifierASTLeaf & varLeaf):CallClassMemberASTFork(methodNode,varLeaf),argsList(nodeList){}
    CallMethodASTFork(IdentifierASTLeaf & methodNode,NodeList & nodeList):CallClassMemberASTFork(methodNode,"this"),argsList(nodeList){}
};

//new Object()方法

class NewObjectASTFork : public ASTFork{
public:
    StaticMethodASTFork constructorMethod;
    NewObjectASTFork(StaticMethodASTFork & method):constructorMethod(method){};
};

#endif //TOYJAVA_JAVAASTREE_H

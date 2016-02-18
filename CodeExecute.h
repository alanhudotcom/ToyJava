//
// Created by fulongbin on 16/1/25.
//

#ifndef TOYJAVA_CODEEXECUTE_H
#define TOYJAVA_CODEEXECUTE_H

#include <map>
#include <vector>
#include <iostream>
#include "JavaBaseType.h"

using namespace std;

class CodeExecuteContext;
typedef  shared_ptr<CodeExecuteContext> PtrExecuteContext;
/**
 * context 执行代码上下文
 */
class CodeExecuteContext{
public:
    //定义变量
    map<string,PtrValue> varIdentPool;
    //匿名变量

    //外部context
    PtrExecuteContext outerContext;
};

class ClassExecuteContext{
public:
    PtrExecuteContext superClass;
    PtrExecuteContext thisClass;
};

#endif //TOYJAVA_CODEEXECUTE_H

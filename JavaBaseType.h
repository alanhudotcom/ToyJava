//
// Created by fulongbin on 16/1/23.
//

#ifndef TOYJAVA_JAVABASETYPE_H
#define TOYJAVA_JAVABASETYPE_H

#include <iostream>
#include <map>
using namespace std;

enum BaseDataType{
    INT,FLOAT,BOOLEAN,STRING,LONG,DOUBLE
};



class BaseObject{
protected:
    BaseDataType enumObjType;
public:
    BaseDataType getObjectType(){
        return enumObjType;
    }
};

typedef  shared_ptr<BaseObject> PtrValue;

class BaseInteger :public BaseObject{
public:
    int value;
    BaseInteger(int val):value(val){
        enumObjType = INT;
        cout << "BaseInteger 构造 value=" << value << endl;
    };
    ~BaseInteger(){
        cout << "析构 值 : " << value << endl;
    }
};

class BaseFloat : public BaseObject{
public:
    float value;
};

class BaseDouble : public BaseObject{
public:
    double value;
    BaseDouble(double val):value(val){
        enumObjType = DOUBLE;
    }
};

class BaseBoolean : public BaseObject{
public:
    bool value;
    BaseBoolean():value(false){
        enumObjType = BOOLEAN;
    }

    BaseBoolean(bool initVal):value(initVal){
        enumObjType = BOOLEAN;
    }
};

class BaseString : public BaseObject{
public:
    string value;
    BaseString(string & val):value(val){}
};

class  JavaClassInfo{
public:
    map<string,PtrValue> varClassPool;

};

class BaseClass  :public BaseObject{
public:
    JavaClassInfo javaClassInfo;
};

#endif //TOYJAVA_JAVABASETYPE_H

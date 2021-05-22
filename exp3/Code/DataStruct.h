#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_
#define HASH_TABLE_SIZE 50

#include "MyEnum.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct TableNode_* TableNode;

struct Type_
{
    enum { BASIC, ARRAY, STRUCTURE, FUNCTION} kind;
    union{
        enum { Type_INT, Type_FLOAT } basic;

        struct { Type elem; int size; } array;

        FieldList structure;

        struct{
            Type returnType;
            // 似乎不用记录名字
            char name[32];
            int argc;
            int line;
            FieldList argv;
            Boolean decFlag;   // 0表示声明，1表示定义
        }function;
    }u;
};

struct FieldList_
{
    char name[33];
    Type type;
    FieldList next;
};

struct TableNode_
{
    char name[33];
    Type type;
    char variable[33];
    TableNode next;
};


#endif
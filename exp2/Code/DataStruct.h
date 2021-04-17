#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_
#define HASH_TABLE_SIZE 50

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
            char name[32];
            int argc;
            FieldList argv;
        }function;
    }u;
};

struct FieldList_
{
    char name[33];
    Type type;
    FieldList tail;
};

struct TableNode_
{
    char name[33];
    Type type;
    TableNode next;
};


#endif
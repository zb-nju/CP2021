#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_
#define HASH_TABLE_SIZE 50

#include "MyEnum.h"

typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;
typedef struct TableNode_ *TableNode;
typedef struct Operand_ *Operand;
typedef struct InterCode_ *InterCode;
typedef struct Arg_list_ *Arg_list;

struct Type_
{
    enum
    {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNCTION
    } kind;
    union
    {
        enum
        {
            Type_INT,
            Type_FLOAT
        } basic;

        struct
        {
            Type elem;
            int size;
        } array;

        FieldList structure;

        struct
        {
            Type returnType;
            // 似乎不用记录名字
            char name[32];
            int argc;
            int line;
            FieldList argv;
            Boolean decFlag; // 0表示声明，1表示定义
        } function;
    } u;
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
    Operand op;
    TableNode next;
};

struct Operand_
{
    enum
    {
        VARIABLE_OP,
        CONSTANT_OP,
        ADDRESS_OP,
        TEMP_VAR_OP,
        FUNCTION_OP,
        LABEL_OP,
        RELOP_OP,
        ARRAY_OP,
        STRUCT_OP,
        ARRAY_ADDR_OP,
        STRUCT_ADDR_OP,
        VALUE_ADDR_OP,
    } kind;
    union
    {
        int var_no;
        char value[32];
    } u;
};

struct InterCode_
{
    enum
    {
        LABEL_IR,
        FUNCTION_IR,
        ASSIGN_IR,
        ADD_IR,
        SUB_IR,
        MUL_IR,
        DIV_IR,
        GET_ADDR_IR,
        GET_VALUE_IR,
        ASSIGN_ADDR_IR,
        GOTO_IR,
        RELOP_GOTO_IR,
        RETURN_IR,
        DEC_IR,
        ARG_IR,
        CALL_IR,
        PARAM_IR,
        READ_IR,
        WRITE_IR
    } kind;
    union
    {
        struct
        {
            Operand right, left;
        } assign;
        struct
        {
            Operand result, op1, op2;
        } binop;
        struct
        {
            Operand op;
        } signleop;
        struct
        {
            Operand x, y, label_z;
            char relop[32];
        } if_goto;
        struct
        {
            Operand op;
            int size;
        } dec;
    } u;
    InterCode prev, next;
};

struct Arg_list_
{
    Operand arg;
    Arg_list next;
};
#endif
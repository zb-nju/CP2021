#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include"Node.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct Type_
{
    enum { BASIC, ARRAY, STRUCTURE, FUNCTION} kind;
    union{
        int basic;

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

//暂时将返回值设置为 void，后续实现时按需删改
//High-level Definitions
void Program(Node root);
void ExtDefList(Node root);
void ExtDef(Node root);
void ExtDecLidt(Node root);

//Specifiers
void Specifier(Node root);
void StuctSpecifier(Node root);
void OptTag(Node root);
void Tag(Node root);

//Declarators
void VarDec(Node root);
void FunDec(Node root);
void VarList(Node root);
void ParamDec(Node root);

//Statements
void CompSt(Node root);
void StmtList(Node root);
void Stmt(Node root);

//Local Definitions
void DefList(Node root);
void Def(Node root);
void DecList(Node root);
void Dec(Node root);

//Expressions
void Exp(Node root);
void Args(Node root);


#endif
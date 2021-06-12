#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "Node.h"
#include "DataStruct.h"

//暂时将返回值设置为 void，后续实现时按需删改
//High-level Definitions
void Program(Node root);

void ExtDefList(Node root);
void ExtDef(Node root);
void ExtDecList(Node root, Type type);

//Specifiers
Type Specifier(Node root);
Type StructSpecifier(Node root);
char* OptTag(Node root);
char* Tag(Node root);

//For struct
void DefList_Struct(Node root, FieldList alreadyDefined);
FieldList Def_Struct(Node root);
FieldList DecList_Struct(Node root, Type decType);
FieldList Dec_Struct(Node root, Type decType);

//Declarators
TableNode VarDec(Node root, Type type);
void FunDec(Node root, Type returnType);
FieldList VarList(Node root, Boolean flag);
FieldList ParamDec(Node root, Boolean flag);

void FunDeclare(Node root, Type returnType);

//Statements
void CompSt(Node root, Type returnType);
void StmtList(Node root, Type returnType);
void Stmt(Node root, Type returnType);

//Local Definitions
void DefList(Node root);
void Def(Node root);
void DecList(Node root, Type decType);
void Dec(Node root, Type decType);

//Expressions
Type Exp(Node root);
void Args(Node root, TableNode tn);

Type Exp_ASSIGNOP(Node root);
Type Exp_AND_OR(Node root);
Type Exp_RELOP_CAL(Node root);
Type Exp_LPRP(Node root);
Type Exp_MIUNS(Node root);
Type Exp_NOT(Node root);
Type Exp_FUNCTION_CALL(Node root);
Type Exp_ARRAY_VISIT(Node root);
Type Exp_STRUCT_VISIT(Node root);
Type Exp_ID(Node root);
Type Exp_INT(Node root);
Type Exp_FLOAT(Node root);

#endif
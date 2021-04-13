#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include"Node.h"
#include"DataStruct.h"
#include"SymbolTable.h"


//暂时将返回值设置为 void，后续实现时按需删改
//High-level Definitions
void Program(Node root);

//似乎并没有暴露这些接口的必要
// void ExtDefList(Node root);
// void ExtDef(Node root);
// void ExtDecList(Node root, Type type);

// //Specifiers
// Type Specifier(Node root);
// void StuctSpecifier(Node root);
// void OptTag(Node root);
// void Tag(Node root);

// //Declarators
// void VarDec(Node root);
// void FunDec(Node root);
// void VarList(Node root);
// void ParamDec(Node root);

// //Statements
// void CompSt(Node root);
// void StmtList(Node root);
// void Stmt(Node root);

// //Local Definitions
// void DefList(Node root);
// void Def(Node root);
// void DecList(Node root);
// void Dec(Node root);

// //Expressions
// void Exp(Node root);
// void Args(Node root);


#endif
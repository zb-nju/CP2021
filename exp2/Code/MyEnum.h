#ifndef _MY_ENUM_H_
#define _MY_ENUM_H_

typedef enum{
    true = 1,
    false = 0
}Boolean;

typedef enum NodeType_{
    Node_Program = 1,
    Node_ExtDefList,
    Node_ExtDef,
    Node_ExtDecList,
    Node_Specifier,
    Node_StructSpecifier,
    Node_OptTag,
    Node_Tag,
    Node_VarDec,
    Node_FunDec,
    Node_VarList,
    Node_ParamDec,
    Node_CompSt,
    Node_StmtList,
    Node_Stmt,
    Node_DefList,
    Node_Def,
    Node_DecList,
    Node_Dec,
    Node_Exp,
    Node_Args,
    Node_IF,
    Node_ELSE,
    Node_TYPE,
    Node_WHILE,
    Node_STRUCT,
    Node_RETURN,
    Node_SEMI,
    Node_COMMA,
    Node_ASSIGNOP,
    Node_RELOP,
    Node_PLUS,
    Node_MINUS,
    Node_STAR,
    Node_DIV,
    Node_AND,
    Node_OR,
    Node_DOT,
    Node_NOT,
    Node_LP,
    Node_RP,
    Node_LB,
    Node_RB,
    Node_LC,
    Node_RC,
    Node_ID,
    Node_INT,
    Node_FLOAT
}NodeName;

char* NodeNameToString(NodeName name);

#endif
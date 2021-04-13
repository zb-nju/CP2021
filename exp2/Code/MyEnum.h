#ifndef _MY_ENUM_H_
#define _MY_ENUM_H_

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

char* NodeNameToString(NodeName name){
    switch (name)
    {
    case Node_Program: return "Program"; break;
    case Node_ExtDefList: return "ExtDefList"; break;
    case Node_ExtDef: return "ExtDef"; break;
    case Node_ExtDecList: return "ExtDecList"; break;
    case Node_Specifier: return "Specifier"; break;
    case Node_StructSpecifier: return "StructSpecifier"; break;
    case Node_OptTag: return "OptTag"; break;
    case Node_Tag: return "Tag"; break;
    case Node_VarDec: return "VarDec"; break;
    case Node_FunDec: return "FunDec"; break;
    case Node_VarList: return "VarList"; break;
    case Node_ParamDec: return "ParaDec"; break;
    case Node_CompSt: return "CompSt"; break;
    case Node_StmtList: return "StmtList"; break;
    case Node_Stmt: return "Stmt"; break;
    case Node_DefList: return "DefList"; break;
    case Node_Def: return "Def"; break;
    case Node_DecList: return "DecList"; break;
    case Node_Dec: return "Dec"; break;
    case Node_Exp: return "Exp"; break;
    case Node_Args: return "Args"; break;
    case Node_IF: return "IF"; break;
    case Node_ELSE: return "ELSE"; break;
    case Node_TYPE: return "TYPE"; break;
    case Node_WHILE: return "WHILE"; break;
    case Node_STRUCT: return "STRUCT"; break;
    case Node_RETURN: return "RETURN"; break;
    case Node_SEMI: return "SEMI"; break;
    case Node_COMMA: return "COMMA"; break;
    case Node_ASSIGNOP: return "ASSIGNOP"; break;
    case Node_RELOP: return "RELOP"; break;
    case Node_PLUS: return "PLUS"; break;
    case Node_MINUS: return "MINUS"; break;
    case Node_STAR: return "STAR"; break;
    case Node_DIV: return "DIV"; break;
    case Node_AND: return "AND"; break;
    case Node_OR: return "OR"; break;
    case Node_DOT: return "DOT"; break;
    case Node_NOT: return "NOT"; break;
    case Node_LP: return "LP"; break;
    case Node_RP: return "RP"; break;
    case Node_LB: return "LB"; break;
    case Node_RB: return "RB"; break;
    case Node_LC: return "LC"; break;
    case Node_RC: return "RC"; break;
    case Node_ID: return "ID"; break;
    case Node_INT: return "INT"; break;
    case Node_FLOAT: return "FLOAT"; break;
    default:
        return "";
        break;
    }
}

#endif
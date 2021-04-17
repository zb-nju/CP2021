#include "Semantic.h"

//High-level Definitions
void Program(Node root){
    ExtDefList(root->firstChild);
}
void ExtDefList(Node root){
    if (root == NULL)
        return;
    assert(root->firstChild != NULL);

    ExtDef(root->firstChild);
    ExtDefList(root->firstChild->nextBrother);
}
void ExtDef(Node root){
    //ExtDef → Specifier ExtDecList SEMI
    //   | Specifier SEMI
    //   | Specifier FunDec CompSt
    Type specifier = Specifier(root->firstChild);
    Node secondChild = root->firstChild->nextBrother;
    if (secondChild->name == Node_ExtDecList){
        ExtDecList(secondChild->nextBrother, specifier);
    }
    else if (secondChild->name == Node_FunDec){
        FunDec(secondChild->nextBrother, specifier);
        FunDec(secondChild->nextBrother->nextBrother, specifier);
    }
    else{
    }
}
void ExtDecList(Node root, Type specifier){
    //ExtDecList → VarDec
    //   | VarDec COMMA ExtDecList
    TableNode tableNode = VarDec(root->firstChild, specifier);
    if (insert(tableNode) == false){
        //TODO: solute conflict
    }
    if (root->firstChild->nextBrother != NULL)
        ExtDecList(root->firstChild->nextBrother->nextBrother, specifier);
}

//Specifiers
Type Specifier(Node root){
    Node child = root->firstChild;
    if(child->name == Node_TYPE){
        Type type = (Type)malloc(sizeof(struct Type_));
        type->kind = BASIC;
        if(strcmp(child->firstChild->val, "int") == 0)
            type->u.basic = Type_INT;
        else
            type->u.basic = Type_FLOAT;
        return type;
    }else
        return StructSpecifier(child);
}
Type StuctSpecifier(Node root){
    
}
void OptTag(Node root){
}
void Tag(Node root){
}

//Declarators
TableNode VarDec(Node root, Type type){
}
void FunDec(Node root, Type returnType){
}
void VarList(Node root){
}
void ParamDec(Node root){
}

//Statements
void CompSt(Node root){
}
void StmtList(Node root){
}
void Stmt(Node root){
}

//Local Definitions
void DefList(Node root){
}
void Def(Node root){
}
void DecList(Node root){
}
void Dec(Node root){
}

//Expressions
void Exp(Node root){
}
void Args(Node root){
}

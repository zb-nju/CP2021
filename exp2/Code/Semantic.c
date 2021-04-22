#include "Semantic.h"
#include "Node.h"
#include "DataStruct.h"
#include "SymbolTable.h"
#include "MyEnum.h"
#include "Help.h"
#include <string.h>

//High-level Definitions
void Program(Node root){
    initSymbolTable();
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
        CompSt(secondChild->nextBrother->nextBrother, specifier);
    }
    else{
    }
}
void ExtDecList(Node root, Type specifier){
    //ExtDecList → VarDec
    //   | VarDec COMMA ExtDecList
    TableNode tableNode = VarDec(root->firstChild, specifier);
    if (insertIntoSymbolTable(tableNode) == false){
        //TODO: 错误3
    }
    if (root->childNum == 3)
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
    //StructSpecifier → STRUCT OptTag LC DefList RC
    //    | STRUCT Tag
    Node secondChild = root->firstChild->nextBrother;
    Type retType;
    if(root->childNum == 5){
        //建立一个新的符号表节点，并将该节点插入符号表

        if(secondChild != NULL && checkSymbolByName(OptTag(secondChild))){
            //TODO: 错误16，实验选做2-3要求根据结构判断是否相同，此处重新做判断
        }

        TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
        if(secondChild != NULL)
            strcpy(newNode->name, OptTag(secondChild));
        Type newType = (Type)malloc(sizeof(struct Type_));

        newType->kind = STRUCTURE;
        newType->u.structure = DefList(secondChild->nextBrother->nextBrother);
        newNode->type = newType;

        newNode->next = NULL;

        insertIntoSymbolTable(newNode);

        retType = newType;

    }else{
        //根据名字找到符号表上对应的节点进行判断
        TableNode ret = getTableNode(Tag(secondChild));
        if(ret == NULL || ret->type->kind != STRUCTURE){
            //TODO: 错误17
        }else
            retType = ret->type;       //可能需要深拷贝
    }
    return retType;
}
char* OptTag(Node root){
    return root->firstChild->val;
}
char* Tag(Node root){
    return root->firstChild->val;
}

//Declarators
TableNode VarDec(Node root, Type type){
    // VarDec → ID
    // | VarDec LB INT RB
    TableNode retNode = NULL;
    if(root->childNum == 1){
        retNode = (TableNode)malloc(sizeof(struct TableNode_));

        strcpy(retNode->name, root->firstChild->val);

        retNode->type = type;

        retNode->next = NULL;
    }else{
        retNode = VarDec(root->firstChild);

        Type newType = (Type)malloc(sizeof(struct Type_));
        newType->kind = ARRAY;
        newType->u.array.elem = retNode->type;
        if(root->firstChild->nextBrother->nextBrother->name != Node_INT){
            // TODO: 错误10
        }
        newType->u.array.size = stringToInt(root->firstChild->nextBrother->nextBrother->val);

        retNode->type = newType;
    }
    return retNode;
}
void FunDec(Node root, Type returnType){
    // FunDec → ID LP VarList RP
    //        | ID LP RP
    TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
    strcpy(newNode->name, root->firstChild->val);
    newNode->next = NULL;

    Type newType = (Type)malloc(sizeof(struct Type_));
    newType->kind = FUNCTION;
    newType->u.function.returnType = returnType;
    if(root->childNum == 4){
        FieldList temp = VarList(root->firstChild->nextBrother->nextBrother);
        newType->u.function.argv = temp;
        newType->u.function.argc = calculateArgc(temp);
    }else{
        newType->u.function.argv = NULL;
        newType->u.function.argc = 0;
    }

    newNode->type = newType;
    if(insertIntoSymbolTable(newNode) == false){
        //TODO: 错误4
    }

}
FieldList VarList(Node root){
    // VarList → ParamDec COMMA VarList
    //         | ParamDec
    FieldList field = ParamDec(root->firstChild);
    if(root->childNum == 3){
        field->next = VarList(root->firstChild->nextBrother->nextBrother);
    }
}
FieldList ParamDec(Node root){
    // ParamDec → Specifier VarDec
    Type specifier = Specifier(root->firstChild);
    TableNode tableNode = VarDec(root->firstChild, specifier);
    if (insertIntoSymbolTable(tableNode) == false){
        //TODO: 错误3
    }
    FieldList ret = (FieldList)malloc(sizeof(struct FieldList_));
    strcpy(ret->name, tableNode->name);
    ret->type = tableNode->type;
    ret->next = NULL;

    return ret;
}

//Statements
void CompSt(Node root){
}
void StmtList(Node root){
}
void Stmt(Node root){
}

//Local Definitions
FieldList DefList(Node root){
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

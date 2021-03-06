#include "Semantic.h"
#include "Node.h"
#include "DataStruct.h"
#include "SymbolTable.h"
#include "MyEnum.h"
#include "Help.h"
#include <string.h>

// #define DEBUG
extern TableNode SymbolTable[HASH_TABLE_SIZE];

void addRead(){
    TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
    strcpy(newNode->name, "read");

    Type type = (Type)malloc(sizeof(struct Type_));
    type->kind = FUNCTION;

    Type retType = (Type)malloc(sizeof(struct Type_));
    retType->kind = BASIC;
    retType->u.basic = Type_INT;

    type->u.function.returnType = retType;
    type->u.function.argc = 0;
    type->u.function.line = -1;
    type->u.function.argv = NULL;
    type->u.function.decFlag = true;

    newNode->type = type;

    assert(insertIntoSymbolTable(newNode));
}

void addWrite(){
    TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
    strcpy(newNode->name, "write");

    Type type = (Type)malloc(sizeof(struct Type_));
    type->kind = FUNCTION;

    Type retType = (Type)malloc(sizeof(struct Type_));
    retType->kind = BASIC;
    retType->u.basic = Type_INT;

    type->u.function.returnType = retType;
    type->u.function.argc = 1;
    type->u.function.line = -1;
    type->u.function.decFlag = true;

    FieldList fl = (FieldList)malloc(sizeof(struct FieldList_));
    Type argType = (Type)malloc(sizeof(struct Type_));
    argType->kind = BASIC;
    argType->u.basic = Type_INT;
    fl->type = argType;
    fl->next = NULL;

    type->u.function.argv = fl;

    newNode->type = type;

    assert(insertIntoSymbolTable(newNode));
}



//High-level Definitions
void Program(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Program", root->lineNum);
        perror(msg);
    #endif

    initSymbolTable();
    addRead();
    addWrite();
    ExtDefList(root->firstChild);
    // 判断是否有只声明无定义的函数
    for(int i=0; i<HASH_TABLE_SIZE; ++i){
        if(SymbolTable[i]!=NULL && SymbolTable[i]->type->kind == FUNCTION){
            if(SymbolTable[i]->type->u.function.decFlag == false){
                // Error Type 18
                printf("Error type 18 at Line %d: Undefined function '%s'.\n", SymbolTable[i]->type->u.function.line, SymbolTable[i]->type->u.function.name);
            }
        }
    }
   
}
void ExtDefList(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, ExtDefList", root->lineNum);
        perror(msg);
    #endif
    if (root->childNum == 0)
        return;

    ExtDef(root->firstChild);
    ExtDefList(root->firstChild->nextBrother);
}
void ExtDef(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, ExtDef", root->lineNum);
        perror(msg);
    #endif
    //ExtDef → Specifier ExtDecList SEMI
    //   | Specifier SEMI
    //   | Specifier FunDec CompSt
    //   | Specifier FunDec SEMI
    Type specifier = Specifier(root->firstChild);
    Node secondChild = root->firstChild->nextBrother;
    if (secondChild->name == Node_ExtDecList){
        ExtDecList(secondChild, specifier);
    }
    else if (secondChild->name == Node_FunDec){
        if(secondChild->nextBrother == NULL){
            FunDeclare(secondChild, specifier);
        }else{
            FunDec(secondChild, specifier);
            CompSt(secondChild->nextBrother, specifier);
        }
    }
    else{
    }
}
void ExtDecList(Node root, Type specifier){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, ExtDecList", root->lineNum);
        perror(msg);
    #endif
    //ExtDecList → VarDec
    //   | VarDec COMMA ExtDecList
    TableNode tableNode = VarDec(root->firstChild, specifier);
    if (insertIntoSymbolTable(tableNode) == false){
        // Error Type 3
        printf("Error type 3 at Line %d: Redefined variable '%s'.\n",root->lineNum, tableNode->name);
        return;
    }
    if (root->childNum == 3)
        ExtDecList(root->firstChild->nextBrother->nextBrother, specifier);
}

//Specifiers
Type Specifier(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Specifier", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;
    if(child->name == Node_TYPE){
        Type type = (Type)malloc(sizeof(struct Type_));
        type->kind = BASIC;
        if(strcmp(child->val, "int") == 0){
            type->u.basic = Type_INT;
        }
        else{
            type->u.basic = Type_FLOAT;
        }
        return type;
    }else
        return StructSpecifier(child);
}
Type StructSpecifier(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, StructSpecifier", root->lineNum);
        perror(msg);
    #endif
    //StructSpecifier → STRUCT OptTag LC DefList RC
    //    | STRUCT Tag
    Node secondChild = root->firstChild->nextBrother;
    Type retType = NULL;
    if(root->childNum >= 4){
        //建立一个新的符号表节点，并将该节点插入符号表

        if(root->childNum == 5 && checkSymbolByName(OptTag(secondChild))){
            // Error Type 16
            printf("Error Type 16 at Line %d: Refined structure '%s'.\n", secondChild->lineNum, OptTag(secondChild));
            return retType;
        }

        TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
        if(root->childNum == 5)
            strcpy(newNode->name, OptTag(secondChild));
        Type newType = (Type)malloc(sizeof(struct Type_));

        newType->kind = STRUCTURE;
        FieldList alreadyDefined = (FieldList)malloc(sizeof(struct FieldList_));
        alreadyDefined->next=NULL;
        if(root->childNum == 5){
            DefList_Struct(secondChild->nextBrother->nextBrother, alreadyDefined);
        }else{
            DefList_Struct(root->firstChild->nextBrother->nextBrother, alreadyDefined);
        }
        newType->u.structure = alreadyDefined->next;
        newNode->type = newType;
        newNode->next = NULL;
        newNode->op = NULL;

        insertIntoSymbolTable(newNode);

        retType = newType;

    }else{
        //根据名字找到符号表上对应的节点进行判断
        TableNode ret = getTableNode(Tag(secondChild));
        if(ret == NULL || ret->type->kind != STRUCTURE){
            // Error Type 17
            printf("Error Type 17 at Line %d: Undefined structure '%s'.\n", secondChild->lineNum, Tag(secondChild));
        }else
            retType = ret->type;       //TODO: 可能需要深拷贝
    }
    return retType;
}
char* OptTag(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, OptTag", root->lineNum);
        perror(msg);
    #endif
    return root->firstChild->val;
}
char* Tag(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Tag", root->lineNum);
        perror(msg);
    #endif
    return root->firstChild->val;
}

//For struct
void DefList_Struct(Node root, FieldList alreadyDefined){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, DefList_Struct", root->lineNum);
        perror(msg);
    #endif
    if (root->childNum == 0)
        return;

    FieldList def = Def_Struct(root->firstChild);
    FieldList tmp = def;
    while(tmp){
        FieldList cur = alreadyDefined->next;
        while(cur){
            if(strcmp(cur->name, tmp->name)==0){
                printf("Error Type 15 at Line %d: Refined field '%s'.\n", root->firstChild->lineNum, tmp->name);
                break;
            }
            cur = cur->next;
        }
        tmp = tmp->next;
    }
    tmp = alreadyDefined;
    while(tmp->next){
        tmp = tmp->next;
    }
    tmp->next = def;

    DefList_Struct(root->firstChild->nextBrother, alreadyDefined);
    return;
}
FieldList Def_Struct(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Def_Struct", root->lineNum);
        perror(msg);
    #endif
    Type specifier = Specifier(root->firstChild);
    Node secondChild = root->firstChild->nextBrother;
    return DecList_Struct(secondChild, specifier);
}
FieldList DecList_Struct(Node root, Type decType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, DecList_Struct", root->lineNum);
        perror(msg);
    #endif
    FieldList ret = Dec_Struct(root->firstChild, decType);
    if (root->childNum == 3)
        ret->next = DecList_Struct(root->firstChild->nextBrother->nextBrother, decType);

    return ret;
}
FieldList Dec_Struct(Node root, Type decType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Dec_Struct", root->lineNum);
        perror(msg);
    #endif
    FieldList ret=(FieldList)malloc(sizeof(struct FieldList_)); 
    Node child = root->firstChild;
    TableNode tableNode = VarDec(child, decType);
    ret->type = tableNode->type;
    strcpy(ret->name, tableNode->name);
    
    if(root->childNum==3)
    {
        //Error Type 15 
        printf("Error Type 15 at Line %d:  wrongly defined structure '%s'.\n", child->lineNum, ret->name);
    }
    return ret;
}

//Declarators
TableNode VarDec(Node root, Type type){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, VarDec", root->lineNum);
        perror(msg);
    #endif
    // VarDec → ID
    // | VarDec LB INT RB
    TableNode retNode = NULL;
    if(root->childNum == 1){
        retNode = (TableNode)malloc(sizeof(struct TableNode_));

        strcpy(retNode->name, root->firstChild->val);

        retNode->type = type;

        retNode->next = NULL;

        retNode->op = NULL;
    }else{
        //retNode = VarDec(root->firstChild);

        Type newType = (Type)malloc(sizeof(struct Type_));
        retNode = VarDec(root->firstChild, type);
        newType->kind = ARRAY;
        newType->u.array.elem = retNode->type;
        if(root->firstChild->nextBrother->nextBrother->name != Node_INT){
            // Error Type 10
            printf("Error Type 10 at Line %d: Not an array before [  ].\n", root->firstChild->lineNum);
            return retNode;
        }
        newType->u.array.size = stringToInt(root->firstChild->nextBrother->nextBrother->val);

        retNode->type = newType;
    }
    return retNode;
}
void FunDec(Node root, Type returnType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, FunDec", root->lineNum);
        perror(msg);
    #endif
    // FunDec → ID LP VarList RP
    //        | ID LP RP
    TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
    strcpy(newNode->name, root->firstChild->val);
    newNode->next = NULL;
    newNode->op = NULL;

    Type newType = (Type)malloc(sizeof(struct Type_));
    newType->kind = FUNCTION;
    newType->u.function.returnType = returnType;
    if(root->childNum == 4){
        FieldList temp = VarList(root->firstChild->nextBrother->nextBrother, true);
        newType->u.function.argv = temp;
        newType->u.function.argc = calculateArgc(temp);
    }else{
        newType->u.function.argv = NULL;
        newType->u.function.argc = 0;
    }
    strcpy(newType->u.function.name, root->firstChild->val);
    newType->u.function.line = root->lineNum;
    newType->u.function.decFlag = true;

    newNode->type = newType;
    if(insertIntoSymbolTable(newNode) == false){
        TableNode alreadyExist = getTableNode(newNode->name);
        if(alreadyExist->type->u.function.decFlag == false){
            FieldList argvList = alreadyExist->type->u.function.argv;
            FieldList newList = newType->u.function.argv;
            if(judgeType(alreadyExist->type->u.function.returnType, newType->u.function.returnType) == false){
                printf("Error type 19 at Line %d: Inconsistent declaration of function '%s'.\n", root->lineNum, alreadyExist->name);
                return;
            }

            while(newList != NULL && argvList != NULL){
                if(judgeType(newList->type, argvList->type) == false){
                    printf("Error type 19 at Line %d: Inconsistent declaration of function '%s'.\n", root->lineNum, alreadyExist->name);
                    return;
                }
                newList = newList->next;
                argvList = argvList->next;
            }
            if(newList != NULL || argvList != NULL){
                printf("Error type 19 at Line %d: Inconsistent declaration of function '%s'.\n", root->lineNum, alreadyExist->name);
            }
            alreadyExist->type->u.function.decFlag = true;
        }else{
            // Error type 4
            printf("Error type 4 at line %d: Redefined function '%s'.\n", root->lineNum, newNode->name);
        }
    }

}
FieldList VarList(Node root, Boolean flag){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, VarList", root->lineNum);
        perror(msg);
    #endif
    // VarList → ParamDec COMMA VarList
    //         | ParamDec
    FieldList field = ParamDec(root->firstChild, flag);
    if(root->childNum == 3){
        field->next = VarList(root->firstChild->nextBrother->nextBrother, flag);
    }
    return field;
}
FieldList ParamDec(Node root, Boolean flag){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, ParamDec", root->lineNum);
        perror(msg);
    #endif
    // ParamDec → Specifier VarDec
    Type specifier = Specifier(root->firstChild);
    TableNode tableNode = VarDec(root->firstChild->nextBrother, specifier);
    if (flag && insertIntoSymbolTable(tableNode) == false){
        // Error Type 3
        printf("Error type 3 at Line %d: Redefined variable '%s'.\n",root->lineNum, tableNode->name);
    }
    FieldList ret = (FieldList)malloc(sizeof(struct FieldList_));
    strcpy(ret->name, tableNode->name);
    ret->type = tableNode->type;
    ret->next = NULL;

    return ret;
}

void FunDeclare(Node root, Type returnType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, FunDeclare", root->lineNum);
        perror(msg);
    #endif
    // FunDec → ID LP VarList RP
    //        | ID LP RP
    TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
    strcpy(newNode->name, root->firstChild->val);
    newNode->next = NULL;
    newNode->op = NULL;

    Type newType = (Type)malloc(sizeof(struct Type_));
    newType->kind = FUNCTION;
    newType->u.function.returnType = returnType;
    if(root->childNum == 4){
        FieldList temp = VarList(root->firstChild->nextBrother->nextBrother, false);
        newType->u.function.argv = temp;
        newType->u.function.argc = calculateArgc(temp);
    }else{
        newType->u.function.argv = NULL;
        newType->u.function.argc = 0;
    }
    strcpy(newType->u.function.name, root->firstChild->val);
    newType->u.function.line = root->lineNum;
    newType->u.function.decFlag = false;

    newNode->type = newType;
    if(insertIntoSymbolTable(newNode) == false){
        TableNode alreadyExist = getTableNode(newNode->name);
        FieldList argvList = alreadyExist->type->u.function.argv;
        FieldList newList = newType->u.function.argv;
        if(judgeType(alreadyExist->type->u.function.returnType, newType->u.function.returnType) == false){
            printf("Error type 19 at Line %d: Inconsistent declaration of function '%s'.\n", root->lineNum, alreadyExist->name);
            return;
        }

        while(newList != NULL && argvList != NULL){
            if(judgeType(newList->type, argvList->type) == false){
                printf("Error type 19 at Line %d: Inconsistent declaration of function '%s'.\n", root->lineNum, alreadyExist->name);
                return;
            }
            newList = newList->next;
            argvList = argvList->next;
        }
        if(newList != NULL || argvList != NULL){
            printf("Error type 19 at Line %d: Inconsistent declaration of function '%s'.\n", root->lineNum, alreadyExist->name);
        }
        
    }

}

//Statements
void CompSt(Node root, Type returnType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, CompSt", root->lineNum);
        perror(msg);
    #endif
    // CompSt → LC DefList StmtList RC
    if (root->childNum == 0)
        return;

    if(root->firstChild->nextBrother->name == Node_DefList){
        DefList(root->firstChild->nextBrother);
        StmtList(root->firstChild->nextBrother->nextBrother, returnType);
    }else if(root->firstChild->nextBrother->name == Node_StmtList){
        StmtList(root->firstChild->nextBrother, returnType);
    }
}
void StmtList(Node root, Type returnType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, StmtList", root->lineNum);
        perror(msg);
    #endif
    // StmtList → Stmt StmtList
    //          | /*empty*/
    if (root->childNum == 0)
        return;
    if(root->firstChild != NULL){
        Stmt(root->firstChild, returnType);
        StmtList(root->firstChild->nextBrother, returnType);
    }
    
}
void Stmt(Node root, Type returnType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Stmt", root->lineNum);
        perror(msg);
    #endif
    // Stmt → Exp SEMI
    //      | CompSt
    //      | RETURN Exp SEMI
    //      | IF LP Exp RP Stmt
    //      | IF LP Exp RP Stmt ELSE Stmt
    //      | WHILE LP Exp RP Stmt
    Node child = root->firstChild;
    // perror(NodeNameToString(child->name));
    if(child->name == Node_Exp){
        // perror("here");
        child->type = Exp(child);
    }else if(child->name == Node_CompSt){
        CompSt(child, returnType);
    }else if(child->name == Node_RETURN){
        Type ret = Exp(child->nextBrother);
        child->nextBrother->type = ret;
        // Error type 8
        if(judgeType(ret, returnType)==false)
        {
            printf("Error type 8 at line %d: Type mismatched for return.\n",child->lineNum);
        }
    }else if(child->name == Node_WHILE){
        Type t = Exp(child->nextBrother->nextBrother);
        child->nextBrother->nextBrother->type = t;
        if(t!=NULL && (t->kind != BASIC || t->u.basic != Type_INT))
        {
            printf("Other error type at line %d: the condition in WHILE is not Type_INT.\n", child->lineNum);
        }
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
    }else if(root->childNum == 5){
        Type t = Exp(child->nextBrother->nextBrother);
        child->nextBrother->nextBrother->type = t;
        if(t!=NULL && (t->kind != BASIC || t->u.basic != Type_INT))
        {
            printf("Other error type at line %d: the condition in IF is not Type_INT.\n", child->lineNum);
        }
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
    }else{
        Type t = Exp(child->nextBrother->nextBrother);
        child->nextBrother->nextBrother->type = t;
        if(t!=NULL && (t->kind != BASIC || t->u.basic != Type_INT))
        {
            printf("Other error type at line %d: the condition in IF is not Type_INT.\n", child->lineNum);
        }
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
    }

}

//Local Definitions
void DefList(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, DefList", root->lineNum);
        perror(msg);
    #endif
    // DefList → Def DefList
    //         | /*empty*/
    if (root->childNum == 0)
        return;

    Def(root->firstChild);
    DefList(root->firstChild->nextBrother);
}
void Def(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Def", root->lineNum);
        perror(msg);
    #endif
    // Def → Specifier DecList SEMI
    Type specifier = Specifier(root->firstChild);
    Node secondChild = root->firstChild->nextBrother;
    DecList(secondChild, specifier);
}
void DecList(Node root, Type decType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, DecList", root->lineNum);
        perror(msg);
    #endif
    // DecList → Dec
    //         | Dec COMMA DecList
    Dec(root->firstChild, decType);
    if (root->childNum == 3)
        DecList(root->firstChild->nextBrother->nextBrother, decType);
}    
void Dec(Node root, Type decType){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Dec", root->lineNum);
        perror(msg);
    #endif
    // Dec → VarDec
    //     | VarDec ASSIGNOP Exp
    Node child = root->firstChild;
    TableNode tableNode = VarDec(child, decType);
    if (insertIntoSymbolTable(tableNode) == false){
        // Error Type 3
        printf("Error Type 3 at Line %d: Refined variable '%s'.\n", child->lineNum, tableNode->name);
    }
    if (root->childNum == 3){
        Type t = Exp(child->nextBrother->nextBrother);
        child->nextBrother->nextBrother->type = t;
        if(judgeType(decType, t)==false){
            printf("Error Type 5 at Line %d: Type mismatched for assignment.\n", child->lineNum);
        }
    }
}

//Expressions
Type Exp(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp", root->lineNum);
        perror(msg);
        // perror(root->val);
    #endif
    // Exp → Exp ASSIGNOP Exp
    //     | Exp AND Exp
    //     | Exp OR Exp
    //     | Exp RELOP Exp
    //     | Exp PLUS Exp
    //     | Exp MINUS Exp
    //     | Exp STAR Exp
    //     | Exp DIV Exp
    //     | LP Exp RP
    //     | MINUS Exp
    //     | NOT Exp
    //     | ID LP Args RP
    //     | ID LP RP
    //     | Exp LB Exp RB
    //     | Exp DOT ID
    //     | ID
    //     | INT
    //     | FLOAT
    Node child = root->firstChild;
    // #ifdef DEBUG
    //     perror(intToString(root->childNum));
    //     Node t = child;
    //     while(t){
    //         perror(t->val);
    //         perror(intToString(t->childNum));
    //         t = t->nextBrother;
    //     }
    // #endif
    if(root->childNum == 1){
        if(child->name == Node_ID){
            Type t = Exp_ID(root);
            root->type = t;
            return t;
        }else if(child->name == Node_INT){
            Type t = Exp_INT(root);
            root->type = t;
            return t;
        }else if(child->name == Node_FLOAT){
            Type t = Exp_FLOAT(root);
            root->type = t;
            return t;
        }
    }else if(root->childNum == 2){
        if(child->name == Node_MINUS){
            Type t = Exp_MIUNS(root);
            root->type = t;
            return t;
        }else if(child->name == Node_NOT){
            Type t = Exp_NOT(root);
            root->type = t;
            return t;
        }
    }else if(root->childNum == 3){
        if(child->name == Node_Exp){
            Node secondChild = child->nextBrother;
            if(secondChild->name == Node_ASSIGNOP){
                Type t = Exp_ASSIGNOP(root);
                root->type = t;
                return t;
            }
            else if(secondChild->name == Node_AND || secondChild->name == Node_OR){
                Type t = Exp_AND_OR(root);
                root->type = t;
                return t;
            }
            else if(secondChild->name == Node_DOT){
                Type t = Exp_STRUCT_VISIT(root);
                root->type = t;
                return t;
            }
            else{
                Type t = Exp_RELOP_CAL(root);
                root->type = t;
                return t;
            }
        }else if(child->name == Node_LP){
            Type t = Exp_LPRP(root);
            root->type = t;
            return t;
        }else if(child->name == Node_ID){
            Type t = Exp_FUNCTION_CALL(root);
            root->type = t;
            return t;
        }
    }else{
        if(child->name == Node_ID){
            Type t = Exp_FUNCTION_CALL(root);
            root->type = t;
            return t;
        }else if(child->name == Node_Exp){
            Type t = Exp_ARRAY_VISIT(root);
            root->type = t;
            return t;
        }
    }

}
void Args(Node root, TableNode tn){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Args", root->lineNum);
        perror(msg);
    #endif
    // Args → Exp COMMA Args
    //      | Exp
    FieldList argvList = tn->type->u.function.argv;
    Node child = root->firstChild;
    while(child != NULL && argvList != NULL){
        Type t = Exp(child);
        child->type = t;
        // printType(t);
        // printType(argvList->type);
        if(judgeType(t, argvList->type) == false){
            printf("Error type 9 at Line %d: Function '%s' is not applicable for arguments.\n", root->lineNum, tn->name);
            return;
        }
        argvList = argvList->next;
        if(child->nextBrother != NULL){
            child = child->nextBrother->nextBrother->firstChild;
        }else{
            break;
        }
    }

    if(child->nextBrother != NULL || argvList != NULL){
        printf("Error type 9 at Line %d: Function '%s' is not applicable for arguments.\n", root->lineNum, tn->name);
    }
    return;
}

Type Exp_ASSIGNOP(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_ASSIGNOP", root->lineNum);
        perror(msg);
    #endif
    // Exp → Exp ASSIGNOP Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child);
    child->type = exp1;
    Type exp2 = Exp(child->nextBrother->nextBrother);
    child->nextBrother->nextBrother->type = exp2;

    if(exp1==NULL || exp2==NULL){
        return NULL;
    }
    if(judgeType(exp1, exp2)==false){
        // printType(exp1);
        // printType(exp2);
        printf("Error Type 5 at Line %d: Type mismatched for assignment.\n", child->lineNum);
    }

    Node childOfChild = child->firstChild;
    //printf("%s\n", NodeNameToString(childOfChild->name));
    if(!(child->childNum==1 && childOfChild->name == Node_ID) && !(child->childNum==4 && childOfChild->name == Node_Exp) && !(child->childNum==3 && childOfChild->nextBrother->name == Node_DOT)){
        printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_AND_OR(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_AND_OR", root->lineNum);
        perror(msg);
    #endif
    // Exp → Exp AND Exp
    //     | Exp OR Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child);
    Type exp2 = Exp(child->nextBrother->nextBrother);
    child->type = exp1;
    child->nextBrother->nextBrother->type = exp2;


    if(exp1->kind!=BASIC || exp1->u.basic!=Type_INT || judgeType(exp1, exp2)==false){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_RELOP_CAL(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_RELOP_CAL", root->lineNum);
        perror(msg);
    #endif
    // Exp → Exp RELOP Exp
    //     | Exp PLUS Exp
    //     | Exp MINUS Exp
    //     | Exp STAR Exp
    //     | Exp DIV Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child);
    Type exp2 = Exp(child->nextBrother->nextBrother);
    child->type = exp1;
    child->nextBrother->nextBrother->type = exp2;
    if(exp1 == NULL){
        return NULL;
    }

    if(exp1->kind!=BASIC || judgeType(exp1, exp2)==false){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_LPRP(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_LPRP", root->lineNum);
        perror(msg);
    #endif
    // Exp → LP Exp RP
    Type t = Exp(root->firstChild->nextBrother);
    root->firstChild->nextBrother->type = t;
    return t;
}
Type Exp_MIUNS(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_MIUNS", root->lineNum);
        perror(msg);
    #endif
    // Exp → MINUS Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child->nextBrother);
    child->nextBrother->type = exp1;

    if(exp1->kind!=BASIC){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_NOT(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_NOT", root->lineNum);
        perror(msg);
    #endif
    // Exp → NOT Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child->nextBrother);
    child->nextBrother->type = exp1;

    if(exp1->kind!=BASIC || exp1->u.basic!=Type_INT){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_FUNCTION_CALL(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_FUNCTION_CALL", root->lineNum);
        perror(msg);
    #endif
    // Exp → ID LP Args RP
    //     | ID LP RP
    //char* id_name = root->firstChild->val;
    // perror(root->firstChild->val);
    Boolean exist = checkSymbolByName(root->firstChild->val);
    if(exist == false){
        printf("Error type 2 at Line %d: Undefined function '%s'.\n", root->lineNum, root->firstChild->val);
        return NULL;
    }else{
        TableNode tn = getTableNode(root->firstChild->val);
        if(tn->type->kind != FUNCTION){
            printf("Error type 11 at Line %d: '%s' is not a function.\n", root->lineNum, root->firstChild->val);
            return NULL;
        }
        else{
            if(root->childNum == 4){
                Args(root->firstChild->nextBrother->nextBrother, tn);
            }
            return tn->type->u.function.returnType;  //TODO: 可能需要深拷贝
        }
    }
}
Type Exp_ARRAY_VISIT(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_ARRAY_VISIT", root->lineNum);
        perror(msg);
    #endif
    // Exp → Exp LB Exp RB
    Type array = Exp(root->firstChild);
    Type index = Exp(root->firstChild->nextBrother->nextBrother);
    root->firstChild->type = array;
    root->firstChild->nextBrother->nextBrother->type = index;

    if(array->kind!=ARRAY){
        printf("Error Type 10 at Line %d: Not an array before [  ].\n", root->lineNum);
        return NULL;
    }
    if(index->kind!=BASIC || index->u.basic!=Type_INT){
        printf("Error Type 12 at Line %d: Array argument is not an integer.\n", root->lineNum);
        return NULL;
    }
    return array->u.array.elem;
}
Type Exp_STRUCT_VISIT(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_STRUCT_VISIT", root->lineNum);
        perror(msg);
    #endif
    // Exp → Exp DOT ID
    Type s = Exp(root->firstChild);
    root->firstChild->type = s;

    if(s->kind!=STRUCTURE){
        printf("Error type 13 at Line %d: Illegal use of '.'.\n", root->lineNum);
        return NULL;
    }

    // Find the field
    FieldList tmp = s->u.structure;
    char* id_name = root->firstChild->nextBrother->nextBrother->val;
    while(tmp != NULL){
        if(strcmp(tmp->name, id_name)==0)
            break;
        tmp = tmp->next;
    }
    if(tmp == NULL){
        printf("Error type 14 at Line %d: Non-existent field '%s'.\n",root->lineNum, id_name);
        return NULL;
    }
    return tmp->type;

}
Type Exp_ID(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_ID", root->lineNum);
        perror(msg);
    #endif
    // Exp → ID
    Boolean exist = checkSymbolByName(root->firstChild->val);
    if(exist == false){
        printf("Error type 1 at Line %d: Undefined variable '%s'.\n", root->lineNum, root->firstChild->val);
        return NULL;
    }else{
        TableNode tn = getTableNode(root->firstChild->val);
        if(tn->type->kind == FUNCTION){
            printf("Error type 1 at Line %d: Undefined variable '%s'.\n", root->lineNum, root->firstChild->val);
            return NULL;
        }
        else{
            return tn->type;  //TODO: 可能需要深拷贝
        }
    }
}
Type Exp_INT(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_INT", root->lineNum);
        perror(msg);
    #endif
    // Exp → INT
    Type type = (Type)malloc(sizeof(struct Type_));
    type->kind = BASIC;
    type->u.basic = Type_INT;
    return type;
}
Type Exp_FLOAT(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, Exp_FLOAT", root->lineNum);
        perror(msg);
    #endif
    // Exp → FLOAT
    Type type = (Type)malloc(sizeof(struct Type_));
    type->kind = BASIC;
    type->u.basic = Type_FLOAT;
    return type;
}
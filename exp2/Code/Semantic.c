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
Type StructSpecifier(Node root){
    //StructSpecifier → STRUCT OptTag LC DefList RC
    //    | STRUCT Tag
    Node secondChild = root->firstChild->nextBrother;
    Type retType;
    if(root->childNum >= 4){
        //建立一个新的符号表节点，并将该节点插入符号表

        if(root->childNum == 5 && checkSymbolByName(OptTag(secondChild))){
            //TODO: 错误16，实验选做2-3要求根据结构判断是否相同，此处重新做判断
        }

        TableNode newNode = (TableNode)malloc(sizeof(struct TableNode_));
        if(root->childNum == 5)
            strcpy(newNode->name, OptTag(secondChild));
        Type newType = (Type)malloc(sizeof(struct Type_));

        newType->kind = STRUCTURE;
        if(root->childNum == 5){
            newType->u.structure = DefList(secondChild->nextBrother->nextBrother);
        }else{
            newType->u.structure = DefList(root->firstChild->nextBrother->nextBrother);
        }
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
            retType = ret->type;       //TODO: 可能需要深拷贝
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
        //retNode = VarDec(root->firstChild);

        Type newType = (Type)malloc(sizeof(struct Type_));
        retNode = VarDec(root->firstChild, newType);
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
    return field;
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
void CompSt(Node root, Type returnType){
    // CompSt → LC DefList StmtList RC
    if (root == NULL)
        return;
    assert(root->firstChild != NULL);
    assert(root->firstChild->nextBrother != NULL);

    DefList(root->firstChild->nextBrother);
    StmtList(root->firstChild->nextBrother->nextBrother, returnType);
}
void StmtList(Node root, Type returnType){
    // StmtList → Stmt StmtList
    //          | /*empty*/
    if (root == NULL)
        return;
    assert(root->firstChild != NULL);

    Stmt(root->firstChild, returnType);
    StmtList(root->firstChild->nextBrother, returnType);
}
void Stmt(Node root, Type returnType){
    // Stmt → Exp SEMI
    //      | CompSt
    //      | RETURN Exp SEMI
    //      | IF LP Exp RP Stmt
    //      | IF LP Exp RP Stmt ELSE Stmt
    //      | WHILE LP Exp RP Stmt
    Node child = root->firstChild;
    if(child->name == Node_Exp){
        Exp(child);
    }else if(child->name == Node_CompSt){
        CompSt(child, returnType);
    }else if(child->name == Node_RETURN){
        Type ret = Exp(child->nextBrother);
        // Error type 8
        if(judgeType(ret, returnType)==false)
        {
            printf("Error type 8 at line %d: Type mismatched for return.\n",child->lineNum);
        }
    }else if(child->name == Node_WHILE){
        Type t = Exp(child->nextBrother->nextBrother);
        if(t->kind != BASIC || t->u.basic != Type_INT)
        {
            printf("Other error type at line %d: the condition in WHILE is not Type_INT.\n", child->lineNum);
        }
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
    }else if(root->childNum == 5){
        Type t = Exp(child->nextBrother->nextBrother);
        if(t->kind != BASIC || t->u.basic != Type_INT)
        {
            printf("Other error type at line %d: the condition in IF is not Type_INT.\n", child->lineNum);
        }
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
    }else{
        Type t = Exp(child->nextBrother->nextBrother);
        if(t->kind != BASIC || t->u.basic != Type_INT)
        {
            printf("Other error type at line %d: the condition in IF is not Type_INT.\n", child->lineNum);
        }
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
        Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother, returnType);
    }

}

//Local Definitions
void DefList(Node root){
    // DefList → Def DefList
    //         | /*empty*/
    if (root == NULL)
        return;
    assert(root->firstChild != NULL);

    Def(root->firstChild);
    DefList(root->firstChild->nextBrother);
}
void Def(Node root){
    // Def → Specifier DecList SEMI
    Type specifier = Specifier(root->firstChild);
    Node secondChild = root->firstChild->nextBrother;
    DecList(secondChild->nextBrother, specifier);
}
void DecList(Node root, Type decType){
    // DecList → Dec
    //         | Dec COMMA DecList
    Dec(root->firstChild, decType);
    if (root->childNum == 3)
        DecList(root->firstChild->nextBrother->nextBrother, decType);
}    
void Dec(Node root, Type decType){
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
        if(judgeType(decType, t)==false){
            printf("Error Type 5 at Line %d: Type mismatched for assignment.\n", child->lineNum);
        }
    }
}

//Expressions
Type Exp(Node root){
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
    if(root->childNum == 1){
        if(child->name == Node_ID){
            return Exp_ID(root);
        }else if(child->name == Node_INT){
            return Exp_FLOAT(child);
        }else if(child->name == Node_FLOAT){
            return Exp_INT(child);
        }
    }else if(root->childNum == 2){
        if(child->name == Node_MINUS){
            return Exp_MIUNS(root);
        }else if(child->name == Node_NOT){
            return Exp_NOT(root);
        }
    }else if(root->childNum == 3){
        if(child->name == Node_Exp){
            Node secondChild = child->nextBrother;
            if(secondChild->name == Node_ASSIGNOP)
                return Exp_ASSIGNOP(root);
            else if(secondChild->name == Node_AND || secondChild->name == Node_OR)
                return Exp_AND_OR(root);
            else if(secondChild->name == Node_DOT)
                return Exp_STRUCT_VISIT(root);
            else
                return Exp_RELOP_CAL(root);
        }else if(child->name == Node_LP){
            return Exp_LPRP(root);
        }else if(child->name == Node_ID){
            return Exp_FUNCTION_CALL(root);
        }
    }else{
        if(child->name == Node_ID){
            return Exp_FUNCTION_CALL(root);
        }else if(child->name == Node_Exp){
            return Exp_ARRAY_VISIT(root);
        }
    }

}
void Args(Node root, TableNode tn){
    // Args → Exp COMMA Args
    //      | Exp
    FieldList argvList = tn->type->u.function.argv;
    Node child = root->firstChild;
    while(child != NULL && argvList != NULL){
        if(judgeType(Exp(child), argvList->type) == false){
            printf("Error type 9 at Line %d: Function '%s' is not applicable for arguments.\n", root->lineNum, tn->name);
            return;
        }
        child = child->nextBrother;
        argvList = argvList->next;
    }
    if(child != NULL || argvList != NULL){
        printf("Error type 9 at Line %d: Function '%s' is not applicable for arguments.\n", root->lineNum, tn->name);
    }
    return;
}

Type Exp_ASSIGNOP(Node root){
    // Exp → Exp ASSIGNOP Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child);
    Type exp2 = Exp(child->nextBrother->nextBrother);

    if(judgeType(exp1, exp2)==false){
        printf("Error Type 5 at Line %d: Type mismatched for assignment.\n", child->lineNum);
    }

    Node childOfChild = child->firstChild;
    if(!(child->childNum==1 && childOfChild->name == Node_ID) && !(child->childNum==4 && childOfChild->name == Node_Exp) && !(child->childNum==3 && childOfChild->nextBrother->name == Node_DOT)){
        printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_AND_OR(Node root){
    // Exp → Exp AND Exp
    //     | Exp OR Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child);
    Type exp2 = Exp(child->nextBrother->nextBrother);

    if(exp1->kind!=BASIC || exp1->u.basic!=Type_INT || judgeType(exp1, exp2)==false){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_RELOP_CAL(Node root){
    // Exp → Exp RELOP Exp
    //     | Exp PLUS Exp
    //     | Exp MINUS Exp
    //     | Exp STAR Exp
    //     | Exp DIV Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child);
    Type exp2 = Exp(child->nextBrother->nextBrother);

    if(exp1->kind!=BASIC || judgeType(exp1, exp2)==false){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_LPRP(Node root){
    // Exp → LP Exp RP
    return Exp(root->firstChild);
}
Type Exp_MIUNS(Node root){
    // Exp → MINUS Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child->nextBrother);

    if(exp1->kind!=BASIC){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_NOT(Node root){
    // Exp → NOT Exp
    Node child = root->firstChild;
    Type exp1 = Exp(child->nextBrother);

    if(exp1->kind!=BASIC || exp1->u.basic!=Type_INT){
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", child->lineNum);
    }

    return exp1;
}
Type Exp_FUNCTION_CALL(Node root){
    // Exp → ID LP Args RP
    //     | ID LP RP
    //char* id_name = root->firstChild->val;
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
    // Exp → Exp LB Exp RB
    Type array = Exp(root->firstChild);
    Type index = Exp(root->firstChild->nextBrother->nextBrother);

    if(array->kind!=ARRAY){
        printf("Error Type 10 at Line %d: Not an array before [  ].\n", root->lineNum);
        return NULL;
    }
    if(index->kind!=BASIC || index->u.basic!=Type_INT){
        printf("Error Type 12 at Line %d: Not an integer between [ and ].\n", root->lineNum);
        return NULL;
    }
    return array->u.array.elem;
}
Type Exp_STRUCT_VISIT(Node root){
    // Exp → Exp DOT ID
    Type s = Exp(root->firstChild);

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
    // Exp → INT
    Type type = (Type)malloc(sizeof(struct Type_));
    type->kind = BASIC;
    type->u.basic = Type_INT;
    return type;
}
Type Exp_FLOAT(Node root){
    // Exp → FLOAT
    Type type = (Type)malloc(sizeof(struct Type_));
    type->kind = BASIC;
    type->u.basic = Type_FLOAT;
    return type;
}
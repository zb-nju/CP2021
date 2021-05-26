#include <stdio.h>
#include "Node.h"

Node createNode(int lineNum, NodeName name, char* val, int isToken,  int childNum, ...){
    Node newNode = (Node)malloc(sizeof(struct Node_));
    assert(newNode != NULL);

    newNode->lineNum = lineNum;
    int valLen = strlen(val) + 1;

    newNode->val = (char*)malloc(sizeof(char) * valLen);
    assert(newNode->val != NULL);
    strncpy(newNode->val, val, valLen);

    newNode->name = name;

    newNode->isToken = isToken;

    newNode->childNum = childNum;

    newNode->firstChild = NULL;
    newNode->nextBrother = NULL;
    newNode->type = NULL;

    if(childNum == 5 && newNode->name == Node_StructSpecifier){
        va_list ap;
        va_start(ap, childNum);

        Node temp = va_arg(ap, Node);
        newNode->firstChild = temp;
        for(int i = 1; i < childNum; i++){
            Node tmp = va_arg(ap, Node);
            if(tmp!=NULL){
                temp->nextBrother = tmp;
                temp = temp->nextBrother;
            }else{
                newNode->childNum--;
            }
        }
    }
    else if(childNum > 0){
        va_list ap;
        va_start(ap, childNum);

        Node temp = va_arg(ap, Node);
        newNode->firstChild = temp;
        for(int i = 1; i < childNum; i++){
            Node tmp = va_arg(ap, Node);
            if(tmp != NULL){
                temp->nextBrother = tmp;
                temp = temp->nextBrother;
            }else{
                newNode->childNum--;
            }
        }
    }

    return newNode;
}

void printTree(Node root, int depth){
    if(root == NULL)
        return;

    for(int i = 0; i < depth; i++)
        printf("  ");
    printf("%s", NodeNameToString(root->name));

    if(root->isToken == false)
        printf("(%d)", root->lineNum);
    else if(root->name == Node_TYPE || root->name == Node_ID || root->name == Node_INT)
        printf(": %s", root->val);
    else if(root->name == Node_FLOAT)
        printf(": %lf", atof(root->val));

    printf("\n");
    printTree(root->firstChild, depth + 1);
    printTree(root->nextBrother, depth);
}
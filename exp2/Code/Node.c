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

    newNode->isToken == isToken;

    newNode->firstChild = NULL;
    newNode->nextBrother = NULL;

    if(childNum > 0){
        va_list ap;
        va_start(ap, childNum);

        Node temp = va_arg(ap, Node);
        newNode->firstChild = temp;
        for(int i = 1; i < childNum; i++){
            if(temp != NULL){
                temp->nextBrother = va_arg(ap, Node);
                temp = temp->nextBrother;
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
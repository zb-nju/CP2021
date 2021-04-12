#include <stdio.h>
#include "Node.h"

Node createNode(int lineNum, char* name, char* val, int isToken,  int childNum, ...){
    Node newNode = (Node)malloc(sizeof(struct Node_));
    assert(newNode != NULL);

    newNode->lineNum = lineNum;
    int nameLen = strlen(name) + 1, valLen = strlen(val) + 1;

    newNode->name = (char*)malloc(sizeof(char) * nameLen);
    newNode->val = (char*)malloc(sizeof(char) * valLen);
    assert(newNode->name != NULL);
    assert(newNode->val != NULL);

    strncpy(newNode->name, name, nameLen);
    strncpy(newNode->val, val, valLen);

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
    printf("%s", root->name);

    if(root->isToken == false)
        printf("(%d)", root->lineNum);
    else if(strcmp(root->name, "TYPE") == 0 || strcmp(root->name, "ID") || strcmp(root->name, "INT"))
        printf(": %s", root->val);
    else if(strcmp(root->name, "FLOAT") == 0)
        printf(": %lf", atof(root->val));

    printf("\n");
    printTree(root->firstChild, depth + 1);
    printTree(root->nextBrother, depth);
}
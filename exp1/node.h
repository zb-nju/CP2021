#ifndef NODEH
#define NODEH

#define MAX_CHILD_NUM 7

typedef struct node_ node;

struct node_{
    char name[20];
    int lineNum;

    struct node_* child[MAX_CHILD_NUM];
};



#endif

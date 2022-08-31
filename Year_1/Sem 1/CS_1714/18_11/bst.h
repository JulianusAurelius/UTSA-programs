#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdlib.h>

enum BSTOrder {PREORDER, INORDER, POSTORDER};

typedef struct BSTNode {
    int value;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

void traverseBST(struct BSTNode* root, enum BSTOrder order);
void destroy(struct BSTNode* root);

#endif
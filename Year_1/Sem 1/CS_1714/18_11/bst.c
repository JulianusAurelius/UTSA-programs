#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void traverseBST(struct BSTNode* root, enum BSTOrder order)
{
    if (root == NULL)
        return;
    if (order == PREORDER)
    {
        printf("%d\t", root->value);
        traverseBST(root->left, order);
        traverseBST(root->right, order);
    }
    else if (order == INORDER)
    {
        traverseBST(root->left, order);
        printf("%d\t", root->value);
        traverseBST(root->right, order);
    }
    else if (order == POSTORDER)
    {
        traverseBST(root->left, order);
        traverseBST(root->right, order);
        printf("%d\t", root->value);
    }
}

void destroy(struct BSTNode* root)
{
    if (root == NULL)
        return;
    destroy(root->left);
    destroy(root->right);
    free(root);
}
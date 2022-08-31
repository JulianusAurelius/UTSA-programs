#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc, char *argv[])
{
    int num;
    printf("Enter the number of nodes for the tree: ");
    scanf("%d", &num);
    printf("\n");
    BSTNode *root = NULL;
    BSTNode *curr = NULL;
    for (int i = 0; i < num; i++)
    {
        int data;
        printf("Enter a node value: ");
        scanf("%d", &data);
        printf("\n");
        BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
        node->value = data;
        curr = root;
        while ( 1 )
        {
            if (curr == NULL)
            {
                root = node;
                break;
            }
            if (node->value < curr->value)
            {
                if (curr->left == NULL)
                {
                    curr->left = node;
                    break;
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {
                if (curr->right == NULL)
                {
                    curr->right = node;
                    break;
                }
                else
                {
                    curr = curr->right;
                }
            }
        }
    }
    printf("Enter the order for traversal and printing (0-Preorder, 1-Inorder, 2-Postorder): ");
    int order;
    scanf("%d", &order);
    printf("\n");
    traverseBST(root, order);
    destroy(root);

    return 0;
}
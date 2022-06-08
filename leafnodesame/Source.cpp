#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "Binary.h"
#include "LinkedList.h"
#include "queue_int.h"
void inorder(bnode_t* tree, node_t** hp, node_t** temp);
int isLeafTraversalSame(bnode_t* tree, bnode_t* tree2)
{
	node_t* linkedlist1 = NULL;
	node_t* linkedList2 = NULL;
	node_t* temp = NULL;
	inorder(tree, &linkedlist1, &temp);
	inorder(tree2, &linkedList2, &temp);
	while (linkedlist1 != NULL && linkedList2 != NULL)
	{
		if (linkedlist1->data != linkedList2->data)
		{
			return 0;
		}
		linkedlist1 = linkedlist1->next;
		linkedList2 = linkedList2->next;
	}

	return 1;

}
void inorder(bnode_t*tree, node_t** hp, node_t **temp)  //INORDER (creating leaf nodes linked LIST!)
{
	if(tree!=NULL)
	{
		inorder(tree->left, hp, temp);
		if (tree->left == NULL && tree->right == NULL)
		{
			if (*hp != NULL)
			{
				AddAfter(*temp, tree->data);
				*temp = (*temp)->next;
			}
			else
			{
				*hp = AddBeginning(*hp, tree->data);
				*temp = *hp;
			}
		}
		inorder(tree->right, hp, temp);
	}
	
}
bnode_t* CreateBinaryTree1(BType data[], int size)
{
	bnode_t* root=NULL;
	bnode_t* temp = NULL;
	int counter = 1;
	queue_t q;
	InitializeQ(&q);
	int i = 0;
	if (i == 0)
	{
		root = getBinaryNode(data[i]);
	}
	temp = root;
	while (counter < size)
	{
		i = temp->data;
		if (data[counter] == 2 * i)
		{
			temp->left = getBinaryNode(data[counter]);
		}
		else if (data[counter] == 2 * i + 1)
		{
			temp->right = getBinaryNode(data[counter]);

		}

		if (temp->left != NULL && temp->right != NULL)
		{
			insert(&q, temp->left);
			insert(&q, temp->right);
			temp = remove(&q);

		}
		counter++;
	}


	return root;
}

void preorder(bnode_t* root)
{
	if (root != NULL)
	{
		printf("%d -> ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
int main(void)
{
	int Size=6;
	int data[6];
	printf("Enter the numbers for the binary tree 1: ");
	for (int i = 0; i < Size; i++)
	{
		scanf("%d", &data[i]);
    }
	bnode_t* tree1 = CreateBinaryTree1(data, Size);
	preorder(tree1);
	printf("NULL\n");

	//another tree
	bnode_t* tree2 = getBinaryNode(1);
	tree2->right = getBinaryNode(3);
	tree2->left = getBinaryNode(2);
	tree2->right->right = getBinaryNode(6);
	tree2->right->left = getBinaryNode(5);
	tree2->left->right = getBinaryNode(4);

	preorder(tree2);
	printf("NULL\n");
	  //YAYAY I CONNECTED THE LEAF NODES
	int check = isLeafTraversalSame(tree1, tree2);
	return 0;
}
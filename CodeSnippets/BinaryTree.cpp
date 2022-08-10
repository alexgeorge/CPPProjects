#include <stdio.h>
#include <stdlib.h>

/*binary node struct */
typedef struct st_node 
{
    int data;
    struct st_node* left;
    struct st_node* right;        
}bnode;

/* create  a new node helper */
bnode* newNode(int data)
{
    bnode* node = (bnode*) malloc(sizeof(bnode));
    node->data = data;
    node->right = 0;
    node->left = 0;    
    return node;    
}

/* there are 3 tree traversals preorder, postorder and inorder 
preorder - visit root
left traverse 
right traverse
*/

void printPreorder(bnode* node)
{
    if (!node) return;
    //first check the data
    printf("[%d]", node->data);
    //traverse left
    printPreorder(node->left);  
    //traverse rigt
    printPreorder(node->right);       
}

/*post order 
left, right and then node
bottoms up approach
*/

void printPostorder(bnode* node)
{
    if (!node) return;
    //traverse left
    printPostorder(node->left);  
    //traverse rigt
    printPostorder(node->right);       
    //now the data node
    printf("[%d]", node->data);
}

/*inorder
left, node and right
*/

void printInorder(bnode* node)
{
    if (!node) return;
    //left
    printInorder(node->left);
    //node data
    printf("[%d]", node->data);
    //right
    printInorder(node->right);        
}

//traverse the tree and delete the nodes
void clearNodes(bnode* node)
{
    if (!node) return;
    clearNodes(node->left);
    clearNodes(node->right);
    printf("Deleting node [%d] \n",node->data);
    free(node);   
    node = 0;
}

// Returns true if given tree is BST.
bool isBST(bnode* root, bnode* l = NULL, bnode* r = NULL)
{
	// Base condition
	if (root == NULL)
		return true;

	// if left node exist that check it has
	// correct data or not
	if (l != NULL && root->data < l->data)
		return false;

	// if right node exist that check it has
	// correct data or not
	if (r != NULL && root->data > r->data)
		return false;

	// check recursively for every node.
	return isBST(root->left, l, root) &&
		isBST(root->right, root, r);
}


//Now test the implementration 

int main()
{
    bnode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    
    printf ("Preorder traversal is:- \n");
    printPreorder(root);

    printf ("Postoder traversal is:- \n");
    printPostorder(root);

    printf ("Inorder traversal is:- \n");
    printInorder(root);
    printf("\n");
    //this will lead to memory leak as we
    //dont free the memory. Add clearNode()
    clearNodes(root);
    return 1;   
}








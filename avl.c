#include<stdio.h>
#include<stdlib.h>

struct avl_node {
    int data;
    struct avl_node *left;
    struct avl_node *right;
};
struct avl_node *tree=NULL;


void inorder(struct avl_node *tree)
{
    if(tree == NULL)
	return;
    else {
 	inorder(tree -> left);
	printf("%d\t",tree ->data);
	inorder(tree ->right);
    }
   
}

void preorder(struct avl_node *tree)
{
    if(tree == NULL)
	return;
    else {
	printf("%d\t", tree ->data);
	preorder(tree ->left);
	preorder(tree ->right);
    }
}

void postorder(struct avl_node *tree)
{
    if(tree == NULL)
	return;
    else {
	postorder(tree ->left);
	postorder(tree ->right);
	printf("%d\t",tree ->data);
    }
}


struct avl_node* left_left_rotation(struct avl_node *parent)
{
    struct avl_node *node1;
    node1 = parent -> left;
    parent -> left = node1 -> right;
    node1 -> right = parent;
    return node1;
}


struct avl_node* right_right_rotation(struct avl_node *parent)
{
    struct avl_node *node1;
    node1=parent ->right;
    parent->right = node1 -> left;
    node1 -> left= parent;
    return node1;
}

struct avl_node* right_left_rotation(struct avl_node *parent)
{
    struct avl_node *node1;
    node1=parent -> right;
    parent->right = left_left_rotation(node1);
    return right_right_rotation(parent);
}

struct avl_node* left_right_rotation(struct avl_node *parent)
{
    struct avl_node *node1;
    node1= parent -> left;
    parent-> left = right_right_rotation(node1);
    return left_left_rotation(parent);
}


int find_height(struct avl_node *node)
{
    int height=0;
    if (node !=NULL){
	int left_height= find_height(node ->left);
	int right_height= find_height(node -> right);
	int max=(left_height > right_height) ? left_height : right_height;
	height = 1+ max;
    }
//  printf("%d",height);
    return height;
}

int get_diff(struct avl_node *node)
{
    int left_height=find_height(node -> left);
    int right_height=find_height(node -> right);
    int b_factor= left_height - right_height;
//    printf("%d",b_factor);
    return b_factor;
}  



struct avl_node* balancing(struct avl_node *node)
{
    int b_f= get_diff(node);
    if (b_f >1) {
	if (get_diff(node->left) >0)
	    node=left_left_rotation(node);
	else
	    node=left_right_rotation(node);
    }
    else if(b_f < -1) {
	if(get_diff(node ->right) >0)
	    node=right_left_rotation(node);
	else
	    node=right_right_rotation(node);
    }
    return node;
}		


struct avl_node* insert(struct avl_node *root,int val)
{
    if (root==NULL) {
	root = (struct avl_node*) malloc(sizeof(struct avl_node));
	root -> data = val;
	root -> left = NULL;
    	root -> right = NULL;
	return root;
    }
    else if (val < root->data) {
	root->left = insert(root->left, val);
	root=balancing(root);
    }
    else if (val > root->data) {
	root->right = insert(root->right, val);
	root=balancing(root);
    }
    return root;
}



main()
{
    int n,val;
    printf("Enter the Number of 'nodes' in the Tree: ");
    scanf("%d",&n);
    while (n) {
	printf("Enter the node : ");
	scanf("%d",&val);
	tree=insert(tree,val);
    	n--;
    }
    printf("Inorder Traversal : \t");
    inorder(tree);
    printf("\n");
    printf("Preorder Traversal : \t");
    preorder(tree);
    printf("\n");
    printf("Postorder Traversal : \t");
    postorder(tree);
    printf("\n");

}



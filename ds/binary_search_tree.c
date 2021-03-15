//Binary Search Tree
//https://github.com/aufheben68

#include "treeprint.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


TreeNode* insertItem(TreeNode *root, int x);
bool search(TreeNode* root, int x, int i);
void destroyTree(TreeNode *t);
int max(TreeNode* root);
TreeNode* find(TreeNode* root,int x);
TreeNode* findMin(TreeNode* root);
TreeNode* Getsuccessor(TreeNode* root,int x);
int size(TreeNode* root);

int main(int argc, char** argv) {
    TreeNode *root = NULL;
	int maxr,size1;
	TreeNode *T=NULL;
    char word[31];
    int x;
    printf("Dwste entoles:\n");
    while (1) {
	scanf("%s",word);
	if ((strcmp(word, "insert")==0)) {
		scanf("%d", &x);
		root = insertItem(root, x);
    	printTree(root);
	}else if (strcmp(word, "search")==0) {
		scanf("%d", &x);
		bool check = search(root, x, 0);
		if(check == true){
		printf("The number has been found!\n");
		}
		else printf("The number has not been found!\n");
	}else if(strcmp(word,"max")==0){
		maxr  = max(root);
		printf("The max element is: %d\n", maxr);
	}else if(strcmp(word,"size")==0){
		scanf("%d", &x);
		TreeNode*  T= find(root,x);
		size1=size(T);
		printf("Size(number) of nodes of the subtree\n");
		printf("including itself is: %d\n",size1);
		
	}else if(strcmp(word,"succ")==0){
		scanf("%d", &x);
		TreeNode* successor = Getsuccessor(root,x);
		if(successor == NULL){
			printf("Successor has not been found.\n");
		}else{
    		printf("The next successor of the number you have searched is %d\n", successor->item);
	}
	} else if (strcmp(word, "exit")==0){
		destroyTree(root);
		break;
	}else printf("Unknown command. Please try again.");
	
	printf("\n");
    };
        
    return (EXIT_SUCCESS);
}



// insert new key on the tree
TreeNode* insertItem(TreeNode *root, int x) {  
   TreeNode *v = root;  
   TreeNode *pv = NULL;  
   while (v != NULL) {  
      pv = v; 
      if (x < v->item) v=v->left;
      else if (x > v->item) v=v->right;
           else { 
                  printf("%d is already stored in the tree.\n", x);
		  return root;
           }   
   }
   TreeNode *tmp = (TreeNode *) malloc(sizeof(TreeNode));
   tmp->item=x; tmp->left=tmp->right=NULL;    
   if (root != NULL) { 
      if (x < pv->item) pv->left=tmp;
         else pv->right=tmp;
   } else root=tmp;
   return root;
}


//Function that helps us free the memory that the tree has allocated
void destroyTree(TreeNode *t) {
    // postorder
    if (t==NULL) return;
    destroyTree(t->left);   
    destroyTree(t->right); 
    free(t); 
}

//Function for searching an element on the tree
bool search(TreeNode* root, int x, int i){
	if(root != NULL){
		i++;
		if(x < root->item){
			return search(root->left, x, i);
		}else if (x > root->item)
			return search(root->right, x, i);
			printf("Number of nodes that have been checked: %d\n",i);
			return true;		
	}
	else{
		printf("Number of nodes that have been checked: %d\n", i);
 		return false;
	}
}

//function for max
int max(TreeNode* root){

	if(root != NULL){
		while(root->right != NULL)
			root = root->right;
		return root->item;	
	}
	else return 0;
}

//function that finds a node on the tree
TreeNode* find(TreeNode*root, int x) {
	if(root == NULL) return NULL;
	else if(root->item == x) return root;
	else if(root->item < x) return find(root->right,x);
	else return find(root->left,x);
}

//function for min
TreeNode* findMin(TreeNode* root) {
	if(root == NULL) return NULL;
	while(root->left != NULL)
		root = root->left;
	return root;
}
	
//function for the successor
TreeNode* Getsuccessor(TreeNode* root,int x) {
	// search for node in time - O(h)
	TreeNode* current = find(root,x);
	if(current == NULL) return NULL;
	if(current->right != NULL) {  //In case we have a right subtree
		return findMin(current->right); // O(h)
	}
	else {   //In case we dont have a right subtree - O(h)
		TreeNode* successor = NULL;
		TreeNode* ancestor = root;
		while(ancestor != current) {
			if(current->item < ancestor->item) {
				successor = ancestor; 
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;
		}
		return successor;
	}
}	
 //recursive function that computes the number of nodes a given subtree has
int size(TreeNode* T){  
  if (T==NULL)
    return 0;
  else
    return(size(T->left)+ 1 + size(T->right));  
}

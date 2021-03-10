//DUADIKA DENTRA ANAZITISIS

#include "treeprint.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// eisagwgi stoixeiou sto dentro
TreeNode* insertItem(TreeNode *root, int x);
// psaksimo stoixeiou sto dentro
bool search(TreeNode* root, int x, int i);
// katastrofh dentrou
void destroyTree(TreeNode *t);
// to megalutero stoixeio tou dentrou
int max(TreeNode* root);
//to find ena sugkekrimeno komvo sto dentro
TreeNode* find(TreeNode* root,int x);
//vriskei to mikrotero
TreeNode* findMin(TreeNode* root);
//vres ton epomeno megalutero
TreeNode* Getsuccessor(TreeNode* root,int x);
//vres to megethos twn nodes tou upodentrou
int size(TreeNode* root);

int main(int argc, char** argv) {
    TreeNode *root = NULL;
	int maxr,size1;
	TreeNode *T=NULL;
    char word[31];  // mia symboloseira me to poly 30 characters;
    int x;
    printf("Dwste entoles:\n");
    while (1) {
	scanf("%s",word);
	if ((strcmp(word, "insert")==0)) {
		scanf("%d", &x);
		root = insertItem(root, x);
    	// ektypwsi dentrou
    	printTree(root);
	}else if (strcmp(word, "search")==0) {
		scanf("%d", &x);
		bool check = search(root, x, 0);
		if(check == true){
		printf("O arithmos vrethike!\n");
		}
		else printf("Arithmos den vrethike!\n");
	}else if(strcmp(word,"max")==0){
		maxr  = max(root);
		printf("To megisto einai to: %d\n", maxr);
	}else if(strcmp(word,"size")==0){
		scanf("%d", &x);
		TreeNode*  T= find(root,x);
		size1=size(T);
		printf("To megethos(arithmos) twn nodes tou upodentrou\n");
		printf("mazi me ton eafto tou einai: %d\n",size1);
		
	}else if(strcmp(word,"succ")==0){
		scanf("%d", &x);
		TreeNode* successor = Getsuccessor(root,x);
		if(successor == NULL){
			printf("Den vrethike megaluteros arithmos.\n");
		}else{
    		printf("O epomenos megaluteros einai to %d\n", successor->item);
	}
	} else if (strcmp(word, "exit")==0){
		destroyTree(root);
		break;
	}else printf("Agnwsti entolh. Xanaprospathiste.");
	
	printf("\n");
    };
        
    return (EXIT_SUCCESS);
}



// eisagwgi neou kleidiou sto dentro
TreeNode* insertItem(TreeNode *root, int x) {  
   TreeNode *v = root;  // v trexon kombos
   TreeNode *pv = NULL; // pv goneas tou v 
   while (v != NULL) {  
      pv = v; 
      if (x < v->item) v=v->left;
      else if (x > v->item) v=v->right;
           else { // yparxei idi, ektypwsi mhnymatos
                  printf("To %d yparxei idi sto dentro.\n", x);
		  return root;
           }   
   }
   TreeNode *tmp = (TreeNode *) malloc(sizeof(TreeNode));
   tmp->item=x; tmp->left=tmp->right=NULL;    
   if (root != NULL) { 
      if (x < pv->item) pv->left=tmp;
         else pv->right=tmp;
   } else root=tmp;
   return root; // epistrofi rizas dentrou
}


//Sunartisi katastrofhs dentrou me riza t
void destroyTree(TreeNode *t) {
    // apodesmeysi mnimis me xrisi postorder diasxisis
    if (t==NULL) return;
    destroyTree(t->left);   // diagrafi kombwn aristerou ypodentrou
    destroyTree(t->right);  // diagrafi kombwn deksiou ypodentrou
    free(t); // diagrafi kombou t
}

//Synartisi pou vriskei ena stoixeio sto dentro kai epistrefei kai ta nodes pou elegxthikan
bool search(TreeNode* root, int x, int i){
	if(root != NULL){
		i++;
		if(x < root->item){
			return search(root->left, x, i);
		}else if (x > root->item)
			return search(root->right, x, i);
			printf("Arithmos nodes pou elegxthikan: %d\n",i);
			return true;		
	}
	else{
		printf("Arithmos nodes pou elegxthikan: %d\n", i);
 		return false;
	}
}

//Synartisi max pou vriskei to megisto
int max(TreeNode* root){

	if(root != NULL){
		while(root->right != NULL)
			root = root->right;
		return root->item;	
	}
	else return 0;
}

//Sunartisi find pou vriskei ena node se ena duadiko dentro anazitisis
TreeNode* find(TreeNode*root, int x) {
	if(root == NULL) return NULL;
	else if(root->item == x) return root;
	else if(root->item < x) return find(root->right,x);
	else return find(root->left,x);
}

//Sunartisi pou vriskei to mikrotero se ena duadiko dentro anazitisis
TreeNode* findMin(TreeNode* root) {
	if(root == NULL) return NULL;
	while(root->left != NULL)
		root = root->left;
	return root;
}
	
//Sunartisi pou vriskei ton epomeno megalutero enos arithmou tou dentrou
TreeNode* Getsuccessor(TreeNode* root,int x) {
	// Psakse to node se xrono - O(h)
	TreeNode* current = find(root,x);
	if(current == NULL) return NULL;
	if(current->right != NULL) {  //Periptwsi 1:Ehei deksi upodentro
		return findMin(current->right); // O(h)
	}
	else {   //Periptwsi 2:Den ehei deksi upodentro  - O(h)
		TreeNode* successor = NULL;
		TreeNode* ancestor = root;
		while(ancestor != current) {
			if(current->item < ancestor->item) {
				successor = ancestor; //Afto einai to pio vathu node gia to opoio to current einai sta aristera tou
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;
		}
		return successor;
	}
}	
 //sunartisi pou upologizei to megethos(arithmo)twn komvwn tou upodentrou
int size(TreeNode* T){  
  if (T==NULL)
    return 0;
  else
    return(size(T->left)+ 1 + size(T->right));  
}

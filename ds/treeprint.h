//File: treeprint.h
//https://github.com/aufheben68


#include <stdlib.h>
#include <stdio.h> 
#include <assert.h> 
#include <stdbool.h> 

typedef struct treeNode TreeNode;


typedef struct treeNode {
  int item;
  TreeNode *left;
  TreeNode *right;
  int rank;  
} TreeNode;



void inorder(TreeNode *t, int *pr) {
    if (t==NULL) return;

    inorder(t->left, pr);   

    t->rank = ++(*pr);  
     
    inorder(t->right, pr);  
}


typedef TreeNode *T; 


#define MaxQSize 50 



typedef struct queue {
   T q[MaxQSize];
   int front, rear;
} Queue;

void init(Queue *q) {
  q->front=q->rear=0;
}

void destroy(Queue *q) {
  q->front=q->rear=0;
}

bool isEmpty(Queue *q) {
    return (q->front==q->rear);
}

bool isFull(Queue *q) {
    return (q->rear==MaxQSize);
}

T dequeue(Queue *queue) {
  assert(!isEmpty(queue));  
  return queue->q[queue->front++];
}

void enqueue(Queue *queue, T newitem) {
     assert(!isFull(queue));  
     queue->q[queue->rear++]=newitem;
}


void printTree(TreeNode *t) {

   if (t==NULL) return;

   int rank=0; 
   inorder(t, &rank); 

   
   Queue q[2]; 

   init(&q[0]);
   init(&q[1]);

   const int ItemWidth=3; 
   int level=0; 
   int column=0; 

   enqueue(&q[level],t);

   while (!isEmpty(&q[level])) 
   {

      t=dequeue(&q[level]); 

      int width= ItemWidth * t->rank - column;  
      printf("%*d", width, t->item);  
      column = ItemWidth * t->rank;

      
      if (t->left!=NULL) 
		enqueue(&q[1-level], t->left);
      if (t->right!=NULL) 
		enqueue(&q[1-level], t->right);

      if (isEmpty(&q[level])) {
		level=1-level;
		printf("\n"); 
		column=0;  
      }
   }
   printf("\n");
} 


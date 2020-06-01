
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLUSH stdin=freopen(NULL,"r",stdin)
#define MAX_LEN 50

typedef struct node BST_node;

struct node {
   short id;
   float gpa;
   BST_node *leftChild;
   BST_node *rightChild;
};

BST_node* createBST_node();   
BST_node* createBST();  
void displayBST(BST_node* root);            
void insert_node(BST_node**, BST_node* );
void tree_traversal(BST_node*); 
BST_node* searchBST(BST_node*, short);
void changeBST (BST_node**);
void move_node(BST_node**, short);
short get_id(BST_node*, short);
//void removeBST(BST_node**);  

int main() {    
     
   printf("\nCreating List of students:\n\n");
    
    BST_node* root = createBST();
 
    displayBST(root);
   
    

    if (root!=NULL) {
       putchar('\n');
       changeBST(&root); // Note: comment it out if you don't implement it!
       displayBST(root);
    } 
    
    
  //  removeBST(&root);
    return 0;
}

void displayBST(BST_node* root){

    printf("\n------------------\n");    
    printf(" ID\t  GPA\n");
    printf("------------------\n");
    
   if(root == NULL) {
        printf("List of students is empty.\n");
    }
    else{
        tree_traversal(root);
    }
} 

BST_node* createBST_node(){
    BST_node* root = (BST_node*) malloc( sizeof(BST_node) );
    char tmp[MAX_LEN] ={0};
    char gpa[MAX_LEN] = {0};
    printf("Insert student's id (1 - 100): ");
    fgets(tmp,MAX_LEN,stdin);
    tmp[strcspn(tmp, "\n")] = 0;
    root->id = atoi(tmp);
    get_id(root, 0);
    if(root->id == 0){
        root = NULL;
    }
    else if (root->id  != 0) {
        // GPA input has to be greater than -1 and smaller than 101
        printf("Insert student's GPA (0-100): ");
        fgets(gpa,sizeof(float)+1,stdin);
        printf("\n");
        gpa[strcspn(gpa, "\n")] = 0;
        root->gpa = (float) strtof(gpa,NULL);
        get_id(root, 1);
    }
    return root;
}



BST_node* createBST() {
    BST_node* root = NULL;
    BST_node* node;
    
     while((node = createBST_node()) != NULL){
     insert_node(&root, node);
    }
     return root;
}

void insert_node(BST_node** root, BST_node* node) {
    
    BST_node* temp = node;
    BST_node* current = *root;
    BST_node* parent;
   
    temp->leftChild = NULL;
    temp->rightChild = NULL;
   
    if(current == NULL) {
        *root = temp;
    } else {
        current = *root;
        parent = NULL;
        
        do { 
            parent = current;
            
            //go to left of the tree
            if(temp->id < parent->id) {
                current = current->leftChild;                
                
                //insert to the left
                if(current == NULL) {
                    parent->leftChild = temp;
                }
            }  //go to right of the tree
            else {
                current = current->rightChild;
                //insert to the right
                if(current == NULL) {
                    parent->rightChild = temp;
                }
            }
            
        } while (current != NULL);              
    }
}

void tree_traversal(BST_node* root) { 
    if(root != NULL){
    tree_traversal(root->leftChild);
    printf("\n");
    printf("%d", root->id);
    printf("    %.2f", root->gpa);
    tree_traversal(root->rightChild); 
    } 
} 

// function called to change ID in a node in BST
void changeBST (BST_node** root) {
    short flag = 0;
    BST_node *current = *root;
    BST_node *temp = NULL;
    char tmp[MAX_LEN] ={0};
    printf("\nEnter the id of the record you want to change:");
    fgets(tmp,MAX_LEN,stdin);
    tmp[strcspn(tmp, "\n")] = 0;
    int id = atoi(tmp);
    temp = searchBST(current, id);
    int gpa = temp->gpa;
    move_node(&current, id);
    printf("\nInput the new id:");
    fgets(tmp,MAX_LEN,stdin);
    tmp[strcspn(tmp, "\n")] = 0;
    id = atoi(tmp);
    temp->gpa = gpa;
    temp->id = id;
    get_id(temp, flag);
    insert_node(&current,temp);      
} 

BST_node* searchBST(BST_node* root, short id){
     BST_node *current = root;
    while(current != NULL && current->id != id){        
        current = (current->id > id) ? current->leftChild : current->rightChild;
    }
    printf("\n");
    return current;
 }

void move_node(BST_node** root, short key){
    BST_node *current = *root;
    BST_node *parent = NULL;
    
    do{
        parent = current;
        if(key < current->id ){
            current = current->leftChild;
            
        }
        
        if(key > current->id){
            current = current->rightChild;
           
        }  
        
        if(key == current->id && current->leftChild == NULL && current->rightChild == NULL && current->id < parent->id){
            parent->leftChild = NULL;
           
        }
        
        if(key == current->id && current->leftChild == NULL && current->rightChild == NULL && current->id > parent->id){
            parent->rightChild= NULL;   
        }
        
        if(key == current->id && current->rightChild == NULL && current->leftChild != NULL && current->id > parent->id){ 
           parent->rightChild = current->leftChild;  
        }
        
        if(key == current->id && current->rightChild != NULL && current->leftChild == NULL && current->id > parent->id){ 
           parent->rightChild = current->rightChild;  
        }
        
        
        if(key == current->id && current->leftChild != NULL && current->rightChild == NULL && current->id < parent->id){  
            parent->leftChild = current->leftChild; 
            
        } 
        
        if(key == current->id && current->leftChild == NULL && current->rightChild != NULL && current->id < parent->id){  
            parent->leftChild = current->rightChild; 
        }     
    }while (current->id != key); 
  }

short get_id(BST_node* root, short flag) {
    char tmp[MAX_LEN] = {0};
    if(((root->id < 1000 || root->id > 9999) && flag == 0) && root->id != 0){
     printf("Incorrect value! Please try again!\n");
    printf("Insert student's id (1 - 100): ");
    fgets(tmp,MAX_LEN,stdin);
    tmp[strcspn(tmp, "\n")] = 0;
    root->id = atoi(tmp);
    if(root->id == 0){
        root = NULL;
    }
    } 
    
     if((root->gpa > 100 || root->gpa < 0) && flag == 1 ){
        printf("Incorrect value! Please try again!\n");
        char gpa[MAX_LEN] = {0};
        printf("Insert student's GPA (0-100): ");
        fgets(gpa,sizeof(float)+1,stdin);
        printf("\n");
        gpa[strcspn(gpa, "\n")] = 0;
        root->gpa = (float) strtof(gpa,NULL);   
    } 
 }
/* This one is implemented but it doesn't  work for some reason 
void removeBST(BST_node** root){
    BST_node *rem = *root;
    if(rem != NULL){
     removeBST(rem->leftChild);
     removeBST(rem->rightChild);
     free(rem.leftChild);
     free(rem->rightChild);
     free(rem); 
    } 

}
*/
 
    
    
      


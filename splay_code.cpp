#include <bits/stdc++.h>
using namespace std;

struct node
{
  int key;
  struct node *left;
  struct node *right;
};

struct node* newnode(int k)
{ 
    struct node* n=(struct node*)malloc(sizeof(struct node));
    n->key=k;
    n->left=NULL;
     n->right=NULL;
     return n;
}
                                      //right-rotation
struct node* right_rot(struct node* G,struct node* p,struct node* n)
{
    p->left=n->right;
    n->right=p;
    if(G==NULL){
    return n;
    }
    else{
        if(G->right->key==p->key){ G->right=n;}
        else{G->left=n;}
        return n;
    }
}
                                      //left-rotation
struct node* left_rot(struct node* G,struct node* p,struct node* n)
{
    
    p->right=n->left;
    n->left=p;
    if(G==NULL){
    return n;
    }
    else{
        if(G->right->key==p->key){ G->right=n;}
        else{G->left=n;}
        return n;
       }
 }

struct node* splay(struct node* G,struct node *root,int k)
{
    if(root==NULL || root->key==k)     //found root or not present
    {
        return root;
    }
//searching in left side of root    
    if(root->key > k)
    {
        if(root->left == NULL)
        {
            return root;
        }
        if(root->left->key > k)
        {
            // {cout<<"right"<<endl;
            root->left->left=splay(root->left,root->left->left,k);
            if(root->left->left==NULL)
            {
                return root;             
            }
            else                           //zig-zig
            {
                // cout<<"right"<<endl;
             root->left=right_rot(root,root->left,root->left->left);
             return right_rot(G,root,root->left);
            }
        }
        else if(root->left->key < k)
        {
            root->left->right=splay(G,root->left->right,k);
            if(root->left->right == NULL)
            {
            return root;
            }
            else                          //zag-zig
            {
            root->left = left_rot(root,root->left,root->left->right);
            return right_rot(G,root,root->left); 
            }
         }
         else
         {
             return right_rot(G,root,root->left);     //zig
         } 
    }
//searching in right side of tree
  else{
         if(root->right == NULL)
            {
                return root;
            }
        if(root->right->key > k)
        {
        // cout<<"right"<<endl;
            root->right->left=splay(root->right,root->right->left,k);
            if(root->right->left==NULL)
            {
                return root;             
             }
            else                             //zig-zag
            {
              // cout<<"right"<<endl;
             root->right=right_rot(root,root->right,root->right->left);
             return left_rot(G,root,root->right);
            }
           
        }
        else if(root->right->key < k)
        {
            
            root->right->right=splay(G,root->right->right,k);
            if(root->right->right == NULL){
                return root;
            }
            else{                            //zag-zag
            root->right = left_rot(root,root->right,root->right->right);
            return left_rot(G,root,root->right); 
            }
         }
         else{
             return left_rot(G,root,root->right);    //zag
         } 
      }
//
}

void inorder(struct node* root)    //inorder display of tree
{
    if(root!=NULL){
    inorder(root->left);
    cout<<root->key<<" ";
    inorder(root->right);
    }
}
void preorder(struct node* root)   //preorder display of tree
{
    if(root!=NULL){
    cout<<root->key<<" ";
    preorder(root->left);
    preorder(root->right);
    }
}

int main() {
    struct node* root=(struct node*)malloc(sizeof(struct node));
    root=newnode(5);
    root->right=newnode(6);
    root->left=newnode(3);
    root->left->left=newnode(2);
    root->left->right=newnode(4);
    root->left->left->left=newnode(1);
    
    cout<<"preorder: ";
    preorder(root);
    cout<<endl;
    cout<<"enter the node key to splay :"<<endl;
    int key;
    cin>>key;                 //asking key to splay
    root=splay(NULL,root,key);
    cout<<root->key<<" is root of tree"<<endl;
    
    cout<<"preorder:";        //printing tree after splaying
    preorder(root);
    cout<<endl;
    cout<<"inorder:";
    inorder(root);
    
     return 0;
}
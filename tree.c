#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include "tree.h"

struct tree
{
  int data;
  struct tree *left,*right,*parent;
};

struct tree *createTree(int data, struct tree *left, struct tree *right)
{
  struct tree *root;
  //allocates a node to hold data
  root = malloc(sizeof(struct tree));            
  assert(root != NULL);

  root->data = data;
  root->parent = NULL;

  //If a left node exists
  if(left != NULL)
  {
    //If the left parent exist                                         
    if(left->parent != NULL)
    { 
      //check the left node                    
      if (left->parent->left == left)
      {
        //cut the link      
        left->parent->left = NULL;     
      }
      //check to see if it is the right node
      if (left->parent->right == left)
      {     
        //cut the link
        left->parent->right = NULL;   
      }
    }
    //set the left parent equal to the root
    left->parent = root;            
  }

  if(right != NULL)
  {                     
    //same as above but for the right node
    if(right->parent!=NULL)
    {
      if (right->parent->left == right)
      {
        right->parent->left = NULL;
      }
      if(right->parent->right  == right)
      {
        right->parent->right = NULL;
      }
    }
    right->parent = root;
  }
  //set the new nodes left and right
  root->left = left;                   
  root->right = right;
  return root;
}

void destroyTree(struct tree *root)
{     
  //recursively go through and free the root from the bottom up
  if(root == NULL)
    return;

  destroyTree(root->left);
  destroyTree(root->right);
  free(root);
}


int getData(struct tree *root)
{      
  //return the data
  assert (root!=NULL);
  return root->data;;
}


struct tree *getLeft(struct tree *root)
{     
  //return the left node of the root
  assert(root!=NULL);
  return root->left;
}

struct tree *getRight(struct tree *root)
{    
  //return the right node of the root
  assert(root!=NULL);
  return root->right;
}


struct tree *getParent(struct tree *root)
{   
  //get the parent of the root node
  assert(root!= NULL);
  return root->parent;
}

void setLeft(struct tree *root, struct tree *left)
{
  if (root->left!=NULL)
  {
    root->left->parent=NULL;
    root->left=NULL;
  }

  if (left!=NULL)
  {
    if(left->parent!=NULL)
    {
      if (left->parent->left == left)
      {
        left->parent->left = NULL;
      }

      if (left->parent->right == left)
      {
        left->parent->right = NULL;
      }
    }
    left->parent = NULL;
  }

  root->left = left;
  left->parent = root;
  return;
}

void setRight(struct tree *root, struct tree *right)
{      
  if (root->right!=NULL)
  {
    root->right->parent=NULL;
    root->right=NULL;
  }

  if (right!=NULL)
  {
    if(right->parent!=NULL)
    {
      if (right->parent->left == right)
      {
        right->parent->right = NULL;
      }

      if (right->parent->right == right)
      {
        right->parent->right = NULL;
      }
    }
    right->parent = NULL;
  }
  
  root->right = right;
  right->parent = root;
  return;
}



#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * TODO: Implement all the functions in tree.h here.
 *
 * Use as many helper functions as you need, just declare them to be static.
 *
 */
int total_len;

typedef struct keystruc{
  int key;
  int structure;
} keystruc;

static Tree *alloc_node(int data) {
  Tree *ret = calloc(1, sizeof(Tree));
  if (ret == NULL) {
    return NULL;
  }

  ret->data = data;

  return ret;
}

// helper function: to make binary file into array [key, structure]
static keystruc* make_tree_array(char* filename)
{
  //printf("Start making tree array\n");
  FILE* fptr = fopen(filename, "rb");
  // count number of nodes
  int count = 0;
  int key;
  unsigned char structure;
  while (1)
  {
    if (fread(&key, sizeof(int), 1, fptr) != 1)
    {
      break;
    }
    if (fread(&structure, sizeof(unsigned char), 1, fptr) != 1)
    {
      break;
    }
    count++;
  }
  //printf("total Count: %d\n", count);
  total_len = count;

  //initialize keystruc array
  keystruc* tree_array = malloc(sizeof(keystruc) * count);

  // POINT BACK!!!
  fseek(fptr, 0, SEEK_SET);
  while(count)
  {
    if (fread(&key, sizeof(int), 1, fptr) != 1)
    {
      break;
    }
    if (fread(&structure, sizeof(unsigned char), 1, fptr) != 1)
    {
      
      break;
    }

    tree_array[total_len - count].key = key;
    tree_array[total_len - count].structure = structure;
    count--;
    //printf("Count left: %d\n", count);
  }
  //printf("Finish making tree array\n");
  
  fclose(fptr);
  return tree_array;
}

static Tree* Helper_read_from_file(char* filename, int total_node, int* index, keystruc* tree_array)
{
  // base case
  if (*index >= total_len)
  {
    return NULL;
  }

  // initialize the current node
  Tree* current_node = alloc_node(tree_array[*index].key);
  int current_index = *index;
  (*index)++;
  

  // traverse thru left, if node has left
  if (tree_array[current_index].structure & 0x01)
  {
    //(*index)++;
    current_node->left = Helper_read_from_file(filename, total_node, index, tree_array);
  } else
  {
    current_node->left = NULL;
  }
  // traverse thru right, if node has right
  if (tree_array[current_index].structure & 0x02)
  {
    //(*index)++;
    current_node->right = Helper_read_from_file(filename, total_node, index, tree_array);
  } else
  {
    current_node->right = NULL;
  }


  return current_node;

}

static void print_tree_preorder(Tree* tree)
{
  if (tree == NULL)
  {
    return;
  }
  printf("Node: %d\n", tree->data);
  print_tree_preorder(tree->left);
  print_tree_preorder(tree->right);
}

Tree* read_from_file(char* filename)
{
  //printf("Start reading from file\n");
  int index = 0;
  keystruc* tree_array = make_tree_array(filename);
  Tree* rtn_tree = Helper_read_from_file(filename, total_len, &index, tree_array);
  free(tree_array);
  //print_tree_preorder(rtn_tree);
  //printf("Finish reading from file\n");
  return rtn_tree;
}

Tree *invert_tree(Tree *root)
{
  if (root == NULL)
  {
    return NULL;
  }

  Tree* tree = alloc_node(root->data);

  tree->left = invert_tree(root->right);
  tree->right = invert_tree(root->left);

  return tree;
}

static void Helper_preorder_print(Tree* root, FILE* fptr)
{
  if (root == NULL)
  {
    return;
  }

  unsigned char structure = 0;

  fwrite(&(root->data), sizeof(int), 1, fptr);

  if (root->left != NULL)
  {
    structure += 1;
  }

  if (root->right != NULL)
  {
    structure += 2;
  }

  fwrite(&structure, sizeof(unsigned char), 1, fptr);

  Helper_preorder_print(root->left, fptr);
  Helper_preorder_print(root->right, fptr);

}

void preorder_print(Tree *root, char *filename)
{
  FILE* fptr = fopen(filename, "wb");
  
  Helper_preorder_print(root, fptr);

  fclose(fptr);
}

static void Helper_free_tree(Tree* root)
{
  if (root == NULL)
  {
      return;
  }

  Helper_free_tree(root->left);
  Helper_free_tree(root->right);
  free(root);
}
void free_tree(Tree *root)
{
  //print_tree_preorder(root);
  //printf("\n");
  Helper_free_tree(root);
}

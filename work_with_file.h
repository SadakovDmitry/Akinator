#ifndef USED_W_W_FILE
#define USED_W_W_FILE

#include "lib.h"
char* Convert_str_in_buf(char* new_val);
void Beautiful_Dump();
void Draw_Graph(struct Tree* tree);
void Print_Node_to_file(struct Node* node, FILE* file_dot, int i);
void Save_new_tree(struct Node* node, FILE* file);
void Arrows_in_Graph(struct Node* node, FILE* file_dot);
void Reload_tree(struct Tree* tree);
void Convert_file_to_tree_with_pointers(struct Tree* tree);

#define STR_TYPE
#define _GNU_SOURCE
#define tree_t "%s"
//#define TYPE_INSERT atoi(&buf[i + 2])
//#define INSERT  Insert(tree, atoi(&buf[i + 2]));
#define INSERT_TO_POINTER Insert_to_Pointer(tree, new_val, now_node);


typedef char* Tree_t;


const int STR_SIZE = 100;
const int INSERT_LEFT  =  1;
const int INSERT_RIGHT = -1;



struct Node
{
    Tree_t val;
    int num_node;
    struct Node* left;
    struct Node* right;
    struct Node* prev;
};

struct Tree
{
    struct Node* root;
    int size;
};

#endif

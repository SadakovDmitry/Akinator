#include "lib.h"
#include "work_with_file.h"
#include "tree_functions.h"

struct Node* Create_Node(Tree_t new_val)
{
    struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));
    new_node -> val = (char*) calloc(100, sizeof(char));

    new_node -> val = new_val;
    new_node -> left = NULL;
    new_node -> right = NULL;

    return new_node;
}

struct Tree* Tree_Ctor()
{
    struct Tree* tree = (struct Tree*) calloc(1, sizeof(struct Tree));

    tree -> size = 0;

    return tree;
}



struct Node* Insert(struct Tree* tree, Tree_t new_val)
{
    assert(tree);

    struct Node* now_node = tree -> root;

    struct Node* new_node = Create_Node(new_val);

    if(!(now_node))
    {
        tree -> root = new_node;
        return tree -> root;
    }

    while(true)
    {
        if(new_val >= now_node -> val)
        {
            if(now_node -> right == NULL)
            {
                now_node -> right = new_node;
                break;
            }
            else
            {
                now_node = now_node -> right;
            }
        }
        else
        {
            if(now_node -> left == NULL)
            {
                now_node -> left = new_node;
                break;
            }
            else
            {
                now_node = now_node -> left;
            }
        }
    }
    tree -> size++;

    return new_node;
}

struct Node* Insert_to_Pointer(struct Tree* tree, Tree_t new_val, struct Node* now_node, int indicator)
{
    struct Node* new_node = Create_Node(new_val);
    tree -> size++;

    if(!(now_node))
    {
        tree -> root = new_node;
        return tree -> root;
    }

    new_node -> prev = now_node;

    if(indicator == INSERT_LEFT)
    {
        now_node -> left  = new_node;
    }
    else if(indicator == INSERT_RIGHT)
    {
        now_node -> right = new_node;
    }

    return new_node;
}

void Delite_Sub_Tree(struct Node* del_node)
{
    assert(del_node);

    del_node -> right = NULL;
    del_node -> left  = NULL;

    Delite_Sub_Tree(del_node -> left );

    free(del_node -> left );
    free(del_node -> right);

    Delite_Sub_Tree(del_node -> right);

    free(del_node -> left );
    free(del_node -> right);


}

void Tree_Dtor(struct Tree* tree)
{
    assert(tree);

    Delite_Sub_Tree(tree -> root);
}



void Print_Post_Order(struct Node* node)
{
    if(node == NULL){
        printf("null ");
        return;
    }

    printf("( ");
    Print_Post_Order(node -> left);
    Print_Post_Order(node -> right);
    printf("\""tree_t"\" ", node -> val);
    printf(") ");
}

void Print_Pre_Order(struct Node* node)
{
    Save_new_tree(node, stdout);
}

void Print_In_Order(struct Node* node)
{
    if(node == NULL){
        printf("null ");
        return;
    }

    printf("( ");
    Print_In_Order(node -> left);
    printf("\""tree_t"\" ", node -> val);
    Print_In_Order(node -> right);
    printf(") ");
}



void Tree_Dump(struct Tree* tree)
{
    assert(tree);

    Beautiful_Dump();
    printf("root = %p\nsize = %d\n", tree -> root, tree -> size);
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    Print_Pre_Order(tree -> root);
}
/*
void Clean_buf()
{
    while(getchar() != '\n')
        ;
}
*/

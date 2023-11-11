#include "lib.h"
#include "/Users/dima/MIPT/Stack/stack.h"

//#define DUMP_ON

typedef int Tree_t;

struct Tree* Tree_Ctor(Tree_t value);
struct Node* Create_Node(Tree_t new_val);
struct Node* Insert(struct Tree* tree, Tree_t new_val);
void Print_Pre_Order(struct Node* node);
void Print_In_Order(struct Node* node);
void Print_Post_Order(struct Node* node);
void Tree_Dtor(struct Tree* tree);
void Delite_Sub_Tree(struct Node* del_node);
void Beautiful_Dump();
void Draw_Graph(struct Tree* tree);
void Print_Node_to_file(struct Node* node, FILE* file_dot, int i);

struct Node
{
    Tree_t val;
    int num_node;
    struct Node* left;
    struct Node* right;
};

struct Tree
{
    struct Node* root;
    int size;
};

struct Node* Create_Node(Tree_t new_val)
{
    struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));

    new_node -> val = new_val;
    new_node -> left = NULL;
    new_node -> right = NULL;

    return new_node;
}

struct Tree* Tree_Ctor(Tree_t value)
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
    printf("%d ", node -> val);
    printf(") ");
}

void Print_Pre_Order(struct Node* node)
{
    if(node == NULL){
        printf("null ");
        return;
    }

    printf("( ");
    printf("%d ", node -> val);
    Print_Pre_Order(node -> left);
    Print_Pre_Order(node -> right);
    printf(") ");
}

void Print_In_Order(struct Node* node)
{
    if(node == NULL){
        printf("null ");
        return;
    }

    printf("( ");
    Print_In_Order(node -> left);
    printf("%d ", node -> val);
    Print_In_Order(node -> right);
    printf(") ");
}

void Tree_Dump(struct Tree* tree)
{
    assert(tree);

    Beautiful_Dump();
    printf("root = %p\nsize = %d\n", tree -> root, tree -> size);
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    Print_In_Order(tree -> root);
}

void Print_Node_to_file(struct Node* node, FILE* file_dot, int i)
{
    if(node == NULL) return;
    i++;

    Print_Node_to_file(node -> left, file_dot, i);
    node -> num_node = i;
    fprintf(file_dot, "%d [shape = record, style = \"rounded\", label = \"{val: %d |{ <left> left: %p | <right> right: %p }}\"];\n\t", i, node -> val, node -> left, node -> right);

    i++;

    Print_Node_to_file(node -> right, file_dot, i);
}

void Arrows_in_Graph(struct Node* node, FILE* file_dot)
{
    if(node == NULL) return;

    if (node -> left != NULL)
    {
        fprintf(file_dot, "%d -> %d\n\t", node -> num_node , (node -> left) -> num_node);
    }

    Arrows_in_Graph(node -> left, file_dot);

    if (node -> right != NULL)
    {
        fprintf(file_dot, "%d -> %d\n\t", node -> num_node , (node -> right) -> num_node);
    }

    Arrows_in_Graph(node -> right, file_dot);

}

void Beautiful_Dump()
{
    printf( "\n\n\033[36m          /＞   フ\n"
            "         |  _  _| \n"
            "        /`ミ _x 彡 \n"
            "       /        | \n"
            "      /  ヽ     ﾉ \n"
            "  ／￣|    | | | \n"
            "  | (￣ヽ__ヽ_)_) \n"
            "  ＼二つ    \033[31mDUMP\033[0m\n\n");
}

void Draw_Graph(struct Tree* tree)
{
    FILE* file_dot = fopen("Tree_Graph.dot", "w");

    assert(file_dot);

    fprintf(file_dot, "digraph G\n{\n\trankdir = \"TB\";\n\n\tnode[color = \"red\", fontsize = 14];\n\tedge[color = \"black\", fontcolor = \"blue\", fontsize = 12, weight = 0];\n\n\t");

    fprintf(file_dot, "Tree [shape = record, style = \"rounded\", label = \"root: %p | size: %d\"];\n\t", tree -> root, tree -> size);

    int i = 0;
    Print_Node_to_file(tree -> root, file_dot, i);
    Arrows_in_Graph(tree -> root, file_dot);

    fprintf(file_dot, "\n}\n");
}

void Convert_file_to_tree(struct Tree* tree)
{
    struct stat st = {};
    int open_brackets = 0;
    int close_brackets = 0;
    int i = 0;

    FILE* file = fopen("Tree.txt", "r");
    stat("Tree.txt", &st);

    char* buf = (char*) calloc(st.st_size, sizeof(char));

    fread(buf, sizeof (char), st.st_size, file);

     while (true)
    {
        if(buf[i] == '(')
        {
            open_brackets++;
            Insert(tree, atoi(&buf[i + 2]));
        }
        else if(buf[i] == ')')
        {
            close_brackets++;
        }
        if(close_brackets == open_brackets)
        {
            break;
        }
        i++;

        #ifdef DUMO_ON
            Tree_Dump(tree);
        #endif
    }

}



int main()
{
    struct Tree* tree = Tree_Ctor(10);
    /*
    Insert(tree, 20);
    Insert(tree, 5);
    Insert(tree, 30);
    */
    Convert_file_to_tree(tree);

    Tree_Dump(tree);
    Draw_Graph(tree);
}

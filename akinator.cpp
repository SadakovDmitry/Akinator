#include "lib.h"
#include "work_with_file.h"
#include "tree_functions.h"
#include "operating_mode.h"

#include "/Users/dima/MIPT/Stack/stack.h"



int main()
{
    struct Canary canary = {};
    struct ERRORS ERR = {};
    struct Tree* tree = Tree_Ctor();
    int capacity = 1;

    struct Stack* stk = Stack_Ctor( capacity, &ERR, &canary);

    Convert_file_to_tree_with_pointers(tree);

    Draw_Graph(tree);

    Guessing(tree);

    Reload_tree(tree);

    Tree_Dump(tree);
    Draw_Graph(tree);

    Stack_Dtor (stk, &canary);

    //exit(EXIT_SUCCESS);
}

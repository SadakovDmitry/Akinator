#include "work_with_file.h"
#include "tree_functions.h"
#include "lib.h"

#include "/Users/dima/MIPT/Stack/stack.h"
//#include "stack.h"


char* Convert_str_in_buf(char* new_val)
{
    #ifdef STR_TYPE
        int i = 0;

        char* str_val = (char*) calloc(STR_SIZE, sizeof(char));

        while(*(new_val + i + 1) != '\"')
        {
            *(str_val + i) = *(new_val + i + 1);
            i++;
        }

    #endif

    return str_val;
}

void Print_Node_to_file(struct Node* node, FILE* file_dot, int i)
{
    if(node == NULL) return;
    i++;
    Print_Node_to_file(node -> left, file_dot, i);
    i--;
    //fprintf(file_dot, "%lld [rank = \"%d\", shape = record, style = \"rounded\", label = \"{val: "tree_t" |{ <left> left: %p | <right> right: %p }}\"];\n\t", (long long int) node, i, node -> val, node -> left, node -> right);
    fprintf(file_dot, "%lld [rank = \"%d\", shape = record, style = \"rounded\", label = \"{"tree_t" |{ <left> left | <right> right }}\"];\n\t", (long long int) node, i, node -> val);
    i++;
    Print_Node_to_file(node -> right, file_dot, i);
    i--;
}

void Arrows_in_Graph(struct Node* node, FILE* file_dot)
{
    if(node == NULL) return;

    if (node -> left != NULL)
    {
        fprintf(file_dot, "%lld:<left> -> %lld[color = \"green\"]\n\t", (long long int) node, (long long int) node -> left);
    }

    Arrows_in_Graph(node -> left, file_dot);

    if (node -> right != NULL)
    {
        fprintf(file_dot, "%lld:<right> -> %lld[color = \"red\"]\n\t", (long long int) node, (long long int) node -> right);
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

    int i = 1;
    Print_Node_to_file(tree -> root, file_dot, i);
    Arrows_in_Graph(tree -> root, file_dot);

    fprintf(file_dot, "\n}\n");

    fclose(file_dot);
}

void Save_new_tree(struct Node* node, FILE* file)
{
    if(node == NULL){
        fprintf(file, "null ");
        return;
    }

    fprintf(file, "( ");
    fprintf(file, "\""tree_t"\" ", node -> val);
    Save_new_tree(node -> left, file);
    Save_new_tree(node -> right, file);
    fprintf(file, ") ");
}

void Reload_tree(struct Tree* tree)
{
    char answer[STR_SIZE] = "";

    printf("\nDo you wont save new data base ?\n");
    scanf("%s", answer);

    if (strcasecmp("yes", answer) == 0)
    {
        FILE* file = fopen("Tree.txt", "w");
        Save_new_tree(tree -> root, file);
        fclose(file);
    }
}

void Convert_file_to_tree_with_pointers(struct Tree* tree)
{
    struct stat st = {};
    int open_brackets = 0;
    int close_brackets = 0;
    struct Node* temp = NULL;
    char* new_val = NULL;
    int i = 0;
    int indicator = INSERT_LEFT;

    FILE* file = fopen("Tree.txt", "r");
    stat("Tree.txt", &st);

    char* buf = (char*) calloc(st.st_size, sizeof(char));

    fread(buf, sizeof (char), st.st_size, file);

    struct Node* now_node = tree -> root;

    while (true)
    {
        if(buf[i] == '(')
        {
            open_brackets++;
            temp = now_node;

            new_val = Convert_str_in_buf(&buf[i + 2]);

            now_node = Insert_to_Pointer(tree, new_val, now_node, indicator);

            indicator = INSERT_LEFT;
            now_node -> prev = temp;

        }
        else if(buf[i] == ')')
        {
            close_brackets++;
            now_node = now_node -> prev;
            indicator = INSERT_RIGHT;
        }
        else if(strncmp(&buf[i], "null", 4) == 0)
        {
            indicator = indicator * INSERT_RIGHT;
            i = i + 3;
        }

        if(close_brackets == open_brackets)
        {
            break;
        }
        i++;

        #ifdef DUMP_ON_TREE
            Tree_Dump(tree);
        #endif
    }
    fclose(file);
}




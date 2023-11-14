#include "lib.h"
#include "/Users/dima/MIPT/Stack/stack.h"

//#define DUMP_ON
#define STR_TYPE
#define _GNU_SOURCE
#define tree_t "%s"
#define TYPE_INSERT atoi(&buf[i + 2])
//#define INSERT  Insert(tree, atoi(&buf[i + 2]));
#define INSERT_LEFT   Insert_to_Pointer_left(tree, new_val, now_node);
#define INSERT_RIGHT  Insert_to_Pointer_right(tree, new_val, now_node);

typedef char* Tree_t;

const int STR_SIZE = 100;

void Reload_tree(struct Tree* tree);
void Guessing(struct Tree* tree);
struct Tree* Tree_Ctor();
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
struct Node* Insert_to_Pointer(struct Tree* tree, Tree_t new_val, struct Node* now_node);
void Save_new_tree(struct Node* node, FILE* file);

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

        //*(str_val + i) = '\0';
        //str_val = (char*) realloc(str_val, i + 1);
    #endif

    return str_val;
}

struct Node* Create_Node(Tree_t new_val)
{
    struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));
    new_node -> val = (char*) calloc(100, sizeof(char));

    new_node -> val = new_val;
    //fprintf(stderr, " str = %s\n", new_val);
    new_node -> left = NULL;
    new_node -> right = NULL;

    return new_node;
}

struct Tree* Tree_Ctor()
{
    struct Tree* tree = (struct Tree*) calloc(1, sizeof(struct Tree));


    tree -> size = 0;
    /*
    (tree -> root) -> left = NULL;
    (tree -> root) -> right = NULL;
    (tree -> root) -> val = value;
    */

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

struct Node* Insert_to_Pointer_left(struct Tree* tree, Tree_t new_val, struct Node* now_node)
{
    struct Node* new_node = Create_Node(new_val);
    tree -> size++;

    if(!(now_node))
    {
        tree -> root = new_node;
        return tree -> root;
    }

    new_node -> prev = now_node;
    now_node -> left = new_node;

    return new_node;
}

struct Node* Insert_to_Pointer_right(struct Tree* tree, Tree_t new_val, struct Node* now_node)
{
    struct Node* new_node = Create_Node(new_val);
    tree -> size++;

    if(!(now_node))
    {
        tree -> root = new_node;
        return tree -> root;
    }

    new_node -> prev = now_node;
    now_node -> right = new_node;

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



void Print_Node_to_file(struct Node* node, FILE* file_dot, int i)
{
    if(node == NULL) return;
    //i++;

    Print_Node_to_file(node -> left, file_dot, i);
    //node -> num_node = i;
    //fprintf(stderr, " str = %s\n", node -> val);
    fprintf(file_dot, "%lld [shape = record, style = \"rounded\", label = \"{val: "tree_t" |{ <left> left: %p | <right> right: %p }}\"];\n\t", (long long int) node, node -> val, node -> left, node -> right);

    //i++;

    Print_Node_to_file(node -> right, file_dot, i);
}

void Arrows_in_Graph(struct Node* node, FILE* file_dot)
{
    if(node == NULL) return;

    if (node -> left != NULL)
    {
        fprintf(file_dot, "%lld -> %lld\n\t", (long long int) node, (long long int) node -> left);
    }

    Arrows_in_Graph(node -> left, file_dot);

    if (node -> right != NULL)
    {
        fprintf(file_dot, "%lld -> %lld\n\t", (long long int) node, (long long int) node -> right);
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



/*
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
            //printf("str = %s", TYPE_INSERT);
            INSERT
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

        #ifdef DUMP_ON
            Tree_Dump(tree);
        #endif
    }
}
*/

void Convert_file_to_tree_with_pointers(struct Tree* tree)
{
    struct stat st = {};
    int open_brackets = 0;
    int close_brackets = 0;
    struct Node* temp = NULL;
    char* new_val = NULL;
    int i = 0;
    int ind = 1;

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

            if(ind == 1)
            {
                now_node = INSERT_LEFT

            }
            else
            {
                now_node = INSERT_RIGHT
            }
            ind = 1;
            now_node -> prev = temp;

        }
        else if(buf[i] == ')')
        {
            close_brackets++;
            now_node = now_node -> prev;
            ind = -1;
        }
        else if(strncmp(&buf[i], "null", 4) == 0)
        {
            ind = ind * -1;
            i = i + 3;
        }
        //printf("str = %c\n ind = %d\n\n", buf[i], ind);


        if(close_brackets == open_brackets)
        {
            break;
        }
        i++;

        #ifdef DUMP_ON
            Tree_Dump(tree);
        #endif
    }
    fclose(file);
    }



void Guessing(struct Tree* tree)
{
    struct Node* now_node = tree -> root;
    char answer[100] = "";

    while (true)
    {
        printf("\nIs it %s ?\n", now_node -> val);
        scanf("%s", answer);

        if (strcasecmp("yes", answer) == 0)
        {
            now_node = now_node -> left;

            if(!(now_node -> left))
            {
                printf("\nIs it %s ?\n", now_node -> val);
                scanf("%s", answer);

                if (strcasecmp("yes", answer) == 0)
                {
                    printf("\nBrilliant!!!\n");
                }
                else if (strcasecmp("no", answer) == 0)
                {
                        printf("\nWho/What is it ?\n");
                        scanf("%s", answer);
                        char* new_val = (char*) calloc(100, sizeof(char));
                        new_val = strcpy(new_val, answer);
                        Insert_to_Pointer_left(tree, new_val, now_node);
                        Insert_to_Pointer_right(tree, now_node -> val, now_node);

                        printf("\nPrint what differense between %s and %s ?\n", answer, now_node -> val);

                        size_t len = STR_SIZE;
                        char* str_dif = (char*) calloc(STR_SIZE, sizeof(char));

                        while(getchar() != '\n')
                            ;

                        getline(&str_dif, &len, stdin);

                        len = strlen(str_dif);
                        char* new_dif = (char*) calloc(STR_SIZE, sizeof(char));
                        new_dif = strncpy(new_dif, str_dif, len - 1);

                        now_node -> val = new_dif;
                }
                break;
            }
        }
        else if (strcasecmp("no", answer) == 0)
        {
            now_node = now_node -> right;

            if(!(now_node -> right))
            {
                printf("\nIs it %s ?\n", now_node -> val);
                scanf("%s", answer);

                if (strcasecmp("yes", answer) == 0)
                {
                    printf("\nBrilliant!!!\n");
                }
                else if (strcasecmp("no", answer) == 0)
                {
                    //printf("\nDo you wont add this ?\n");
                    //scanf("%s", answer);
                    //if (strcasecmp("yes", answer) == 0)
                    //{
                        printf("\nWho/What is it ?\n");
                        scanf("%s", answer);
                        char* new_val = (char*) calloc(100, sizeof(char));
                        new_val = strcpy(new_val, answer);
                        Insert_to_Pointer_left(tree, new_val, now_node);
                        Insert_to_Pointer_right(tree, now_node -> val, now_node);

                        printf("\nPrint what differense between %s and %s ?\n", answer, now_node -> val);
                        //scanf("%s", answer);
                        //int len = 0;
                        //while(scanf("%s", answer) == 1)
                        //{
                        size_t len = STR_SIZE;
                        char* str_dif = (char*) calloc(STR_SIZE, sizeof(char));

                        Clean_buf();

                        getline(&str_dif, &len, stdin);

                        len = strlen(str_dif);
                        char* new_dif = (char*) calloc(STR_SIZE, sizeof(char));
                        new_dif = strncpy(new_dif, str_dif, len - 1);
                        //fprintf(stderr, "%s\n", str_dif);

                        now_node -> val = new_dif;
                    //}
                }
                break;
            }
        }
        else
        {
            printf("Incorrect input! You can answer only \"yes\" or \"no\"!");
        }
    }
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


void Clean_buf()
{
    while(getchar() != '\n')
        ;
}


int main()
{
    struct Tree* tree = Tree_Ctor();

    Convert_file_to_tree_with_pointers(tree);

    Draw_Graph(tree);

    Guessing(tree);

    Reload_tree(tree);

    Tree_Dump(tree);
    Draw_Graph(tree);
    //exit(EXIT_SUCCESS);
}

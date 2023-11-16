#include "lib.h"
#include "work_with_file.h"
#include "tree_functions.h"
#include "operating_mode.h"

#include "/Users/dima/MIPT/Stack/stack.h"

void Add_new_elem(struct Tree* tree, struct Node* now_node)
{
    char answer[STR_SIZE] = "";

    Set_new_value(tree, now_node, answer);

    Set_difference(now_node, answer);

}

void Set_new_value(struct Tree* tree, struct Node* now_node, char* answer)
{
    printf("\nWho/What is it ?\n");
    scanf("%s", answer);

    char* new_val = (char*) calloc(STR_SIZE, sizeof(char));
    new_val = strcpy(new_val, answer);

    Insert_to_Pointer(tree, new_val, now_node, INSERT_LEFT);
    Insert_to_Pointer(tree, now_node -> val, now_node, INSERT_RIGHT);
}

void Set_difference(struct Node* now_node, char* answer)
{
    size_t len = STR_SIZE;
    char* str_dif = (char*) calloc(STR_SIZE, sizeof(char));
    char* new_dif = (char*) calloc(STR_SIZE, sizeof(char));

    printf("\nPrint what differense between %s and %s ?\n", answer, now_node -> val);

    Clean_buf();

    getline(&str_dif, &len, stdin);

    len = strlen(str_dif);
    new_dif = strncpy(new_dif, str_dif, len - 1);

    now_node -> val = new_dif;
}

void Cmp_with_answer(struct Tree* tree, struct Node* now_node)
{
    char answer[STR_SIZE] = "";

    printf("\nIs it %s ?\n", now_node -> val);
    scanf("%s", answer);

    if (strcasecmp("yes", answer) == 0)
    {
        printf("\nBrilliant!!!\n");
    }
    else if (strcasecmp("no", answer) == 0)
    {
        Add_new_elem(tree, now_node);
    }
}

void Go_next(struct Tree* tree, struct Node* now_node, int indicator)
{
    if(indicator == INSERT_LEFT)
    {
        now_node = now_node -> left;

        if(!(now_node -> left))
        {
            Cmp_with_answer(tree, now_node);
        }
    }
    else if(indicator == INSERT_RIGHT)
    {
        now_node = now_node -> right;

        if(!(now_node -> right))
        {
            Cmp_with_answer(tree, now_node);
        }
    }
}



void Guessing(struct Tree* tree)
{
    struct Node* now_node = tree -> root;
    char answer[STR_SIZE] = "";

    while (true)
    {
        printf("\nIs it %s ?\n", now_node -> val);
        scanf("%s", answer);

        if (strcasecmp("yes", answer) == 0)
        {
            now_node = now_node -> left;
            //Stack_Push(stk, YES, canary)

            if(!(now_node -> left))
            {
                Cmp_with_answer(tree, now_node);

                break;
            }
        }
        else if (strcasecmp("no", answer) == 0)
        {
            now_node = now_node -> right;

            if(!(now_node -> right))
            {
                Cmp_with_answer(tree, now_node);

                break;
            }
        }
        else
        {
            printf("Incorrect input! You can answer only \"yes\" or \"no\"!");
        }
    }
}

void Print_Definition(struct Tree* tree)
{

}

#include "lib.h"
#include "work_with_file.h"
#include "tree_functions.h"
#include "operating_mode.h"

#include "/Users/dima/MIPT/Stack/stack.h"
//#include "stack.h"


void Choose_Operating_Mode(struct Tree* tree, struct Stack* stk, struct Canary* canary, struct ERRORS* ERR)
{
    char answer[STR_SIZE] = "";

    printf("\nWhich mode do you want to use ? (Guessing or Definition or Differenses)\n");
    scanf("%s", answer);
    //printf("\n<%s>\n", answer);

    if (strcasecmp("guessing", answer) == 0)
    {
        printf("\n\033[32mStart guessing!!!\033[0m\n\n");
        Guessing(tree, stk, canary);
    }
    else if (strcasecmp("definition", answer) == 0)
    {
        printf("\n\033[32mStart definition!!!\033[0m\n\n");
        Definition(tree, stk, canary);
    }
    else if (strcasecmp("differenses", answer) == 0)
    {
        printf("\n\033[32mStart differenses!!!\033[0m\n\n");
        Differenses(tree, canary, ERR);
    }
    else
    {
        printf("\n\033[31mUncorrect input try again!!!\n\033[0m");
        Choose_Operating_Mode(tree, stk, canary, ERR);
    }
}



void Add_new_elem(struct Tree* tree, struct Node* now_node)
{
    char answer[STR_SIZE] = "";

    Set_new_value(tree, now_node, answer);

    Set_difference(now_node, answer);

    Reload_tree(tree);

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
    else
    {
        printf("\n\033[31mUncorrect input !!! you can answer only \"yes\" or \"no\"!\n\033[0m");
        Cmp_with_answer(tree, now_node);
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

void Guessing(struct Tree* tree, struct Stack* stk, struct Canary* canary)
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
            //Stack_Push(stk, YES, canary);
            //STACK_DUMP(stk, canary)

            if(!(now_node -> left))
            {
                Cmp_with_answer(tree, now_node);

                break;
            }
        }
        else if (strcasecmp("no", answer) == 0)
        {
            now_node = now_node -> right;
            //Stack_Push(stk, NO, canary);
            //STACK_DUMP(stk, canary)

            if(!(now_node -> right))
            {
                Cmp_with_answer(tree, now_node);

                break;
            }
        }
        else
        {
            printf("\n\033[31mIncorrect input! You can answer only \"yes\" or \"no\"!\033[0m");
        }
    }
}





/*
Elem_t* Convert_Stack_to_buf(struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val = 0;
    Elem_t* buf_ans = (Elem_t*) calloc(stk -> size + 1, sizeof(Elem_t));

    for (int i = stk -> size - 1; i >= 0; i--)
    {
        buf_ans[i] = Stack_Pop(stk, &Ret_val, canary);
        printf("pos: %d = %d\n", i, buf_ans[i]);
    }

    return buf_ans;
}
*/

void Print_Definition(struct Tree* tree, struct Stack* stk, struct Canary* canary)
{
    int size_stk = stk -> size;
    Elem_t ret_val = 0;

    struct Node* now_node = tree -> root;
    //Elem_t* buf_ans = (Elem_t*) calloc(stk -> size, sizeof(Elem_t));

    // buf_ans = Convert_Stack_to_buf(stk, canary);

    //printf("\nsize_stk = %d\n", size_stk);
    for(int i = 0; i < size_stk; i++)
    {
        //if(buf_ans[i] == YES)
        ret_val = Stack_Pop(stk, &ret_val, canary);

        if (ret_val == YES)
        {
            printf(" %s,", now_node -> val);
            now_node = now_node -> left;
        }
        //else if(buf_ans[i] == NO)
        if (ret_val == NO)
        {
            printf(" isn't %s,", now_node -> val);
            now_node = now_node -> right;
        }
    }
    printf("\n");
}

void Definition(struct Tree* tree, struct Stack* stk, struct Canary* canary)
{
    char answer[STR_SIZE] = "";

    printf("What/who do you want to find ?\n");
    scanf("%s", answer);

    Find_Answer(tree, tree -> root, answer, stk, canary);

    printf("\n\033[32mDefinition:\033[0m%s -", answer);
    Print_Definition(tree, stk, canary);


}

void Find_Way_to_Obj(struct Node* now_node, struct Stack* stk, struct Canary* canary)
{
    //struct Node* tmp_node = (struct Node*) calloc(1, sizeof(struct Node));
    assert(stk);
    assert(canary);
    assert(now_node);

    struct Node* tmp_node = NULL;

    while (now_node -> prev != NULL)
    {
        tmp_node = now_node;
        now_node = now_node -> prev;

        if (now_node -> left == tmp_node)
        {
            Stack_Push(stk, YES, canary);
            //STACK_DUMP(stk, canary)
            continue;
        }
        if (now_node -> right == tmp_node)
        {
            Stack_Push(stk, NO, canary);
            //STACK_DUMP(stk, canary)
            continue;
        }

        //STACK_DUMP(stk, canary)
    }
}

void Find_Answer(struct Tree* tree, struct Node* node, char* answer, struct Stack* stk, struct Canary* canary)
{
    //Elem_t Ret_val = 0;
    assert(stk);
    assert(canary);
    assert(node);


    if(node -> left == NULL)
    {
        if (strcasecmp(answer, node -> val) == 0)
        {
            //printf("%s ", answer);
            //Print_Definition(tree, stk, canary);
            Find_Way_to_Obj(node, stk, canary);
        }
        return;
    }

    //Stack_Push(stk, YES, canary);
    Find_Answer(tree, node -> left,  answer, stk, canary);
    //Stack_Pop(stk, &Ret_val, canary);

    if(node -> right == NULL && !(strcasecmp(answer, node -> val)))
    {
        //printf("%s ", answer);
        //Print_Definition(tree, stk, canary);
        Find_Way_to_Obj(node, stk, canary);

        return;
    }

    //Stack_Push(stk, NO, canary);
    Find_Answer(tree, node -> right, answer, stk, canary);
    //Stack_Pop(stk, &Ret_val, canary);
    return;
}





void Differenses(struct Tree* tree, struct Canary* canary, struct ERRORS* ERR)
{
    int capacity = 1;

    struct Stack* first_stk  = Stack_Ctor (capacity, ERR, canary);
    struct Stack* second_stk = Stack_Ctor (capacity, ERR, canary);

    char first_obj[STR_SIZE] = "";
    char second_obj[STR_SIZE] = "";

    printf ("What/who do you want to compare ?\n");
    scanf ("%s %s", first_obj, second_obj);

    Find_Answer (tree, tree -> root, first_obj , first_stk , canary);
    Find_Answer (tree, tree -> root, second_obj, second_stk, canary);

    Cmp_two_Stk(tree, first_stk, second_stk, first_obj, second_obj, canary);

    Stack_Dtor (first_stk , canary);
    Stack_Dtor (second_stk, canary);


}

struct Node* Go_to_next_node(int ret_val, struct Node* now_node)
{
    if (ret_val == YES)
    {
        printf(" %s,", now_node -> val);
        now_node = now_node -> left;
    }
    if (ret_val == NO)
    {
        printf(" isn't %s,", now_node -> val);
        now_node = now_node -> right;
    }
    return now_node;
}

void Cmp_two_Stk(struct Tree* tree, struct Stack* first_stk, struct Stack* second_stk, char* first_ans, char* second_ans, struct Canary* canary)
{
    assert(first_stk);
    assert(second_stk);

    //int stk_size = MIN(first_stk -> size, second_stk -> size);
    struct Node* now_node = tree -> root;
    //Elem_t first_val  = 0;
    //Elem_t second_val = 0;

    Elem_t first_val  = Stack_Pop(first_stk, &first_val, canary);
    Elem_t second_val = Stack_Pop(second_stk, &second_val, canary);
    printf("\033[35m%s and %s \033[0m:", first_ans, second_ans);


    while (first_val == second_val && first_stk -> size > 0 && second_stk -> size > 0)
    {
        now_node = Go_to_next_node(first_val, now_node);

        Stack_Pop(first_stk, &first_val, canary);
        Stack_Pop(second_stk, &second_val, canary);

    }

    if(first_stk -> size != 0)
    {
        printf(" but %s", first_ans);
    }
    struct Node* first_dif = now_node;

    while (first_stk -> size > 0)
    {
        now_node = Go_to_next_node(first_val, now_node);

        Stack_Pop(first_stk, &first_val, canary);
    }

    now_node = first_dif;
    if (second_stk -> size != 0)
    {
        printf(" but %s", second_ans);
    }

    while (second_stk -> size > 0)
    {
        now_node = Go_to_next_node(second_val, now_node);

        Stack_Pop(second_stk, &second_val, canary);
    }
}

#ifndef USED_OP_MODE
#define USED_OP_MODE

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void Guessing(struct Tree* tree, struct Stack* stk, struct Canary* canary);
void Cmp_with_answer(struct Tree* tree, struct Node* now_node);
void Add_new_elem(struct Tree* tree, struct Node* now_node);
void Go_next(struct Tree* tree, struct Node* now_node, int indicator);
void Set_difference(struct Node* now_node, char* answer);
void Set_new_value(struct Tree* tree, struct Node* node, char* answer);
void Choose_Operating_Mode(struct Tree* tree, struct Stack* stk, struct Canary* canary, struct ERRORS* ERR);
void Find_Answer(struct Tree* tree, struct Node* node, char* answer, struct Stack* stk, struct Canary* canary);
void Definition(struct Tree* tree, struct Stack* stk, struct Canary* canary);
void Differenses(struct Tree* tree, struct Canary* canary, struct ERRORS* ERR);
struct Node* Go_to_next_node(int ret_val, struct Node* now_node);
void Cmp_two_Stk(struct Tree* tree, struct Stack* first_stk, struct Stack* second_stk, char* first_ans, char* second_ans, struct Canary* canary);

const int YES = 1;
const int NO  = 0;

#endif

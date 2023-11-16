void Guessing(struct Tree* tree);
void Cmp_with_answer(struct Tree* tree, struct Node* now_node);
void Add_new_elem(struct Tree* tree, struct Node* now_node);
void Go_next(struct Tree* tree, struct Node* now_node, int indicator);
void Set_difference(struct Node* now_node, char* answer);
void Set_new_value(struct Tree* tree, struct Node* node, char* answer);


const int YES = 1;
const int NO  = 0;

#ifndef USED_TREE_FUNC
#define USED_TREE_FUNC

struct Tree* Tree_Ctor();
void Tree_Dtor(struct Tree* tree);
void Tree_Dump(struct Tree* tree);
struct Node* Create_Node(Tree_t new_val);
struct Node* Insert(struct Tree* tree, Tree_t new_val);
void Print_Pre_Order(struct Node* node);
void Print_In_Order(struct Node* node);
void Print_Post_Order(struct Node* node);
void Tree_Dtor(struct Tree* tree);
void Delite_Sub_Tree(struct Node* del_node);
struct Node* Insert_to_Pointer(struct Tree* tree, Tree_t val, struct Node* now_node, int indicator);
void Clean_buf();

#endif

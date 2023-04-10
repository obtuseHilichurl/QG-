typedef struct binary_tree_node
{
	int value;
	struct binary_tree_node* left;
	struct binary_tree_node* right;
}N;

typedef struct binary_tree
{
	N* ancestor;
	int count;
}T;

void menu();  // 输出菜单
void init_binary_tree(T* tree);  // 初始化二叉树
int insert_tree(N* node, int value);
N* find_tree(N* node, int value);
N* find_front(N* p);
N* find_post(N* p);
N* find_dad(N* p0, N* pt);
void delete_tree(T* tree, int value);
void level_traversal(T* tree);
void preorder_traversal_re(N* node);
void inorder_traversal_re(N* node);
void postorder_traversal_re(N* node);
void preorder_traversal(T* tree);
void inorder_traversal(T* tree);
void postorder_traversal(T* tree);


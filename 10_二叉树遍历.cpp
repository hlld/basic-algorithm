#include <cstdio>
#include <vector>

using namespace std;

struct tree_node {
    int val;
    struct tree_node *left;
    struct tree_node *right;
};

tree_node* create_tree_node(int val)
{
    tree_node* node = new tree_node;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroy_tree_node(tree_node** node)
{
    if (node == NULL || *node == NULL) {
        return;
    }
    tree_node* p = *node;
    destroy_tree_node(&p->left);
    destroy_tree_node(&p->right);
    delete p;
    *node = NULL;
}

void insert_tree_node(tree_node* pos, tree_node* node, int into_left)
{
    if (pos == NULL || node == NULL || pos == node) {
        return;
    }
    if (into_left == 1) {
        if (pos->left != NULL) {
            destroy_tree_node(&pos->left);
        }
        pos->left = node;
    }
    else {
        if (pos->right != NULL) {
            destroy_tree_node(&pos->right);
        }
        pos->right = node;
    }
}

void traverse_tree_node(tree_node* node, vector<int>& res, int order) {
    if (node != NULL) {
        // 先序遍历（先根节点，后左节点，再右节点）
        if (order == 0) {
            res.push_back(node->val);
        }
        traverse_tree_node(node->left, res, order);
        // 中序遍历（先左节点，后根节点，再右节点）
        if (order == 1) {
            res.push_back(node->val);
        }
        traverse_tree_node(node->right, res, order);
        // 后序遍历（先左节点，后右节点，再根节点）
        if (order == 2) {
            res.push_back(node->val);
        }
    }
}

void print_result(vector<int>& vc)
{
    for (int k = 0; k < vc.size(); k++) {
        printf("%d ", vc[k]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    tree_node* root = create_tree_node(0);
    insert_tree_node(root, create_tree_node(1), 1);
    insert_tree_node(root, create_tree_node(2), 0);
    insert_tree_node(root->left, create_tree_node(3), 1);
    insert_tree_node(root->right, create_tree_node(4), 1);
    vector<vector<int>> res(3);
    traverse_tree_node(root, res[0], 0);
    traverse_tree_node(root, res[1], 1);
    traverse_tree_node(root, res[2], 2);
    print_result(res[0]);
    print_result(res[1]);
    print_result(res[2]);
    destroy_tree_node(&root);
    return 0;
}
